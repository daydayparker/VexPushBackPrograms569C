#include "main.h"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/api.hpp"
// PROS //

//DRIVE MOTORS
//{FRONT, MIDDLE, BACK}
pros::MotorGroup allDriveMotorGroup(
    {-18, -16, -4, 20, 10, 12}, 
    pros::v5::MotorGears::blue, 
    pros::v5::MotorUnits::degrees
);
pros::MotorGroup leftDriveMotorGroup(
    {-18, -16, -4}, 
    pros::v5::MotorGears::blue, 
    pros::v5::MotorUnits::degrees)
    ;
pros::MotorGroup rightDriveMotorGroup(
    {20, 10, 12}, 
    pros::v5::MotorGears::blue, 
    pros::v5::MotorUnits::degrees
);

//INTAKE MOTOR
pros::Motor intakeMotor(
    8, 
    pros::v5::MotorGears::blue, 
    pros::v5::MotorUnits::degrees
);

//LEVER MOTOR
pros::Motor leverMotor(15, 
    pros::v5::MotorGears::red, 
    pros::v5::MotorUnits::degrees
);

//ODOMETRY
pros::Distance distanceSensor(17);
pros::Imu inertialSensor(13);
pros::Rotation horizontalRotationSensor(1);
pros::Rotation verticalRotationSensor(2);

//PNEUMATICS
pros::adi::DigitalOut descorePneumatic('A');
pros::adi::DigitalOut leverPneumatic('B');
pros::adi::DigitalOut matchLoadPneumatic('C');

//CONTROLLER
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// LEMLIB //

//DRIVETRAIN
lemlib::Drivetrain drivetrain(
    &leftDriveMotorGroup,
    &rightDriveMotorGroup,
    9.75, //MAKE CONSTANT
    lemlib::Omniwheel::NEW_325,
    450, //MAKE CONSTANT
    2 //MAKE CONSTANT
);

//TRACKING WHEELS
lemlib::TrackingWheel horizontalTrackingWheel(
    &horizontalRotationSensor,
    lemlib::Omniwheel::NEW_2,
    1,
    1
);
lemlib::TrackingWheel verticalTrackingWheel(
    &verticalRotationSensor,
    lemlib::Omniwheel::NEW_2, 
    1, 
    1
);

//ODOMETRY SENSORS
lemlib::OdomSensors sensors(
    &verticalTrackingWheel,
    nullptr,
    &horizontalTrackingWheel,
    nullptr,
    &inertialSensor
);

//LATERAL PID CONTROLLER
lemlib::ControllerSettings lateralController(
    10, // proportional gain (kP)
    0, // integral gain (kI)
    3, // derivative gain (kD)
    3, // anti windup
    1, // small error range, in inches
    100, // small error range timeout, in milliseconds
    3, // large error range, in inches
    500, // large error range timeout, in milliseconds
    20 // maximum acceleration (slew)
);

//ANGULAR PID CONTROLLER
lemlib::ControllerSettings angularController(
    2, // proportional gain (kP)
    0, // integral gain (kI)
    10, // derivative gain (kD)
    3, // anti windup
    1, // small error range, in degrees
    100, // small error range timeout, in milliseconds
    3, // large error range, in degrees
    500, // large error range timeout, in milliseconds
    0 // maximum acceleration (slew)
);

//THROTTLE CURVE
lemlib::ExpoDriveCurve throttleCurve(
    3,    // joystick deadband out of 127
    14,   // minimum output where drivetrain will move out of 127
    1.019 // expo curve gain
 );

//STEER CURVE
lemlib::ExpoDriveCurve steerCurve(
    3,    // joystick deadband out of 127
    14,   // minimum output where drivetrain will move out of 127
    1.019 // expo curve gain
);

//CHASSIS
lemlib::Chassis chassis(
    drivetrain,
    lateralController,
    angularController,
    sensors
);