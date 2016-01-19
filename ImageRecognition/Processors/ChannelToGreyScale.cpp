#include "ChannelToGreyScale.h"

ChannelToGreyScale::ChannelToGreyScale( const std::string& name, ColorChannel channel )
	:	ImageProcessor( name ),
		m_channelNum( (int)channel )
{}


void ChannelToGreyScale::Process( cv::Mat& srcImage, cv::Mat& destImage )
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

		for ( int i = 0; i < srcImage.rows; ++i )
		{
			for ( int j = 0; j < srcImage.cols; ++j )
			{
				cv::Vec3b lastValue = source( i, j );
				unsigned char color = lastValue[ m_channelNum ];
				destination( i, j ) = cv::Vec3b( color, color, color );
			}
		}

	break;
	}
}

