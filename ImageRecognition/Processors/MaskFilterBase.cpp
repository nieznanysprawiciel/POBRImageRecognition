#include "MaskFilterBase.h"
#include "Helpers.h"


MaskFilterBase::MaskFilterBase(const std::string& processorName, float x1, float y1, float z1,
								float x2, float y2, float z2,
								float x3, float y3, float z3,
								float divider )
								:	ImageProcessor( processorName ),
									m_mask( 3, 3 )
{
	FillMatrix( m_mask, x1, y1, z1,
						x2, y2, z2,
						x3, y3, z3,
						divider );

}

MaskFilterBase::~MaskFilterBase()
{}

void		MaskFilterBase::Process( cv::Mat& srcImage, cv::Mat& destImage )
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
				destination( i, j ) = Filter( source, i, j, m_mask );
		}

	break;
	}
}


cv::Vec3b	MaskFilterBase::Filter( cv::Mat_<cv::Vec3b>& image, int i, int j, cv::Mat1f& filter )
{
	cv::Vec3f result( 0.0, 0.0, 0.0 );

	for (int k = -1; k < 2; ++k )
	{
		for (int l = -1; l < 2; ++l)
		{
			cv::Vec3f pixel = image(i + k, j + l);
			auto filterVal = filter(k + 1, l + 1);
			result[0] += pixel[0] * filterVal;
			result[1] += pixel[1] * filterVal;
			result[2] += pixel[2] * filterVal;
		}
	}
	return Clamp( result );
}
