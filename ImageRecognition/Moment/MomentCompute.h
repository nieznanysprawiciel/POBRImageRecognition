#ifndef MOMENTCOMPUTE_H
#define MOMENTCOMPUTE_H

#include "opencv2/core/core.hpp"
#include "../Segmentation/Segment.h"
#include "MomentDesc.h"

#include <vector>
#include <QStringListModel>



class MomentCompute
{
private:
	int				m_minWidthFilter;
	int				m_minHeightFilter;

	std::vector<MomentInvariant>		m_moments;
	std::vector<MomentInvariant>		m_recognized;
	QStringListModel					m_model;
public:
	MomentCompute();

	QStringListModel*				Predict			();
	std::vector<MomentInvariant>&	ComputeMoments	( std::vector<Segment*>& segments );
	std::vector<MomentInvariant>&	GetMoments		()	{ return m_moments; }
	std::vector<MomentInvariant>&	GetRecognized	()	{ return m_recognized; }

	void							ClearMoments	()	{ m_moments.clear(); }

	QStringListModel*				GetMomentModel	()	{ return &m_model; }

private:
	std::vector<Segment*>		FilterSegments	( std::vector<Segment*>& segments );
	bool						CheckCondition	( MomentInvariant& moment );

	MomentInvariant				SegmentMoments	( Segment* segment );
	cv::Vec2d					SegmentsCenter	( Segment* segment );

	Moment						Moments			(std::vector<Pixel>& pixels , cv::Vec2d center );

	double						ComputeM1		( Moment& moment, double m00 );
	double						ComputeM2		( Moment& moment, double m00 );
	double						ComputeM3		( Moment& moment, double m00 );
	double						ComputeM4		( Moment& moment, double m00 );
	double						ComputeM5		( Moment& moment, double m00 );
	double						ComputeM6		( Moment& moment, double m00 );
	double						ComputeM7		( Moment& moment, double m00 );
	double						ComputeM8		( Moment& moment, double m00 );
	double						ComputeM9		( Moment& moment, double m00 );
	double						ComputeM10		( Moment& moment, double m00 );
};

#endif // MOMENTCOMPUTE_H
