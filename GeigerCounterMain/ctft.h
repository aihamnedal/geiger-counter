#pragma once

#include <Wire.h>
#include "MLX90640_API.h"
#include "MLX90640_I2C_Driver.h"
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"
#include "logo.h"

// These are 'flexible' lines that can be changed
#define TFT_CS 2
#define TFT_DC 27
#define TFT_RST 25 // RST can be set to -1 if you tie it to Arduino's reset
#define MOSI 23
#define SCK 22
#define MISO 19

#define TFT_LED  27
#define TA_SHIFT 8 //Default shift for MLX90640 in open air
const byte MLX90640_address = 0x33; //Default 7-bit unshifted address of the MLX90640

struct RectangleArea {
  int xPos;
  int yPos;
  int xWidth;
  int yWidth;
};

int getTextWidth(Adafruit_HX8357 & screen, String text, int size)
{
  screen.setCursor(0, 0);
  screen.setTextSize(size);
  int16_t xPos, yPos;
  uint16_t xWidth, yWidth;
  screen.getTextBounds(text, 0, 0, &xPos, &yPos, &xWidth, &yWidth);
  return xWidth;
}

int getTextHeight(Adafruit_HX8357 & screen, String text, int size)
{
  screen.setCursor(0, 0);
  screen.setTextSize(size);
  int16_t xPos, yPos;
  uint16_t xWidth, yWidth;
  screen.getTextBounds(text, 0, 0, &xPos, &yPos, &xWidth, &yWidth);
  return yWidth;
}

RectangleArea drawText(Adafruit_HX8357 & screen, int x, int y, int size, String text, uint16_t color)
{
  screen.setCursor(x, y);
  screen.setTextColor(color);
  screen.setTextSize(size);
  screen.println(text);

  int16_t xPos, yPos;
  uint16_t xWidth, yWidth;
  screen.getTextBounds(text, x, y, &xPos, &yPos, &xWidth, &yWidth);
  return {
    .xPos = xPos,
    .yPos = yPos,
    .xWidth = xWidth,
    .yWidth = yWidth,
  };
}

void drawLogo(Adafruit_HX8357 & screen, int x, int y) {
  screen.drawXBitmap(x, y, logo_bits, logo_width, logo_height, HX8357_YELLOW);
}

void drawRectangle(Adafruit_HX8357 & screen, int x, int y, int w, int h, uint16_t color) {
  screen.drawRect(x, y, w, h, color);
}

void drawRectangleFill(Adafruit_HX8357 & screen, int x, int y, int w, int h, uint16_t color) {
  screen.fillRect(x, y, w, h, color);
}

void fillScreen(Adafruit_HX8357 & screen, uint16_t color) {
  screen.fillScreen(color);
}

void setupScreen(Adafruit_HX8357 & screen) {
  screen.begin();
  Serial.println("Initialized.");
  screen.fillScreen(HX8357_BLACK);
}

void getColourT(int j, int & R_colour, int & G_colour, int & B_colour)
   {
    if (j >= 0 && j < 30)
       {
        R_colour = 0;
        G_colour = 0;
        B_colour = 20 + (120.0/30.0) * j;
       }
    
    if (j >= 30 && j < 60)
       {
        R_colour = (120.0 / 30) * (j - 30.0);
        G_colour = 0;
        B_colour = 140 - (60.0/30.0) * (j - 30.0);
       }

    if (j >= 60 && j < 90)
       {
        R_colour = 120 + (135.0/30.0) * (j - 60.0);
        G_colour = 0;
        B_colour = 80 - (70.0/30.0) * (j - 60.0);
       }

    if (j >= 90 && j < 120)
       {
        R_colour = 255;
        G_colour = 0 + (60.0/30.0) * (j - 90.0);
        B_colour = 10 - (10.0/30.0) * (j - 90.0);
       }

    if (j >= 120 && j < 150)
       {
        R_colour = 255;
        G_colour = 60 + (175.0/30.0) * (j - 120.0);
        B_colour = 0;
       }

    if (j >= 150 && j <= 180)
       {
        R_colour = 255;
        G_colour = 235 + (20.0/30.0) * (j - 150.0);
        B_colour = 0 + 255.0/30.0 * (j - 150.0);
       }

   }

