#include "main.h"

//HELPER FUNCTIONS
double getAverageDriveEncoderValue();
void setDrive(int left, int right);
int sign(double number);

//DRIVER FUNCTIONS
void setDriveByDriver();

//AUTONOMOUS FUNCTIONS
void rotate(
    int degrees, 
    double kP = 4.0, 
    double kI = 0.0, 
    double kD = 28.0, //28.0
    double acceleration = 12.0, 
    double slewRateThreshold = 27.0
);
void shake(int shakes, double firstVoltage, double secondVoltage, int shakeDuration, int coolDown);
void translate(
    int displacement, 
    double kP = 0.1, //0.10
    double kI = 0.0, 
    double kD = 0.026, //0.025
    double kA = 5.0, 
    double acceleration = 4.0, 
    double slewRateThreshold = 27.0
);

