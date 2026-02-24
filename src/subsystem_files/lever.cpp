#include "main.h"

void leverLoop(void *){
    while (true)
    {
        //CHECK MOTOR POSITION
        //controller.print(0, 0, "%f", leverMotor.get_position());

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X))
		{
			leverState = 0;
		}
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
        {
			leverState = 1;
        }
        //LEVER CONSTANTS HERE
        else if (!(leverMotor.get_position() <= 5)){
            leverState = 2;
        }
        else{
            leverState = 3;
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
        case 3:
            leverMotor.move(0);
            break;
        default:
            leverMotor.move(0); 
            break;  
        }

        pros::delay(WHILE_LOOP_DELAY_DURATION);
    }
    
}