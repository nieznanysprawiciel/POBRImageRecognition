#include "MedianFilter.h"
#include <algorithm>

bool			Order	( cv::Vec3b color1, cv::Vec3b color2 );


MedianFilter::MedianFilter()
	:	ImageProcessor( "Filtr medianowy" )
{
	m_threshold = 5;
}


MedianFilter::~MedianFilter()
{}





void		MedianFilter::Process( cv::Mat& srcImage, cv::Mat& destImage )
{
	CV_Assert( srcImage.depth() != sizeof(uchar) );
	CV_Assert( srcImage.rows == destImage.rows );
	CV_Assert( srcImage.cols == destImage.cols );

	switch( srcImage.channels() )
	{
	case 1:
		CV_Assert(false);
	case 3:
		cv::Mat_<cv::Vec3b> source = srcImage;
		cv::Mat_<cv::Vec3b> destination = destImage;

		std::vector<cv::Vec3b> colors;
		colors.resize( 9 );

		for ( int i = 1; i < srcImage.rows - 1; ++i )
		{
			for ( int j = 1; j < srcImage.cols - 1; ++j )
			{
				colors[0] = source( i - 1, j - 1 );
				colors[1] = source( i    , j - 1 );
				colors[2] = source( i + 1, j - 1 );

				colors[3] = source( i - 1, j );
				colors[4] = source( i    , j );
				colors[5] = source( i + 1, j );

				colors[6] = source( i - 1, j + 1 );
				colors[7] = source( i    , j + 1 );
				colors[8] = source( i + 1, j + 1 );

				std::sort( colors.begin(), colors.end(), Order );

				destination( i, j ) = colors[ 4 ];
			}
		}

	break;
	}
}


bool			Order	( cv::Vec3b color1, cv::Vec3b color2 )
{
	int sum1 = color1[0] + color1[1] + color1[2];
	int sum2 = color2[0] + color2[1] + color2[2];

	if( sum1 < sum2 )
		return true;
	return false;
}

