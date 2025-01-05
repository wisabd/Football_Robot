#pragma once
#include "Actuator.hpp"

void BehServoTest(CActuator& actuator) {	
// Phase 1: 
	//	-Move servo_0 to 0 deg
	//	-Move servo_1 to 0 deg
	actuator.ServoSetAng(0, 0);
	actuator.ServoSetAng(1, 0);	
	sleep(1);					// Wait for 1 sec
// Phase 2: 
	//	-Move servo_0 to 90 deg
	//	-Move servo_1 to 180 deg
	actuator.ServoSetAng(0, 90);
	actuator.ServoSetAng(1, 180);	
	sleep(1);					// Wait for 1 sec
}

