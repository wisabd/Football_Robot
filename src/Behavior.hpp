#pragma once
#include "Perception.hpp"
#include "Actuator.hpp"
#include "Sound.hpp"
#include "InternalState.hpp"
#include "server.hpp"

//ID  Joint
// 0  Front Steering
// 1  Rear Steering

//ID  Wheel
// 0  Front Right Wheel
// 1  Front Left Wheel
// 2  Rear Right Wheel
// 3  Rear Left Wheel

void Stop(CActuator& actuator) {
	// Front Wheels
	actuator.wheel[0].SetSpeed(0);
	actuator.wheel[1].SetSpeed(0);
	// Rear Wheels
	actuator.wheel[2].SetSpeed(0);
	actuator.wheel[3].SetSpeed(0);
	// Send target wheels
	actuator.ExeWheelSpeed();
}

void InitPose(CActuator& actuator) {	
	// Stop
	Stop(actuator);

	// Steering System
	actuator.joint[0].SetAng(0);
	actuator.joint[1].SetAng(0);
	// Send target joints
	actuator.ExeAng();

	sleep(1);
}

void SteerRight(CActuator& actuator) {
	// Stop
	Stop(actuator);

	// Steer to Right Side
	actuator.joint[0].SetAng(30);
	actuator.joint[1].SetAng(0);
	actuator.ExeAng();

	sleep(1);
}

void SteerLeft(CActuator& actuator) {
	// Stop
	Stop(actuator);

	// Steer to Left Side
	actuator.joint[0].SetAng(-30);
	actuator.joint[1].SetAng(0);
	actuator.ExeAng();

	sleep(1);
}

void TurnRight(CActuator& actuator) {	
	// Steer Right Side
	SteerRight(actuator);

	// Go Forward
	actuator.wheel[0].SetSpeed(-346);
	actuator.wheel[1].SetSpeed(577);
	actuator.wheel[2].SetSpeed(-300);
	actuator.wheel[3].SetSpeed(724);
	actuator.ExeWheelSpeed();

	sleep(2);

	// Stop
	Stop(actuator);
}

void TurnLeft(CActuator& actuator) {	
	// Steer Right Side
	SteerLeft(actuator);

	// Go Forward
	actuator.wheel[0].SetSpeed(-577);
	actuator.wheel[1].SetSpeed(346);
	actuator.wheel[2].SetSpeed(-724);
	actuator.wheel[3].SetSpeed(300);
	actuator.ExeWheelSpeed();

	sleep(2);

	// Stop
	Stop(actuator);
}

void GoStraight(CActuator& actuator) {	
	// Stop and Look Front
	InitPose(actuator);

	// Go Forward
	actuator.wheel[0].SetSpeed(-500);
	actuator.wheel[1].SetSpeed(500);
	actuator.wheel[2].SetSpeed(-500);
	actuator.wheel[3].SetSpeed(500);
	actuator.ExeWheelSpeed();

	sleep(2);

	// Stop
	Stop(actuator);
}

void GoBack(CActuator& actuator) {
	// Stop and Look Front
	InitPose(actuator);

	// Go Backward
	actuator.wheel[0].SetSpeed(500);
	actuator.wheel[1].SetSpeed(-500);
	actuator.wheel[2].SetSpeed(500);
	actuator.wheel[3].SetSpeed(-500);
	actuator.ExeWheelSpeed();

	sleep(2);

	// Stop
	Stop(actuator);
}


void Release(CActuator& actuator) {



        actuator.joint[2].SetAng(-40);
        actuator.joint[3].SetAng(40);
        actuator.ExeAng();
        sleep(2);
}

void Catch(CActuator& actuator) {

        // Steer to Right Side

        actuator.joint[2].SetAng(-120);
        actuator.joint[3].SetAng(120);
        actuator.ExeAng();
        sleep(2);
}



int RobTest(CActuator& actuator, int cnt) {
	if (cnt == 0) {
		InitPose(actuator);
		GoStraight(actuator);
	}
	else if (cnt == 1) {
		InitPose(actuator);
		GoBack(actuator);
	} 
	else if (cnt == 2) {
		TurnRight(actuator);
	}
	else if (cnt == 3) {
		TurnLeft(actuator);		
	}
	cnt++;
	if (cnt > 3)
		cnt = 0;
	sleep(3);
	actuator.ExeInitAng();	
	return cnt;
}

void BehSelFromPerception(CSound& sound, CPerception& perception, CActuator& actuator) {
        if (perception.GetTouch(0) == true) {
                sound.SetSoundID(0);
				GoStraight(actuator);
        }
        else if (perception.GetTouch(1) == true) {
                sound.SetSoundID(1);
				GoBack(actuator);
        }
        else if (perception.GetTiltSide(1) == 1) {
                sound.SetSoundID(2);
                TurnRight(actuator);
        }
        else if (perception.GetTiltSide(1) == -1) {
                sound.SetSoundID(3);
                TurnLeft(actuator);
        }
        else
                actuator.ExeInitAng();
}


void BehSelFromIntState(CSound& sound, CInternalState& emotion, CActuator& actuator) {
        if (emotion.GetHappyState() == true) {
                emotion.ClearHappyState();
                std::cout<<"Happy"<<std::endl;
                sound.SetSoundID(1);
                
		Catch(actuator);
		sleep(4);
		Release(actuator);
        }
        else if (emotion.GetSadState() == true) {
                emotion.ClearSadState();
                std::cout<<"Sad"<<std::endl;
                sound.SetSoundID(2);
                SteerRight(actuator);
				SteerLeft(actuator);
        }
        else
                actuator.ExeInitAng();
}

int check = 0;

void BehSelFromAndroid(CSound& sound, rit::server& myServer, CActuator& actuator) {
        int androidCmd = myServer.GetCmd();
        if (androidCmd == 0) {
                std::cout<<"Left"<<std::endl;
                sound.SetSoundID(0);
                TurnLeft(actuator);
        }
        else if (androidCmd == 1) {
                std::cout<<"Right"<<std::endl;
                sound.SetSoundID(1);
                TurnRight(actuator);
        }
        else if (androidCmd == 2) {
                std::cout<<"Straight"<<std::endl;
                sound.SetSoundID(2);
                GoStraight(actuator);
        }
        else if (androidCmd == 3) {
                std::cout<<"Back"<<std::endl;
                sound.SetSoundID(3);
                GoBack(actuator);
        }
        if (androidCmd == 10 && check == 1){
                std::cout<<"ReleaseBall"<<std::endl;
                Release(actuator);
                check = 0;
        }
        else if (androidCmd == 10 && check == 0){
                Catch(actuator);
                check = 1;
        }

        else if (androidCmd != 10 && check == 1){
		Catch(actuator);
	}
        else
                actuator.ExeInitAng();
}

