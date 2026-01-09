#include "main.h"

//ALL MOTORS
/*
{LEFT FRONT, LEFT MIDDLE, LEFT BACK,},
{RIGHT FRONT, RIGHT MIDDLE, RIGHT BACK},
{UPPER INTAKE, LOWER INTAKE, SWITCHER}
*/
// pros::MotorGroup allMotorGroup({-19, -11, -9, 20, 10, 12, 8, 6, -5}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

//DRIVE MOTORS
//{FRONT, MIDDLE, BACK}
pros::MotorGroup leftDriveMotorGroup({-19, -11, -9}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::MotorGroup rightDriveMotorGroup({20, 10, 12}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

//INTAKE MOTORS
//{UPPER, LOWER, SWITCHER}
pros::Motor switcherIntakeMotor(-5, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::MotorGroup upperLowerIntakeMotor({8,6}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::MotorGroup allIntakeMotorGroup({8,6,-5}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

//ODOMETRY
pros::Imu inertialSensor(13);

//PNEUMATICS
pros::adi::DigitalOut descorePneumatic('A');
pros::adi::DigitalOut doubleParkPneumatic('H');
pros::adi::DigitalOut matchLoadPneumatic('B');

//CONTROLLER
pros::Controller controller(pros::E_CONTROLLER_MASTER);
