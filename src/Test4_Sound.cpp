#include <csignal>
#include "SoundTest.hpp"
bool exitFlag = false;

void SigHandler(int signo) {
	// If you press "ctrl + c", this function is activated
	std::cout<<std::endl<<"Terminate process "<<signo<<std::endl;
	exitFlag = true; // If exitFlag becomes true, the "while" loop in main() is terminated
}

int main() {
	signal(SIGINT, SigHandler);	
	bool hostPC = false;
	//-------Sound setting-------//
	//1. Store sound files in 'sound' directory
	//2. Write file names in soundFile array. 
	//	 The order becomes the ID of the file.
	//   For example, the IDs of "didntwork.wav", "cool.wav", "doh.wav" are 0, 1, and 2, respectively.	 
	const int numSoundFile = 5;	// Number of sound files. The maximum file number is set to 30.
	std::string soundFile[numSoundFile] = {"hellobaby.wav", "adios.wav", "danger.wav", "camera.wav", "doh.wav"};	// Sound file list
	CSound sound(numSoundFile, soundFile);		// Create sound

	//-------While loop-------//
	// If you want to quit the process, press "ctrl + c"
	while (exitFlag == false && hostPC == false) {

		SoundTest(sound);				

	}
	sound.KillSound();

    return 0;
}

