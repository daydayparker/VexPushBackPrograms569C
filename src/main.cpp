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



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

 //COLOR: 0 IS BLUE AND 1 IS RED
int color = 1;

void initialize() {
	//PUT AWESOME TEXT ON THE CONTROLLER SCREEN
	controller.print(0, 0, "By: %s", "daydayparker");
	//controller.print(0, 0, "Angle: %f", potentiometer.get_angle());

	//SET MOTOR BRAKE TYPES
	setDriveMotorBrakeType(pros::E_MOTOR_BRAKE_HOLD);
	allIntakeMotorGroup.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);

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
void disabled() {
	
}

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

void autonomous() {
	//leftMatchAuton(); //1
	//rightMidMatchAuton(); //2
	rightNoMidMatchAuton(); //3
	//skillsAutonRoute(); //4
	//johnTesting(); //8
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
	/*
	if (potentiometer.get_value() < 125){
		//BLUE
		color = 0;
	}
	else{
		//RED
		color = 1;
	}
	*/
	
	controller.print(0, 0, (color) ? "red" : "blue");
	pros::Task intakeTask(intakeLoop);

	while (true){
		//controller.print(0,0, "%f", potentiometer.get_value());
		pros::delay(WHILE_LOOP_DELAY_DURATION);

		//A = DOUBLE PARK EXTENDED / RETRACTED: TOGGLE
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)){
			isDoubleParkPneumaticExtended = !isDoubleParkPneumaticExtended;
			isMatchLoadPneumaticExtended = false;
			setDoubleParkPneumatic(isDoubleParkPneumaticExtended);
			setMatchLoadPneumatic(isMatchLoadPneumaticExtended);
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

		setDriveByDriver();
	}
}