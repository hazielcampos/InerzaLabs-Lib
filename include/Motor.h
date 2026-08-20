#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

#define AIN1 15
#define AIN2 16

#define BIN1 18
#define BIN2 17

#define CIN1 8
#define CIN2 3

#define DIN1 10
#define DIN2 9
#define FREQ 5000
#define RESOLUTION 8
#define MAX_PWM 255


class Motor {
    private:
        char _channel;
        int8_t _direction: 2;
        int _rawSpeed;
        int _pwmA;
        int _pwmB;

    public:
        Motor(char channel, bool invertDirection = false);
        void setSpeed(int speed);
        void invertDirection(bool direction);
        void stop();
        void activeStop();
};

#endif