#include "define.h"

#define EXPORT_API __declspec(dllexport)

extern "C"{
	void EXPORT_API TEST(){
		MessageBox(NULL, L"TEST SUCCESS", L"TEST", MB_OK);
	}
}