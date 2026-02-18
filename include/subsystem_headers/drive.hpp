#include "main.h"

//HELPER FUNCTIONS
double getAverageDriveEncoderValue();
double getDistanceSensorValueInInches();
void resetDriveEncoders();
void setDrive(int left, int right);
int sign(double number);

//DRIVER FUNCTIONS
void setDriveByDriver();

//AUTONOMOUS FUNCTIONS
void rotate(int degrees, double kP = 4.0, double kI = 0.0, double kD = 28.0, double acceleration = 12, double slewRateThreshold = 27);
void shake(int shakes, double firstVoltage, double secondVoltage, int firstDuration, int secondDuration);
void translate(int displacement, bool usesDistanceSensor = false, double kP = 0.1, double kI = 0.0, double kD = 0.025, double kA = 6, double acceleration = 4, double slewRateThreshold = 27);
//void translate(int displacement, bool usesDistanceSensor = false, double KPAAA = 6.0, double kP = TKP);
