#include <time.h>
#include "define.h"

class Calibration
{
public:
	Calibration(void);
	~Calibration(void);

	/*M * X1 = X2
	X2 is basis space*/
	void DataStore(cv::Point3f first, cv::Point3f second);

	//RANSAC implement, num : 시행횟수
	void CalcMatrix();

	//Initialize
	void InitParam(int LoopCount, float Threshold, int samplecount);

	/*N 계산
	p : target probability
	alpha : inlier ratio
	sampleCount : 
	*/
	int CalcLoopNUM(float p, float alpha, int samplecount);

	cv::Mat GetRTMatrix();

private:
	//Parameter
	int m_N;							//number of loop count
	float m_Threshold;					//inlier, outlier bound
	int m_m;							//pick sample count

	cv::Mat RTMat;

	//Data set
	std::vector<std::pair<cv::Point3f, cv::Point3f>> DataSet;
	//Randbox mixing
	void SelectRandomNum(int *Box);

	// RT한 뒤 오차 반환
	float CalcDist(cv::Mat RT, int idx);

	//inlier 갯수 반환
	int CalcInlierCount(cv::Mat RT, float threshold, float *averError);

	// ex. idx == 1 . first row 
	void CreateRefMat(int *idxarr, cv::Mat* Mat1);
	void CreateTargetMat(int *idxarr, cv::Mat* Mat2, int idx);

	void printMat(cv::Mat src);
};

