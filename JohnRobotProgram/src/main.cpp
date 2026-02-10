#include "main.h"
//#include "liblvgl/lvgl.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
/*
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}
*/

/*
void display_img_from_c_array(){
	// create a variable for the c array (image)
	LV_IMAGE_DECLARE(john_robot_image);

	// declare and define the image object
	lv_obj_t* img = lv_image_create(lv_screen_active());

	// set the source data for the image
	lv_image_set_src(img, &john_robot_image);

	//align image
	lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
}

void display_img_from_file(const void * src){

}
*/

//STATE-TRACKING BOOLEANS
bool isDescorePneumaticExtended;
bool isDoubleParkPneumaticExtended;
bool isMatchLoadPneumaticExtended;
bool isIntakeSpinningForward;
bool isIntakeSpinningBackward;
bool shouldSwitcherSpinFoward;
bool shouldSwitcherSpinBackward;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize() {
	//PUT AWESOME TEXT ON THE CONTROLLER SCREEN
	//controller.print(0, 0, "By: %s", "daydayparker");


	//ASSIGN VALUES TO STATE-TRACKING BOOLEANS
	isDescorePneumaticExtended = false;
	isDoubleParkPneumaticExtended = false;
	isMatchLoadPneumaticExtended = false;
	isIntakeSpinningForward = false;
	isIntakeSpinningBackward = false;
	shouldSwitcherSpinFoward = true;
	shouldSwitcherSpinBackward = false;

	//SET MOTOR BRAKE TYPES
	setDriveMotorBrakeType(pros::E_MOTOR_BRAKE_COAST);
	allIntakeMotorGroup.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);

	//CALIBRATE THE INERTIAL SENSOR
	inertialSensor.reset();

	//WAITING FOR THE INERTIAL SENSOR TO CALIBRATE
	while (inertialSensor.is_calibrating()){
		pros::delay(WHILE_LOOP_DELAY_DURATION);
	}
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void leftMatchAuton(){
	//MAKE SURE BALLS DO NOT FALL OUT
	setDescorePneumatic(true);

	//COLLECT THREE BALLS FROM MIDDLE AREA
	translate(675);
	rotate(-45);
	setIntake(MAX_VOLTAGE);
	translate(740); //680

	//UNSTUCK BALLS IF BALLS ARE STUCK
	setIntake(-MAX_VOLTAGE);
	pros::delay(125);
	setIntake(MAX_VOLTAGE);

	//ALIGN WITH TOP GOAL
	rotate(-135);
	translate(-975); // -1050

	//SCORE ON TOP GOAL
	setIntake(MAX_VOLTAGE);
	setSwitcherIntake(0.4 * MAX_VOLTAGE, false, true);
	pros::delay(1250); //2000 

	//ALIGN WITH MATCH LOADER
	rotate(-130);

	//CONTINUE ALIGNING WITH MATCH LOADER
	setSwitcherIntake(MAX_VOLTAGE, false, true);
	translate(2375); //2325 = TOO CLOSE
	rotate(-183);
	
	//PREPARE TO RETRIEVE THREE BALLS FROM MATCH LOADER
	setIntake(MAX_VOLTAGE);
	setMatchLoadPneumatic(true);
	pros::delay(500);

	//RETRIEVE THREE BALLS FROM MATCH LOADER
	setDrive(0.4 * MAX_VOLTAGE, 0.4 * MAX_VOLTAGE);
	pros::delay(500);
	shake(3, MAX_VOLTAGE * 0.5, -MAX_VOLTAGE * 0.3, 300, 80);
	rotate(-182);

	//ALIGN WITH LONG GOAL
	//setMatchLoadPneumatic(false);
	setDrive(-0.6 * MAX_VOLTAGE, -0.6 * MAX_VOLTAGE);
	pros::delay(500);

	//SCORE ON LONG GOAL
	setDescorePneumatic(false); 
	setIntake(MAX_VOLTAGE);
	pros::delay(1000);

	//UNSTUCK BALLS IF BALLS ARE STUCK
	setIntake(-MAX_VOLTAGE);
	pros::delay(125);

	//CONTINUE SCORING ON LONG GOAL
	setIntake(MAX_VOLTAGE);
	pros::delay(1350);  
	
	//STOP MOVING AND STOP INTAKE
	setDrive(0,0);
	setIntake(0);

	//DESCORE
	translate(600);
	rotate(-135);
	translate(-700); //-750
	rotate(-180);
	translate(-900); //-1250
}

