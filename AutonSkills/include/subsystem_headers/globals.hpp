#include "main.h"

//ALL MOTORS
extern pros::MotorGroup allMotorGroup;

//DRIVE MOTORS  
extern pros::MotorGroup leftDriveMotorGroup;
extern pros::MotorGroup rightDriveMotorGroup;

//INTAKE MOTORS
extern pros::Motor switcherIntakeMotor;
extern pros::MotorGroup upperLowerIntakeMotor;
extern pros::MotorGroup allIntakeMotorGroup;

//ODOMETRY
extern pros::Imu inertialSensor;

//PNEUMATICS
extern pros::adi::DigitalOut descorePneumatic;
extern pros::adi::DigitalOut doubleParkPneumatic;
extern pros::adi::DigitalOut matchLoadPneumatic;

//CONTROLLER
extern pros::Controller controller;
