#ifndef MECANUM_DRIVE_H
#define MECANUM_DRIVE_H

#include <Motor.h>

class MecanumDrive {
    private:
        Motor _frontLeftMotor;
        Motor _frontRightMotor;
        Motor _rearLeftMotor;
        Motor _rearRightMotor;

    public:
        MecanumDrive(Motor frontLeftMotor, Motor frontRightMotor, Motor rearLeftMotor, Motor rearRightMotor);
        void drive(int xSpeed, int ySpeed, int zRotation);
        void stop();
};

#endif