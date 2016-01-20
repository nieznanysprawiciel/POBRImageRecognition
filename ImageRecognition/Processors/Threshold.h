#ifndef THRESHOLD_H
#define THRESHOLD_H

#include "../ImageProcessor.h"


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


class HueThreshold : public Threshold
{
private:
public:
	HueThreshold( unsigned char min, unsigned char max )
	: Threshold( "Progowanie barwy HSL", 255, 0, 255, 0, max, min )
	{}

};

class LuminanceThreshold : public Threshold
{
private:
public:
	LuminanceThreshold( unsigned char min, unsigned char max )
	: Threshold( "Progowanie jasności HSL", max, min, 255, 0, 255, 0 )
	{}

};

class SaturationThreshold : public Threshold
{
private:
public:
	SaturationThreshold( unsigned char min, unsigned char max )
	: Threshold( "Progowanie saturacji HSL", 255, 0, max, min, 255, 0 )
	{}

};

#endif // THRESHOLD_H
