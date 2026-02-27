#include "main.h"

void leftMatchAuton(){
descorePneumatic.set_value(true);

    //COLLECT THREE RED BALLS FROM MIDDLE AREA AND PUT MATCH LOADER DOWN
    translate(675);
    rotate(-45);
    intakeMotor.move(MAX_VOLTAGE);
    matchLoadPneumatic.set_value(true);
    translate(790);

    //ALIGN WITH UPPER MIDDLE GOAL
    rotate(-135); 
    pros::delay(200);
    hoodPneumatic.set_value(true);
    matchLoadPneumatic.set_value(false);
    translate(-725); //500 - 600 = :
    intakeMotor.move(MAX_VOLTAGE);
    leverMotor.move(0.5 * MAX_VOLTAGE);
    pros::delay(900);

    //SCORE ON UPPER MIDDLE GOAL
    intakeMotor.move(0);
    leverMotor.move(-MAX_VOLTAGE);

    //DRIVE OVER TO MATCH LOADER
    leverPneumatic.set_value(true);
    translate(2280); //-2000
    rotate(-180); //NOTE: could be -178
    hoodPneumatic.set_value(false);

    //ALIGN WITH MATCH LOADER
    translate(-100);
    matchLoadPneumatic.set_value(true);
    pros::delay(250);

    //MAKE SURE BALLS DO NOT GET STUCK 
    intakeMotor.move(-MAX_VOLTAGE);
    pros::delay(200); //400
    intakeMotor.move(MAX_VOLTAGE);
    leverMotor.move(0);

    //RETRIEVE THREE RED BALLS FROM MATCH LOADER
    setDrive(0.4 * MAX_VOLTAGE, 0.4 * MAX_VOLTAGE);
    pros::delay(150); 
    shake(3, MAX_VOLTAGE * 0.5, -MAX_VOLTAGE * 0.25, 325, 75); //400 on forward
    rotate(-181); //-180

    //OPEN HOOD AND LIFT MECH
    hoodPneumatic.set_value(true);
    pros::delay(200);

    //ALIGN WITH LONG GOAL
    matchLoadPneumatic.set_value(false);
    setDrive(-0.475 * MAX_VOLTAGE, -0.475 * MAX_VOLTAGE);
    pros::delay(700);

    //SCORE ON LONG GOAL
    intakeMotor.move(MAX_VOLTAGE);
    leverMotor.move(MAX_VOLTAGE);
    pros::delay(600);

    //STOP MOVING AND STOP INTAKE
    setDrive(0,0);
    intakeMotor.move(0);

    //REALIGN AND DISABLE DESCORE
    rotate(-180);
    leverMotor.move(0);

    //DESCORE AND LEVER ARM DOWN
    translate(600);
    rotate(-135);
    leverMotor.move(-MAX_VOLTAGE);
    translate(-765); //-750
    rotate(-180);
    leverMotor.move(0);
    descorePneumatic.set_value(false);
    translate(-1000); //-1250
    rotate(-150);
}

