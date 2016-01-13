#include "SegmantationLogic.h"


#define NUM_PREDEFINED_COLORS 30
cv::Vec3b predefinedColors[ NUM_PREDEFINED_COLORS ];




SegmentationLogic::SegmentationLogic()
{
	m_samplesDensity = 15;

	int R = 0;
	int G = 100;
	int B = 200;
	for( auto& color : predefinedColors )
	{
		color = cv::Vec3b( B, G, R );
		R = ( R + 73 ) % 255;
		G = ( G + 213 ) % 255;
		B = ( B + 23 ) % 255;
	}

}

SegmentationLogic::~SegmentationLogic()
{
	ClearSegments();
}


void		SegmentationLogic::ClearSegments()
{
	for( auto segment : m_segments )
		delete segment;
	m_segments.clear();
}


void		SegmentationLogic::MakeSegmentation( cv::Mat& image )
{
	ClearSegments();
	cv::Mat_<cv::Vec3b> source = image;
	int segmentNum = 0;
	QStringList newSegmentsList;

	for( int y = m_samplesDensity / 2; y < image.rows; y += m_samplesDensity )
	{
		for ( int x = m_samplesDensity / 2; x < image.cols; x += m_samplesDensity )
		{
			cv::Vec3b color = source( y ,x );
			Pixel seedPixel( x, y );

			if( !IsObject( color ) )
				continue;
			if( CheckInSegments( seedPixel ) )
				continue;

			newSegmentsList.append( "Segment" + QString::number( segmentNum ) );
			m_fillColor = predefinedColors[ segmentNum++ % NUM_PREDEFINED_COLORS ];

			Segment* newSegment = BuildSegment( seedPixel, source );
			m_segments.push_back( newSegment );
		}
	}

	m_segmentsModel.setStringList( newSegmentsList );

//	// Test
//	Pixel seedPixel( 485, 452 );
//	Segment* newSegment = BuildSegment( seedPixel, source );
//	m_segments.push_back( newSegment );

//	seedPixel = Pixel( 542, 485 );
//	newSegment = BuildSegment( seedPixel, source );
//	m_segments.push_back( newSegment );
}


bool		SegmentationLogic::CheckInSegments( Pixel pixel )
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

bool		SegmentationLogic::CheckInBoundingBox	( Pixel pixel, BoundingBox& box )
{
	if( pixel.X <= box.maxX && pixel.X >= box.minX
	&&	pixel.Y <= box.maxY && pixel.Y >= box.minY )
		return true;
	return false;
}

bool		SegmentationLogic::IsObject	( cv::Vec3b color )
{
	if( color == cv::Vec3b( 255, 255, 255 ) )
		return true;
	return false;
}



Segment*	SegmentationLogic::BuildSegment		( Pixel seedPixel, cv::Mat_<cv::Vec3b>& srcImage )
{
	Segment* newSegment = new Segment;

	auto& regionPixels = newSegment->GetRegion();
	regionPixels.reserve( 400 );		// Rezeruwjemy pamięć, bo regiony będą raczej dużo zajmować.

	FloodFill( seedPixel, srcImage, newSegment );

	return newSegment;
}

// Flood fill
//

#include <queue>

#define DIRECTION_UP -1
#define DIRECTION_DOWN 1

struct PixelSpan
{
	short		leftPixelX;
	short		rightPixelX;
	short		pixelsY;
	char				direction;

	PixelSpan( short left, short right, short pixY, char dir )
	{
		leftPixelX = left;
		rightPixelX = right;
		pixelsY = pixY;
		direction = dir;
	}
};

