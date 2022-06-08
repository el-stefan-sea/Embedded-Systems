#include "dibse.h"

void DibsE::setup()
{
    rbgLed.begin();
    displayMatrix.clear();
}

void DibsE::loop()
{
    if (this->iterationCounter >= this->duration)
    {
        if (this->isBlinking)
        {
            if (this->ledIsOn)
            {
                this->rbgLed.setPixelColor(0, 0, 0, 0);
                this->ledIsOn = false;
            }
            else
            {
                this->rbgLed.setPixelColor(0, red, green, blue);
                this->ledIsOn = true;
            }
            this->rbgLed.show();
            this->iterationCounter = 0;
        }
    }
    this->iterationCounter += 1;

    this->displayMatrix.update();
}

void DibsE::simpleBlinkOn(int duration, int red, int green, int blue)
{
    this->duration = duration;
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->isBlinking = true;
    this->ledIsOn = true;
}

void DibsE::simpleBlinkOff()
{
    this->isBlinking = false;
}

void DibsE::displayDistance(int distance)
{
    byte critical = B11111111;
    byte semiCritical = B11111110;
    byte dangerous = B11111100;
    byte semiDangerous = B11111000;
    byte close = B11110000;
    byte semiClose = B11100000;
    byte tolerable = B11000000;
    byte semiSafe = B10000000;
    byte safe = B00000000;

    // Move older distance-indications to the right
    for (int i = 7; i > 0; i--)
    {
        this->ledDisplayMatrixBuffer[i] = this->ledDisplayMatrixBuffer[i - 1];
    }

    // Depending on distance - set indications in Row 1
    if (distance <= 3)
    {
        this->ledDisplayMatrixBuffer[0] = critical;
    }
    else if (distance > 3 && distance <= 4)
    {
        this->ledDisplayMatrixBuffer[0] = semiCritical;
    }
    else if (distance > 4 && distance <= 6)
    {
        this->ledDisplayMatrixBuffer[0] = dangerous;
    }
    else if (distance > 6 && distance <= 9)
    {
        this->ledDisplayMatrixBuffer[0] = semiDangerous;
    }
    else if (distance > 9 && distance <= 12)
    {
        this->ledDisplayMatrixBuffer[0] = close;
    }
    else if (distance > 12 && distance <= 18)
    {
        this->ledDisplayMatrixBuffer[0] = semiClose;
    }
    else if (distance > 18 && distance <= 24)
    {
        this->ledDisplayMatrixBuffer[0] = tolerable;
    }
    else if (distance > 24 && distance <= 36)
    {
        this->ledDisplayMatrixBuffer[0] = semiSafe;
    }
    else if (distance > 36)
    {
        this->ledDisplayMatrixBuffer[0] = safe;
    }
}

void DibsE::outputLEDMatrixDisplay(int distance)
{
    uint32_t timeInMilliSeconds = millis();
    if(timeInMilliSeconds - this->timeSinceStart >= 3000)
    {
        this->timeSinceStart = timeInMilliSeconds;
        this->displayDistance(distance);
        byte* displayBuffer = this->ledDisplayMatrixBuffer;
        for(int i = 0; i < 8; i++)
        {
            this->displayMatrix.drawColumn(i, displayBuffer[i]);
        }
    }
}