void rightMatchAuton(){
    descorePneumatic.set_value(true);
    leverPneumatic.set_value(true);

    //COLLECT THREE RED BALLS FROM MIDDLE AREA AND PUT MATCH LOADER DOWN
    translate(675);
    rotate(45);
    intakeMotor.move(MAX_VOLTAGE);
    matchLoadPneumatic.set_value(true);
    translate(777);

    //ALIGN WITH BOTTOM MIDDLE GOAL
    rotate(-45); //-41 
    pros::delay(200);
    matchLoadPneumatic.set_value(false);
    translate(700); //500 - 600 = :
    intakeMotor.move(-0.9 * MAX_VOLTAGE);
    pros::delay(900);

    //SCORE ON BOTTOM MIDDLE GOAL
    intakeMotor.move(0);

    //DRIVE OVER TO MATCH LOADER
    translate(-2150); //-2000
    rotate(-180); //NOTE: could be -178

    //ALIGN WITH MATCH LOADER
    translate(-100);
    matchLoadPneumatic.set_value(true);
    pros::delay(250);

    //MAKE SURE BALLS DO NOT GET STUCK 
    intakeMotor.move(-MAX_VOLTAGE);
    pros::delay(300); //400
    intakeMotor.move(MAX_VOLTAGE);

    //RETRIEVE THREE RED BALLS FROM MATCH LOADER
    setDrive(0.4 * MAX_VOLTAGE, 0.4 * MAX_VOLTAGE);
    pros::delay(600); 
    shake(3, MAX_VOLTAGE * 0.5, -MAX_VOLTAGE * 0.25, 325, 75); //400 on forward
    rotate(-179); //-180

    //OPEN HOOD AND LIFT MECH
    hoodPneumatic.set_value(true);
    pros::delay(200);

    //ALIGN WITH LONG GOAL
    matchLoadPneumatic.set_value(false);
    setDrive(-0.475 * MAX_VOLTAGE, -0.475 * MAX_VOLTAGE);
    pros::delay(700);

    //SCORE ON LONG GOAL
    intakeMotor.move(MAX_VOLTAGE);
    leverMotor.move(MAX_VOLTAGE);
    pros::delay(500);

    //STOP MOVING AND STOP INTAKE
    setDrive(0,0);
    intakeMotor.move(0);

    //REALIGN
    rotate(-180);
    leverMotor.move(0);

    //DESCORE AND LEVER ARM DOWN
    translate(600);
    rotate(-135);
    leverMotor.move(-MAX_VOLTAGE);
    translate(-725); //-750
    rotate(-180);
    leverMotor.move(0);
    descorePneumatic.set_value(false); 
    translate(-1000); //-1250
    rotate(-150);
}

void soloMatchAuton(){

}

