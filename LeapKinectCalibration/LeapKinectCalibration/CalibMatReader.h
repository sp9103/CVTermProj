#include "define.h"

class CalibMatReader
{
public:
	CalibMatReader(void);
	~CalibMatReader(void);

	int ReadMat(char *filepath, cv::Mat *CalibMat);

	void WriteMat(char *filepath, cv::Mat CalibMat);
};

