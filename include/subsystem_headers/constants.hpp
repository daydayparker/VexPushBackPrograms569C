#include "main.h"

//AUTONOMOUS PID TUNING CONSTANTS
////TRANSLATION CONSTANTS
extern const double TKP;
extern const double TKI;
extern const double TKD;
extern const double TKA;
extern const double TRANSLATION_ACCELERATION;
extern const double TRANSLATIONAL_SLEW_RATE_THRESHOLD;
extern const double TRANSLATIONAL_MINIMUM_DERIVATIVE;
extern const int TRANSLATIONAL_DERIVATIVE_EXIT;
////ROTATIONAL extern constANTS
extern const double RKP;
extern const double RKI;
extern const double RKD;
extern const double ROTATIONAL_ACCELERATION;
extern const double ROTATIONAL_SLEW_RATE_THRESHOLD;
extern const double ROTATIONAL_MINIMUM_DERIVATIVE;
extern const int ROTATIONAL_ERROR_EXIT;
extern const int ROTATIONAL_DERIVATIVE_EXIT;

//SPECIAL BOOLEANS
extern bool ALWAYS_TRUE;

//CONVERSION CONSTANTS
extern const double MILLIMETERS_TO_INCHES;

//DURATION  CONSTANTS
//https://www.vexforum.com/t/v5-distance-sensor-technical-details/88482/8
//DISTANCE SENSOR FREQUENCY IS ~30 HZ: jpearman
extern const int WHILE_LOOP_DELAY_DURATION;
extern const int DISTANCE_SENSOR_DELAY;

//MOTOR CONSTANTS
extern const int MAX_VOLTAGE;
extern const int NUMBER_OF_MOTORS;

//PRECISION CONSTANTS
extern const int ANALOG_DEAD_ZONE;
extern const int ROTATION_PRECISION;
extern const int TRANSLATION_PRECISION;





