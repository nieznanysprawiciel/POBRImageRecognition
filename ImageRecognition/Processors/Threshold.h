#ifndef THRESHOLD_H
#define THRESHOLD_H

#include "ImageProcessor.h"


class Threshold : public ImageProcessor
{
private:
	unsigned char m_minR;
	unsigned char m_maxR;
	unsigned char m_minG;
	unsigned char m_maxG;
	unsigned char m_minB;
	unsigned char m_maxB;

public:
	Threshold(	const std::string& name,
				unsigned char maxR, unsigned char minR,
				unsigned char maxG, unsigned char minG,
				unsigned char maxB, unsigned char minB );

	virtual void Process( cv::Mat& srcImage, cv::Mat& destImage ) override;
};

#endif // THRESHOLD_H
