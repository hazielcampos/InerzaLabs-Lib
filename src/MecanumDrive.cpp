#include "MecanumDrive.h"

MecanumDrive::MecanumDrive(Motor& frontLeftMotor, Motor& frontRightMotor, Motor& rearLeftMotor, Motor& rearRightMotor)
    : _frontLeftMotor(frontLeftMotor), _frontRightMotor(frontRightMotor), _rearLeftMotor(rearLeftMotor), _rearRightMotor(rearRightMotor) {}

void MecanumDrive::drive(int xSpeed, int ySpeed, int zRotation) {
    int frontLeftSpeed = ySpeed + xSpeed + zRotation;
    int frontRightSpeed = ySpeed - xSpeed - zRotation;
    int rearLeftSpeed = ySpeed - xSpeed + zRotation;
    int rearRightSpeed = ySpeed + xSpeed - zRotation;
    _frontLeftMotor.setSpeed(frontLeftSpeed);
    _frontRightMotor.setSpeed(frontRightSpeed);
    _rearLeftMotor.setSpeed(rearLeftSpeed);
    _rearRightMotor.setSpeed(rearRightSpeed);
}

void MecanumDrive::stop() {
    _frontLeftMotor.stop();
    _frontRightMotor.stop();
    _rearLeftMotor.stop();
    _rearRightMotor.stop();
}

void MecanumDrive::update() {
    _frontLeftMotor.update();
    _frontRightMotor.update();
    _rearLeftMotor.update();
    _rearRightMotor.update();
}