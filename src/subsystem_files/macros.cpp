#include "main.h"


void descoreMacro(){
	isDescoreMacroRunning = true;
    double initialAngle = inertialSensor.get_rotation();
	int basisAngle = std::round(initialAngle / 180) * 180;
	rotate(basisAngle, isDescoreMacroRunning);
	translate(600, isDescoreMacroRunning);
	rotate(basisAngle - 45, isDescoreMacroRunning);
	translate(-725, isDescoreMacroRunning);
	rotate(basisAngle, isDescoreMacroRunning);
	translate(-700, isDescoreMacroRunning);
	isDescoreMacroRunning = false;
}