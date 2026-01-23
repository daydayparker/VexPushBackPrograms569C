#include "main.h"

void setIntake(int power){
    allIntakeMotorGroup.move(power);
}

void setSwitcherIntake(int power, bool shouldSwitcherSpinFoward, bool shouldSwitcherSpinBackward){
    int actualPower = 0;
    if (shouldSwitcherSpinFoward){
        actualPower = power;
    }
    if(shouldSwitcherSpinBackward){
        actualPower = -power;
    }
    switcherIntakeMotor.move(actualPower);
}

void setUpperLowerIntake(int power){
    upperLowerIntakeMotorGroup.move(power);
}

