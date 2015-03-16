#include "define.h"
#include "KinectConnector.h"
#include "LeapConnector.h"
#include "Calibration.h"
#include "CalibMatReader.h"

#define DATASETCOUNT 400

int CalcPrevDist(cv::Point3f p);			//이전 프레임과 현재 프레임에서의 거리계산
void KinectDataSelect(SkeletonInfo src, cv::Point3f *elbow, cv::Point3f *wrist);

int main(){
	KinectConnector kinect;
	Controller controller;
	LeapConnector LeapMotion;
	Calibration calib;
	CalibMatReader writer;

	int DataCount = 0;
	cv::Point3f LeapElbow, LeapWrist;
	cv::Point3f KinectElbow, KinectWrist;

	cv::Mat rgb, depth;
	SkeletonInfo m_skel;

	//Init
	kinect.KinectInitialize(KinectSource_Color | KinectSource_Depth| KinectSource_Body);
	controller.addListener(LeapMotion);

	rgb.create(KINECT_COLOR_HEIGHT, KINECT_COLOR_WIDTH, CV_8UC4);
	depth.create(KINECT_DEPTH_HEIGHT, KINECT_DEPTH_WIDTH, CV_8UC4);

	//Data Record
	while(1){

		//Data get to device - Kinect
		kinect.GetColorImage(&rgb);
		kinect.GetDepthImage(&depth);
		kinect.GetSkeletonPos(&m_skel, &depth, 1);
		//Data get to device - Leap

		//Data select - Kinect
		KinectDataSelect(m_skel, &KinectElbow, &KinectWrist);


		if(CalcPrevDist(LeapWrist) > 20){
			//Data store
			DataCount++;
			calib.DataStore(KinectWrist, LeapWrist);
			calib.DataStore(KinectElbow, LeapElbow);
		}

		if(DataCount > DATASETCOUNT)
			break;

		waitKey(30);
	}

	//Deinit
	kinect.KinectDestroy();
	controller.removeListener(LeapMotion);

	rgb.release();
	depth.release();

	cv::destroyAllWindows();

	//Solving Problem - RANSAC & Least Square
	int LoopCount = calib.CalcLoopNUM(0.999, 0.8, DATASETCOUNT * 2);		//(wrist, elbow), palm
	printf("RANSAC LOOP count : %d\n", LoopCount);
	calib.InitParam(LoopCount, 20, DATASETCOUNT * 2);						//Threshold = 20mm (2cm)
	calib.CalcMatrix();
	writer.WriteMat( "Calib.bin", calib.GetRTMatrix());

	return 0;
}

int CalcPrevDist(cv::Point3f p){
	static cv::Point3f prvPoint = cv::Point3f(-1.0f, -1.0f, -1.0f);

	int dist = sqrt(pow(prvPoint.x - p.x,2) + pow(prvPoint.y - p.y,2) + pow(prvPoint.z - p.z,2));

	return dist;
}

void KinectDataSelect(SkeletonInfo src, cv::Point3f *elbow, cv::Point3f *wrist){
	CameraSpacePoint el, wr;

	el = src.InfoBody[0].JointPos[JointType_ElbowRight].Position;
	wr = src.InfoBody[0].JointPos[JointType_WristRight].Position;

	elbow->x = el.X;
	elbow->y = el.Y;
	elbow->z = el.Z;
	wrist->x = wr.X;
	wrist->y = wr.Y;
	wrist->z = wr.Z;
}