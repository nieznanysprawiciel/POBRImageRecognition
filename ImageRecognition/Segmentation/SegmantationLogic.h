#ifndef SEGMANTATIONLOGIC_H
#define SEGMANTATIONLOGIC_H

#include "opencv2/core/core.hpp"
#include "Segment.h"
#include <vector>
#include <QStringListModel>
#include "Moment/MomentDesc.h"


class SegmentationLogic
{
private:
	unsigned int				m_samplesDensity;
	unsigned int				m_samplesDensityText;
	cv::Vec3b					m_fillColor;

	std::vector<Segment*>		m_segments1;
	std::vector<Segment*>		m_segments2;

	QStringListModel			m_segmentsModel1;
	QStringListModel			m_segmentsModel2;

public:
	SegmentationLogic();
	virtual ~SegmentationLogic();

	std::vector<Segment*>&		GetSegments( int );
	void						ClearSegments();
	void						ClearTextSegments();

	virtual void				MakeSegmentation	( cv::Mat& image );
	void						MakeSegmentationText( cv::Mat& image, std::vector<MomentInvariant>& moments );

	QStringListModel*			GetSegmentsModel	( int );

private:
	bool						CheckInSegments		( Pixel pixel );
	bool						CheckInBoundingBox	( Pixel pixel, BoundingBox& box );
	bool						IsObject			( cv::Vec3b color );

	Segment*					BuildSegment		( Pixel seedPixel, cv::Mat_<cv::Vec3b>& srcImage );
	void						FloodFill			( Pixel seedPixel, cv::Mat_<cv::Vec3b>& srcImage, Segment* segment );

	short						ExtendLeft			( Pixel seedPixel, cv::Mat_<cv::Vec3b>& srcImage, Segment* segment );
	short						ExtendRight			( Pixel seedPixel, cv::Mat_<cv::Vec3b>& srcImage, Segment* segment );

	short						FindNextSpan		( Pixel begin, cv::Mat_<cv::Vec3b>& srcImage, short maxX );
};

#endif // SEGMANTATIONLOGIC_H