void SegmentationLogic::FloodFill( Pixel seedPixel, cv::Mat_<cv::Vec3b>& srcImage, Segment* segment )
{
	auto& boundingBox = segment->GetBoundingBox();
	std::queue<PixelSpan>	linesToFill;

	short leftPix = ExtendLeft( seedPixel, srcImage, segment );
	short rightPix = ExtendRight( seedPixel, srcImage, segment );
	boundingBox.TryUpdateMinMaxX( leftPix );
	boundingBox.TryUpdateMinMaxX( rightPix );

	linesToFill.push( PixelSpan( leftPix, rightPix, seedPixel.Y + DIRECTION_DOWN, DIRECTION_DOWN ) );
	linesToFill.push( PixelSpan( leftPix, rightPix, seedPixel.Y + DIRECTION_UP, DIRECTION_UP ) );


	while( !linesToFill.empty() )
	{
		auto currentLine = linesToFill.front();
		linesToFill.pop();

		leftPix = currentLine.leftPixelX;
		rightPix = currentLine.rightPixelX;
		short pixY = currentLine.pixelsY;

		if( pixY < 0 )
			continue;

		boundingBox.TryUpdateMinMaxY( pixY );

		auto& leftColor = srcImage( pixY, leftPix );
		if( !IsObject( leftColor ) )
			leftPix = FindNextSpan( Pixel( leftPix, pixY ), srcImage, currentLine.rightPixelX );
		if( leftPix >= currentLine.rightPixelX )
			continue;

		do
		{
			auto prevLeftPix = leftPix;
			leftPix = ExtendLeft( Pixel( prevLeftPix, pixY ), srcImage, segment );
			rightPix = ExtendRight( Pixel( prevLeftPix, pixY ), srcImage, segment );

			if( leftPix < currentLine.leftPixelX || rightPix > currentLine.rightPixelX )
				linesToFill.push( PixelSpan( leftPix, rightPix, pixY - currentLine.direction, -currentLine.direction ) );
			linesToFill.push( PixelSpan( leftPix, rightPix, pixY + currentLine.direction, currentLine.direction ) );

			boundingBox.TryUpdateMinMaxX( leftPix );
			boundingBox.TryUpdateMinMaxX( rightPix );

		} while( FindNextSpan( Pixel( rightPix, pixY ), srcImage, currentLine.rightPixelX ) <= currentLine.rightPixelX );
	}
}


short SegmentationLogic::ExtendLeft( Pixel seedPixel, cv::Mat_<cv::Vec3b>& srcImage, Segment* segment )
{
	auto& regionPixels = segment->GetRegion();
	int pixX = seedPixel.X;

	while( IsObject( srcImage( seedPixel.Y, pixX ) ) )
	{
		srcImage( seedPixel.Y, pixX ) = m_fillColor;
		regionPixels.push_back( Pixel( pixX, seedPixel.Y ) );

		--pixX;
		if( pixX < 0 )
			continue;
	}
	return ++pixX;
}

short SegmentationLogic::ExtendRight( Pixel seedPixel, cv::Mat_<cv::Vec3b>& srcImage, Segment* segment )
{
	auto& regionPixels = segment->GetRegion();

	unsigned short pixX = seedPixel.X + 1;	// Idąc w prawą zawsze pomijamy pierwszy element
	if( pixX > srcImage.cols )
		return --pixX;

	while( IsObject( srcImage( seedPixel.Y, pixX ) ) )
	{
		srcImage( seedPixel.Y, pixX ) = m_fillColor;
		regionPixels.push_back( Pixel( pixX, seedPixel.Y ) );

		++pixX;
		if( pixX > srcImage.cols )
			continue;
	}
	return pixX;
}

short SegmentationLogic::FindNextSpan		( Pixel begin, cv::Mat_<cv::Vec3b>& srcImage, short maxX )
{
	unsigned short pixX = begin.X + 1;	// Idąc  prawą zawsze pomijamy pierwszy element
	if( pixX > maxX )
		return maxX + 1;

	while( !IsObject( srcImage( begin.Y, pixX ) ) )
	{
		++pixX;
		if( pixX > maxX )
			return maxX + 1;
	}
	return pixX;
}



