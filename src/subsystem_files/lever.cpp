#include "main.h"

void leverLoop(void *){
    while (true)
    {
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X))
		{
			leverState = 0;
		}
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
        {
			leverState = 1;
        }
        else{
            leverState = 2;
        }
        
        switch (leverState)
        {
        //FORWARD
        case 0:
            leverMotor.move(MAX_VOLTAGE);
            break;
        //SLOW FORWARD
        case 1:
            leverMotor.move(0.5 * MAX_VOLTAGE);
            break;
        //REVERSE
        case 2:
            leverMotor.move(-MAX_VOLTAGE);
            break;
        default:
            leverMotor.move(-MAX_VOLTAGE); 
            break;  
        }

        pros::delay(WHILE_LOOP_DELAY_DURATION);
    }
    
}