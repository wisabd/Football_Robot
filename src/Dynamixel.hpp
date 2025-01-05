#pragma once
#include "SerialComm.hpp"

// Instruction
#define READ_DATA 	0x02
#define WRITE_DATA 	0x03
#define REG_WRITE 	0x04
#define ACTION 		0x05
#define SYNC_WRITE 	0x83

//Motor ID
#define BROADCASTING_ID 0xfe

//Address
#define TORQUE_ENABLE 	0x18
#define LED 			0x19
#define GOAL_POSITION	0x1e	//from 0 to 300deg = 0x000~0x3ff = int 0~1023, resolution = 0.3deg
#define MOVING_SPEED	0x20
#define CW_COMPLIANCE_MARGIN 0x1A

template<class _T, unsigned int _N>
inline unsigned char NTH_BYTE(_T __x) {
    return ((__x >> (8 * _N)) & 0xff);
}
template<class _T>
inline unsigned char highbyte(_T __x) {
    return NTH_BYTE<_T, 1>(__x);
}
template<class _T>
inline unsigned char lowbyte(_T __x) {
    return NTH_BYTE<_T, 0>(__x);
}

class Motor {
private:
	int ID;
	int ang;
	int speed;
	int maxDegAng;
	int midDegAng;
	int maxBitAng;	
	int num;
public:
	Motor():
		ang(0),
		speed(0),
		maxDegAng(300),
		midDegAng(150),
		maxBitAng(1023) {}
	void SetNum(int _num) {
		num = _num;
	}
	void SetID(int _ID) {
		if (_ID < 0 || _ID > 253)
			std::cout<<"Out of ID range! Set between 0 to 253"<<std::endl;
		else
			ID = _ID;
	}
	void SetAng(int _ang) {
		if (_ang < -maxDegAng || _ang > maxDegAng) {
			std::cout<<"Out of angle range! Set between -150 to 150"<<std::endl;
			ang = 0;
		}
		else
			ang = _ang;				
	}
	void SetSpeed(int _speed) {
		if (_speed < -1023 || _speed > 1023) {
			std::cout<<"Out of speed range! Set between -1023 to 1023"<<std::endl;
			speed = 0;
		}
		else
			speed = _speed;				
	}
	int GetNum() {
		return num;
	}
	int GetID() {
		return ID;
	}		
	int GetAng() {
		return ang;
	}
	int GetSpeed() {
		return speed;
	}
	int GetBiasedAng() {
		int biasedAng = ang + midDegAng;
		return maxBitAng * biasedAng / maxDegAng;
	}
	int GetBiasedSpeed() {
		int biasedSpeed = speed;
		if (biasedSpeed < 0)
			biasedSpeed = 1024 - speed;
		return biasedSpeed;
	}
};