void rightMidMatchAuton(){
	//MAKE SURE BALLS DO NOT FALL OUT
	setDescorePneumatic(true);

	//COLLECT THREE RED BALLS FROM MIDDLE AREA
	translate(675);
	rotate(45);
	setIntake(MAX_VOLTAGE);
	translate(777);

	//ALIGN WITH BOTTOM MIDDLE GOAL
	rotate(-45); //-41 
	pros::delay(300);
	setIntake(-0.9 * MAX_VOLTAGE);
	translate(500); //500 - 600 = :
	pros::delay(550);

	//SCORE ON BOTTOM MIDDLE GOAL
	setIntake(0);

	//ALIGN WITH MATCH LOADER
	translate(-1975); //-2000
	rotate(-180); //NOTE: could be -178

	//ALIGN WITH MATCH LOADER
	translate(-100);
	setMatchLoadPneumatic(true);
	pros::delay(200);

	//MAKE SURE BALLS DO NOT GET STUCK 
	setIntake(-MAX_VOLTAGE);
	pros::delay(125); //400
	setIntake(MAX_VOLTAGE);

	//RETRIEVE THREE RED BALLS FROM MATCH LOADER
	setDrive(0.4 * MAX_VOLTAGE, 0.4 * MAX_VOLTAGE);
	pros::delay(500); // 1750
	shake(3, MAX_VOLTAGE * 0.5, -MAX_VOLTAGE * 0.25, 325, 75); //400 on forward
	rotate(-179); //-180

	//ALIGN WITH LONG GOAL
	setMatchLoadPneumatic(false);
	setDrive(-0.475 * MAX_VOLTAGE, -0.475 * MAX_VOLTAGE);
	pros::delay(650);

	//SCORE ON LONG GOAL
	setDescorePneumatic(false); 
	setIntake(MAX_VOLTAGE);
	pros::delay(1000);

	//UNSTUCK BALLS IF BALLS ARE STUCK
	setIntake(-MAX_VOLTAGE);
	pros::delay(125);

	//CONTINUE SCORING ON LONG GOAL
	setIntake(MAX_VOLTAGE);
	pros::delay(1250);
	
	//STOP MOVING AND STOP INTAKE
	setDrive(0,0);
	setIntake(0);

	//REALIGN
	rotate(-180);

	//DESCORE
	translate(600);
	rotate(-135);
	translate(-700); //-750
	rotate(-180);
	translate(-700); //-1250
	rotate(-150);
	
	/*
	translate(500);
	rotate(-270);
	translate(500);
	rotate(-360);
	translate(1200);
	rotate(-330);
	*/

	/*
	
	*/
}

