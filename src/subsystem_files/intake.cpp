#include "main.h"

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
        else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){
            if (intakeState == 2){
                intakeOn = true;
                intakeState = 3;
            }
            else{
                intakeOn = false;
                intakeState = 2;
            }
        }
        else if (intakeOn){
            intakeState = 3;
        }
        else{
            intakeState = 2;
        }
        
        switch (intakeState)
        {
        //REVERSE
        case 0:
            intakeMotor.move(-MAX_VOLTAGE);
            break;
        //SLOW REVERSE
        case 1:
            intakeMotor.move(-0.5 * MAX_VOLTAGE);
            break;
        //STOP INTAKE
        case 2:
            intakeMotor.move(0);
            break;
        //SPIN INTAKE FORWARD
        case 3:
            intakeMotor.move(MAX_VOLTAGE);
            break;
        default:
            intakeMotor.move(0); 
            break;  
        }

        pros::delay(WHILE_LOOP_DELAY_DURATION);
    }
    
}