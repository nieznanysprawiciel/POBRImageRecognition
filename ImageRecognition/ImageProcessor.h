#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include "opencv2/core/core.hpp"

#include <string>

class ImageProcessor
{
private:
protected:
	std::string		m_name;
public:
	ImageProcessor( const std::string &name )
		: m_name( name )	{}
	virtual ~ImageProcessor() = default;

	const std::string& GetName()	{ return m_name; }

	virtual void Process( cv::Mat& srcImage, cv::Mat& destImage ) = 0;
};

#endif // IMAGEPROCESSOR_H
