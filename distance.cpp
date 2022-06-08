#include "distance.h"

void DistanceSensor::begin()
{
    pinMode(this->triggerPin, OUTPUT);
    pinMode(this->echoPin, INPUT);
}

void DistanceSensor::update()
{
    this->getDistanceInCM(true);
}

uint16_t DistanceSensor::getDistanceInCM(bool immediate)
{
    if(immediate)
    {
        this->echoDuration = this->readEchoDuration();
        this->distanceCM = calculateDistanceInCM(this->echoDuration);
        return this->distanceCM;
    }
    else
    {
        return this->distanceCM;
    }
    
}

uint16_t DistanceSensor::calculateDistanceInCM(uint16_t duration)
{
    // (duration * 10 / 291) / 2 is a better approximation
    // than (duration / 29) / 2 (duration * 0.0343 cm/uS)
    return (duration * 5 / 291);
}

uint16_t DistanceSensor::readEchoDuration()
{
    //Trigger LOW pulse to ensure a clean HIGH Pulse
    digitalWrite(this->triggerPin, LOW);
    delayMicroseconds(5);
    // Trigger sensor with HIGH Pulse of 10 or more uS
    digitalWrite(this->triggerPin, HIGH);
    delayMicroseconds(10);
    // set Pin to LOW and wait for Echo
    digitalWrite(this->triggerPin, LOW);
    
    pinMode(this->echoPin, INPUT);
    this->echoDuration = pulseIn(this->echoPin, HIGH);
    return this->echoDuration;
}