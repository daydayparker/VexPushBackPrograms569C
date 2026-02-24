#include "main.h"

//DRIVE MOTORS
//{FRONT, MIDDLE, BACK}
pros::MotorGroup allDriveMotorGroup({-18, -16, -4, 20, 10, 12}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::MotorGroup leftDriveMotorGroup({-18, -16, -4}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::MotorGroup rightDriveMotorGroup({20, 10, 12}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

//INTAKE MOTOR
pros::Motor intakeMotor(8, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

//LEVER MOTOR
pros::Motor leverMotor(15, pros::v5::MotorGears::red, pros::v5::MotorUnits::degrees);

//ODOMETRY
pros::Distance distanceSensor(17);
pros::Imu inertialSensor(13);

//PNEUMATICS
pros::adi::DigitalOut descorePneumatic('A');
pros::adi::DigitalOut matchLoadPneumatic('B');

//CONTROLLER
pros::Controller controller(pros::E_CONTROLLER_MASTER);