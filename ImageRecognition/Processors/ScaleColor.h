#ifndef SCALECOLOR_H
#define SCALECOLOR_H

#include "ImageProcessor.h"


class ScaleColor : public ImageProcessor
{
private:
	float		m_scaleR;
	float		m_scaleG;
	float		m_scaleB;
public:
	ScaleColor( const std::string& filterName,
				float scaleR, float scaleG, float scaleB );

	virtual void Process( cv::Mat& srcImage, cv::Mat& destImage ) override;
private:
	cv::Vec3b		Scale( cv::Mat_<cv::Vec3b>& image, int i, int j );
};

#endif // SCALECOLOR_H
