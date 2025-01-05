#include <csignal>
#include "PerceptionTest.hpp"
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
	//	In this case, you cannot use tilt and IMU sensors. 
	//	You can only detect markers from camera.

	//-------hostPC : false-------//
	//	If you want to use this code in BBB, set hostPC to 'false'.
	//	In this case, you can use tilt, IMU, and camera sensors. 
	//  Important!!! If you do not turn off BBB when you connect or disconnect anything, such as Dynamixel and sensors,
	//  your BBB will break down!
	bool hostPC = false;

	//-------Perception setting-------//
	//1. Set the threshold for roll and pitch tilt.
	//   For example, if you want to sense whether roll angle of the robot is 
	//	 either more than x rad or less than -x, and whether pitch angle of the robot is 
	//	 either more than y rad or less than -y, set tiltThres as 'double tiltThres[2] = {x, y};'
	double tiltThres[2] = {0.3, 0.3}; // Range: 0 ~ 1.5
	CPerception perception(hostPC, tiltThres);	// Create perception

	//-------While loop-------//
	// If you want to quit the process, press "ctrl + c"
	while (exitFlag == false) {

		ReadPerception(perception);
		perception.Clear();		// Clear perception
		msleep(100);

	}
	perception.KillPerception();
    return 0;
}