void rightNoMidMatchAuton(){
	//MAKE SURE BALLS DO NOT FALL OUT
	setDescorePneumatic(true);

	//COLLECT THREE RED BALLS FROM MIDDLE AREA
	translate(675);
	rotate(45);
	setIntake(MAX_VOLTAGE);
	translate(845);

	//ALIGN WITH MATCH LOADER
	rotate(135);
	translate(1435); //1450
	rotate(180); // 180
	setMatchLoadPneumatic(true);

	//MAKE SURE BALLS DO NOT GET STUCK 
	setIntake(-MAX_VOLTAGE);
	pros::delay(400);
	setIntake(MAX_VOLTAGE);
	pros::delay(125);

	//RETRIEVE THREE RED BALLS FROM MATCH LOADER
	setDrive(0.4 * MAX_VOLTAGE, 0.4 * MAX_VOLTAGE);
	pros::delay(500); // 1750
	shake(3, MAX_VOLTAGE * 0.5, -MAX_VOLTAGE * 0.25, 500, 100);
	rotate(180);

	//ALIGN WITH LONG GOAL
	setMatchLoadPneumatic(false);
	setDrive(-0.5 * MAX_VOLTAGE, -0.5 * MAX_VOLTAGE);
	pros::delay(500);

	//SCORE ON LONG GOAL
	setDescorePneumatic(false); 
	setIntake(MAX_VOLTAGE);
	pros::delay(1000);

	//UNSTUCK BALLS IF BALLS ARE STUCK
	setIntake(-MAX_VOLTAGE);
	pros::delay(250);

	//CONTINUE SCORING ON LONG GOAL
	setIntake(MAX_VOLTAGE);
	pros::delay(2000);
	
	//STOP MOVING AND STOP INTAKE
	setDrive(0,0);
	setIntake(0);

	//DESCORE
	translate(600);
	rotate(225);
	translate(-725); //-750
	rotate(180);
	translate(-700); //-1250
	rotate(210);
}

void safeRightMidMatchAuton(){
	//MAKE SURE BALLS DO NOT FALL OUT
	setDescorePneumatic(true);

	//COLLECT THREE RED BALLS FROM MIDDLE AREA
	translate(675);
	rotate(45);
	setIntake(MAX_VOLTAGE);
	translate(777);

	//ALIGN WITH BOTTOM MIDDLE GOAL
	rotate(-45); //-41 
	pros::delay(300);
	setIntake(-0.9 * MAX_VOLTAGE);
	translate(500); //500 - 600 = :
	pros::delay(550);

	//SCORE ON BOTTOM MIDDLE GOAL
	setIntake(0);

	//ALIGN WITH MATCH LOADER
	translate(-1900); //-2000
	rotate(-180); //NOTE: could be -178

	//ALIGN WITH MATCH LOADER
	translate(-100);
	setMatchLoadPneumatic(true);
	pros::delay(250);

	//MAKE SURE BALLS DO NOT GET STUCK 
	setIntake(-MAX_VOLTAGE);
	pros::delay(125); //400
	setIntake(MAX_VOLTAGE);

	//RETRIEVE THREE RED BALLS FROM MATCH LOADER
	setDrive(0.4 * MAX_VOLTAGE, 0.4 * MAX_VOLTAGE);
	pros::delay(500); // 1750
	shake(3, MAX_VOLTAGE * 0.5, -MAX_VOLTAGE * 0.25, 350, 100); //400 on forward
	rotate(-180);

	//ALIGN WITH LONG GOAL
	setMatchLoadPneumatic(false);
	setDrive(-0.425 * MAX_VOLTAGE, -0.425 * MAX_VOLTAGE);
	pros::delay(500);

	//SCORE ON LONG GOAL
	setDescorePneumatic(false); 
	setIntake(MAX_VOLTAGE);
	pros::delay(1000);

	//UNSTUCK BALLS IF BALLS ARE STUCK
	setIntake(-MAX_VOLTAGE);
	pros::delay(125);

	//CONTINUE SCORING ON LONG GOAL
	setIntake(MAX_VOLTAGE);
	pros::delay(1250);

	//UNSTUCK BALLS IF BALLS ARE STUCK
	setIntake(-MAX_VOLTAGE);
	pros::delay(125);

	//CONTINUE SCORING ON LONG GOAL
	setIntake(MAX_VOLTAGE);
	pros::delay(1250);

	//UNSTUCK BALLS IF BALLS ARE STUCK
	setIntake(-MAX_VOLTAGE);
	pros::delay(125);

	//CONTINUE SCORING ON LONG GOAL
	setIntake(MAX_VOLTAGE);
	pros::delay(1250);

	//UNSTUCK BALLS IF BALLS ARE STUCK
	setIntake(-MAX_VOLTAGE);
	pros::delay(125);

	//CONTINUE SCORING ON LONG GOAL
	setIntake(MAX_VOLTAGE);
	pros::delay(1250);
	
	//STOP MOVING AND STOP INTAKE
	setDrive(0,0);
	setIntake(0);

	//REALIGN
	rotate(-180);

	//DESCORE
	translate(600);
	rotate(-135);
	translate(-700); //-750
	rotate(-180);
	translate(-900); //-1250
}

