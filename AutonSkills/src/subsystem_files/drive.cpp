#include "main.h"

//HELPER FUNCTIONS
double getAverageDriveEncoderValue(){ 
    return (leftDriveMotorGroup.get_position(0) + rightDriveMotorGroup.get_position(0)) / 2;
}

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
    int leftJoystickValue = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) * 0.9;
    int rightJoystickValue = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) * 0.9;
    if (abs(leftJoystickValue) < ANALOG_DEAD_ZONE){
        leftJoystickValue = 0;
    }
    if (abs(rightJoystickValue) < ANALOG_DEAD_ZONE){
        rightJoystickValue = 0;
    }
    setDrive(leftJoystickValue, rightJoystickValue);
}

//AUTONOMOUS FUNCTIONS
void rotate(int degrees, double KP, double KI, double KD, double acceleration, double slewRateThreshold){
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
    while (exitCounter < 15)
    {
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

        
        if (fabs(derivative) < 0.05){
            safetyExitCounter++;
        }
        if (safetyExitCounter > 30){
            break;
        }


        //CALCULATE THE MOTOR POWER FROM PID
        int voltageFromPropotionalIntegralDerivative = KP * error + KI * integral + KD * derivative;

        //SEND THE CHOSEN VOLTAGE TO THE MOTORS
        setDrive(voltageFromPropotionalIntegralDerivative, -voltageFromPropotionalIntegralDerivative);
        
        //DELAY FOR LOOPING
        pros::delay(WHILE_LOOP_DELAY_DURATION);

    }

    //STOP MOVING
    setDrive(0, 0);
}

void shake(int totalShakes, double maxVoltageMultiplier, int shakeDuration, int coolDown){
    for (int shakeCounter = 0; shakeCounter < totalShakes; shakeCounter++)
    {
        setDrive(maxVoltageMultiplier * MAX_VOLTAGE, maxVoltageMultiplier * MAX_VOLTAGE);
        pros::delay(500);
        setDrive(0,0);
        pros::delay(333);
    }
}

void translate(int displacement, double KP, double KI, double KD, double acceleration, double slewRateThreshold){
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
    error = fabs(displacement) - fabs(averageDriveMotorEncoderValue);

    //SLEW RATE VARIABLES AND CONSTANTS
    int loopCounter = 0;
    const int DIRECTION = fabs(displacement) / displacement;

    int safetyExitCounter = 0;

    while (fabs(error) > TRANSLATION_PRECISION)
    {
        //INCREMENT COUNTER USED FOR SLEW RATE
        loopCounter++;

        //CALCULATE VOLTAGE FROM SLEW RATE
        double voltageFromSlewRate = DIRECTION * (loopCounter * acceleration + slewRateThreshold);

        //RETRIEVE THE TOTAL THAT THE MOTORS HAVE ROTATED
        averageDriveMotorEncoderValue = getAverageDriveEncoderValue();

        //UPDATE PID VARIABLES
        error = displacement - averageDriveMotorEncoderValue;
        derivative = error - previousError;
        integral += error;
        previousError = error;


        controller.print(0, 0, "d: %f", derivative);

        if (fabs(derivative) < 0.1){
            safetyExitCounter++;
        }
        if (safetyExitCounter > 30){
            break;
        }


        //CALCULATE THE MOTOR POWER FROM PID
        double voltageFromPropotionalIntegralDerivative = KP * error + KI * integral + KD * derivative;

        //USE VOLTAGE FROM SLEW RATE IF IT IS LESS THAN VOLTAGE FROM PID
        if (fabs(voltageFromPropotionalIntegralDerivative) > fabs(voltageFromSlewRate)){
            driveMotorVoltage = voltageFromSlewRate;
        }
        else{
            driveMotorVoltage = voltageFromPropotionalIntegralDerivative;
        }

        //SEND THE CHOSEN VOLTAGE TO THE MOTORS
        setDrive(driveMotorVoltage, driveMotorVoltage);

        //DELAY FOR LOOPING
        pros::delay(WHILE_LOOP_DELAY_DURATION);
    }
    

    //STOP MOVING
    setDrive(0, 0);
}

