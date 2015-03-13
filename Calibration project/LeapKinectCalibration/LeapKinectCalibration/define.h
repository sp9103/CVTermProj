#pragma once
#include "Kinect.h"
#include "Kinect.Face.h"
#include <opencv.hpp>
#include <vector>
#include <Leap.h>

#define KINECT_COUNT			1
#define KINECT_DEPTH_WIDTH		512
#define KINECT_DEPTH_HEIGHT		424
#define KINECT_COLOR_HEIGHT		1080
#define KINECT_COLOR_WIDTH		1920

#define OPENCV_WAIT_DELAY		20
#define PI						3.141592653589


#define SWAP(a,b,t) ((t)=(a), (a)=(b), (b)=(t))

//Face information structure
typedef struct _faceinfo{
	bool bDetect;						//Face Detection 됬는지 안됫는지
	CameraSpacePoint Facepos;			//3d 공간상의 Face 좌표
	//얼굴 회전 각도
	int yaw;
	int pitch;
	int roll;
}faceinfo;

//Single Body Structure;
typedef struct BodyInfo{
	Joint JointPos[JointType_Count];
	//cv::Point2d jointPoints[JointType_Count];
	UINT64 BodyID;
	faceinfo Face;
	float upperbodylen;
	float lowerbodylen;
	float spinedepth;
}BodyInfo;

typedef struct synconizedSkeletons{
	int Hid;
	int numObservingKinect;
	bool bObsevingKinect[KINECT_COUNT];
	BodyInfo InfoBody[KINECT_COUNT];

}synconizedSkeletons;


typedef struct synconizedSkeletonsAll{

	SYSTEMTIME	st;
	int numObservedBody;
	bool bObsevedBody[BODY_COUNT];
	synconizedSkeletons syncSkels[BODY_COUNT];

}synconizedSkeletonsAll;

//Store sensor out Body information
typedef struct SkeletonInfo{
	int Kinect_ID;
	int Count;												//현재 추적하고 있는 스켈레톤 갯수
	SYSTEMTIME	st;
	BodyInfo InfoBody[BODY_COUNT];
}SkeletonInfo;

// Safe release for interfaces
template<class Interface>
inline void SafeRelease(Interface *& pInterfaceToRelease)
{
	if (pInterfaceToRelease != NULL)
	{
		pInterfaceToRelease->Release();
		pInterfaceToRelease = NULL;
	}
}

typedef enum _KinectSource KinectSource;

enum _KinectSource
{
	KinectSource_Color	= 0x1,
	KinectSource_Depth	= 0x2,
	KinectSource_Body	= 0x4,
	KinectSource_Face	= 0xC
} ;