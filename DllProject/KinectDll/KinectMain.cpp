#include <Windows.h>
#include "define.h"

#include "KinectConnector.h"

#define EXPORT_API __declspec(dllexport)

extern "C"{
	KinectConnector kinect;
	HRESULT hr;

	Mat KinectRGB, KinectDepth;

	SkeletonInfo m_Body;

	void EXPORT_API TEST(){
		MessageBox(NULL, L"Kinect Test Successs", L"TEST", MB_OK);
	}

	///////////////////////////////////////////////////////////////////////Kinect Function///////////////////////////////////////////////////////////////////////////////////////
	//생성자에서 호출
	void EXPORT_API KinectInitialize(){
		KinectRGB.create(KINECT_COLOR_HEIGHT, KINECT_COLOR_WIDTH, CV_8UC4);
		KinectDepth.create(KINECT_DEPTH_HEIGHT, KINECT_DEPTH_WIDTH, CV_8UC4);

		cv::namedWindow("RGB", CV_WINDOW_KEEPRATIO);
		cv::namedWindow("DEPTH", CV_WINDOW_KEEPRATIO);

		kinect.KinectInitialize(KinectSource_Color | KinectSource_Depth| KinectSource_Body | KinectSource_Face);
	}

	//소멸자에서 호출
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
			hr = kinect.GetSkeletonPos(&m_Body, &KinectRGB, 0);
		else
			return -1;

		if(SUCCEEDED(hr))
			kinect.FaceDetection(&m_Body, &KinectRGB);
		else
			return -1;

		imshow("RGB", KinectRGB);
		imshow("DEPTH", KinectDepth);

		return 1;
	}

	int EXPORT_API GetUpperBody(float a1Array[], float facepos[], float faceDir[]){
		static float t1Array[3*13];
		static float tfacepos[3];
		static float tfaceDir[4];

		kinect.GetDepthImage(&KinectDepth);
		hr = kinect.GetColorImage(&KinectRGB);
		if(SUCCEEDED(hr))
			hr = kinect.GetSkeletonPos(&m_Body, &KinectRGB, 0);
		else
			return -1;

		if(SUCCEEDED(hr))
			kinect.FaceDetection(&m_Body, &KinectRGB);
		else
			return -1;

		imshow("RGB", KinectRGB);
		imshow("DEPTH", KinectDepth);

		//Nearest Body Select
		if(m_Body.Count > 1){
			float NearestDepth = 999.0f;
			int NearestIdx;

			for(int i = 0; i < m_Body.Count; i++){
				if(m_Body.InfoBody[i].spinedepth < NearestDepth){
					NearestDepth = m_Body.InfoBody[i].spinedepth;
					NearestIdx = i;
				}
			}

			memcpy(&m_Body.InfoBody[0], &m_Body.InfoBody[NearestIdx], sizeof(BodyInfo)); 
		}

		//Convert Struct to Array
		//SPineMid 부터  HandRight까지 x,y,z 순서로
		if(m_Body.Count > 0){
			for(int i = 0; i < 12; i++){
				t1Array[i*3+0] = m_Body.InfoBody[0].JointPos[i].Position.X;
				t1Array[i*3+1] = m_Body.InfoBody[0].JointPos[i].Position.Y;
				t1Array[i*3+2] = m_Body.InfoBody[0].JointPos[i].Position.Z;
			}
			//SpineShould
			t1Array[12*3+0] = m_Body.InfoBody[0].JointPos[20].Position.X;
			t1Array[12*3+1] = m_Body.InfoBody[0].JointPos[20].Position.Y;
			t1Array[12*3+2] = m_Body.InfoBody[0].JointPos[20].Position.Z;

			//Convert Struct to Array - Face
			if(m_Body.InfoBody[0].Face.bDetect){
				//Face position
				tfacepos[0] = m_Body.InfoBody[0].Face.Facepos.X;
				tfacepos[1] = m_Body.InfoBody[0].Face.Facepos.Y;
				tfacepos[2] = m_Body.InfoBody[0].Face.Facepos.Z;
				//Face Direction
				tfaceDir[0] = m_Body.InfoBody[0].Face.faceDir.x;
				tfaceDir[1] = m_Body.InfoBody[0].Face.faceDir.y;
				tfaceDir[2] = m_Body.InfoBody[0].Face.faceDir.z;
				tfaceDir[3] = m_Body.InfoBody[0].Face.faceDir.w;
			}

		}

		memcpy(a1Array, t1Array, sizeof(float)*3*13);
		memcpy(facepos, tfacepos, sizeof(float)*3);
		memcpy(faceDir, tfaceDir, sizeof(float)*4);

		return 1;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}