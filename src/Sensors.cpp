#include "Sensors.h"

Ultrasonic::Ultrasonic(int trigger, int echo) {
    _triggerPin = trigger;
    _echoPin = echo;
};

void Ultrasonic::init() {
    pinMode(_triggerPin, OUTPUT);
    pinMode(_echoPin, INPUT);
};
void Ultrasonic::update() {
    digitalWrite(_triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_triggerPin, LOW);

    _duration = pulseIn(_echoPin, HIGH);
    _distance = (_duration * 0.0343) / 2;
};

float Ultrasonic::getDistance() {
    return _distance;
};