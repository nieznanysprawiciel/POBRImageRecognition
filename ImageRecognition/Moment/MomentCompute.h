#ifndef MOMENTCOMPUTE_H
#define MOMENTCOMPUTE_H

#include "opencv2/core/core.hpp"
#include "../Segmentation/Segment.h"
#include "MomentDesc.h"

#include <vector>
//#include <QStringListModel>



class MomentCompute
{
private:
	int				m_minWidthFilter;
	int				m_minHeightFilter;

	std::vector<CentralMoment>		m_moments;
public:
	MomentCompute();

	std::vector<CentralMoment>&	ComputeMoments	( std::vector<Segment*>& segments );

	std::vector<CentralMoment>&	GetMoments		()	{ return m_moments; }

private:
	std::vector<Segment*>		FilterSegments	( std::vector<Segment*>& segments );

	CentralMoment				SegmentMoments	( Segment* segment );
	cv::Vec2i					SegmentsCenter	( Segment* segment );

	Moment						Moments			( std::vector<Pixel>* pixels , cv::Vec2i center );

	double						ComputeM1		( Moment& moment );
	double						ComputeM2		( Moment& moment );
	double						ComputeM3		( Moment& moment );
	double						ComputeM4		( Moment& moment );
	double						ComputeM5		( Moment& moment );
	double						ComputeM6		( Moment& moment );
	double						ComputeM7		( Moment& moment );
	double						ComputeM8		( Moment& moment );
	double						ComputeM9		( Moment& moment );
	double						ComputeM10		( Moment& moment );
};

#endif // MOMENTCOMPUTE_H