//Returns true if the MLX90640 is detected on the I2C bus
bool isThermalConnected()
{
  Wire.beginTransmission((uint8_t)MLX90640_address);

  if (Wire.endTransmission() != 0)
      return (false); //Sensor did not ACK
  return (true);
}   

void setupThermal(Adafruit_HX8357 & screen, paramsMLX90640 & mlx90640, int & i, int & j, int & R_colour, int & G_colour, int & B_colour) {
  Wire.begin();
  Wire.setClock(400000); //Increase I2C clock speed to 400kHz

  while (!Serial); //Wait for user to open terminal

  Serial.println("MLX90640 IR Array Example");

  if (isThermalConnected() == false)
      {
      Serial.println("MLX90640 not detected at default I2C address. Please check wiring. Freezing.");
      while (1);
      }
      
  Serial.println("MLX90640 online!");

  //Get device parameters - We only have to do this once
  int status;
  uint16_t eeMLX90640[832];
  
  status = MLX90640_DumpEE(MLX90640_address, eeMLX90640);

  if (status != 0)
      Serial.println("Failed to load system parameters");

  status = MLX90640_ExtractParameters(eeMLX90640, &mlx90640);

  if (status != 0)
      {
      Serial.println("Parameter extraction failed");
      Serial.print(" status = ");
      Serial.println(status);
      }

  //Once params are extracted, we can release eeMLX90640 array

  MLX90640_I2CWrite(0x33, 0x800D, 6401);    // writes the value 1901 (HEX) = 6401 (DEC) in the register at position 0x800D to enable reading out the temperatures!!!
  // ===============================================================================================================================================================

  //MLX90640_SetRefreshRate(MLX90640_address, 0x00); //Set rate to 0.25Hz effective - Works
  //MLX90640_SetRefreshRate(MLX90640_address, 0x01); //Set rate to 0.5Hz effective - Works
  //MLX90640_SetRefreshRate(MLX90640_address, 0x02); //Set rate to 1Hz effective - Works
  //MLX90640_SetRefreshRate(MLX90640_address, 0x03); //Set rate to 2Hz effective - Works
  MLX90640_SetRefreshRate(MLX90640_address, 0x04); //Set rate to 4Hz effective - Works
  //MLX90640_SetRefreshRate(MLX90640_address, 0x05); //Set rate to 8Hz effective - Works at 800kHz
  //MLX90640_SetRefreshRate(MLX90640_address, 0x06); //Set rate to 16Hz effective - Works at 800kHz
  //MLX90640_SetRefreshRate(MLX90640_address, 0x07); //Set rate to 32Hz effective - fails

      
  pinMode(TFT_LED, OUTPUT);
  digitalWrite(TFT_LED, HIGH);

  screen.begin();

  screen.setRotation(1);

  screen.fillScreen(HX8357_BLACK);
  screen.fillRect(0, 0, 319, 13, screen.color565(255, 0, 10));
  screen.setCursor(100, 3);
  screen.setTextSize(1);
  screen.setTextColor(HX8357_YELLOW, screen.color565(255, 0, 10));
  screen.print("Thermographie - stoppi");    

  screen.drawLine(250, 210 - 0, 258, 210 - 0, screen.color565(255, 255, 255));
  screen.drawLine(250, 210 - 30, 258, 210 - 30, screen.color565(255, 255, 255));
  screen.drawLine(250, 210 - 60, 258, 210 - 60, screen.color565(255, 255, 255));
  screen.drawLine(250, 210 - 90, 258, 210 - 90, screen.color565(255, 255, 255));
  screen.drawLine(250, 210 - 120, 258, 210 - 120, screen.color565(255, 255, 255));
  screen.drawLine(250, 210 - 150, 258, 210 - 150, screen.color565(255, 255, 255));
  screen.drawLine(250, 210 - 180, 258, 210 - 180, screen.color565(255, 255, 255));

  screen.setCursor(80, 220);
  screen.setTextColor(HX8357_WHITE, screen.color565(0, 0, 0));
  screen.print("T+ = ");    


  // drawing the colour-scale
  // ========================

  for (i = 0; i < 181; i++)
  {
  //value = random(180);
    getColourT(i, R_colour, G_colour, B_colour);
    screen.drawLine(240, 210 - i, 250, 210 - i, screen.color565(R_colour, G_colour, B_colour));
  } 

}

