#include "ImageLogic.h"

#include "ProcessingList.h"
#include "ImageProcessor.h"
#include "opencv2/highgui/highgui.hpp"

ImageLogic::ImageLogic()
{
	// Tworzymy miejsce dla obrazu źródłowego
	m_commonImages.push_back( cv::Mat() );
}


void		ImageLogic::ProcessImages( ProcessingList* list1, ProcessingList* list2 )
{
	auto& processors1 = list1->GetProcessors();
	auto& processors2 = list2->GetProcessors();

	assert( list1->GetNumCommonProc() == list2->GetNumCommonProc() );

	int commonProc = list1->GetNumCommonProc();

	if( commonProc != m_commonImages.size() )
		AllocateImages( commonProc, 0 );

	if( processors1.size() != m_path1.size() )
		AllocateImages( processors1.size() - commonProc, 1 );

	if( processors2.size() != m_path2.size() )
		AllocateImages( processors2.size() - commonProc, 2 );

	for( unsigned int i = 1; i < commonProc; ++i )
		processors1[ i ]->Process( m_commonImages[ i - 1 ], m_commonImages[ i ] );

	cv::Mat* prev = &GetLastImage( 0 );
	for( unsigned int i = commonProc; i < processors1.size(); ++i )
	{
		processors1[ i ]->Process( *prev, m_path1[ i - commonProc ] );
		prev = &m_path1[ i - commonProc ];
	}

	prev = &GetLastImage( 0 );
	for( unsigned int i = commonProc; i < processors2.size(); ++i )
	{
		processors2[ i ]->Process( *prev, m_path2[ i - commonProc ] );
		prev = &m_path2[ i - commonProc ];
	}
}

void		ImageLogic::AllocateImages	( unsigned int newSize, int path )
{
	auto& imageVector = GetImageVector( path );

	if( imageVector.size() > newSize )
		imageVector.resize( newSize );
	else
	{
		for( unsigned int i = imageVector.size(); i < newSize; ++i )
		{
			imageVector.push_back( cv::Mat() );
			imageVector[ i ].create( m_commonImages[ 0 ].rows, m_commonImages[ 0 ].cols, CV_8UC3 );
		}
	}
}

bool		ImageLogic::LoadImage		( const std::string& fileName )
{
	m_commonImages[ 0 ] = cv::imread( fileName );

	unsigned int imagesSize = m_commonImages.size();
	if( imagesSize == 1 )
		return true;

	// Stwórz odpowiednią ilość obrazów odpowiedniej wielkości.
	m_commonImages.erase( m_commonImages.begin() + 1, m_commonImages.end() );
	AllocateImages( imagesSize, 0 );

	return true;
}

cv::Mat&	ImageLogic::GetSourceImage	()
{
	return m_commonImages[ 0 ];
}

cv::Mat&	ImageLogic::GetImage		( unsigned int index, int path  )
{
	auto& imageVec = GetImageVector( path );

	if( index < m_commonImages.size() )
		return m_commonImages[ index ];

	index = index - m_commonImages.size();
	if( index < imageVec.size() )
		return imageVec[ index ];

	return m_commonImages[ 0 ];		/// ??
}

cv::Mat&	ImageLogic::GetSegmentsImage( int path )
{
	assert( path == 1 || path == 2 );

	if( path == 1 )
		return m_segmentsImage1;
	else
		return m_segmentsImage2;
}

cv::Mat&	ImageLogic::CreateSegmentsImage( int path )
{
	auto& lastImage = GetLastImage( path );

	assert( path == 0 );

	if( path == 1)
	{
		m_segmentsImage1 = lastImage.clone();
		return m_segmentsImage1;
	}
	else
	{
		m_segmentsImage2 = lastImage.clone();
		return m_segmentsImage2;
	}
}

cv::Mat&	ImageLogic::GetLastImage	( int path )
{
	if( path == 0 )
		return m_commonImages.back();
	else if( path == 1)
		return m_path1.back();
	else
		return m_path2.back();
}

std::vector< cv::Mat >&			ImageLogic::GetImageVector( int path )
{
	if( path == 0 )
		return m_commonImages;
	else if( path == 1)
		return m_path1;
	else
		return m_path2;
}