void soloMatchAuton(){

}

void skillsAutonRoute1(){
	//MOVING TOWARDS MATCH LOADER
	translate(1525);

	//ROTATE TOWARDS MATCH LOADER
	rotate(90); 

	//ACTUATE MATCH LOADER PNEUMATIC AND DESCORE PNEUMATIC
	setDescorePneumatic(true);
	setMatchLoadPneumatic(true);
	pros::delay(625);

	//MAKE ROOM FOR MATCH LOADER
	translate(-75, 2);
	pros::delay(100);

	//RETRIEVE BALLS FROM CLOSE LEFT MATCH LOADER
	setIntake(MAX_VOLTAGE);
	shake(6, 0.5 * MAX_VOLTAGE, -0.25 * MAX_VOLTAGE, 500, 100);
	setDrive(MAX_VOLTAGE, MAX_VOLTAGE);
	pros::delay(1750);

	//MOVE TOWARDS CENTER
	rotate(90);
	translate(-500);
	setIntake(0);
	setMatchLoadPneumatic(false);
	rotate(0);
	translate(-800);
	
	//MOVE TOWARDS FAR WALL
	rotate(-90); 
	translate(-4000);

	//ALIGN WITH RIGHT LONG GOAL
	rotate(0);
	translate(610); //-600 = TOO CLOSE

	//FACE RIGHT LONG GOAL
	rotate(90);
	pros::delay(100);
	setDrive(-0.5 * MAX_VOLTAGE, -0.5 * MAX_VOLTAGE);
	pros::delay(1000);

	//SCORE ON RIGHT LONG GOAL
	setDescorePneumatic(false);
	setIntake(MAX_VOLTAGE);
	pros::delay(500);
	setIntake(-MAX_VOLTAGE);
	pros::delay(250);
	setIntake(MAX_VOLTAGE);
	pros::delay(3250);

	//ALIGN WITH FAR RIGHT MATCH LOADER
	setDescorePneumatic(true);
	setMatchLoadPneumatic(true);
	rotate(-3);
	setDrive(0.275 * MAX_VOLTAGE, 0.275 * MAX_VOLTAGE);
	pros::delay(1000);

	//RETRIEVE BALLS FROM FAR RIGHT MATCH LOADER
	setDescorePneumatic(true);
	shake(4, 0.5 * MAX_VOLTAGE, -0.25 * MAX_VOLTAGE, 500, 100);
	setDrive(MAX_VOLTAGE, MAX_VOLTAGE);
	pros::delay(1750);

	//ALIGN WITH RIGHT LONG GOAL
	setDrive(-0.4 * MAX_VOLTAGE, -0.4 * MAX_VOLTAGE);
	pros::delay(1500);

	//SCORE ON RIGHT LONG GOAL AGAIN
	setMatchLoadPneumatic(false);
	setDescorePneumatic(false);
	setIntake(MAX_VOLTAGE);
	pros::delay(500);
	setIntake(-MAX_VOLTAGE);
	pros::delay(250);
	setIntake(MAX_VOLTAGE);
	pros::delay(3250);
	
}

