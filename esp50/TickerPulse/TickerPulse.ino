#include <Ticker.h>

#define pulsePin 12

Ticker cpsTicker;
volatile int pulseCount = 0;
int cps = 0;

unsigned long previousMillis = 0;
const long interval = 1000;  // 1 second interval for CPS calculation

void countPulses()
{
  cps = pulseCount;  // Get pulse count from previous interval
  pulseCount = 0;    // Reset pulse count for next interval

  // Print CPS value to Serial Monitor and Plotter
  // Serial.print("CPS: ");
  // Serial.println(cps);

  Serial.print("CPM: ");
  Serial.println(CPM(cps));
  // Serial.print("Voltage: ");
  // Serial.println(pulseMV(analogRead(pulsePin)));  // Print mV instead of raw ADC value
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
  analogReadResolution(12);            // Set ADC resolution to 12 bits
  analogSetAttenuation(ADC_0db);       // Set ADC attenuation to 0dB for 0-1.1V range
  pinMode(pulsePin, INPUT);            // Ensure pin is set as input
  cpsTicker.attach(1, countPulses);   // Call countPulses every 30 seconds (or modify if needed)
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
