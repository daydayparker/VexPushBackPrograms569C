#include "main.h"

//ALLIANCE COLOR
extern int color;

//DRIVE MOTORS  
extern pros::MotorGroup leftDriveMotorGroup;
extern pros::MotorGroup rightDriveMotorGroup;
extern pros::MotorGroup driveMotorGroup;

//INTAKE MOTORS
extern pros::MotorGroup allIntakeMotorGroup;
extern pros::Motor switcherIntakeMotor;
extern pros::MotorGroup upperLowerIntakeMotorGroup;

//ODOMETRY
extern pros::Imu inertialSensor;
extern pros::Distance distanceSensor;

//OPTICAL`
extern pros::Optical opticalSensor;

//PNEUMATICS
extern pros::adi::DigitalOut descorePneumatic;
extern pros::adi::DigitalOut doubleParkPneumatic;
extern pros::adi::DigitalOut matchLoadPneumatic;

//POTENTIOMETER
extern pros::adi::Potentiometer potentiometer;

//CONTROLLER
extern pros::Controller controller;