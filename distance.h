#ifndef DISTANCE_H
#define DISTANCE_H

#include <stdint.h>
#include <Arduino.h>


class DistanceSensor
{
    public:
    DistanceSensor(uint32_t trigPin, uint32_t sensorPin) : triggerPin(trigPin), echoPin(sensorPin) {}
    
    void begin();
    void update();

    uint16_t getDistanceInCM(bool immediate = false);
    uint16_t calculateDistanceInCM(uint16_t duration);
    uint16_t readEchoDuration();

    

    protected:
    uint32_t triggerPin;
    uint32_t echoPin;

    uint16_t distanceCM = 0;
    uint16_t echoDuration = 0;
};
#endif