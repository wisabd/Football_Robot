#include "Perception.hpp"
void ReadPerception(CPerception& perception) {
	for (int i=0; i<numTouch; i++) {
		if(perception.GetTouch(i) == true) {
			std::cout<<"Touch "<<i<<std::endl;
		}
	}
	for (int i=0; i<numTilt; i++) {			
		int tiltSide = perception.GetTiltSide(i);
		if (tiltSide == 1) {
			std::cout<<"Tilt "<<i<<" plus side"<<std::endl;
		}
		else if(tiltSide == -1) {
			std::cout<<"Tilt "<<i<<" minus side"<<std::endl;					
		}
	}		
	for (int i=0; i<numMarker; i++) {
		if(perception.GetMarker(i) == true) {
			std::cout<<"Marker "<<i<<std::endl;
		}
	}
}