void skillsAutonRoute2(){
	//MOVING TOWARDS MATCH LOADER
	translate(1500);

	//ROTATE TOWARDS MATCH LOADER
	rotate(90); 

	//ACTUATE MATCH LOADER PNEUMATIC AND DESCORE PNEUMATIC
	setDescorePneumatic(true);
	setMatchLoadPneumatic(true);
	pros::delay(625);

	//MAKE ROOM FOR MATCH LOADER
	translate(-75, 2);
	pros::delay(100);

	//RETRIEVE BALLS FROM CLOSE RIGHT MATCH LOADER
	setIntake(MAX_VOLTAGE);
	setDrive(0.4 * MAX_VOLTAGE, 0.4 * MAX_VOLTAGE);
	pros::delay(250);
	setDrive(0, 0);
	shake(6, 0.5 * MAX_VOLTAGE, -0.25 * MAX_VOLTAGE, 500, 100);
	setDrive(MAX_VOLTAGE, MAX_VOLTAGE);
	pros::delay(1750);

	//MOVE TOWARDS LEFT LONG GOAL
	rotate(90);
	translate(-900);
	setMatchLoadPneumatic(false);
	rotate(185);
	translate(4250);

	//ALIGN WITH LEFT LONG GOAL
	rotate(90);
	translate(-1000);
	setDrive(-0.35 * MAX_VOLTAGE, -0.35 * MAX_VOLTAGE);
	pros::delay(250);

	//SCORE ON LEFT LONG GOAL
	setDescorePneumatic(false);
	setIntake(-MAX_VOLTAGE); //
	pros::delay(125); //
	setIntake(MAX_VOLTAGE);
	pros::delay(500);
	setIntake(-MAX_VOLTAGE);
	pros::delay(250);
	setIntake(MAX_VOLTAGE);
	pros::delay(3250);

	//MOVE TOWARDS LEFT MATCH LOADER
	rotate(88); //87 = TOO LEFT
	setMatchLoadPneumatic(true);
	translate(1000);
	setDescorePneumatic(true);
	shake(6, 0.5 * MAX_VOLTAGE, -0.25 * MAX_VOLTAGE, 500, 100);

	//ALIGN WITH LEFT LONG GOAL AGAIN
	rotate(90);
	translate(-1000);
	setMatchLoadPneumatic(false);
	setDrive(-0.35 * MAX_VOLTAGE, -0.35 * MAX_VOLTAGE);
	pros::delay(250);

	//SCORE ON LEFT LONG GOAL AGAIN
	setDescorePneumatic(false);
	setIntake(MAX_VOLTAGE);
	pros::delay(500);
	setIntake(-MAX_VOLTAGE);
	pros::delay(250);
	setIntake(MAX_VOLTAGE);
	pros::delay(5000);
	setIntake(0);

	//ALIGN WITH PARKING ZONE
	translate(600);
	rotate(0);
	translate(2250);
	rotate(90);
	setDrive(0.5 * MAX_VOLTAGE, 0.5 * MAX_VOLTAGE);
	pros::delay(500);
	setDrive(0, 0);
	translate(-750);
	setDrive(MAX_VOLTAGE, MAX_VOLTAGE);
	pros::delay(3000);
	setDrive(0, 0);
}

void spinIntakeAuton(){
	pros::delay(1000);
	setSwitcherIntake(0.25 * MAX_VOLTAGE, true, false); 
}

void johnTesting(){
	translateWithDistanceSensor(400);
}

