#include "SegmantationLogic.h"



bool		SegmantationLogic::IsObject	( cv::Vec3b color )
{
	if( color == cv::Vec3b( 1,1,1) )
		return true;
	return false;
}


SegmantationLogic::SegmantationLogic()
{
	m_samplesDensity = 15;
}


void		SegmantationLogic::ClearSegments()
{
	for( auto segment : m_segments )
		delete segment;
	m_segments.clear();
}


void		SegmantationLogic::MakeSegmentation( cv::Mat& srcImage , cv::Mat& destImage )
{
	cv::Mat_<cv::Vec3b> source = srcImage;
	cv::Mat_<cv::Vec3b> destination = destImage;


	for( int j = m_samplesDensity / 2; j < srcImage.cols; j += m_samplesDensity )
	{
		for ( int i = m_samplesDensity / 2; i < srcImage.rows; i += m_samplesDensity )
		{
			cv::Vec3b color = source( i ,j );
			Pixel seedPixel( i, j );

			if( !IsObject( color ) )
				continue;
			if( CheckInSegments( seedPixel ) )
				continue;

			Segment* newSegment = BuildSegment( seedPixel, source, destination );
			m_segments.push_back( newSegment );
		}
	}
}


bool		SegmantationLogic::CheckInSegments( Pixel pixel )
{
	for( auto segment : m_segments )
	{
		if( CheckInBoundingBox( pixel, segment->GetBoundingBox() ) )
		{
			auto& pixInSegment = segment->GetRegion();
			for( auto segPixel : pixInSegment )
				if( pixel == segPixel )
					return true;
		}
	}
	return false;
}

bool		SegmantationLogic::CheckInBoundingBox	( Pixel pixel, BoundingBox& box )
{
	if( pixel.X <= box.maxX && pixel.X >= box.minX
	&&	pixel.Y <= box.maxY && pixel.Y >= box.minY )
		return true;
	return false;
}



Segment*	SegmantationLogic::BuildSegment		( Pixel seedPixel, cv::Mat_<cv::Vec3b>& srcImage, cv::Mat_<cv::Vec3b>& destImage )
{
	Segment* newSegment = new Segment;

	auto& regionPixels = newSegment->GetRegion();
	regionPixels.reserve( 400 );		// Rezeruwjemy pamięć, bo regiony będą raczej dużo zajmować.

	// W przyszłości trzeba wylosować kolor za każdym razem lub wybrac z palety
	m_fillColor = cv::Vec3b( 0, 0, 1 );

	FloodFill( seedPixel, srcImage, destImage, newSegment );

	return newSegment;
}

// Flood fill
//

#include <queue>

#define DIRECTION_UP -1
#define DIRECTION_DOWN 1

struct PixelSpan
{
	unsigned short		leftPixelX;
	unsigned short		rightPixelX;
	unsigned short		pixelsY;
	char				direction;

	PixelSpan( unsigned short left, unsigned short right, unsigned short pixY, char dir )
	{
		leftPixelX = left;
		rightPixelX = right;
		pixelsY = pixY;
		direction = dir;
	}
};

void SegmantationLogic::FloodFill( Pixel seedPixel, cv::Mat_<cv::Vec3b>& srcImage, cv::Mat_<cv::Vec3b>& destImage, Segment* segment )
{
	auto& boundingBox = segment->GetBoundingBox();
	std::queue<PixelSpan>	linesToFill;

	unsigned short leftPix = ExtendLeft( seedPixel, srcImage, destImage, segment );
	unsigned short rightPix = ExtendRight( seedPixel, srcImage, destImage, segment );
	boundingBox.TryUpdateMinMaxX( leftPix );
	boundingBox.TryUpdateMinMaxX( rightPix );

	linesToFill.push( PixelSpan( leftPix, rightPix, seedPixel.Y + DIRECTION_UP, DIRECTION_UP ) );

	while( !linesToFill.empty() )
	{
		auto& currentLine = linesToFill.front();
		leftPix = currentLine.leftPixelX;
		rightPix = currentLine.rightPixelX;
		unsigned short pixY = currentLine.pixelsY;

		boundingBox.TryUpdateMinMaxY( pixY );

		do
		{
			leftPix = ExtendLeft( Pixel( leftPix, pixY ), srcImage, destImage, segment );
			rightPix = ExtendRight( Pixel( leftPix, pixY ), srcImage, destImage, segment );
			linesToFill.push( PixelSpan( leftPix, rightPix, pixY + currentLine.direction, currentLine.direction ) );

			if( leftPix < currentLine.leftPixelX || rightPix > currentLine.rightPixelX )
				linesToFill.push( PixelSpan( leftPix, rightPix, pixY - currentLine.direction, -currentLine.direction ) );

			boundingBox.TryUpdateMinMaxX( leftPix );
			boundingBox.TryUpdateMinMaxX( rightPix );

		} while( FindNextSpan( Pixel( rightPix, pixY ), srcImage, currentLine.rightPixelX ) != currentLine.rightPixelX );


		linesToFill.pop();
	}
}


unsigned short SegmantationLogic::ExtendLeft( Pixel seedPixel, cv::Mat_<cv::Vec3b>& srcImage, cv::Mat_<cv::Vec3b>& destImage, Segment* segment )
{
	auto& regionPixels = segment->GetRegion();
	int pixX = seedPixel.X;

	while( IsObject( srcImage( pixX, seedPixel.Y ) ) )
	{
		destImage( pixX, seedPixel.Y ) = m_fillColor;
		regionPixels.push_back( Pixel( pixX, seedPixel.Y ) );

		--pixX;
		if( pixX < 0 )
			continue;
	}
	return ++pixX;
}

unsigned short SegmantationLogic::ExtendRight( Pixel seedPixel, cv::Mat_<cv::Vec3b>& srcImage, cv::Mat_<cv::Vec3b>& destImage, Segment* segment )
{
	auto& regionPixels = segment->GetRegion();

	unsigned short pixX = seedPixel.X + 1;	// Idąc  prawą zawsze pomijamy pierwszy element
	if( pixX > srcImage.rows )
		return --pixX;

	while( IsObject( srcImage( pixX, seedPixel.Y ) ) )
	{
		destImage( pixX, seedPixel.Y ) = m_fillColor;
		regionPixels.push_back( Pixel( pixX, seedPixel.Y ) );

		++pixX;
		if( pixX > srcImage.cols )
			continue;
	}
	return --pixX;
}

unsigned short SegmantationLogic::FindNextSpan		( Pixel begin, cv::Mat_<cv::Vec3b>& srcImage, unsigned short maxX )
{
	unsigned short pixX = begin.X + 1;	// Idąc  prawą zawsze pomijamy pierwszy element
	if( pixX > maxX )
		return maxX;

	while( !IsObject( srcImage( pixX, begin.Y ) ) )
	{
		++pixX;
		if( pixX > maxX )
			continue;
	}
	return --pixX;
}



