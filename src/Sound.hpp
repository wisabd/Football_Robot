#pragma once
#include <iostream>
#include <ctime>
#include <boost/scoped_ptr.hpp>
#include <boost/thread.hpp>
#define maxSoundFile 30

class CSound {
private:
	int numSound;
	int soundID;
	bool exitFlag;
	boost::scoped_ptr<boost::thread> soundThread;
	std::string fileName[maxSoundFile];
public:
	CSound(int _numSound, std::string* _fileName) {
		exitFlag = false;
		soundID = -1;
		numSound = _numSound;
		for (int i=0; i<numSound; i++) {
			fileName[i] = _fileName[i];
		}
		soundThread.reset(new boost::thread(boost::bind(&CSound::PlaySound, this)));
	}
	~CSound() {
		soundThread->join();
	}
	void SetSoundID(int _soundID) { soundID = _soundID; }
	void KillSound() { exitFlag = true; }
	void PlaySound() {
	    std::string soundCommand("mplayer -ao alsa:device=default=Device ../sound/");
		std::string soundPlay;
		while(exitFlag == false) {
			if (soundID >= 0 && soundID < numSound) {
				soundPlay = soundCommand + fileName[soundID];
				if (system(soundPlay.c_str()) == -1)
					std::cout<<"Command failure"<<std::endl;
				soundID = -1;
			}
			usleep(1000);
		}
	}	
};
