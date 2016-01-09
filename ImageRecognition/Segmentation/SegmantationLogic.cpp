#include "SegmantationLogic.h"




SegmantationLogic::SegmantationLogic()
{
	m_samplesDensity = 15;
}


void		SegmantationLogic::ClearSegments()
{
	for( auto segment : m_segments )
		delete segment;
	m_segments.clear();
}


void		SegmantationLogic::MakeSegmentation( cv::Mat& srcImage )
{
	cv::Mat_<cv::Vec3b> source = srcImage;
	for( int j = m_samplesDensity / 2; j < srcImage.cols; j += m_samplesDensity )
	{
		for ( int i = m_samplesDensity / 2; i < srcImage.rows; i += m_samplesDensity )
		{
			cv::Vec3b color = source( i ,j );
			Pixel seedPixel( i, j );

			if( !IsObject( color ) )
				continue;
			if( CheckInSegments( seedPixel ) )
				continue;

			Segment* newSegment = BuildSegment( seedPixel, source );
			m_segments.push_back( newSegment );
		}
	}
}


bool		SegmantationLogic::CheckInSegments( Pixel pixel )
{
	for( auto segment : m_segments )
	{
		if( CheckInBoundingBox( pixel, segment->GetBoundingBox() ) )
		{
			auto& pixInSegment = segment->GetRegion();
			for( auto segPixel : pixInSegment )
				if( pixel == segPixel )
					return true;
		}
	}
	return false;
}

bool		SegmantationLogic::CheckInBoundingBox	( Pixel pixel, BoundingBox& box )
{
	if( pixel.X <= box.maxX && pixel.X >= box.minX
	&&	pixel.Y <= box.maxY && pixel.Y >= box.minY )
		return true;
	return false;
}

bool		SegmantationLogic::IsObject	( cv::Vec3b color )
{
	if( color == cv::Vec3b( 1,1,1) )
		return true;
	return false;
}

Segment*	SegmantationLogic::BuildSegment		( Pixel seedPixel, cv::Mat_<cv::Vec3b>& srcImage )
{

}
