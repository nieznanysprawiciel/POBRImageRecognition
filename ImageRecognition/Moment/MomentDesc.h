#ifndef MOMENTDESC_H
#define MOMENTDESC_H

#include "opencv2/core/core.hpp"


struct CentralMoment
{
	double M1;
	double M2;
	double M3;
	double M4;
	double M5;
	double M6;
	double M7;
	double M8;
	double M9;
	double M10;

	cv::Vec2i	Center;
};


#define MOMENT_X_DIMM 4
#define MOMENT_Y_DIMM 4

struct Moment
{
	double	xy[ MOMENT_X_DIMM ][ MOMENT_Y_DIMM ];
};


#endif // MOMENTDESC_H
