#ifndef FAKEPROCESSOR_H
#define FAKEPROCESSOR_H

#include "ImageProcessor.h"



class FakeProcessor : public ImageProcessor
{
private:

public:
	FakeProcessor()
	: ImageProcessor( "Obrazek źródłowy" ) {}

	virtual void Process( cv::Mat&, cv::Mat& ) override {}
};

#endif // FAKEPROCESSOR_H
