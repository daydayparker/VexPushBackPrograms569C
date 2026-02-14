#include "main.h"

bool intakeOn = false;

void setIntake(int power){
    allIntakeMotorGroup.move(power);
}

void setSwitcherIntake(int power){
    switcherIntakeMotor.move(power);
}

void setUpperLowerIntake(int power){
    upperLowerIntakeMotorGroup.move(power);
}

void intakeLoop(void*){
    while (true)
    {
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
		{
			intakeState = 0;
		}
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
        {
			intakeState = 1;
        }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT))
        {
            intakeState = 2;
        }
        else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){
            if (intakeState == 3){
                intakeOn = true;
                intakeState = 4;
            }
            else{
                intakeOn = false;
                intakeState = 3;
            }
        }
        else if (intakeOn){
            intakeState = 4;
        }
        else{
            intakeState = 3;
        }
      

        
        switch (intakeState)
        {
        //REVERSE
        case 0:
            setUpperLowerIntake(-MAX_VOLTAGE);
            setSwitcherIntake(-MAX_VOLTAGE);
            break;
        //SLOW REVERSE
        case 1:
            setUpperLowerIntake(-0.5 * MAX_VOLTAGE);
            setSwitcherIntake(-0.5 * MAX_VOLTAGE);
            break;
        //SCORE TOP GOAL
        case 2:
            setUpperLowerIntake(MAX_VOLTAGE);
            setSwitcherIntake(-0.65 * MAX_VOLTAGE);
            break;
        //STOP INTAKE
        case 3:
            setUpperLowerIntake(0);
            setSwitcherIntake(0);
            break;
        //SPIN INTAKE FORWARD
        case 4:
            setUpperLowerIntake(MAX_VOLTAGE);
            setSwitcherIntake(MAX_VOLTAGE);
            break;
        default:
            setIntake(0);
            break;
        }

        pros::delay(10);
    }
    
}

