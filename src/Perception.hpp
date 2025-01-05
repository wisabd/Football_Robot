#pragma once
#include <iostream>
#include <ctime>
#include <math.h>
#include <boost/scoped_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <ARToolKitLib.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "SPI.hpp"
#include "GPIO.hpp"

#define numTouch	5
#define numTilt		2
#define numMarker	6

void msleep(int msec) {
	for (int i=0; i < msec; i++)
		usleep(1000);
}

class CPerception {
private:
	bool exitFlag;
	bool hostPC;
	bool marker[numMarker];		// 0:A, 1:B, 2:C, 3:D, 4:G, 5:F
	bool touch[numTouch];		// 0,1,2,3,4 touch sensors
	double tilt[numTilt];		// 0:roll, 1:pitch
	double tiltThres[numTilt];  // 0:roll thread, 1:pitch thread	
	int tiltSide[numTilt];		// -1: tilt minus side, 0: normal, 1: tilt plus side
	int width;
	int height;
	int markerThreshold;
	int markerFilterCnt;
	boost::scoped_ptr<cv::VideoCapture> cap;
	cv::Mat curr_rgb;
	ARToolKitLib markerDetector;
	boost::scoped_ptr<SPI> mySPI;
	boost::scoped_ptr<boost::thread> touchThread;
	boost::scoped_ptr<boost::thread> tiltThread;
	boost::scoped_ptr<boost::thread> markerThread;
public:
	CPerception(bool _hostPC, double* _tiltThres) {		
		hostPC = _hostPC;
		exitFlag = false;		
		markerFilterCnt = 0;
		TouchInit();
		TiltInit(_tiltThres);
		MarkerInit();
	}	
	~CPerception() {
		if (hostPC == false) {
			touchThread->join();
			tiltThread->join();
		}
		markerThread->join();
		cap->release();
		std::cout<<"Finish cap"<<std::endl;
	}
	cv::Mat GetCurrRGB() { 
		return curr_rgb;	
	}
	void TouchInit() {
		for (int i=0; i<numTouch; i++)
			touch[i] = false;
		if (hostPC == false)
			touchThread.reset(new boost::thread(boost::bind(&CPerception::TouchRecog, this)));
	}
	void TiltInit(double* _tiltThres) {
		for (int i=0; i<numTilt; i++) {
			tilt[i] = 0;
			tiltSide[i] = 0;
			tiltThres[i] = _tiltThres[i];
		}
		if (hostPC == false) {
			mySPI.reset(new SPI("/dev/spidev1.0"));
			uint8_t itx[2] = {49, 1};
			uint8_t irx[2] = {0};
			mySPI->transfer(itx, irx, 2);
			usleep(1000);
			itx[1] = 0;
			mySPI->transfer(itx, irx, 2);
			usleep(1000);
			itx[0] = 55;
			itx[1] = 0xb0;
			mySPI->transfer(itx, irx, 2);
			usleep(1000);		
			tiltThread.reset(new boost::thread(boost::bind(&CPerception::TiltRecog, this)));
		}
	}
	
	void MarkerInit() {
		if (hostPC == true) {
			width = 640;
			height = 480;
		}
		else {
			width = 160;
			height = 120;
		}
		for (int i=0; i<numMarker; i++)
			marker[i] = false;
		char cparam_name[] = "../data/camera_para.dat";
		char model_name[] = "../data/marker_data";
		markerThreshold = 128;			
		cap.reset(new cv::VideoCapture(CV_CAP_ANY));
		cap->set(CV_CAP_PROP_FRAME_WIDTH, width);
		cap->set(CV_CAP_PROP_FRAME_HEIGHT, height);	
		if (!cap->isOpened()) {
			std::cout<<"Camera is disconnect"<<std::endl;
		}				
		else {
			if (markerDetector.Initialization(cparam_name, model_name, width, height) < 0) {
				std::cout <<"Marker detector initialization failed !" << std::endl;    		
			}		
			else {
				std::cout <<"Ready to detect marker"<<std::endl;
				markerThread.reset(new boost::thread(boost::bind(&CPerception::MarkerRecog, this)));
			}
		}
	}
	
