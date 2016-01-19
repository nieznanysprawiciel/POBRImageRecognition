#include "ConvertToHSL.h"
#include "Helpers.h"
#include <math.h>


ConvertToHSL::ConvertToHSL()
: ImageProcessor( "RGB -> HSL" )
{}


void ConvertToHSL::Process( cv::Mat& srcImage, cv::Mat& destImage )
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

		for ( int i = 0; i < srcImage.rows; ++i )
		{
			for ( int j = 0; j < srcImage.cols; ++j )
				destination( i, j ) = ToHSL( source, i, j );
		}

	break;
	}
}

/// Helpers
///
cv::Vec3b orderColors( cv::Vec3b color )
{
	cv::Vec3b order( 0, 1, 2 );
	if( color[ 0 ] > color[ 1 ] )
	{
		if( color[ 2 ] > color[ 0 ] )
		{
			order[ 0 ] = 2;
			order[ 2 ] = 0;
		}
	}
	else
	{
		if( color[ 1 ] > color[ 2 ] )
		{
			order[ 0 ] = 1;
			order[ 1 ] = 0;
		}
		else
		{
			order[ 0 ] = 2;
			order[ 2 ] = 0;
		}
	}
	if( color[ order[ 1 ] ] > color[ order[ 2 ] ] )
		std::swap( order[ 1 ], order[ 2 ] );
	return order;
}

float max3( float val1, float val2, float val3 )
{
	return std::max( val1, std::max( val2, val3 ) );
}

float min3( float val1, float val2, float val3 )
{
	return std::min( val1, std::min( val2, val3 ) );
}

#define RED 2
#define GREEN 1
#define BLUE 0

cv::Vec3b		ConvertToHSL::ToHSL( cv::Mat_<cv::Vec3b>& image, int i, int j )
{
	cv::Vec3b lastValue = image(i, j);
	cv::Vec3f color( lastValue[ 0 ] / 255.0f, lastValue[ 1 ] / 255.0f, lastValue[ 2 ] / 255.0f  );
	//cv::Vec3b order = orderColors( lastValue );


	float max = max3( color[ 0 ], color[ 1 ], color[ 2 ] );		//color[ order[ 0 ] ];
	float min = min3( color[ 0 ], color[ 1 ], color[ 2 ] );		//color[ order[ 2 ] ];

	int maxColor = RED;
	if( max == color[ 0 ] )
		maxColor = BLUE;
	else if( max == color[ 1 ] )
		maxColor = GREEN;


	float luminance = ( min + max ) / 2;
	float hue = 0.0f;
	float saturation = 0.0f;

	float maxMinusMin = max - min;
	if( min != max )
	{
		if( luminance <= 0.5f )
			saturation = maxMinusMin / ( max + min );
		else
			saturation = maxMinusMin / ( 2.0f - max - min );


		// Maksymalną wartością jest kanała czerwony
		if( maxColor == RED )
			hue = ( color[ GREEN ] - color[ BLUE ] ) / maxMinusMin;
		// Maksymalną wartością jest kanała zielony
		else if( maxColor == GREEN )
			hue = 2.0f + ( color[ BLUE ] - color[ RED ] ) / maxMinusMin;
		// Maksymalną wartością jest kanała niebieski
		else
			hue = 4.0f + ( color[ RED ] - color[ GREEN ] ) / maxMinusMin;

		hue = hue / 6.0f ;	// Skalowanie do [ 0, 1 ]
		if( hue < 0 )
			hue += 6.0f;
	}
	// else saturation = 0, hue = 0

	cv::Vec3f result;
	result[ 0 ] = 255.0f * luminance;
	result[ 1 ] = 255.0f * saturation;
	result[ 2 ] = 255.0f * hue;

	return Clamp( result );
}
