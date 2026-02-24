#include "main.h"

extern int color;

//DRIVE MOTORS
extern pros::MotorGroup allDriveMotorGroup;
extern pros::MotorGroup leftDriveMotorGroup;
extern pros::MotorGroup rightDriveMotorGroup;

//INTAKE MOTOR
extern pros::Motor intakeMotor;

//LEVER MOTOR
extern pros::Motor leverMotor;

//ODOMETRY
extern pros::Imu inertialSensor;
extern pros::Distance distanceSensor;
extern pros::Rotation horizontalRotationSensor;
extern pros::Rotation verticalRotationSensor;

//PNEUMATICS
extern pros::adi::DigitalOut descorePneumatic;
extern pros::adi::DigitalOut leverPneumatic;
extern pros::adi::DigitalOut matchLoadPneumatic;

//CONTROLLER
extern pros::Controller controller;