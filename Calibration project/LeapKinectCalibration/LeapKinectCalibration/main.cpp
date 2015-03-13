#include "define.h"
#include "KinectConnector.h"
#include "LeapConnector.h"

#define DATASETCOUNT 400

int main(){
	KinectConnector kinect;
	Controller controller;
	LeapConnector LeapMotion;
	int DataCount = 0;

	//Init
	kinect.KinectInitialize(KinectSource_Color | KinectSource_Depth| KinectSource_Body);
	controller.addListener(LeapMotion);

	//Data Record
	while(1){

		
		waitKey(30);

		if(DataCount > DATASETCOUNT)
			break;
	}

	//Deinit
	kinect.KinectDestroy();
	controller.removeListener(LeapMotion);

	//Solving Problem

	return 0;
}