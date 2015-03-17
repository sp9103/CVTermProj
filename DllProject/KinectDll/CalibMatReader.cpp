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
	if(CalibMat->rows != 4 || CalibMat->cols != 4){
		CalibMat->release();
		CalibMat->create(4,4, CV_32FC1);
	}

	fp = fopen(filepath, "rb");
	if(fp == NULL){
		MessageBox(NULL, L"Calibration Matrix open fail", L"Fail", MB_OK);
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

	if(fp != NULL)
		fclose(fp);

	return 1;
}

void CalibMatReader::WriteMat(char* filepath, cv::Mat CalibMat){
	FILE *fp = NULL;

	fp = fopen(filepath, "wb");
	
	//write matrix
	if(CalibMat.rows != 4 || CalibMat.cols != 4){
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 4; j++){
				float temp;
				if(i == j){
					temp = 1.0f;
					fwrite(&temp, sizeof(float), 1, fp);
				}
				else{
					temp = 0.0f;
					fwrite(&temp, sizeof(float), 1, fp);
				}
			}
		}

		return;
	}

	//matrix write
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			float temp;

			temp = CalibMat.at<float>(i,j);

			fwrite(&temp, sizeof(float), 1, fp);
		}
	}

	if(fp != NULL)
		fclose(fp);
}