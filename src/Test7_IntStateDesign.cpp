#include <csignal>
#include "Behavior.hpp"
bool exitFlag = false;

void SigHandler(int signo) {
	// If you press "ctrl + c", this function is activated
	std::cout<<std::endl<<"Terminate process "<<signo<<std::endl;
	exitFlag = true; // If exitFlag becomes true, the "while" loop in main() is terminated
}

void TerimateProcess(CSound& sound, CPerception& perception, CActuator& actuator) {
	sound.KillSound();
	perception.KillPerception();
	InitPose(actuator);
	actuator.ExeStopWheelSpeed();	
	std::cout<<"End Main"<<std::endl;	
}

int main() {
	signal(SIGINT, SigHandler);	

	//-------hostPC : true-------//
	//	If you want to use this code in Host PC, set hostPC to 'true'.
	//	In this case, you cannot use tilt and IMU sensors. 
	//	You can only detect markers from camera.
	//  To use Dynamixel, connect USB2Dynamixel between HostPC and CON2 of BBB cape,
	//  and connect Dynamixel to Con1 of BBB cape.
	//  After that, type 'sudo chmod 777 /dev/ttyUSB*' to Host PC terminal.

	//-------hostPC : false-------//
	//	If you want to use this code in BBB, set hostPC to 'false'.
	//	In this case, you can use tilt, IMU, and camera sensors. 
	//  To use Dynamixel, turn off BBB, connect it to Con3 of BBB cape, and then turn BBB on.
	//  Important!!! If you do not turn off BBB when you connect or disconnect anything, such as Dynamixel and sensors,
	//  your BBB will break down!
	bool hostPC = false;

	//-------Sound setting-------//
	//1. Store sound files in 'sound' directory
	//2. Write file names in soundFile array. 
	//	 The order becomes the ID of the file.
	//   For example, the IDs of "didntwork.wav", "cool.wav", "doh.wav" are 0, 1, and 2, respectively.	 
	const int numSoundFile = 5;	// Number of sound files. The maximum file number is set to 30.
	std::string soundFile[numSoundFile] = {"hellobaby.wav","doh.wav", "adios.wav", "danger.wav", "camera.wav"};	// Sound file list
	CSound sound(numSoundFile, soundFile);		// Create sound

	//-------Perception setting-------//
	//1. Set the threshold for roll and pitch tilt.
	//   For example, if you want to sense whether roll angle of the robot is 
	//	 either more than x rad or less than -x, and whether pitch angle of the robot is 
	//	 either more than y rad or less than -y, set tiltThres as 'double tiltThres[2] = {x, y};'
	double tiltThres[2] = {0.1, 0.1};
	CPerception perception(hostPC, tiltThres);	// Create perception

	//-------Internal state setting-------//
	//  In this code, emotion, i.e., happy, fear, sad, angry, is defined as the internal state of the robot
	//  You can design your robot's internal state
	//  Set thresholds of emotion
	unsigned int happyTH = 20;
	unsigned int angryTH = 20;
	unsigned int fearTH = 20;
	unsigned int sadTH = 20;
	unsigned int shootTH = 20;
	CInternalState emotion(happyTH, angryTH, fearTH, sadTH, shootTH);	// Create internal state

	//-------Actuator setting-------//
	//1. Set numbers of joint motors and wheel motors
	const int jointNum = 4;
	const int wheelNum = 4;
	int jointID[jointNum];
	int wheelID[wheelNum];
	int jointInitAng[jointNum] = {-89, 88, 0, 89};
	//2. Set IDs of motors
	//	 	- For n number of joint motors, ID starts from 0 to n-1
	//	 	- For m number of wheel motors, ID starts from n to n+m-1
	//3. Set initial joint angle of joint motors
	jointID[0] = 0; jointID[1] = 1;

	wheelID[0] = 2; wheelID[1] = 3; wheelID [2] = 4; wheelID[3] = 5;

jointID[2] = 6; jointID[3] = 7;
	//4. Set initial moving speed of joint motors
	int jointSpeed = 50;
	CActuator actuator(jointNum, wheelNum, jointID, wheelID, jointInitAng, jointSpeed, hostPC);	// Create actuator
	actuator.ExeJointSpeed();	// Initialize moving speed of joint motors
	//5. Set the robot to the initial pose
	actuator.ExeInitAng();
	sleep(1);

	//-------While loop-------//
	// If you want to quit the process, press "ctrl + c"
	while (exitFlag == false) {

		//1. Perception reading
		perception.ReadPerception();
		//2. Internal state generation
		emotion.UpdateIntState(perception);
		//3. Behavior selection
		BehSelFromIntState(sound, emotion, actuator, perception);		
		//4. Clear perception
		perception.Clear();

		msleep(100);
	}
	//4. Terminate process
	TerimateProcess(sound, perception, actuator);	
    return 0;
}

