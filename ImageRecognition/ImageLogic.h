#ifndef IMAGELOGIC_H
#define IMAGELOGIC_H

#include "opencv2/core/core.hpp"

#include <vector>
#include <string>


class ProcessingList;



class ImageLogic
{
private:
	std::vector< cv::Mat >		m_images;
	cv::Mat						m_sourceImage;
public:
	ImageLogic();

	void		ProcessImages	( ProcessingList* list );
	void		AllocateImages	( unsigned int newSize );

	bool		LoadImage		( const std::string& fileName );

	cv::Mat&	GetSourceImage	();
	cv::Mat&	GetImage		( unsigned int index );
	cv::Mat&	GetLastImage	()	{ return m_images.back(); }
};

#endif // IMAGELOGIC_H
