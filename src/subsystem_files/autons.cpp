#include "main.h"

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
	setSwitcherIntake(-0.4 * MAX_VOLTAGE);
	pros::delay(1250); //2000 

	//ALIGN WITH MATCH LOADER
	rotate(-130);

	//CONTINUE ALIGNING WITH MATCH LOADER
	setSwitcherIntake(-MAX_VOLTAGE);
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

void skillsAutonRoute(){

	//MOVING TOWARDS MATCH LOADER
	translate(1500);

	//ROTATE TOWARDS MATCH LOADER
	rotate(90); 

	//ACTUATE MATCH LOADER PNEUMATIC AND DESCORE PNEUMATIC
	setDescorePneumatic(true);
	setMatchLoadPneumatic(true);
	pros::delay(625);

	//MAKE ROOM FOR MATCH LOADER
	translate(-75);
	pros::delay(100);

	//RETRIEVE BALLS FROM CLOSE RIGHT MATCH LOADER
	//SCORING!!!!!!!!!
	setIntake(MAX_VOLTAGE);
	setDrive(0.3 * MAX_VOLTAGE, 0.3 * MAX_VOLTAGE);
	pros::delay(1000);
	setDrive(0, 0);
	pros::delay(1000);
	shake(3, MAX_VOLTAGE, 0, 250, 750);

	//MOVE TOWARDS LEFT LONG GOAL
	rotate(90);
	translate(-700);
	setMatchLoadPneumatic(false);
	rotate(3); //0: offset because curve
	setUpperLowerIntake(0);
	pros::delay(250);
	setSwitcherIntake(0);
	translate(-4625, false, 0.06, 0, 0.025, 0); ///////////////////////////////////////////////////////////////////////////////////// 4500 - 4750
	pros::delay(500);

 	//ALIGN WITH LEFT LONG GOAL
	rotate(90);
	translate(-1000);
	setDrive(-MAX_VOLTAGE, -MAX_VOLTAGE);
	pros::delay(500);

	//SCORE ON LEFT LONG GOAL
	setDescorePneumatic(false);
	setIntake(-MAX_VOLTAGE); //
	pros::delay(125); //
	setIntake(MAX_VOLTAGE);
	pros::delay(500);
	setIntake(-MAX_VOLTAGE);
	pros::delay(250);
	setIntake(MAX_VOLTAGE);
	pros::delay(2500);
	setIntake(-MAX_VOLTAGE);
	pros::delay(250);
	setIntake(MAX_VOLTAGE);
	pros::delay(3000);

	//MOVE TOWARDS LEFT MATCH LOADER
	rotate(87);//BECAUSE FIELDS ARE SLIGHTLY OFF
	setMatchLoadPneumatic(true);
	translate(1000);
	setDescorePneumatic(true);
	//SCORING!!!!!!!!!
	setDrive(0.3 * MAX_VOLTAGE, 0.3 * MAX_VOLTAGE);
	pros::delay(1000);
	setDrive(0, 0);
	pros::delay(1000);
	shake(3, MAX_VOLTAGE, 0, 250, 750);

	//ALIGN WITH LEFT LONG GOAL AGAIN
	rotate(87);//BECAUSE FIELDS ARE SLIGHTLY OFF
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
	pros::delay(2500);
	setIntake(-MAX_VOLTAGE);
	pros::delay(250);
	setIntake(MAX_VOLTAGE);
	pros::delay(3000);

	//ALIGN WITH PARKING ZONE
	translate(600);
	rotate(0);
	translate(500);
	rotate(45);
	translate(1500);
	rotate(20);
	setMatchLoadPneumatic(true);
	pros::delay(250);
	setIntake(-MAX_VOLTAGE);
	setDrive(MAX_VOLTAGE, MAX_VOLTAGE);
	pros::delay(700); // 800
	setDrive(0, 0);
	setMatchLoadPneumatic(false);
	pros::delay(1000);
	setDescorePneumatic(true);
	setIntake(MAX_VOLTAGE);
	
	/*
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
	*/
}

void spinIntakeAuton(){
	pros::delay(1000);
	setSwitcherIntake(0.25 * MAX_VOLTAGE); 
}

void johnTesting(){
	translate(2000);
}