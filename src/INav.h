#ifndef INAV_H
#define INAV_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_LSM6DSOX.h>
#include "Board.h"

class INav {
private:
    Adafruit_LSM6DSOX _lsm6ds;
    
    float _gyroZ_offset = 0.0;
    float _yaw = 0.0;
    float _roll = 0.0;
    float _pitch = 0.0;
    float _gyroZ_filtered = 0.0;
    bool _isStatic = false;
    
    unsigned long _lastTime = 0;
    
    static constexpr float ALPHA = 0.2f;

public:
    INav();
    
    bool begin(TwoWire &wirePort = Wire);
    void calibrate(uint16_t samples = 1000);
    void update();
    
    float getYaw() const { return _yaw; }
    float getRoll() const { return _roll; }
    float getPitch() const { return _pitch; }
    bool isStatic() const { return _isStatic; }
    
    void resetYaw() { _yaw = 0.0; }
};

#endif