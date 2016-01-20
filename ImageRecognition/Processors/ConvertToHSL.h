#ifndef CONVERTTOHSL_H
#define CONVERTTOHSL_H

#include "../ImageProcessor.h"



class ConvertToHSL : public ImageProcessor
{
private:
public:
	ConvertToHSL();

	virtual void Process( cv::Mat& srcImage, cv::Mat& destImage ) override;

private:
	cv::Vec3b	ToHSL( cv::Mat_<cv::Vec3b>& image, int i, int j );
};

#endif // CONVERTTOHSL_H
