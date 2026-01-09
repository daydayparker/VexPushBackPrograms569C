#include "main.h"

void setUpperLowerIntake(int power){
    upperLowerIntakeMotor.move(power);
}

void setSwitcherIntake(int power, bool shouldSwitcherSpinFoward, bool shouldSwitcherSpinBackward){
    int actualPower = 0;
    if (shouldSwitcherSpinFoward){
        actualPower = power;
    }
    if(shouldSwitcherSpinBackward){
        actualPower = -power * 0.1;
    }
    switcherIntakeMotor.move(actualPower);
}

void setIntake(int power){
    allIntakeMotorGroup.move(power);
}
