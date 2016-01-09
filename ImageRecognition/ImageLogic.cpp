#include "ImageLogic.h"

#include "ProcessingList.h"
#include "ImageProcessor.h"
#include "opencv2/highgui/highgui.hpp"

ImageLogic::ImageLogic()
{
	// Tworzymy miejsce dla obrazu źródłowego
	m_images.push_back( cv::Mat() );
}


void		ImageLogic::ProcessImages( ProcessingList* list )
{
	auto& processors = list->GetProcessors();
	if( processors.size() != m_images.size() )
		AllocateImages( processors.size() );


	for( unsigned int i = 1; i < processors.size(); ++i )
		processors[ i ]->Process( m_images[ i - 1 ], m_images[ i ] );
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
			m_images[ i ].create( m_images[ 0 ].rows, m_images[ 0 ].cols, CV_8UC3 );
		}
	}
}

bool		ImageLogic::LoadImage		( const std::string& fileName )
{
	m_images[ 0 ] = cv::imread( fileName );

	unsigned int imagesSize = m_images.size();
	if( imagesSize == 1 )
		return true;

	// Stwórz odpowiednią ilość obrazów odpowiedniej wielkości.
	m_images.erase( m_images.begin() + 1, m_images.end() );
	AllocateImages( imagesSize );

	return true;
}

cv::Mat&	ImageLogic::GetSourceImage	()
{
	return m_images[ 0 ];
}

cv::Mat&	ImageLogic::GetImage		( unsigned int index )
{
	if( index < m_images.size() )
		return m_images[ index ];
	return m_images[ 0 ];		/// ??
}

