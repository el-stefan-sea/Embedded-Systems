#ifndef DIBSE_H
#define DIBSE_H

#include <Arduino.h>
#include <stdint.h>
#include <Adafruit_NeoPixel.h>
#include "LedMatrix.h"

class DibsE
{
    public:
        DibsE() : displayMatrix(11, MOSI, SCK), rbgLed(1, A4, NEO_GRB + NEO_KHZ800) {}
        void setup();
        void loop();
        void simpleBlinkOn(int duration, int red, int green, int blue);
        void simpleBlinkOff();
        void displayDistance(int distance);
        void outputLEDMatrixDisplay(int distance);
        

    protected:
        LedMatrix displayMatrix;
        Adafruit_NeoPixel rbgLed;
        bool isBlinking = false;
        bool ledIsOn = false;
        uint32_t duration = 0;
        uint8_t red = 0;
        uint8_t green = 0;
        uint8_t blue = 0;
        uint32_t iterationCounter = 0;
        byte ledDisplayMatrixBuffer[8] = {};
        uint32_t timeSinceStart = 0;
};

#endif