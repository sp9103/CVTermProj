#include "CalibMatReader.h"


CalibMatReader::CalibMatReader(void)
{
}


CalibMatReader::~CalibMatReader(void)
{
}

int CalibMatReader::ReadMat(char *filepath, cv::Mat *CalibMat){
	FILE *fp = NULL;

	//Matrix assign fail
	if(CalibMat->rows != 4 && CalibMat->cols != 4){
		CalibMat->release();
		CalibMat->create(4,4, CV_32FC1);
	}

	fp = fopen(filepath, "rb");
	if(fp == NULL){
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 4; j++){
				if(i == j)
					CalibMat->at<float>(i,j) = 100.0f;
				else
					CalibMat->at<float>(i,j) = 0.0f;
			}
		}
		return -1;
	}

	for(int i = 0; i < 16; i++){
		float temp;
		fread(&temp, sizeof(float), 1, fp);
		CalibMat->at<float>(i/4, i%4) = temp;
	}

	fclose(fp);

	return 1;
}

void CalibMatReader::WriteMat(cv::Mat CalibMat){
}