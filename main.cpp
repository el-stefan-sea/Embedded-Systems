#include <Arduino.h>
#include "dibse.h"
#include "distance.h"



DistanceSensor sonarSensor(8, 4);
DibsE dibseBot;


uint32_t timeStarted = 0;

void setup() {
  // put your setup code here, to run once:
  sonarSensor.begin();
  dibseBot.setup();
  dibseBot.simpleBlinkOn(1000, 255, 255, 255);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint32_t currentMillis = millis();
  if(currentMillis - timeStarted >= 1000)
  {
    timeStarted = currentMillis;

    sonarSensor.update();
    Serial.print(sonarSensor.getDistanceInCM());
    Serial.print("cm");
    
    if (sonarSensor.getDistanceInCM() <= 3)
    {
      dibseBot.simpleBlinkOn(4000, 255, 0, 0);
      Serial.println(" -- Distance Critical");
    }
    else if (sonarSensor.getDistanceInCM() <= 6)
    {
      dibseBot.simpleBlinkOn(8000, 255, 140, 0);
      Serial.println(" -- Distance Dangerous");
    }
    else if (sonarSensor.getDistanceInCM() <= 12)
    {
      dibseBot.simpleBlinkOn(16000, 255, 255, 0);
      Serial.println(" -- Distance Close");
    }
    else if (sonarSensor.getDistanceInCM() <= 24)
    {
      dibseBot.simpleBlinkOn(32000, 0, 255, 0);
      Serial.println(" -- Distance Tolerable");
    }
    else
    {
      dibseBot.simpleBlinkOn(64000, 0, 0, 255);
      Serial.println(" -- Distance Safe");
    }
  }
  dibseBot.outputLEDMatrixDisplay(sonarSensor.getDistanceInCM(false));
  dibseBot.loop();
}

// #include <Arduino.h>
// #include "LedMatrix.h"

// // LED Matrix pins
// #define LED_LATCH 11
// #define LED_DATA 16
// #define LED_CLOCK 15

// LedMatrix ledMatrix(LED_LATCH, LED_DATA, LED_CLOCK);

// void setup()
// {
// }

// void loop()
// {
//   // Clears the display buffer.
//   ledMatrix.clear();

//   // Draws an x into the display buffer.
//   for (uint8_t x = 0; x < 8; x++)
//   {
//     ledMatrix.drawPixel(x, x, true);
//     ledMatrix.drawPixel(x, 7 - x, true);
//   }

//   // Display everything on the display.
//   ledMatrix.update();
// }
