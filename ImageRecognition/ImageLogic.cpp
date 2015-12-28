#include "ImageLogic.h"

#include "ProcessingList.h"
#include "ImageProcessor.h"
#include "opencv2/highgui/highgui.hpp"

ImageLogic::ImageLogic()
{
}


void		ImageLogic::ProcessImages( ProcessingList* list )
{
	auto& processors = list->GetProcessors();
	if( processors.size() != m_images.size() )
		AllocateImages( processors.size() );

	cv::Mat* srcImage = &m_sourceImage;
	for( unsigned int i = 0; i < processors.size(); ++i )
	{
		processors[ i ]->Process( *srcImage, m_images[ i ] );
		srcImage = &m_images[ i ];
	}
}

void		ImageLogic::AllocateImages	( unsigned int newSize )
{
	if( m_images.size() > newSize )
		m_images.resize( newSize );
	else
	{
		for( unsigned int i = m_images.size(); i < newSize; ++i )
		{
			m_images.push_back( cv::Mat() );
			m_images[ i ].create( m_sourceImage.rows, m_sourceImage.cols, CV_8UC3 );
		}
	}
}

bool		ImageLogic::LoadImage		( const std::string& fileName )
{
	m_sourceImage = cv::imread( fileName );

	unsigned int imagesSize = m_images.size();
	if( imagesSize == 0 )
		return true;

	// Stwórz odpowiednią ilość obrazów odpowiedniej wielkości.
	m_images.clear();
	AllocateImages( imagesSize );

	return true;
}

cv::Mat&	ImageLogic::GetSourceImage	()
{
	return m_sourceImage;
}

cv::Mat&	ImageLogic::GetImage		( unsigned int index )
{
	if( index < m_images.size() )
		return m_images[ index ];
	return m_sourceImage;		/// ??
}

