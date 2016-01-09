#include "SegmantationLogic.h"




SegmantationLogic::SegmantationLogic()
{
}


void		SegmantationLogic::ClearSegments()
{
	for( auto segment : m_segments )
		delete segment;
	m_segments.clear();
}


void		SegmantationLogic::MakeSegmentation( cv::Mat& srcImage )
{

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
