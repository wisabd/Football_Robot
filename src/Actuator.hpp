#pragma once
#include<boost/scoped_ptr.hpp>
#include<boost/scoped_array.hpp>
#include "Dynamixel.hpp"
#include "Motor.h"
#define maxDynamixel 12
#define numServo 2
#define JOINT 0
#define WHEEL 1
class CActuator {
public:
    unsigned int baudRate;
    boost::asio::io_service io;
    boost::scoped_ptr<boost::thread> serialThread;
    boost::scoped_ptr<SerialComm> serial;
	boost::scoped_array<ServoControl> servoControls;
	Motor joint[maxDynamixel];
	Motor wheel[maxDynamixel];
	int jointInitAng[maxDynamixel];
	CActuator(bool hostPC) {
		SerialInit(hostPC);
		ServoInit();
	}
	CActuator(int jointNum, int wheelNum, int* jointID, int* wheelID, int* _jointInitAng, int jointSpeed, bool hostPC) {
		joint[0].SetNum(jointNum);
		wheel[0].SetNum(wheelNum);
		for(int i=0; i<jointNum; i++) {
			jointInitAng[i] = _jointInitAng[i];
			joint[i].SetID(jointID[i]);				// Set joint motor's ID: 0~253
			joint[i].SetSpeed(jointSpeed);			// Speed range (joint motor): 0~1023
			joint[i].SetAng(jointInitAng[i]);     				// Angle range: -150(deg)~150(deg)
		}
		for(int i=0; i<wheelNum; i++)
			wheel[i].SetID(wheelID[i]);		
		SerialInit(hostPC);
		ServoInit();
	}
	~CActuator() {
		
	}	

	// Initialize serial communication
	void SerialInit(bool hostPC) {
		baudRate = 57600;
		std::string port("/dev/ttyO1");	// In the case of BBB.												
		if (hostPC == true)
			port.assign("/dev/ttyUSB0");// In the case of Host PC.	
		serial.reset(new SerialComm(io, baudRate, port));
		std::cout<<serial->active()<<std::endl;	 
		SetMargin();
		serialThread.reset(new boost::thread(boost::bind(&boost::asio::io_service::run, &io)));

	}

