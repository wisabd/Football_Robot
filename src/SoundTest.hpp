#include "Sound.hpp"
void SoundTest(CSound& sound) {
	sound.SetSoundID(0); // 2.2 sec
	sleep(3);
	sound.SetSoundID(1); // 3.2 sec
	sleep(5);
	sound.SetSoundID(2); // 6 sec
	sleep(7);
	sound.SetSoundID(3); // 2 sec
	sleep(3);
}
