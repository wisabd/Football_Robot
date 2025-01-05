#include <csignal>
#include "ServoTest.hpp"
bool exitFlag = false;

void SigHandler(int signo) {
	// If you press "ctrl + c", this function is activated
	std::cout<<std::endl<<"Terminate process "<<signo<<std::endl;
	exitFlag = true; // If exitFlag becomes true, the "while" loop in main() is terminated
}

int main() {
	signal(SIGINT, SigHandler);	
	bool hostPC = false;

	//-------Actuator setting-------//
	//1. Set numbers of joint motors and wheel motors
	CActuator actuator(hostPC);	// Create actuator

	//-------While loop-------//
	// If you want to quit the process, press "ctrl + c"
	while (exitFlag == false) {
		
		BehServoTest(actuator);

	}

    return 0;
}