void skillsAuton(){
    descorePneumatic.set_value(true);

    //COLLECT ONE RED FROM MIDDLE AREA
    translate(675);
    rotate(-45);
    intakeMotor.move(MAX_VOLTAGE);
    translate(790);

    //ALIGN WITH UPPER MIDDLE GOAL
    rotate(-135); 
    pros::delay(200);
    hoodPneumatic.set_value(true);
    translate(-800); //500 - 600 = :
    intakeMotor.move(MAX_VOLTAGE);
    leverMotor.move(0.5 * MAX_VOLTAGE);
    pros::delay(900);

    //SCORE ON UPPER MIDDLE GOAL
    intakeMotor.move(0);
    leverMotor.move(-MAX_VOLTAGE);

    //DRIVE OVER TO MATCH LOADER
    leverPneumatic.set_value(true);
    translate(2220); //-2000
    rotate(-180, 4.5); //NOTE: could be -178
    hoodPneumatic.set_value(false);

    //ALIGN WITH MATCH LOADER
    translate(-100);
    matchLoadPneumatic.set_value(true);
    pros::delay(550);

    //MAKE SURE BALLS DO NOT GET STUCK 
    intakeMotor.move(-MAX_VOLTAGE);
    pros::delay(200); //400
    intakeMotor.move(MAX_VOLTAGE);

    //RETRIEVE ALL BALLS FROM MATCH LOADER
    setDrive(0.3 * MAX_VOLTAGE, 0.3 * MAX_VOLTAGE);
    pros::delay(1700); 
    shake(3, MAX_VOLTAGE * 0.5, -MAX_VOLTAGE * 0.25, 325, 75); //400 on forward
    rotate(-181); //-180
    leverMotor.move(0);

    //MATCHLOADER UP AND LEAVE MATCHLOADER AREA
    matchLoadPneumatic.set_value(false);
    translate(-500);

    //DRIVE PAST LONG GOAL
    rotate(-225);
    translate(-850); //-750
    rotate(-180);
    translate(-3500); //-1250

    //ALIGN WITH FIRST LONG GOAL
    rotate(-90, 3.5);
    translate(-580); //-550 HEREHEREHEREHERHERHERHERHERER
    rotate(0);
    setDrive(-0.55 * MAX_VOLTAGE, -0.55 * MAX_VOLTAGE);
    hoodPneumatic.set_value(true);
    pros::delay(900);

    //SCORE ON LONG GOAL
    intakeMotor.move(MAX_VOLTAGE);
    leverMotor.move(0.65 * MAX_VOLTAGE); 
    pros::delay(800);
    intakeMotor.move(-MAX_VOLTAGE);
    leverMotor.move(-MAX_VOLTAGE);
    rotate(0);
    hoodPneumatic.set_value(false);
    translate(700);

    //ALIGN WITH MATCH LOADER
    translate(-100);
    matchLoadPneumatic.set_value(true);
    pros::delay(350);

    //MAKE SURE BALLS DO NOT GET STUCK 
    intakeMotor.move(-MAX_VOLTAGE);
    pros::delay(200); //400
    intakeMotor.move(MAX_VOLTAGE);

    //RETRIEVE ALL BALLS FROM MATCH LOADER
    setDrive(0.3 * MAX_VOLTAGE, 0.3 * MAX_VOLTAGE);
    pros::delay(1700); 
    shake(3, MAX_VOLTAGE * 0.5, -MAX_VOLTAGE * 0.25, 375, 100); //400 on forward
    rotate(3);
    leverMotor.move(0);

    //ALIGN WITH LONG GOAL
    matchLoadPneumatic.set_value(false);
    setDrive(-0.55 * MAX_VOLTAGE, -0.55 * MAX_VOLTAGE);
    pros::delay(750);

    //SCORE ON LONG GOAL
    hoodPneumatic.set_value(true);
    leverMotor.move(0.65 * MAX_VOLTAGE);
    pros::delay(800);
    leverMotor.move(-MAX_VOLTAGE);

    //REALIGN
    intakeMotor.move(0);
    rotate(0);
    hoodPneumatic.set_value(false);

    //EXIT LONG GOAL
    translate(300);

    //TURN TO APPROACH WALL
    rotate(30);

    //APPROACH WALL
    translate(1400); //1300

    //TURNING MORE PARALLEL TO THE WALL
    rotate(75);

    //APPROACH PARK ZONE
    translate(750);

    //ALIGN WITH PARK ZONE
    setDrive(0.3 * MAX_VOLTAGE, 0.3 * MAX_VOLTAGE);
    pros::delay(500);
    setDrive(0,0);

    //BACK UP FROM PARK ZONE
    translate(-200);

    //GET BLOCKS FROM PARK ZONE
    intakeMotor.move(MAX_VOLTAGE);
    setDrive(0.40 * MAX_VOLTAGE, 0.45 * MAX_VOLTAGE); //0.40, 0.45
    pros::delay(1250);
    setDrive(0.50 * MAX_VOLTAGE, 0.50 * MAX_VOLTAGE); //0.4, 0.4
    pros::delay(1000);
    setDrive(0,0);
    pros::delay(250);
    leverMotor.move(0);

    //RESET ANGLE WITH PARK ZONE
    rotate(77); //77
    setDrive(-0.275 * MAX_VOLTAGE, -0.275 * MAX_VOLTAGE);
    pros::delay(1300); //1000
    setDrive(0,0);
    pros::delay(250);
    
    //DRIVE OVER TO MATCH LOADER
    translate(500);
    rotate(120); 
    translate(1000);
    rotate(0);

    /*
    //ALIGN WITH TOP MIDDLE GOAL
    leverPneumatic.set_value(false);
    translate(500);
    rotate(0);
    translate(-1580); //-2000
    rotate(45);

    //SCORE ON TOP MIDDLE GOAL
    hoodPneumatic.set_value(true);
    translate(-875); //-900
    leverMotor.move(MAX_VOLTAGE);
    pros::delay(150);
    leverMotor.move(0.25 * MAX_VOLTAGE); //0.5
    pros::delay(1200);

    ////////
    ///////
    //DRIVE OVER TO MATCH LOADER
    leverPneumatic.set_value(true);
    leverMotor.move(-MAX_VOLTAGE);
    translate(2150); //-2010
    rotate(-1); //NOTE: could be -178
    hoodPneumatic.set_value(false);
    */

    //ALIGN WITH MATCH LOADER
    translate(-100);
    matchLoadPneumatic.set_value(true);
    pros::delay(350);

    //MAKE SURE BALLS DO NOT GET STUCK c
    intakeMotor.move(-MAX_VOLTAGE);
    pros::delay(200); //400
    intakeMotor.move(MAX_VOLTAGE);

    //RETRIEVE ALL BALLS FROM MATCH LOADER
    setDrive(0.3 * MAX_VOLTAGE, 0.3 * MAX_VOLTAGE);
    pros::delay(1500); 
    shake(3, MAX_VOLTAGE * 0.5, -MAX_VOLTAGE * 0.25, 375, 100); //400 on forward
    leverMotor.move(0);

    //MATCHLOADER UP AND LEAVE MATCHLOADER AREA
    matchLoadPneumatic.set_value(false);
    translate(-500);

    //DRIVE PAST LONG GOAL
    rotate(-45);
    translate(-850); //-750
    rotate(0);
    translate(-3500); //-1250

    //ALIGN WITH FIRST LONG GOAL
    rotate(90, 3.5);
    translate(-575); //-550 HEREHEREHEREHERHERHERHERHERER
    rotate(180);
    setDrive(-0.55 * MAX_VOLTAGE, -0.55 * MAX_VOLTAGE);
    hoodPneumatic.set_value(true);
    pros::delay(700);

    //SCORE ON LONG GOAL
    hoodPneumatic.set_value(true);
    leverMotor.move(0.65 * MAX_VOLTAGE);
    pros::delay(800);
    leverMotor.move(-MAX_VOLTAGE);

    //ALIGN WITH MATCH LOADER
    translate(-100);
    matchLoadPneumatic.set_value(true);
    pros::delay(350);

    //MAKE SURE BALLS DO NOT GET STUCK 
    intakeMotor.move(-MAX_VOLTAGE);
    pros::delay(200); //400
    intakeMotor.move(MAX_VOLTAGE);

    //RETRIEVE ALL BALLS FROM MATCH LOADER
    setDrive(0.3 * MAX_VOLTAGE, 0.3 * MAX_VOLTAGE);
    pros::delay(1500); 
    shake(3, MAX_VOLTAGE * 0.5, -MAX_VOLTAGE * 0.25, 375, 100); //400 on forward
    rotate(183);
    leverMotor.move(0);

    //ALIGN WITH LONG GOAL
    matchLoadPneumatic.set_value(false);
    setDrive(-0.55 * MAX_VOLTAGE, -0.55 * MAX_VOLTAGE);
    pros::delay(750);

    //SCORE ON LONG GOAL
    hoodPneumatic.set_value(true);
    leverMotor.move(0.7 * MAX_VOLTAGE);
    pros::delay(800);
    leverMotor.move(-MAX_VOLTAGE);

    //REALIGN
    intakeMotor.move(0);
    rotate(180);
    hoodPneumatic.set_value(false);

    //EXIT LONG GOAL
    translate(300);

    //TURN TO APPROACH WALL
    rotate(210);

    //APPROACH WALL
    translate(1400); //1300

    //TURNING MORE PARALLEL TO THE WALL
    rotate(255);

    //APPROACH PARK ZONE
    translate(750);

    //ALIGN WITH PARK ZONE
    setDrive(0.3 * MAX_VOLTAGE, 0.3 * MAX_VOLTAGE);
    pros::delay(500);
    setDrive(0,0);

    //BACK UP FROM PARK ZONE
    translate(-200);

    //GET BLOCKS FROM PARK ZONE
    intakeMotor.move(-MAX_VOLTAGE);
    setDrive(0.40 * MAX_VOLTAGE, 0.45 * MAX_VOLTAGE); //0.40, 0.45
    pros::delay(1250);
    setDrive(0.50 * MAX_VOLTAGE, 0.50 * MAX_VOLTAGE); //0.4, 0.4
    pros::delay(100);
    setDrive(0,0);
    pros::delay(250);
    leverMotor.move(0);
}

