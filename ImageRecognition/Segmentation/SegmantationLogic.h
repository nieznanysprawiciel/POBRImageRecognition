#ifndef SEGMANTATIONLOGIC_H
#define SEGMANTATIONLOGIC_H

#include "opencv2/core/core.hpp"
#include "Segment.h"
#include <vector>


class SegmentationLogic
{
private:
	unsigned int				m_samplesDensity;
	cv::Vec3b					m_fillColor;

	std::vector<Segment*>		m_segments;

public:
	SegmentationLogic();
	virtual ~SegmentationLogic();

	std::vector<Segment*>&		GetSegments()	{ return m_segments; }
	void						ClearSegments();

	virtual void				MakeSegmentation	( cv::Mat& image );

private:
	bool						CheckInSegments		( Pixel pixel );
	bool						CheckInBoundingBox	( Pixel pixel, BoundingBox& box );
	bool						IsObject			( cv::Vec3b color );

	Segment*					BuildSegment		( Pixel seedPixel, cv::Mat_<cv::Vec3b>& srcImage );
	void						FloodFill			( Pixel seedPixel, cv::Mat_<cv::Vec3b>& srcImage, Segment* segment );

	unsigned short				ExtendLeft			( Pixel seedPixel, cv::Mat_<cv::Vec3b>& srcImage, Segment* segment );
	unsigned short				ExtendRight			( Pixel seedPixel, cv::Mat_<cv::Vec3b>& srcImage, Segment* segment );

	unsigned short				FindNextSpan		( Pixel begin, cv::Mat_<cv::Vec3b>& srcImage, unsigned short maxX );
};

#endif // SEGMANTATIONLOGIC_H
