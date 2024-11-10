#pragma once

// Libraries
#include <dummy.h>
#include <ESP32Ping.h>
#include <Ticker.h>
#include <WiFi.h>
#include <SPI.h>
// Custom files
#include "cwifi.h"
#include "ctft.h"

// SoftSPI - note that on some processors this might be *faster* than hardware SPI!
Adafruit_HX8357 screen = Adafruit_HX8357(TFT_CS, TFT_DC, MOSI, SCK, TFT_RST, MISO);

// Thermal
static float mlx90640To[768];
paramsMLX90640 mlx90640;
int R_colour, G_colour, B_colour;
int i, j;
float T_max, T_min;
float T_center;

// WiFi
NetworkServer server(80); // Network server

// Geiger counter
Ticker cpsTicker;
volatile int pulseCount = 0;
int cps = 0;
unsigned long previousMillis = 0;
const long interval = 1000;  // 1 second interval for CPS calculation

#define pulsePin 12

unsigned long timeSinceBoot;

void countPulses()
{
  cps = pulseCount;  // Get pulse count from previous interval
  pulseCount = 0;    // Reset pulse count for next interval

  Serial.print("CPM: ");
  Serial.println(CPM(cps));
}

float pulseMV(int ADC_value)
{
  float factor = 3300.0 / 4095.0;  // Conversion factor for 3.3V on a 12-bit ADC
  return ADC_value * factor;
}

int CPM(int CPS)
{
  return CPS * 60;
}

bool thresholdReached(float pulseVoltageMV)
{
  return pulseVoltageMV >= 499.0;  // Return true if pulse voltage exceeds 30 mV threshold
}

void setup() {
  Serial.begin(115200);

  setupWIFI(server);

  analogReadResolution(12);            // Set ADC resolution to 12 bits
  analogSetAttenuation(ADC_0db);       // Set ADC attenuation to 0dB for 0-1.1V range
  pinMode(pulsePin, INPUT);            // Ensure pin is set as input
  cpsTicker.attach(1, countPulses);   // Call countPulses every 30 seconds (or modify if needed)

  setupScreen(screen);

  screen.setRotation(3);
  drawLogo(screen, screen.width()/2 - logo_width/2, screen.height()/2 - logo_height/2 - 15);
  screen.setRotation(3);
  auto ret = drawText(screen, screen.width()/2 - getTextWidth(screen, "Calibrating...", 3)/2, 5, 3, "Calibrating...", HX8357_WHITE);

  delay(2000);

  drawRectangleFill(screen, ret.xPos, ret.yPos, ret.xWidth, ret.yWidth, HX8357_BLACK);
  drawText(screen, screen.width()/2 - getTextWidth(screen, "Done!", 3)/2, 5, 3, "Done!", HX8357_WHITE);

  delay(1500);

  fillScreen(screen, HX8357_BLACK);
  drawText(screen, screen.width(), screen.height()/2, 3, "CPM: ", HX8357_WHITE);
  
 // setupThermal(screen, mlx90640, i, j, R_colour, G_colour, B_colour);
  
  timeSinceBoot = millis();
}

void loop() {
  int adcValue = getStableAnalogRead(pulsePin);    // Read ADC value
  float pulseVoltage = pulseMV(adcValue);          // Convert ADC value to mV
  
  // Print raw ADC value and pulse voltage for debugging
  // Serial.print("Raw ADC Value: ");
  // Serial.print(adcValue);
  // Serial.print("  Pulse Voltage: ");
  // Serial.println(pulseVoltage);

  if (thresholdReached(pulseVoltage) == true) {             // Check if threshold is reached
    pulseCount++;                                  // Increment pulse count
    delay(10);                                     // Small delay to avoid double-counting
  }
  
  //loopThermal(screen, mlx90640To, mlx90640, i, j, R_colour, G_colour, B_colour, T_max, T_min, T_center);
  
  if (millis() - timeSinceBoot > 1000) {
    int seconds = millis()/1000;
    //String secondsString = std::to_string(seconds);
   
    
    //auto ret = drawText(screen, cpmx - getTextWidth(screen, secondsString, 3)/2, cpmy, 3, secondsString, HX8357_WHITE);
   
    
    timeSinceBoot = millis();
  }
  
}

int getStableAnalogRead(int pin) {
  const int numReadings = 10;
  long sum = 0;
  for (int i = 0; i < numReadings; i++) {
    sum += analogRead(pin);
    delay(2);  // Small delay for each read to avoid ADC sampling errors
  }
  return sum / numReadings;  // Return the average ADC value
}
