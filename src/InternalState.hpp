#pragma once
#include "Perception.hpp"
class CInternalState {
private:
	unsigned int happy;
	unsigned int angry;
	unsigned int fear;
	unsigned int sad;
	unsigned int happyTH;
	unsigned int angryTH;
	unsigned int fearTH;
	unsigned int sadTH;
public:
	CInternalState(unsigned int _happyTH, unsigned int _angryTH, unsigned int _fearTH, unsigned int _sadTH) {
		happyTH = _happyTH;
		angryTH = _angryTH;
		fearTH = _fearTH;
		sadTH = _sadTH;
		ClearIntState();
	}
	~CInternalState() {}
	void ClearIntState() {
		happy = 0;
		angry = 0;
		fear  = 0;
		sad   = 0;		
	}
	void ClearHappyState() {
		happy = 0;
	}
	void ClearAngryState() {
		angry = 0;
	}
	void ClearFearState() {
		fear  = 0;
	}
	void ClearSadState() {
		sad   = 0;		
	}
	void UpdateIntState(CPerception& perception) {
		// Increase by 2 if there is an input
		// Decrease by 1 if there is no input
		if (perception.GetTouch(0) == true)
			happy += 2;	
		else if (happy > 0)
			happy --;

		if (perception.GetTouch(1) == true) 
			angry += 2;
		else if (angry > 0)
			angry --;

		if (perception.GetTiltSide(0) != 0 || perception.GetTiltSide(1) != 0)
			fear += 2;				
		else if (fear > 0)
			fear --;

		if (perception.GetMarker(0) == true) // Marker 'A'
			sad += 2;
		else if (sad > 0)
			sad --;
	}
	bool GetHappyState() {
		if (happy > happyTH)
			return true;
		else 
			return false;
	}
	bool GetAngryState() {
		if (angry > angryTH)
			return true;
		else 
			return false;
	}
	bool GetFearState() {
		if (fear > fearTH)
			return true;
		else 
			return false;
	}
	bool GetSadState() {
		if (sad > sadTH)
			return true;
		else 
			return false;
	}	
};
