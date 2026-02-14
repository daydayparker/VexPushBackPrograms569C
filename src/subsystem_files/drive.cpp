#include "main.h"

//HELPER FUNCTIONS
double getAverageDriveEncoderValue(){ 
    return (leftDriveMotorGroup.get_position(0) + rightDriveMotorGroup.get_position(0)) / 2;
}

/*
double getDistanceSensorValueInInches(){
    return distanceSensor.get_distance() * MILLIMETERS_TO_INCHES;
}
*/


void resetDriveEncoders(){
   leftDriveMotorGroup.tare_position_all();
   rightDriveMotorGroup.tare_position_all();
}

void setDrive(int left, int right){
    leftDriveMotorGroup.move(left);
    rightDriveMotorGroup.move(right);
}

void setDriveMotorBrakeType(const pros::motor_brake_mode_e_t mode)
{
    leftDriveMotorGroup.set_brake_mode_all(mode);
	rightDriveMotorGroup.set_brake_mode_all(mode);
}

int sign(double number){
    if (number > 0){
        return 1;
    }
    else if (number < 0){
        return -1;
    }
    return 0;
}


//DRIVER CONTROL FUNCTIONS
void setDriveByDriver(){
    int leftJoystickValue = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightJoystickValue = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    if (abs(leftJoystickValue) < ANALOG_DEAD_ZONE){
        leftJoystickValue = 0;
    }
    if (abs(rightJoystickValue) < ANALOG_DEAD_ZONE){
        rightJoystickValue = 0;
    }
    setDrive(leftJoystickValue, rightJoystickValue);
}

//AUTONOMOUS FUNCTIONS
void rotate(int degrees, double kP, double kI, double kD, double acceleration, double slewRateThreshold){
    //PID VARIABLES
    double error;
    double previousError = 0;
    double derivative = 0;
    double integral = 0;

    //ROTATION VARIABLES
    double currentYaw = 0;

    //MOTOR VARIABLES
    double driveMotorVoltage = 0;

    //INITIALIZING ERROR
    error = degrees - currentYaw;

    //COUNTER VARIABLES
    int exitCounter = 0;
    int safetyExitCounter = 0;

    //ROBOT ROTATING LOOP
    while (exitCounter < ROTATIONAL_ERROR_EXIT)
    {
        //EXIT LOOP LOGIC: ERROR
        if (fabs(error) < ROTATION_PRECISION){
            exitCounter++;
        }
        else{
            exitCounter = 0;
        }

        //RETRIEVE THE TOTAL THAT THE ROBOT HAS ROTATED
        currentYaw = inertialSensor.get_rotation();

        //UPDATE PID VARIABLES
        error = degrees - currentYaw;
        derivative = error - previousError;
        integral += error;
        previousError = error;

        //EXIT LOOP LOGIC: DERIVATIVE
        if (fabs(derivative) < ROTATIONAL_MINIMUM_DERIVATIVE){
            safetyExitCounter++;
        }
        if (safetyExitCounter > ROTATIONAL_DERIVATIVE_EXIT){
            break;
        }

        //CALCULATE THE MOTOR POWER FROM PID
        int voltageFromPropotionalIntegralDerivative = kP * error + kI * integral + kD * derivative;

        //SEND THE CHOSEN VOLTAGE TO THE MOTORS
        setDrive(voltageFromPropotionalIntegralDerivative, -voltageFromPropotionalIntegralDerivative);
        
        //DELAY FOR LOOPING
        pros::delay(WHILE_LOOP_DELAY_DURATION);

    }

    //STOP MOVING
    setDrive(0, 0);
}

void shake(int shakes, double firstVoltage, double secondVoltage, int shakeDuration, int coolDown)
{
    setDriveMotorBrakeType(pros::E_MOTOR_BRAKE_COAST);
    for (int shakeCounter = 0; shakeCounter < shakes; shakeCounter++)
    {
        setDrive(firstVoltage, firstVoltage);
        pros::delay(shakeDuration);
        setDrive(secondVoltage, secondVoltage);
        pros::delay(coolDown);
    }
    setDriveMotorBrakeType(pros::E_MOTOR_BRAKE_BRAKE);
}

void translate(int displacement, bool usesDistanceSensor, double kP, double kI, double kD, double kA, double acceleration, double slewRateThreshold){
    //SETTING UP WHILE LOOP
    int waitTime;
    if (!usesDistanceSensor){
        waitTime = WHILE_LOOP_DELAY_DURATION;
    }
    else{
        waitTime = DISTANCE_SENSOR_DELAY;
    }

    //RESETTING DRIVE ENCODERS
    resetDriveEncoders();

    //PID VARIABLES
    double error;
    double previousError = 0;
    double derivative;
    double integral = 0;

    //MOTOR VARIABLES
    double averageDriveMotorEncoderValue = 0;
    int driveMotorVoltage = 0;

    //INITIALIZING ERROR
    if (!usesDistanceSensor){
        error = fabs(displacement) - fabs(averageDriveMotorEncoderValue);
    }
    else{
       error = displacement - distanceSensor.get_distance();
    }

    //SLEW RATE VARIABLES AND CONSTANTS
    int loopCounter = 0;
    const int DIRECTION = fabs(displacement) / displacement;

    //INITIAL ANGLE
    double initialAngle = inertialSensor.get_rotation();

    //EXIT LOOP SETUP
    int safetyExitCounter = 0;

    while (fabs(error) > TRANSLATION_PRECISION)
    {
        //INCREMENT COUNTER USED FOR SLEW RATE
        loopCounter++;

        //CALCULATE VOLTAGE FROM SLEW RATE
        double voltageFromSlewRate = DIRECTION * (loopCounter * acceleration + slewRateThreshold);

        //UPDATE PID VARIABLES
        if (!usesDistanceSensor){
            error = displacement - getAverageDriveEncoderValue();
        }
        else{
            error = displacement - distanceSensor.get_distance();
        }
        derivative = error - previousError;
        integral += error;
        previousError = error;

        //EXIT LOOP LOGIC
        if (fabs(derivative) < TRANSLATIONAL_MINIMUM_DERIVATIVE){
            safetyExitCounter++;
        }
        if (safetyExitCounter > TRANSLATIONAL_DERIVATIVE_EXIT){
            break;
        }

        //CALCULATE THE MOTOR POWER FROM PID
        double voltageFromPropotionalIntegralDerivative = kP * error + kI * integral + kD * derivative;

        //USE VOLTAGE FROM SLEW RATE IF IT IS LESS THAN VOLTAGE FROM PID
        if (fabs(voltageFromPropotionalIntegralDerivative) > fabs(voltageFromSlewRate)){
            driveMotorVoltage = voltageFromSlewRate;
        }
        else{
            driveMotorVoltage = voltageFromPropotionalIntegralDerivative;
        }

        //CALCULATE ANGLE ERROR
        double angleError = inertialSensor.get_rotation() - initialAngle;
        double angleAdjustment = angleError * kA; 

        //SEND THE CHOSEN VOLTAGE TO THE MOTORS
        setDrive(driveMotorVoltage - angleAdjustment, driveMotorVoltage + angleAdjustment);

        //DELAY FOR LOOPING
        pros::delay(waitTime);
    }

    //STOP MOVING
    setDrive(0, 0);
}