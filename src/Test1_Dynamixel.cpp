#include <csignal>
#include "DynamixelTest.hpp"
#include "Behavior.hpp"

bool exitFlag = false;

void SigHandler(int signo) {
	// If you press "ctrl + c", this function is activated
	std::cout<<std::endl<<"Terminate process "<<signo<<std::endl;
	exitFlag = true; // If exitFlag becomes true, the "while" loop in main() is terminated
}

int main() {
	signal(SIGINT, SigHandler);	

	//-------hostPC : true-------//
	//	If you want to use this code in Host PC, set hostPC to 'true'.
	//  To use Dynamixel, connect USB2Dynamixel between HostPC and CON2 of BBB cape,
	//  and connect Dynamixel to Con1 of BBB cape.
	//  After that, type 'sudo chmod 777 /dev/ttyUSB*' to Host PC terminal.

	//-------hostPC : false-------//
	//	If you want to use this code in BBB, set hostPC to 'false'.
	//  To use Dynamixel, turn off BBB, connect it to Con3 of BBB cape, and then turn BBB on.
	//  Important!!! If you do not turn off BBB when you connect or disconnect anything, such as Dynamixel and sensors,
	//  your BBB will break down!
	bool hostPC = false;

	//-------Actuator setting-------//
	//1. Set numbers of joint motors and wheel motors
	const int jointNum = 4;
	const int wheelNum = 4;
	int jointID[jointNum];
	int wheelID[wheelNum];
	int jointInitAng[jointNum] = {-89,88,0,89};	// Angle range: -150(deg)~150(deg)

	//2. Set IDs of motors
	//	 	- For n number of joint motors, ID starts from 0 to n-1
	//	 	- For m number of wheel motors, ID starts from n to n+m-1
	//3. Set initial joint angle of joint motors
	/*for (int i=0; i<jointNum; i++) {
		jointID[i] = i;
	}
	for (int i=0; i<wheelNum; i++)
		wheelID[i] = jointNum + i;*/
	//handler
	jointID[0]=0; jointID[1]=1;
	//wheel
        wheelID[0]=2; wheelID[1]=3; wheelID[2]=4; wheelID[3]=5; 
	//pick_ball
	jointID[2]=6; jointID[3]=7;
	//4. Set initial moving speed of joint motors
	int jointSpeed = 10;		// Speed range of joint motor: 0~1023
	CActuator actuator(jointNum, wheelNum, jointID, wheelID, jointInitAng, jointSpeed, hostPC);	// Create actuator
	//actuator.ExeJointSpeed();	// Initialize moving speed of joint motors

	//5. Set the robot to the initial pose
	//actuator.ExeInitAng();
	sleep(1);
	
	/*
	//-------While loop-------//
	// If you want to quit the process, press "ctrl + c"
	while (exitFlag == false) {

	//	BehDynamixelTest(actuator);
		BehDynamixelTest2(actuator);
	}
	actuator.ExeInitAng();
	actuator.ExeStopWheelSpeed();	
	*/
	//go straight

	InitPose(actuator);	
	GoStraight(actuator);
	GoBack(actuator);
	TurnLeft(actuator);
	TurnRight(actuator);
	InitPose(actuator);		

    return 0;
}

