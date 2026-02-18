#include "main.h"

//DRIVE MOTORS
//{FRONT, MIDDLE, BACK}
//{-18, -16, -4}
//{20, 10, 12}
//{LEFT FRONT, LEFT MIDDLE, LEFT BACK, RIGHT FRONT, RIGHT MIDDLE, RIGHT BACK}
//{-18, -16, -4, 20, 10, 12}
pros::MotorGroup leftDriveMotorGroup({-18, -16, -4}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::MotorGroup rightDriveMotorGroup({20, 10, 12}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::MotorGroup driveMotorGroup({-18, -16, -4, 20, 10, 12}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

//INTAKE MOTORS
//allIntakeMotorGroup = {UPPER, LOWER, SWITCHER}
//upperLowerIntakeMotor = {UPPER, LOWER}
pros::MotorGroup allIntakeMotorGroup({8,6,-15}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor switcherIntakeMotor(-15, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::MotorGroup upperLowerIntakeMotorGroup({8,6}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

//ODOMETRY
pros::Distance distanceSensor(17);
pros::Imu inertialSensor(13);

//OPTICAL
pros::Optical opticalSensor(2);

//PNEUMATICS
pros::adi::DigitalOut descorePneumatic('A');
pros::adi::DigitalOut matchLoadPneumatic('B');
pros::adi::DigitalOut doubleParkPneumatic('H');

//POTENTIOMETER
pros::adi::Potentiometer potentiometer('D');

//CONTROLLER
pros::Controller controller(pros::E_CONTROLLER_MASTER);
//red 16 +-30
//blue 190 +-30