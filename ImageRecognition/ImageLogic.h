#ifndef IMAGELOGIC_H
#define IMAGELOGIC_H

#include "opencv2/core/core.hpp"

#include <vector>
#include <string>


class ProcessingList;



class ImageLogic
{
private:
	std::vector< cv::Mat >		m_commonImages;
	std::vector< cv::Mat >		m_path1;
	std::vector< cv::Mat >		m_path2;


	cv::Mat						m_segmentsImage1;
	cv::Mat						m_segmentsImage2;

public:
	ImageLogic();

	void		ProcessImages	( ProcessingList* list1 , ProcessingList* list2 );
	void		AllocateImages	( unsigned int newSize, int path );

	bool		LoadImage		( const std::string& fileName );

	cv::Mat&	GetSourceImage	();
	cv::Mat&	GetImage		( unsigned int index , int path );
	cv::Mat&	GetLastImage	( int path );
	cv::Mat&	GetSegmentsImage( int path );

	cv::Mat&	CreateSegmentsImage( int path );

private:
	std::vector< cv::Mat >&			GetImageVector( int path );
};

#endif // IMAGELOGIC_H
