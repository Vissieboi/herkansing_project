#ifndef PROX_H
#define PROX_H
#include <Wire.h>
#include <Zumo32U4.h>

class frontProxSensor : public Zumo32U4ProximitySensors{

    public:
    frontProxSensor();
    // void proxSetup();
    void proxStart();
    void stop();
    private:
    Zumo32U4Motors motors;
    Zumo32U4ProximitySensors proxSensors;
    Zumo32U4ButtonA buttonA;
    Zumo32U4ButtonB buttonB;
    
    const uint8_t sensorThreshold = 1;
    const uint16_t turnSpeedMax = 400;
    const uint16_t turnSpeedMin = 100;
    const uint16_t deceleration = 10;
    const uint16_t acceleration = 10;

    bool senseDir;
    bool turningLeft;
    bool turningRight;
    uint16_t turnSpeed;
    uint16_t lastTimeObjectSeen;

    void turnRight();
    void turnLeft();
    
};

#endif