void autonomous() {
	//leftMatchAuton(); //1
	//rightMidMatchAuton(); //2
	//rightNoMidMatchAuton(); //3
	//safeRightMidMatchAuton(); //4
	//skillsAutonRoute1(); // none
	//soloMatchAuton(); none
	//skillsAutonRoute2(); //6
	//spinIntakeAuton(); //7
	johnTesting(); //8
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol(){
	setDriveMotorBrakeType(pros::E_MOTOR_BRAKE_COAST);
	allIntakeMotorGroup.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);

	while (true){
		pros::delay(WHILE_LOOP_DELAY_DURATION);

		//X = DOUBLE PARK EXTENDED / RETRACTED: TOGGLE
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){
			isDoubleParkPneumaticExtended = !isDoubleParkPneumaticExtended;
			setDoubleParkPneumatic(isDoubleParkPneumaticExtended);
		}

		//UP = SWITCHER DIRECTION FORWARD: SEPARATE BUTTON TOGGLE
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)){
			shouldSwitcherSpinFoward = true;
			shouldSwitcherSpinBackward = false;
			if ((isIntakeSpinningForward || isIntakeSpinningBackward)){	
				setSwitcherIntake(MAX_VOLTAGE, shouldSwitcherSpinFoward, shouldSwitcherSpinBackward);
			}
		}

		//DOWN = SWITCHER DIRECTION BACKWARDS: SEPARATE BUTTON TOGGLE
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)){
			shouldSwitcherSpinFoward = false;
			shouldSwitcherSpinBackward = true;
			if (isIntakeSpinningForward || isIntakeSpinningBackward){
				setSwitcherIntake(MAX_VOLTAGE, shouldSwitcherSpinFoward, shouldSwitcherSpinBackward);
			}
		}

		//LEFT = SPIN INTAKE BACKWARDS SLOWER: HELD
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT))
		{
			setUpperLowerIntake(-0.5 * MAX_VOLTAGE);
			setSwitcherIntake(0.5 * MAX_VOLTAGE, false, true);
			isIntakeSpinningForward = false;
			isIntakeSpinningBackward = true;
		}
		if (controller.get_digital_new_release(pros::E_CONTROLLER_DIGITAL_LEFT))
		{
			isIntakeSpinningForward = false;
			isIntakeSpinningBackward = false;
			setIntake(0);
		}

		//RIGHT = SPIN INTAKE BACKWARDS SLOWER: HELD
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT))
		{
			setUpperLowerIntake(-0.5 * MAX_VOLTAGE);
			setSwitcherIntake(0.5 * MAX_VOLTAGE, false, true);
			isIntakeSpinningForward = false;
			isIntakeSpinningBackward = true;
		}
		if (controller.get_digital_new_release(pros::E_CONTROLLER_DIGITAL_RIGHT))
		{
			isIntakeSpinningForward = false;
			isIntakeSpinningBackward = false;
			setIntake(0);
		}

		//L1 = EXTEND / RETRACT DESCORE PNEUMATIC: TOGGLE
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
			isDescorePneumaticExtended = !isDescorePneumaticExtended;
			setDescorePneumatic(isDescorePneumaticExtended);
		}

		//L2 = MATCH LOAD EXTENDED / RETRACTED: TOGGLE
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)){
			isMatchLoadPneumaticExtended = !isMatchLoadPneumaticExtended;
			setMatchLoadPneumatic(isMatchLoadPneumaticExtended);
		}

		//R1 = SPIN INTAKE FORWARDS OR STOP INTAKE: TOGGLE
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){
			if (isIntakeSpinningForward == false){
				isIntakeSpinningForward = true;
				isIntakeSpinningBackward = false;
				setUpperLowerIntake(MAX_VOLTAGE);
				setSwitcherIntake(MAX_VOLTAGE, shouldSwitcherSpinFoward, shouldSwitcherSpinBackward);
			}
			else{
				isIntakeSpinningForward = false;
				isIntakeSpinningBackward = false;
				setIntake(0);
			}
		}

		//R2 = SPIN INTAKE BACKWARDS: HELD
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2))
		{
			setUpperLowerIntake(-MAX_VOLTAGE);
			setSwitcherIntake(MAX_VOLTAGE, false, true);
			isIntakeSpinningForward = false;
			isIntakeSpinningBackward = true;
		}
		if (controller.get_digital_new_release(pros::E_CONTROLLER_DIGITAL_R2))
		{
			isIntakeSpinningForward = false;
			isIntakeSpinningBackward = false;
			setIntake(0);
		}

		setDriveByDriver();
	}
}