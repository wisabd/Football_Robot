#pragma once
#include "Actuator.hpp"

void BehDynamixelTest(CActuator& actuator) {	
// Phase 1: 
	//	-Move joint motor_0 (ID=0) to 60 deg with 100 speed
	//	-Move joint motor_1 (ID=1) to 60 deg with 200 speed
	//  -Rotate wheel motor_0 (ID=2) to 300 speed				
	// Joint motors
	actuator.joint[0].SetAng(60);		// Angle range: -150(deg)~150(deg)
	actuator.joint[0].SetSpeed(100);	// Speed range of joint motor: 0~1023
	actuator.joint[1].SetAng(60);
	actuator.joint[1].SetSpeed(200);
	// Wheel motor 
	actuator.wheel[0].SetSpeed(300);	// Speed range of wheel motor: -1023~1023
	// Execute motors
	actuator.ExeJointSpeed();			// Execute joint motor speed
    actuator.ExeAng();					// Execute joint motor to move target angle
	actuator.ExeWheelSpeed();			// Execute wheel motor to rotate target speed
    sleep(3);							// Wait for 3 seconds

// Phase 2: 
	//	-Move joint motor_0 (ID=0) to -60 deg with 100 speed
	//	-Move joint motor_1 (ID=1) to -60 deg with 200 speed
	//  -Rotate wheel motor_0 (ID=2) to -300 speed				

	// Joint motors
	actuator.joint[0].SetAng(-60);		// Angle range: -150(deg)~150(deg)
	actuator.joint[0].SetSpeed(100);	// Speed range of joint motor: 0~1023
	actuator.joint[1].SetAng(-60);
	actuator.joint[1].SetSpeed(200);
	// Wheel motor 
	actuator.wheel[0].SetSpeed(-300);	// Speed range of wheel motor: -1023~1023
	// Execute motors
	actuator.ExeJointSpeed();			// Execute joint motor speed
    actuator.ExeAng();					// Execute joint motor to move target angle
	actuator.ExeWheelSpeed();			// Execute wheel motor to rotate target speed
    sleep(3);							// Wait for 3 seconds
}

void BehDynamixelTest2(CActuator& actuator) {		
	for (int i=0; i<2; i++) {
		// Set sign (+, -)
		int sign = 1;
		if (i == 0)
			sign = 1;
		else if (i == 1)
			sign = -1;

		// Joint motors
		actuator.joint[0].SetAng(sign * 60);	// Angle range: -150(deg)~150(deg)
		actuator.joint[0].SetSpeed(100);		// Speed range of joint motor: 0~1023
		actuator.joint[1].SetAng(sign * 60);
		actuator.joint[1].SetSpeed(200);
		// Wheel motor 
		actuator.wheel[0].SetSpeed(sign * 300);	// Speed range of wheel motor: -1023~1023

		// Execute motors
		actuator.ExeJointSpeed();			// Execute joint motor speed
		actuator.ExeAng();					// Execute joint motor to move target angle
		actuator.ExeWheelSpeed();			// Execute wheel motor to rotate target speed
		sleep(3);							// Wait for 3 seconds
	}
}

