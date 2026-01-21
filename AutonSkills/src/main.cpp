#include "main.h"

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
	//INITIALIZE THE LCD
	pros::lcd::initialize();

	//PUT AWESOME TEXT ON THE CONTROLLER SCREEN
	controller.print(0, 0, "By: %f", "daydayparker");


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
void auton(){
	// exits condition makes it so you dont need delay

	//MOVING TOWARDS MATCH LOADER
	translate(1530); //1520 - 1530
	pros::delay(100);

	//ROTATE TOWARDS MATCH LOADER
	rotate(90); 
	pros::delay(100);

	//ACTUATE MATCH LOADER PNEUMATIC AND DESCORE PNEUMATIC
	setDescorePneumatic(true);
	setMatchLoadPneumatic(true);
	pros::delay(625);

	//MAKE ROOM FOR MATCH LOADER
	translate(-75, 2);
	pros::delay(100);

	//RETRIEVE BALLS FROM CLOSE LEFT MATCH LOADER
	setDriveMotorBrakeType(pros::E_MOTOR_BRAKE_BRAKE);
	setIntake(MAX_VOLTAGE);
	shake(4, 0.33, 500, 333);
	setDrive(MAX_VOLTAGE, MAX_VOLTAGE);
	pros::delay(1750);
	setDriveMotorBrakeType(pros::E_MOTOR_BRAKE_COAST);

	//MOVE TOWARDS RIGHT WALL
	translate(-500);
	setIntake(0);
	setMatchLoadPneumatic(false);
	pros::delay(100);
	rotate(180);
	pros::delay(100);
	translate(-675);
	pros::delay(100);
	
	//MOVE TOWARDS FAR WALL
	rotate(270); 
	pros::delay(100);
	translate(4000);
	pros::delay(250);

	//ALIGN WITH RIGHT LONG GOAL
	rotate(180);
	pros::delay(100);
	translate(547);
	pros::delay(100);
	rotate(270);
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
	setDrive(0.225 * MAX_VOLTAGE, 0.275 * MAX_VOLTAGE);
	pros::delay(500);
	setDescorePneumatic(true);
	setDrive(0.275 * MAX_VOLTAGE, 0.25 * MAX_VOLTAGE);
	pros::delay(1000);

	//RETRIEVE BALLS FROM FAR RIGHT MATCH LOADER
	setDriveMotorBrakeType(pros::E_MOTOR_BRAKE_BRAKE);
	shake(3, 0.33, 500, 333);
	setDrive(MAX_VOLTAGE, MAX_VOLTAGE);
	pros::delay(1750);
	setDriveMotorBrakeType(pros::E_MOTOR_BRAKE_COAST);

	//ALIGN WITH RIGHT LONG GOAL
	setDrive(-0.5 * MAX_VOLTAGE, -0.55 * MAX_VOLTAGE);
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

void autonomous() {
	auton();
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
void opcontrol() {
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