void janeTesting(){
    leverPneumatic.set_value(true);
    pros::delay(500);
    setDrive(-0.25 * MAX_VOLTAGE, -0.25 * MAX_VOLTAGE);
    pros::delay(500);
    setDrive(0,0);
    pros::delay(500);

    //BEGINGS HERE
    //EXIT LONG GOAL
    translate(300);

    //TURN TO APPROACH WALL
    rotate(30);

    //APPROACH WALL
    translate(1400); //1300

    //TURNING MORE PARALLEL TO THE WALL
    rotate(75);

    //APPROACH PARK ZONE
    translate(750);

    //ALIGN WITH PARK ZONE
    setDrive(0.3 * MAX_VOLTAGE, 0.3 * MAX_VOLTAGE);
    pros::delay(500);
    setDrive(0,0);

    //BACK UP FROM PARK ZONE
    translate(-200);

    //GET BLOCKS FROM PARK ZONE
    intakeMotor.move(MAX_VOLTAGE);
    setDrive(0.40 * MAX_VOLTAGE, 0.45 * MAX_VOLTAGE); //0.40, 0.45
    pros::delay(1250);
    setDrive(0.50 * MAX_VOLTAGE, 0.50 * MAX_VOLTAGE); //0.4, 0.4
    pros::delay(1000);
    setDrive(0,0);
    pros::delay(250);

    //RESET ANGLE WITH PARK ZONE
    rotate(80); //77
    setDrive(-0.275 * MAX_VOLTAGE, -0.275 * MAX_VOLTAGE);
    pros::delay(1300); //1000
    setDrive(0,0);
    pros::delay(250);
    
    //ALIGN WITH TOP MIDDLE GOAL
    leverPneumatic.set_value(false);
    translate(300);
    rotate(92);
    translate(200);
    rotate(0);
    translate(-1775); //-2000
    rotate(45);

    //SCORE ON TOP MIDDLE GOAL
    hoodPneumatic.set_value(true);
    translate(-825); //-900
    leverMotor.move(MAX_VOLTAGE);
    pros::delay(150);
    leverMotor.move(0.25 * MAX_VOLTAGE); //0.5
    pros::delay(1200);

    ////////
    ///////
    //DRIVE OVER TO MATCH LOADER
    leverPneumatic.set_value(true);
    leverMotor.move(-MAX_VOLTAGE);
    translate(2010); //-2000
    rotate(-1); //NOTE: could be -178
    hoodPneumatic.set_value(false);

    //ALIGN WITH MATCH LOADER
    translate(-100);
    matchLoadPneumatic.set_value(true);
    pros::delay(250);
    leverMotor.move(0);

    //MAKE SURE BALLS DO NOT GET STUCK 
    intakeMotor.move(-MAX_VOLTAGE);
    pros::delay(200); //400
    intakeMotor.move(MAX_VOLTAGE);

    //RETRIEVE ALL BALLS FROM MATCH LOADER
    setDrive(0.4 * MAX_VOLTAGE, 0.4 * MAX_VOLTAGE);
    pros::delay(1200); 
    shake(3, MAX_VOLTAGE * 0.5, -MAX_VOLTAGE * 0.25, 325, 75); //400 on forward

    //OPEN HOOD AND LIFT MECH
    hoodPneumatic.set_value(true);
    pros::delay(200);



    
    //ALIGN WITH LONG GOAL
    matchLoadPneumatic.set_value(false);
    setDrive(-0.475 * MAX_VOLTAGE, -0.475 * MAX_VOLTAGE);
    pros::delay(700);

    //SCORE ON LONG GOAL
    intakeMotor.move(MAX_VOLTAGE);
    leverMotor.move(MAX_VOLTAGE);
    pros::delay(600);

    //STOP MOVING AND STOP INTAKE
    setDrive(0,0);
    intakeMotor.move(0);

    //REALIGN AND DISABLE DESCORE
    rotate(-180);
    leverMotor.move(0);

    //DESCORE AND LEVER ARM DOWN
    translate(600);
    rotate(-135);
    leverMotor.move(-MAX_VOLTAGE);
    translate(-765); //-750
    rotate(-180);
    leverMotor.move(0);
    descorePneumatic.set_value(false);
    translate(-1000); //-1250
    rotate(-150);
}