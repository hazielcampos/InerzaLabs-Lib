#include "INav.h"

INav::INav() {}

bool INav::begin(TwoWire &wirePort) {
    wirePort.begin(SDA_PIN, SCL_PIN);

    if (!_lsm6ds.begin_I2C(0x6B, &wirePort) && !_lsm6ds.begin_I2C(0x6A, &wirePort)) {
        return false;
    }

    _lsm6ds.setAccelRange(LSM6DS_ACCEL_RANGE_2_G);
    _lsm6ds.setGyroRange(LSM6DS_GYRO_RANGE_250_DPS);
    _lsm6ds.setAccelDataRate(LSM6DS_RATE_104_HZ);
    _lsm6ds.setGyroDataRate(LSM6DS_RATE_104_HZ);

    _lastTime = micros();
    return true;
}

void INav::calibrate(uint16_t samples) {
    Serial.println("⚠️ MANTÉN LA PCB INMÓVIL...");
    float sumZ = 0.0;
    for (uint16_t i = 0; i < samples; i++) {
        sensors_event_t accel, gyro, temp;
        _lsm6ds.getEvent(&accel, &gyro, &temp);
        sumZ += gyro.gyro.z * SENSORS_RADS_TO_DPS;
        delay(5);
    }
    _gyroZ_offset = sumZ / samples;
    _lastTime = micros();
    Serial.println("✅ Calibración completada.");
}

void INav::update() {
    sensors_event_t accel, gyro, temp;
    _lsm6ds.getEvent(&accel, &gyro, &temp);

    // 1. Delta time
    unsigned long currentTime = micros();
    float dt = (currentTime - _lastTime) / 1000000.0f;
    _lastTime = currentTime;

    // 2. Cálculos Acelerómetro (Roll y Pitch)
    _roll = atan2(accel.acceleration.y, accel.acceleration.z) * 180.0f / M_PI;
    _pitch = atan2(-accel.acceleration.x, 
                   sqrt(accel.acceleration.y * accel.acceleration.y + 
                        accel.acceleration.z * accel.acceleration.z)) * 180.0f / M_PI;

    // 3. Lectura y Filtro Gyro Z
    float rawGyroZ = (gyro.gyro.z * SENSORS_RADS_TO_DPS) - _gyroZ_offset;
    _gyroZ_filtered = (ALPHA * rawGyroZ) + ((1.0f - ALPHA) * _gyroZ_filtered);

    // 4. Detección de Inmovilidad
    float accelMag = sqrt(accel.acceleration.x * accel.acceleration.x +
                          accel.acceleration.y * accel.acceleration.y +
                          accel.acceleration.z * accel.acceleration.z);

    _isStatic = (abs(accelMag - 9.81f) < 0.25f) && (abs(_gyroZ_filtered) < 0.6f);

    float finalGyroZ = _gyroZ_filtered;

    if (_isStatic) {
        finalGyroZ = 0.0f;
        _gyroZ_offset += rawGyroZ * 0.001f; // Ajuste térmico continuo
    }

    // 5. Integración Yaw
    _yaw += finalGyroZ * dt;

    if (_yaw > 180.0f) _yaw -= 360.0f;
    if (_yaw < -180.0f) _yaw += 360.0f;
}