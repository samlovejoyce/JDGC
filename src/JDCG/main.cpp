#include <iostream>

#include "ImageManager.h"


void testImageProcess()
{
	JDGC::ImageManager *pImage = new JDGC::ImageManager();
	pImage->readImage();
}

int main()
{
	testImageProcess();

	getchar();
	return 0;
}