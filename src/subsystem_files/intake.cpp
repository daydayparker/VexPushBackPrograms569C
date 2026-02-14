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
    int switcherVoltage = 0;

    //TURN ON OPTICAL
    opticalSensor.set_led_pwm(100);
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
            switcherVoltage = -MAX_VOLTAGE;
            break;
        //SLOW REVERSE
        case 1:
            setUpperLowerIntake(-0.5 * MAX_VOLTAGE);
            switcherVoltage = -0.5 * MAX_VOLTAGE;
            break;
        //SCORE TOP GOAL
        case 2:
            setUpperLowerIntake(MAX_VOLTAGE);
            switcherVoltage = -0.65 * MAX_VOLTAGE;
            break;
        //STOP INTAKE
        case 3:
            setUpperLowerIntake(0);
            switcherVoltage = 0;
            break;
        //SPIN INTAKE FORWARD
        case 4:
            setUpperLowerIntake(MAX_VOLTAGE);
            switcherVoltage = MAX_VOLTAGE;
            break;
        default:
            setUpperLowerIntake(0); 
            switcherVoltage = 0;
            break;  
        }

        //COMMENT OUT WHEN UPLOADING TO SKILLS
        //get proxitymity thingie
        //WHEN WE ARE BLUE
        //255 constn idk!
        //400 is wait time for otpacil sensor: constant 
        
        /////
        
        if ((opticalSensor.get_hue() >= 345 || opticalSensor.get_hue() <= 45) && !color && opticalSensor.get_proximity() == 255){
            setSwitcherIntake(-MAX_VOLTAGE);
            pros::delay(400);
        }
        //WHEN WE ARE RED
        else if ((opticalSensor.get_hue() >= 160 && opticalSensor.get_hue() <= 220) && color && opticalSensor.get_proximity() == 255){
            setSwitcherIntake(-MAX_VOLTAGE);
            pros::delay(400);
        }
        else{
            setSwitcherIntake(switcherVoltage);
        }
        
        /////
        
       setSwitcherIntake(switcherVoltage);

        //controller.print(0, 0, "%d            ", opticalSensor.get_proximity());
        pros::delay(10);
    }
    
}

//set up another task