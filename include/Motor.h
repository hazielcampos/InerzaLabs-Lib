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
    int _direction;
    int _rawSpeed;
    int _currentSpeed;        // Velocidad actual del motor
    int _targetSpeed;         // Velocidad deseada

    int _pwmA;
    int _pwmB;

    unsigned long _lastRampTime; // Para control de tiempo no bloqueante
    int _rampInterval;           // Tiempo en ms entre cada paso de la rampa

    void applyPwm(int speed);

  public:
    Motor(char channel, bool invertDirection);
    void setSpeed(int speed);         // Establece la velocidad objetivo
    void setRampInterval(int ms);     // Permite ajustar la suavidad de la rampa
    void update();                    // ¡OBLIGATORIO! Llamar en el loop()
    void invertDirection(bool invert);
    void stop();
    void activeStop();
};

#endif