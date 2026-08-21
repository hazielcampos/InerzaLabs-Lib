#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>

class Ultrasonic {
    private:
        int _triggerPin;
        int _echoPin;
        long _duration;
        float _distance;
    public:
        Ultrasonic(int trigger, int echo);
        float getDistance();
};

#endif