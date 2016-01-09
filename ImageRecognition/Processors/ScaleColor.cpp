#include "ScaleColor.h"
#include "Helpers.h"



ScaleColor::ScaleColor( const std::string& filterName, float scaleR, float scaleG, float scaleB )
: ImageProcessor( filterName )
{
	m_scaleR = scaleR;
	m_scaleG = scaleG;
	m_scaleB = scaleB;
}


void ScaleColor::Process( cv::Mat& srcImage, cv::Mat& destImage )
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
				destination( i, j ) = Scale( source, i, j );
		}

	break;
	}
}

cv::Vec3b		ScaleColor::Scale( cv::Mat_<cv::Vec3b>& image, int i, int j )
{
	cv::Vec3b lastValue = image(i, j);
	cv::Vec3f newValue;

	newValue[ 0 ] = static_cast<float>( lastValue[ 0 ] ) * m_scaleB;
	newValue[ 1 ] = static_cast<float>( lastValue[ 1 ] ) * m_scaleG;
	newValue[ 2 ] = static_cast<float>( lastValue[ 2 ] ) * m_scaleR;

	return Clamp( newValue );
}

