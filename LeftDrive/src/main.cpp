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
void leftMatchAuton(){
	//MAKE SURE BALLS DO NOT FALL OUT
	setDescorePneumatic(true);

	//COLLECT THREE RED BALLS FROM MIDDLE AREA
	translate(675);
	rotate(-45);
	setIntake(MAX_VOLTAGE);
	translate(860, 0.05);

	//ALIGN WITH TOP CENTER GOAL
	rotate(-135);
	translate(-1035); //-1100

	//SCORE ON TOP CENTER GOAL
	setIntake(0.5 * MAX_VOLTAGE);
	setDescorePneumatic(false);
	pros::delay(550);
	setIntake(0);
	setDescorePneumatic(true);
	pros::delay(250);

	//ALIGN WITH MATCH LOADER
	rotate(-130);
	translate(2330); //2330 - 2355
	rotate(-180);
	setMatchLoadPneumatic(true);

	//MAKE SURE BALLS DO NOT GET STUCK
	setIntake(-MAX_VOLTAGE);
	pros::delay(125);
	setIntake(MAX_VOLTAGE);
	pros::delay(125);

	//RETRIEVE THREE RED BALLS FROM MATCH LOADER
	setDrive(0.4 * MAX_VOLTAGE, 0.4 * MAX_VOLTAGE);
	pros::delay(1000);
	shake(1, 0.5, 500, 250);

	//ALIGN WITH MATCH LOADER
	setDrive(-0.75 * MAX_VOLTAGE, -0.75 * MAX_VOLTAGE);
	pros::delay(500);

	//SCORE ON MATCH LOADER
	setDescorePneumatic(false);
	pros::delay(1000);

	//UNSTUCK BALLS IF BALLS ARE STUCK
	setIntake(-MAX_VOLTAGE);
	pros::delay(125);

	//CONTINUE SCORING ON MATCH LOADER
	setIntake(MAX_VOLTAGE);
	pros::delay(1000);
	
	//WINGS UP FOR DEFENSE
	setDescorePneumatic(true);
}

void autonomous() {
	leftMatchAuton();
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