void loopThermal(Adafruit_HX8357 & screen, float (&mlx90640To)[768], paramsMLX90640 & mlx90640, int & i, int & j, int & R_colour, int & G_colour, int & B_colour, float & T_max, float & T_min, float & T_center)
   {
    for (byte x = 0 ; x < 2 ; x++) //Read both subpages
       {
        uint16_t mlx90640Frame[834];
        int status = MLX90640_GetFrameData(MLX90640_address, mlx90640Frame);
    
        if (status < 0)
           {
            Serial.print("GetFrame Error: ");
            Serial.println(status);
           }

        float vdd = MLX90640_GetVdd(mlx90640Frame, &mlx90640);
        float Ta = MLX90640_GetTa(mlx90640Frame, &mlx90640);

        float tr = Ta - TA_SHIFT; //Reflected temperature based on the sensor ambient temperature
        float emissivity = 0.95;

        MLX90640_CalculateTo(mlx90640Frame, &mlx90640, emissivity, tr, mlx90640To);
       }

       
    // determine T_min and T_max and eliminate error pixels
    // ====================================================

    mlx90640To[1*32 + 21] = 0.5 * (mlx90640To[1*32 + 20] + mlx90640To[1*32 + 22]);    // eliminate the error-pixels
    mlx90640To[4*32 + 30] = 0.5 * (mlx90640To[4*32 + 29] + mlx90640To[4*32 + 31]);    // eliminate the error-pixels
    
    T_min = mlx90640To[0];
    T_max = mlx90640To[0];

    for (i = 1; i < 768; i++)
       {
        if((mlx90640To[i] > -41) && (mlx90640To[i] < 301))
           {
            if(mlx90640To[i] < T_min)
               {
                T_min = mlx90640To[i];
               }

            if(mlx90640To[i] > T_max)
               {
                T_max = mlx90640To[i];
               }
           }
        else if(i > 0)   // temperature out of range
           {
            mlx90640To[i] = mlx90640To[i-1];
           }
        else
           {
            mlx90640To[i] = mlx90640To[i+1];
           }
       }


    // determine T_center
    // ==================

    T_center = mlx90640To[11* 32 + 15];    

    // drawing the picture
    // ===================

    for (i = 0 ; i < 24 ; i++)
       {
        for (j = 0; j < 32; j++)
           {
            mlx90640To[i*32 + j] = 180.0 * (mlx90640To[i*32 + j] - T_min) / (T_max - T_min);
                       
            getColourT(mlx90640To[i*32 + j], R_colour, G_colour, B_colour);
            
            screen.fillRect(217 - j * 7, 35 + i * 7, 7, 7, screen.color565(R_colour, G_colour, B_colour));
           }
       }
    
    screen.drawLine(217 - 15*7 + 3.5 - 5, 11*7 + 35 + 3.5, 217 - 15*7 + 3.5 + 5, 11*7 + 35 + 3.5, screen.color565(255, 255, 255));
    screen.drawLine(217 - 15*7 + 3.5, 11*7 + 35 + 3.5 - 5, 217 - 15*7 + 3.5, 11*7 + 35 + 3.5 + 5,  screen.color565(255, 255, 255));
 
    screen.fillRect(260, 25, 37, 10, screen.color565(0, 0, 0));
    screen.fillRect(260, 205, 37, 10, screen.color565(0, 0, 0));    
    screen.fillRect(115, 220, 37, 10, screen.color565(0, 0, 0));    

    screen.setTextColor(HX8357_WHITE, screen.color565(0, 0, 0));
    screen.setCursor(265, 25);
    screen.print(T_max, 1);
    screen.setCursor(265, 205);
    screen.print(T_min, 1);
    screen.setCursor(120, 220);
    screen.print(T_center, 1);

    screen.setCursor(300, 25);
    screen.print("C");
    screen.setCursor(300, 205);
    screen.print("C");
    screen.setCursor(155, 220);
    screen.print("C");
    
    delay(20);
   }

   
   
   

