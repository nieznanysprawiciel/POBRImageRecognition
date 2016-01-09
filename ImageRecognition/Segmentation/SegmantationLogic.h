#ifndef SEGMANTATIONLOGIC_H
#define SEGMANTATIONLOGIC_H

#include "opencv2/core/core.hpp"
#include "Segment.h"
#include <vector>


class SegmantationLogic
{
private:
	std::vector<Segment*>		m_segments;
public:
	SegmantationLogic();

	std::vector<Segment*>&		GetSegments()	{ return m_segments; }
	void						ClearSegments();

	void						MakeSegmentation( cv::Mat& srcImage );

private:
	bool						CheckInSegments		( Pixel pixel );
	bool						CheckInBoundingBox	( Pixel pixel, BoundingBox& box );
};

#endif // SEGMANTATIONLOGIC_H
