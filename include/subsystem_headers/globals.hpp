#include "main.h"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/api.hpp"
// PROS //

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

// LEMLIB //

//DRIVETRAIN
extern lemlib::Drivetrain drivetrain;

//TRACKING WHEELS
extern lemlib::TrackingWheel horizontalTrackingWheel;
extern lemlib::TrackingWheel verticalTrackingWheel;

//ODOMETRY SENSORS
extern lemlib::OdomSensors sensors;

//LATERAL PID CONTROLLER
extern lemlib::ControllerSettings lateralController;

//ANGULAR PID CONTROLLER
extern lemlib::ControllerSettings angularController;

//THROTTLE CURVE
extern lemlib::ExpoDriveCurve throttleCurve; 

//STEER CURVE
extern lemlib::ExpoDriveCurve steerCurve;

//CHASSIS
extern lemlib::Chassis chassis;