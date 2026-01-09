#include "main.h"

//HELPER FUNCTIONS
void setDrive(int left, int right);
void resetDriveEncoders();
double getAverageDriveEncoderValue();

//DRIVER CONTROL FUNCTIONS
void setDriveByDriver();

//AUTONOMOUS FUNCTIONS
void translate(int displacement, double KP = 2, double KI = 0, double KD = 0.025, double acceleration = 4, double slewRateThreshold = 27);
void rotate(int degrees, double KP = 3, double KI = 0, double KD = .5, double acceleration = 4, double slewRateThreshold = 27);

int sign(double number);