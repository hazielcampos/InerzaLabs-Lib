#include "Motor.h"

Motor::Motor(char channel, bool invertDirection) {
    _channel = channel;
    _direction = invertDirection ? -1 : 1;
    _rawSpeed = 0;

    if (_channel == 'A') {
        _pwmA = AIN1;
        _pwmB = AIN2;
    } else if (_channel == 'B') {
        _pwmA = BIN1;
        _pwmB = BIN2;
    } else if (_channel == 'C') {
        _pwmA = CIN1;
        _pwmB = CIN2;
    } else if (_channel == 'D') {
        _pwmA = DIN1;
        _pwmB = DIN2;
    }

    ledcAttach(_pwmA, FREQ, RESOLUTION);
    ledcAttach(_pwmB, FREQ, RESOLUTION);
    stop();
}

void Motor::setSpeed(int speed) {
    _rawSpeed = constrain(speed, -100, 100);
    int effectiveSpeed = _rawSpeed * _direction;
    int v = map(abs(effectiveSpeed), 0, 100, 0, MAX_PWM);

    if(effectiveSpeed >= 0 ) {
        ledcWrite(_pwmA, v);
        ledcWrite(_pwmB, 0);
    } else {
        ledcWrite(_pwmA, 0);
        ledcWrite(_pwmB, v);
    }
}
void Motor::invertDirection(bool invert) {
    _direction = invert ? -1 : 1;
    setSpeed(_rawSpeed);
}
void Motor::stop() {
    _rawSpeed = 0;
    ledcWrite(_pwmA, 0);
    ledcWrite(_pwmB, 0);
}
void Motor::activeStop() {
    _rawSpeed = 0;
    ledcWrite(_pwmA, MAX_PWM);
    ledcWrite(_pwmB, MAX_PWM);
}