	void KillPerception() { exitFlag = true; }
	void TouchRecog() {
		const unsigned int touchGPIO[numTouch]= {66, 69, 45, 23, 47};
		bool touchVal[numTouch] = {false, false, false, false, false};
		ExportTouchSen(touchGPIO, numTouch);
		while(exitFlag == false) {
			for(int i=0; i<numTouch; i++) {				
				gpio_get_value(touchGPIO[i], touchVal[i]);  
				touch[i] = touchVal[i];
				usleep(10);      // sleep for ten nanosecond
			}
			msleep(100);
		}
		UnexportTouchSen(touchGPIO, numTouch);
	}	
	void TiltRecog() {		
		//const double RMR = 2048.0;		//rotation measurement range 2048, 1024, 512, 256 (deg/s)
		//const double AMR = 8.0;			//acceleration measurement range 8, 4, 2 (g)
		//const double DIVIDER = 32768.0;	//2^15
		//const double GYRO_RATE = 0.0625; //RMR / DIVIDER;
		const double ACCEL_RATE = 0.000244141; //AMR / DIVIDER;
		//double gyro_data[3];
		double accel_data[3];
		while(exitFlag == false) {
			uint8_t data_tx[13] = {0};
			uint8_t data[13] = {0};
			data_tx[0] = 0x80;
			mySPI->transfer(data_tx, data, 13);
			for (int i=0; i<3; i++) {
				/*
				gyro_data[i] = (double)combine(data[2*i+1], data[2*i+2]) * GYRO_RATE;
				gyro_data[i] = fmin(1.0, gyro_data[i]);
				gyro_data[i] = fmax(-1.0, gyro_data[i]);
				*/
				accel_data[i] = (double)combine(data[2*i+7], data[2*i+8]) * ACCEL_RATE;
				accel_data[i] = fmin(1.0, accel_data[i]);
				accel_data[i] = fmax(-1.0, accel_data[i]);
			}
			tilt[0] = atan2(accel_data[1], accel_data[2]);
			tilt[1] = -asin(accel_data[0]);
			for (int i=0; i<numTilt; i++) {			
				tiltSide[i] = 0;
				if (tilt[i] > tiltThres[i]) {
					//std::cout<<"Tilt "<<i<<" one side"<<std::endl;
					tiltSide[i] = 1;
				}
				else if(tilt[i] < -tiltThres[i]) {
					//std::cout<<"Tilt "<<i<<" other side"<<std::endl;			
					tiltSide[i] = -1;
				}
			}
			msleep(100);
		}
	}
	void MarkerRecog() {
		while(exitFlag == false) {
			//double t = (double)cv::getTickCount();
			
			cap->grab();
			cap->retrieve(curr_rgb);	
			markerDetector.DetectMarker((ARUint8*)curr_rgb.ptr(), markerThreshold);
			if (markerDetector.m_markerN <= 0)
				markerFilterCnt = 0;
			else {
				markerFilterCnt++;
				if (markerFilterCnt == 1) {
					for(int i=0; i < markerDetector.m_markerN; ++i) {		
						int id = markerDetector.m_markerInfo[i].id;
						if (id >= 0 && id < numMarker) {
							//std::cout<<"ID="<<id<<":"<<markerDetector.m_markerData[id].name<<std::endl;
							marker[id] = true;
						}												
					}							
				}	
				else if (markerFilterCnt == 10)	
					markerFilterCnt = 0;							
				markerFilterCnt = 0;
			}
			
			//msleep(100);
			
			if (hostPC == true) {
				cv::imshow("RGB", curr_rgb);
				char key = cv::waitKey(1);
				if (key == 'q')
					exitFlag = true;
			}
			
			/*
			t = ((double)cv::getTickCount() - t)/cv::getTickFrequency();
			std::cout<<"T="<<t<<std::endl;
			*/
		}	
	}

	void Clear() {
		for (int i=0; i<numTouch; i++)
			touch[i] = false;
		for (int i=0; i<numTilt; i++)		
			tiltSide[i] = 0;
		for (int i=0; i<numMarker; i++)
			marker[i] = false;		
	}
	void ReadPerception() {
		for (int i=0; i<numTouch; i++) {
			if(touch[i] == true) {
				std::cout<<"Touch "<<i<<std::endl;
			}
		}
		for (int i=0; i<numTilt; i++) {			
			if (tiltSide[i] == 1) {
				std::cout<<"Tilt "<<i<<" plus side"<<std::endl;
			}
			else if(tiltSide[i] == -1) {
				std::cout<<"Tilt "<<i<<" minus side"<<std::endl;					
			}
		}		
		for (int i=0; i<numMarker; i++) {
			if(marker[i] == true) {
				std::cout<<"Marker "<<i<<std::endl;
			}
		}
	}
	void SetMarker(int idx, bool val) {
		if (idx < numMarker)
			marker[idx] = val;
		else {
			std::cout<<"[Error:In] Marker idx "<<idx<<" is higher than max idx"<<std::endl;
			marker[idx] = false;
		}
	}
	void SetTouch(int idx, bool val) {
		if (idx < numTouch)
			touch[idx] = val;
		else {
			std::cout<<"[Error:In] Touch idx "<<idx<<" is higher than max idx"<<std::endl;
			touch[idx] = false;
		}
	}
	void SetTilt(int idx, double val) {
		if (idx < numTilt)
			tilt[idx] = val;
		else {
			std::cout<<"[Error:In] Tilt idx "<<idx<<" is higher than max idx"<<std::endl;
			tilt[idx] = 0;
		}
	}
	void SettiltThres(int idx, double val) {
		if (idx < numTilt)
			tiltThres[idx] = val;
		else {
			std::cout<<"[Error:In] tiltThres idx "<<idx<<" is higher than max idx"<<std::endl;
			tiltThres[idx] = 0;
		}
	}
	bool GetMarker(int idx) {
		if (idx < numMarker)
			return marker[idx];
		else {
			std::cout<<"[Error:Out] Marker idx "<<idx<<" is higher than max idx"<<std::endl;
			return false;
		}
	}
	bool GetTouch(int idx) {
		if (idx < numTouch)
			return touch[idx];
		else {
			std::cout<<"[Error:Out] Touch idx "<<idx<<" is higher than max idx"<<std::endl;
			return false;
		}
	}
	double GetTilt(int idx) {
		if (idx < numTilt)
			return tilt[idx];
		else {
			std::cout<<"[Error:Out] Tilt idx "<<idx<<" is higher than max idx"<<std::endl;
			return 0;
		}
	}
	int GetTiltSide(int idx) {
		if (idx < numTilt)
			return tiltSide[idx];
		else {
			std::cout<<"[Error:Out] Tilt idx "<<idx<<" is higher than max idx"<<std::endl;
			return 0;
		}
	}

};
