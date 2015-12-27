#ifndef MASKFILTERBASE_H
#define MASKFILTERBASE_H

#include "../ImageProcessor.h"


class MaskFilterBase : public ImageProcessor
{
private:
	cv::Mat1f		m_mask;
public:
	virtual ~MaskFilterBase();
	MaskFilterBase(	const std::string& processorName,
					float x1, float y1, float z1,
					float x2, float y2, float z2,
					float x3, float y3, float z3,
					float divider );


	virtual void	Process( cv::Mat& srcImage, cv::Mat& destImage ) override;

private:
	cv::Vec3b		Filter( cv::Mat_<cv::Vec3b>& image, int i, int j, cv::Mat1f& filter );
};

#endif // MASKFILTERBASE_H
