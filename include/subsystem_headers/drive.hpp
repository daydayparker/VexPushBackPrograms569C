#include "main.h"

//HELPER FUNCTIONS
double getAverageDriveEncoderValue();
double getDistanceSensorValueInInches();
void resetDriveEncoders();
void setDrive(int left, int right);
void setDriveMotorBrakeType(const pros::motor_brake_mode_e_t mode);
int sign(double number);

//DRIVER FUNCTIONS
void setDriveByDriver();

//AUTONOMOUS FUNCTIONS
void rotate(int degrees);
void shake(int shakes, double firstVoltage, double secondVoltage, int shakeDuration, int coolDown);
void translate(int displacement);
void translateWithDistanceSensor(int distance);