	// Initialize servo motor
	void ServoInit() {
		const float minAngle = 0;
		const float midAngle = 90;
		const float maxAngle = 180;
		const int minPWM = 400;    //400 for 0 deg (found it by experiment)
		const int maxPWM = 1800;   //1800 for 180 deg
		const std::string servoName[numServo] ={"P8_19", "P9_14"};
		servoControls.reset(new ServoControl[numServo] { 
			ServoControl(servoName[0], midAngle, minAngle, maxAngle, minPWM, maxPWM),
			ServoControl(servoName[1], midAngle, minAngle, maxAngle, minPWM, maxPWM)});
		for (int i=0; i<numServo; i++) {		
			servoControls[i].Enable();
		}
	}
	// Set angle of servo motor
	void ServoSetAng(int idx, int angle) {
		if (idx < numServo) {
			servoControls[idx].SetAngle(angle);
			servoControls[idx].UpdatePWMSignal();
		}
		else 
			std::cout<<"Out of servo idx"<<std::endl;
	}
	void ExeInitAng() {
		for (int i=0; i<joint[0].GetNum(); i++)
			joint[i].SetAng(jointInitAng[i]);     				// Angle range: -150(deg)~150(deg)
		ExeAng();
	}
	void SetMargin() {
		unsigned char buffer[12];
		buffer[0] = 0xff;
		buffer[1] = 0xff;
		buffer[2] = BROADCASTING_ID;
		buffer[3] = 7;
		buffer[4] = WRITE_DATA;
		buffer[5] = CW_COMPLIANCE_MARGIN;
		buffer[6] = 5;
		buffer[7] = 5;
		buffer[8] = 0x32;
		buffer[9] = 0x32;
		buffer[10] = ~(buffer[2]+buffer[3]+buffer[4]+buffer[5]+buffer[6]+buffer[7]+buffer[8]+buffer[9]);
		serial->write(buffer, 11);
	}
	void ExeJointSpeed() {
		unsigned char buffer[50];
		unsigned int idx = 7;
		unsigned char checksum = 0;
		int speed = 0;
		buffer[0] = 0xff;
		buffer[1] = 0xff;
		buffer[2] = BROADCASTING_ID;
		buffer[3] = 3 * joint[0].GetNum() + 4;
		buffer[4] = SYNC_WRITE;		//instruction	
		buffer[5] = MOVING_SPEED;
		buffer[6] = 2;
	 	for (int i=2; i<=6; i++)
			checksum += buffer[i];
		for (int i=0; i<joint[0].GetNum(); i++) {
			speed = joint[i].GetBiasedSpeed();
			buffer[idx++] = joint[i].GetID();				
			buffer[idx++] = lowbyte(speed);	
			buffer[idx++] = highbyte(speed);
			checksum += (buffer[idx-1] + buffer[idx-2] + buffer[idx-3]);
		}
		buffer[idx++] = ~checksum;
		serial->write(buffer, idx);		
	}
	void ExeStopWheelSpeed() {
		for (int i=0; i<wheel[0].GetNum(); i++)
			wheel[i].SetSpeed(0);
		ExeWheelSpeed();
	}
	void ExeWheelSpeed() {
		unsigned char buffer[50];
		unsigned int idx = 7;
		unsigned char checksum = 0;
		int speed = 0;
		buffer[0] = 0xff;
		buffer[1] = 0xff;
		buffer[2] = BROADCASTING_ID;
		buffer[3] = 3 * wheel[0].GetNum() + 4;
		buffer[4] = SYNC_WRITE;		//instruction	
		buffer[5] = MOVING_SPEED;
		buffer[6] = 2;
	 	for (int i=2; i<=6; i++)
			checksum += buffer[i];
		for (int i=0; i<wheel[0].GetNum(); i++) {
			speed = wheel[i].GetBiasedSpeed();
			buffer[idx++] = wheel[i].GetID();				
			buffer[idx++] = lowbyte(speed);	
			buffer[idx++] = highbyte(speed);
			checksum += (buffer[idx-1] + buffer[idx-2] + buffer[idx-3]);
		}
		buffer[idx++] = ~checksum;
		serial->write(buffer, idx);		
	}
	void ExeAng() {
		unsigned char buffer[50];
		unsigned int idx = 7;
		unsigned char checksum = 0;
		int angle = 0;
		buffer[0] = 0xff;		//header1
		buffer[1] = 0xff;		//header2
		buffer[2] = BROADCASTING_ID;//motor id
		buffer[3] = 3 * joint[0].GetNum() + 4;    
		buffer[4] = SYNC_WRITE;		//instruction
		buffer[5] = GOAL_POSITION;	//address: (goal_angle)
		buffer[6] = 2;
		for (int i=2; i<=6; i++)
			checksum += buffer[i];
		for (int i=0; i<joint[0].GetNum(); i++) {
			angle = joint[i].GetBiasedAng();
			buffer[idx++] = joint[i].GetID();
			buffer[idx++] = lowbyte(angle);
			buffer[idx++] = highbyte(angle);
			checksum += (buffer[idx-1] + buffer[idx-2] + buffer[idx-3]);
		}
		buffer[idx++] = ~checksum;
		serial->write(buffer, idx);
	}

	/*
	void SetCellType(int ID, int type) {
		unsigned char buffer[12];
		buffer[0] = 0xff;
		buffer[1] = 0xff;
		buffer[2] = 0;
		buffer[3] = ID;
		buffer[4] = WRITE_DATA;
		buffer[5] = 0x06;
		buffer[6] = 0;
		buffer[7] = 0;
		if (type == JOINT) {
			buffer[8] = 255;
			buffer[9] = 3;	
		}
		else if (type == WHEEL) {
			buffer[8] = 0;
			buffer[9] = 0;
		}
		buffer[10] = ~(buffer[2]+buffer[3]+buffer[4]+buffer[5]+buffer[6]+buffer[7]+buffer[8]+buffer[9]);
		serial->write(buffer, 11);
	}
	*/
};	



