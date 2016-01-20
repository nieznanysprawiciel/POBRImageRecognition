#include "MomentCompute.h"

#include <math.h>

MomentCompute::MomentCompute()
{
	m_minWidthFilter = 15;
	m_minHeightFilter = 15;
}


void							MomentCompute::ClearMoments	()
{
	m_moments.clear();
	m_classified.clear();

	// Clear model
	QStringList newSegmentsList;
	m_modelClassified.setStringList( newSegmentsList );
	//m_modelRecogniezed.setStringList( newSegmentsList );
}

std::vector<MomentInvariant>&	MomentCompute::ComputeMoments( std::vector<Segment*>& segments )
{
	// Future
	//std::vector<Segment*>& filteredSegments = FilterSegments( segments );
	std::vector<Segment*>& filteredSegments = segments;

	for( auto segment : filteredSegments )
	{
		MomentInvariant newMoment = SegmentMoments( segment );
		newMoment.SegmentNum = segment->GetSegNummer();
		m_moments.push_back( newMoment );
	}

	return m_moments;
}


QStringListModel*			MomentCompute::Predict			()
{
	QStringList newSegmentsList;

	for( auto& moment : m_moments )
	{
		if( CheckCondition( moment ) )
		{
			newSegmentsList.append( QString( "Segment" ) + QString::number( moment.SegmentNum ));
			m_classified.push_back( moment );
		}
	}

	m_modelClassified.setStringList( newSegmentsList );
	return &m_modelClassified;
}

bool						MomentCompute::CheckCondition	( MomentInvariant& moment )
{
	if( moment.M1 < 1.094e-07 )
	{
		if( moment.M2 >= 0.02324 && moment.M2 < 0.3065 )
		{
			if( moment.M3 < 0.0007278 )
				return true;
		}
	}

	return false;
}

bool		CheckBoundingBoxes( BoundingBox& box1, int width, int height )
{
	double boxRatioX = (double)box1.GetWidth() / (double)width;
	//double boxRatioY = (double)box1.GetHeight() / (double)height;
	double widthHeightRatioBanner = (double)width / (double)height;
	double correctionFactor = 2.7 / widthHeightRatioBanner;

	double widthHeightRatio = (double)box1.GetWidth() / (double)box1.GetHeight();

	widthHeightRatio = widthHeightRatio * correctionFactor;


	if( widthHeightRatio > 2.6 )
		return true;

//	if( boxRatioX > 0.6 /*&& boxRatioY > 0.5*/ )
//		return true;
	return false;
}


QStringListModel*			MomentCompute::Recognize		( std::vector<Segment*>& segments )
{
	QStringList newSegmentsList;

	for( auto& moment : m_classified )
	{
		double textArea = 0.0;
		double bannerArea = moment.Area;
		BoundingBox commonBox;

		for( auto segment : segments )
		{
			if( moment.SegmentNum == segment->GetSegNummer() )
			{
				textArea += segment->GetRegion().size();
				commonBox.TryUpdateMinMaxX( segment->GetBoundingBox().minX );
				commonBox.TryUpdateMinMaxX( segment->GetBoundingBox().maxX );
				commonBox.TryUpdateMinMaxY( segment->GetBoundingBox().minY );
				commonBox.TryUpdateMinMaxY( segment->GetBoundingBox().maxY );
			}
		}
		if( CheckAreaCondition( bannerArea, textArea ) && CheckBoundingBoxes( commonBox, moment.Width, moment.Height ) )
		//if( CheckBoundingBoxes( commonBox, moment.Width, moment.Height ) )
			newSegmentsList.append( QString( "Segment" ) + QString::number( moment.SegmentNum ));
	}

	m_modelRecognized.setStringList( newSegmentsList );
	return &m_modelRecognized;
}

