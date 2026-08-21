#include "Sensors.h"

Ultrasonic::Ultrasonic(int trigger, int echo) {
    _triggerPin = trigger;
    _echoPin = echo;
    pinMode(_triggerPin, OUTPUT);
    pinMode(_echoPin, INPUT);
};

float Ultrasonic::getDistance() {
    digitalWrite(_triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_triggerPin, LOW);

    _duration = pulseIn(_echoPin, HIGH);
    _distance = (_duration * 0.0343) / 2;
    return _distance;
};