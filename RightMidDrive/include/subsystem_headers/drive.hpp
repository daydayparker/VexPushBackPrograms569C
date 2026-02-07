#include "main.h"

//HELPER FUNCTIONS
double getAverageDriveEncoderValue();
void resetDriveEncoders();
void setDrive(int left, int right);
void setDriveMotorBrakeType(const pros::motor_brake_mode_e_t mode);
int sign(double number);

//DRIVER FUNCTIONS
void setDriveByDriver();

//AUTONOMOUS FUNCTIONS
void rotate(int degrees, double KP = 4, double KI = 0, double KD = 28, double acceleration = 4, double slewRateThreshold = 27);
void shake(int totalShakes, double firstVoltage, double secondVoltage, int shakeDuration, int coolDown);
void translate(int displacement, double KP = 0.1, double KI = 0, double KD = 0.025, double acceleration = 8, double slewRateThreshold = 27);
void translateWithDistanceSensor(int distance, double KP = 0.1, double KI = 0, double KD = 0.025, double acceleration = 8, double slewRateThreshold = 27);