bool						MomentCompute::CheckAreaCondition	( double bannerArea, double textArea )
{
	double ratio = textArea / bannerArea;
	if( ratio > 0.08 && ratio < 0.6 )
		return true;
	return false;
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


MomentInvariant					MomentCompute::SegmentMoments	( Segment* segment )
{
	MomentInvariant newMoment;
	auto& pixels = segment->GetRegion();
	double m00 = pixels.size();

	cv::Vec2d center = SegmentsCenter( segment );

	Moment centralMoments = Moments( pixels, center );

	newMoment.Center = center;
	newMoment.Area = pixels.size();		// Area is number of pixels
	newMoment.Width = segment->GetBoundingBox().GetWidth();
	newMoment.Height = segment->GetBoundingBox().GetHeight();
	newMoment.M1 = ComputeM1( centralMoments, m00 );
	newMoment.M2 = ComputeM2( centralMoments, m00 );
	newMoment.M3 = ComputeM3( centralMoments, m00 );
	newMoment.M4 = ComputeM4( centralMoments, m00 );
	newMoment.M5 = ComputeM5( centralMoments, m00 );
	newMoment.M6 = ComputeM6( centralMoments, m00 );
	newMoment.M7 = ComputeM7( centralMoments, m00 );
	newMoment.M8 = ComputeM8( centralMoments, m00 );
	newMoment.M9 = ComputeM9( centralMoments, m00 );
	newMoment.M10 = ComputeM10( centralMoments, m00 );

	return newMoment;
}

cv::Vec2d					MomentCompute::SegmentsCenter	( Segment* segment )
{
	double acumX = 0.0;
	double acumY = 0.0;

	auto& pixels = segment->GetRegion();
	for( auto pix : pixels )
	{
		acumX += pix.X;
		acumY += pix.Y;
	}
	return cv::Vec2d( acumX / pixels.size(), acumY / pixels.size() );
}

Moment						MomentCompute::Moments			(std::vector<Pixel>& pixels, cv::Vec2d center )
{
	Moment moment;
	moment.Clear();

	double powerX[ MOMENT_X_DIMM ];
	double powerY[ MOMENT_Y_DIMM ];
	powerX[ 0 ] = 1.0;
	powerY[ 0 ] = 1.0;

	for( auto pix : pixels )
	{
		double multiplierX = (double)pix.X - center[ 0 ];
		double multiplierY = (double)pix.Y - center[ 1 ];

		double acumX = 1.0;
		double acumY = 1.0;
		for( int i = 1; i < MOMENT_X_DIMM; ++i )
		{
			acumX *= multiplierX;
			powerX[ i ] = acumX;
		}
		for( int i = 1; i < MOMENT_Y_DIMM; ++i )
		{
			acumY *= multiplierY;
			powerY[ i ] = acumY;
		}

		for( int i = 0; i < MOMENT_X_DIMM; ++i )
		{
			for( int j = 0; j < MOMENT_Y_DIMM; ++j )
			{
				moment.xy[ i ][ j ] += powerX[ i ] * powerY[ j ];
			}
		}
	}

	return moment;
}

//===============================================================//
//				Niezmienniki momentowe
//===============================================================//


double						MomentCompute::ComputeM1		(Moment& moment , double m00)
{
	return ( moment.M20() + moment.M02() ) / pow( m00, 4 );
}

double						MomentCompute::ComputeM2		(Moment& moment , double m00)
{
	return ( pow( ( moment.M20() - moment.M02() ), 2 ) + 4 * moment.M11() * moment.M11() ) / pow( m00, 4 );
}

double						MomentCompute::ComputeM3		(Moment& moment , double m00)
{
	double sum1 = pow( ( moment.M30() - 3 * moment.M12() ), 2 );
	double sum2 = pow( (3 * moment.M21() - moment.M03() ), 2 );
	double m00pow5 = m00 * m00 *m00 * m00 * m00;
	return ( sum1 + sum2 ) / m00pow5;
}

double						MomentCompute::ComputeM4		(Moment& moment , double m00)
{
	double sum1 = pow( ( moment.M30() + moment.M12() ), 2 );
	double sum2 = pow( ( moment.M21() + moment.M03() ), 2 );
	double m00pow5 = m00 * m00 *m00 * m00 * m00;
	return ( sum1 + sum2 ) / m00pow5;
}

double						MomentCompute::ComputeM5		(Moment& moment , double m00)
{
	double factor1 = moment.M30() - 3 * moment.M12();
	double factor2 = moment.M30() + moment.M12();
	double sum1 = pow( ( moment.M30() + moment.M12() ), 2 );
	double sum2 = pow( ( moment.M21() + moment.M03() ), 2 );
	double factor3 = sum1 - 3 * sum2;

	double sumsum1 = factor1 * factor2 * factor3;

	factor1 = 3 * moment.M21() - moment.M03();
	factor2 = moment.M21() + moment.M03();
	factor3 = 3 * sum1 - sum2;

	double sumsum2 = factor1 * factor2 * factor3;

	double m00pow10 = m00 * m00 *m00 * m00 * m00 * m00 * m00 *m00 * m00 * m00;

	return ( sumsum1 + sumsum2 ) / m00pow10;
}

double						MomentCompute::ComputeM6		(Moment& moment , double m00)
{
	double factor1 = moment.M20() - moment.M02();
	double sum1 = ( moment.M30() + moment.M12() );
	double sum2 = ( moment.M21() + moment.M03() );
	double factor2 = pow( sum1, 2 ) - pow( sum2, 2 );

	double sumsum1 = factor1 * factor2;
	double sumsum2 = 4 * moment.M11() * sum1 * sum2;

	double m00pow7 = pow( m00, 7 );
	return ( sumsum1 + sumsum2 ) / m00pow7;
}

double						MomentCompute::ComputeM7		(Moment& moment , double m00)
{
	return ( moment.M20() * moment.M02() - moment.M11() * moment.M11() ) / pow( m00, 4 );
}

double						MomentCompute::ComputeM8		( Moment& moment, double m00 )
{
	return ( moment.M30() * moment.M12() + moment.M21() * moment.M03() - moment.M12() * moment.M12() - moment.M21() * moment.M21() ) / pow( m00, 5 );
}

double						MomentCompute::ComputeM9		( Moment& moment, double m00 )
{
	double sum1 = moment.M20() * ( moment.M21() * moment.M03() - pow( moment.M12(), 2 ) );
	double sum2 = moment.M02() * ( moment.M03() * moment.M12() - pow( moment.M21(), 2 ) );
	double sum3 = moment.M11() * ( moment.M30() * moment.M03() - moment.M21() * moment.M12() );

	double m00pow7 = pow( m00, 7 );
	return ( sum1 + sum2 - sum3 ) / m00pow7;
}

double						MomentCompute::ComputeM10		(Moment& moment , double m00)
{
	double sum1 = pow( ( moment.M30() * moment.M03() - moment.M12() * moment.M21() ), 2 );
	double factor1 = moment.M30() * moment.M12() - pow( moment.M21(), 2 );
	double factor2 = moment.M03() * moment.M21() - moment.M12();

	double m00pow10 = pow( m00, 10 );

	return( sum1 - 4 * factor1 * factor2 ) / m00pow10;
}

