#include "Motor.h"

Motor::Motor(char channel, bool invertDirection) {
    _channel = channel;
    _direction = invertDirection ? -1 : 1;
    _rawSpeed = 0;
    _currentSpeed = 0;
    _targetSpeed = 0;
    _lastRampTime = 0;
    _rampInterval = 2; // Puntos de aceleración cada 2ms (Ajustable)

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

// Cambia la velocidad objetivo, la rampa la procesará el update()
void Motor::setSpeed(int speed) {
    _targetSpeed = constrain(speed, -100, 100);
}

// Configura el tiempo de la rampa (por defecto 2ms por cada unidad de velocidad)
void Motor::setRampInterval(int ms) {
    _rampInterval = ms;
}

// Método no bloqueante: Debe llamarse constantemente en el loop()
void Motor::update() {
    if (_currentSpeed != _targetSpeed) {
        if (millis() - _lastRampTime >= _rampInterval) {
            _lastRampTime = millis();

            // Incrementa o decrementa gradualmente hacia la velocidad objetivo
            if (_currentSpeed < _targetSpeed) {
                _currentSpeed++;
            } else {
                _currentSpeed--;
            }

            applyPwm(_currentSpeed);
        }
    }
}

// Función auxiliar para aplicar el PWM a los pines
void Motor::applyPwm(int speed) {
    _rawSpeed = speed;
    int effectiveSpeed = _rawSpeed * _direction;
    int v = map(abs(effectiveSpeed), 0, 100, 0, MAX_PWM);

    if (effectiveSpeed >= 0) {
        ledcWrite(_pwmA, v);
        ledcWrite(_pwmB, 0);
    } else {
        ledcWrite(_pwmA, 0);
        ledcWrite(_pwmB, v);
    }
}

void Motor::invertDirection(bool invert) {
    _direction = invert ? -1 : 1;
    applyPwm(_currentSpeed);
}

void Motor::stop() {
    _targetSpeed = 0;
    _currentSpeed = 0;
    _rawSpeed = 0;
    ledcWrite(_pwmA, 0);
    ledcWrite(_pwmB, 0);
}

void Motor::activeStop() {
    _targetSpeed = 0;
    _currentSpeed = 0;
    _rawSpeed = 0;
    ledcWrite(_pwmA, MAX_PWM);
    ledcWrite(_pwmB, MAX_PWM);
}