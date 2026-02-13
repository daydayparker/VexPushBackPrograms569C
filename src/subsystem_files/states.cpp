#include "main.h"

////STATE-BOOLEANS
//MACRO-BOOLEANS
bool isDescoreMacroRunning = false;
//STATE-TRACKING BOOLEANS
bool isDescorePneumaticExtended = false;
bool isDoubleParkPneumaticExtended = false;
bool isMatchLoadPneumaticExtended = false;
bool isIntakeSpinningForward = false;
bool isIntakeSpinningBackward = false;
bool shouldSwitcherSpinFoward = true;
bool shouldSwitcherSpinBackward = false;