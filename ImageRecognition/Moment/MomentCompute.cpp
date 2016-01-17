#include "MomentCompute.h"

MomentCompute::MomentCompute()
{
	m_minWidthFilter = 15;
	m_minHeightFilter = 15;
}


std::vector<CentralMoment>&	MomentCompute::ComputeMoments( std::vector<Segment*>& segments )
{
	// Future
	//filteredSegments = FilterSegments( segments );
	std::vector<Segment*>& filteredSegments = segments;

	for( auto segment : filteredSegments )
	{
		CentralMoment newMoment = SegmentMoments( segment );
		m_moments.push_back( newMoment );
	}

	return m_moments;
}






std::vector<Segment*>		MomentCompute::FilterSegments( std::vector<Segment*>& segments )
{
	std::vector<Segment*>	filteredSegs;
	filteredSegs.reserve( segments.size() );

	for( auto segment : segments )
	{
		auto& box = segment->GetBoundingBox();
		if( box.GetWidth() >= m_minWidthFilter && box.GetHeight() >= m_minHeightFilter )
			filteredSegs.push_back( segment );
	}

	return std::move( filteredSegs );
}


CentralMoment					MomentCompute::SegmentMoments	( Segment* segment )
{
	CentralMoment newMoment;
	auto& pixels = segment->GetRegion();

	cv::Vec2i center = SegmentsCenter( segment );



	return newMoment;
}

cv::Vec2i					MomentCompute::SegmentsCenter	( Segment* segment )
{

}

Moment						MomentCompute::Moments			( std::vector<Pixel>* pixels, cv::Vec2i center )
{

}

