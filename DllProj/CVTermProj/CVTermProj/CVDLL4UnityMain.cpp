#include <Windows.h>

#include "KinectConnector.h"

#define EXPORT_API __declspec(dllexport)

extern "C"{
	KinectConnector kinect;
	HRESULT hr;

	//Image allocation
	Mat KinectRGB, KinectDepth;

	SkeletonInfo tBodystruct;

	void EXPORT_API TEST(){
		MessageBox(NULL, L"TEST SUCCESS", L"TEST", MB_OK);
	}

	void EXPORT_API KinectInitialize(){
		KinectRGB.create(KINECT_COLOR_HEIGHT, KINECT_COLOR_WIDTH, CV_8UC4);
		KinectDepth.create(KINECT_DEPTH_HEIGHT, KINECT_DEPTH_WIDTH, CV_8UC4);

		cv::namedWindow("RGB", CV_WINDOW_KEEPRATIO);
		cv::namedWindow("DEPTH", CV_WINDOW_KEEPRATIO);

		kinect.KinectInitialize(KinectSource_Color | KinectSource_Depth| KinectSource_Body | KinectSource_Face);
	}

	void EXPORT_API KinectDeinitialize(){
		kinect.KinectDestroy();

		//Image release
		KinectRGB.release();
		KinectDepth.release();

		cv::destroyAllWindows();
	}

	int EXPORT_API KinectRun(){
		kinect.GetDepthImage(&KinectDepth);
		hr = kinect.GetColorImage(&KinectRGB);
		if(SUCCEEDED(hr))
			hr = kinect.GetSkeletonPos(&tBodystruct, &KinectRGB, 0);
		else
			return -1;

		imshow("RGB", KinectRGB);
		imshow("DEPTH", KinectDepth);

		return 1;
	}
}