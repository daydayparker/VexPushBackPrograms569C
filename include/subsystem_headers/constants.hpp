#include "main.h"

//AUTONOMOUS PID TUNING CONSTANTS
////TRANSLATION CONSTANTS
const double TKP = 4;
const double TKI = 0;
const double TKD = 28;
const double TKA = 0;
const double translationalAccerelation = 4;
const double translationalSlewRateThreshold = 27;
////ROTATIONAL CONSTANTS
const double RKP = 0.1;
const double RKI = 0;
const double RKD = 0.025;
const double rotationalAcceleration = 12;
const double rotationalSlewRateThreshold = 27;

//CONVERSION CONSTANTS
const double MILLIMETERS_TO_INCHES= 0.0393701;

//DURATION CONSTANTS
//https://www.vexforum.com/t/v5-distance-sensor-technical-details/88482/8
//DISTANCE SENSOR FREQUENCY IS ~30 HZ: jpearman
const int WHILE_LOOP_DELAY_DURATION = 10;
const int DISTANCE_SENSOR_DELAY = 40;

//MOTOR CONSTANTS
const int MAX_VOLTAGE = 127;
const int NUMBER_OF_MOTORS = 6;

//PRECISION CONSTANTS
const int ANALOG_DEAD_ZONE = 20;
const int ROTATION_PRECISION = 1;
const int TRANSLATION_PRECISION = 5;





