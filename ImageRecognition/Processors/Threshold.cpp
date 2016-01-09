#include "Threshold.h"



Threshold::Threshold(	const std::string& name,
						unsigned char maxR, unsigned char minR,
						unsigned char maxG, unsigned char minG,
						unsigned char maxB, unsigned char minB )
						: ImageProcessor( name ),
						m_minR( minR ),
						m_maxR( maxR ),
						m_minG( minG ),
						m_maxG( maxG ),
						m_minB( minB ),
						m_maxB( maxB )
{}

void Threshold::Process( cv::Mat& srcImage, cv::Mat& destImage )
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

		for (int i = 0; i < srcImage.rows; ++i)
		{
			for (int j = 0; j < srcImage.cols; ++j)
			{
				cv::Vec3b lastValue = source(i, j);
				if( lastValue[ 0 ] >= m_minB && lastValue[ 0 ] <= m_maxB
				&&	lastValue[ 1 ] >= m_minG && lastValue[ 1 ] <= m_maxG
				&&	lastValue[ 2 ] >= m_minR && lastValue[ 2 ] <= m_maxR )
					destination( i, j ) = cv::Vec3b( 255, 255, 255 );
			}
		}

	break;
	}
}
