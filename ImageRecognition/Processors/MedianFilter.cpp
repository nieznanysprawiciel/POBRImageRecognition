#include "MedianFilter.h"

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

		for ( int j = 1; j < srcImage.cols - 1; ++j  )
		{
			for (int i = 1; i < srcImage.rows - 1; ++i )
			{


			}
		}

	break;
	}
}
