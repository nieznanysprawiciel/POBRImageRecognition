#ifndef MOMENTDESC_H
#define MOMENTDESC_H

#include "opencv2/core/core.hpp"

#include <ostream>

struct MomentInvariant
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
	int			SegmentNum;
	int			Area;

	friend std::ostream& operator<<( std::ostream& stream, const MomentInvariant moment );
	std::ostream& Header( std::ostream& stream );
};

inline std::ostream& operator<<( std::ostream& stream, const MomentInvariant moment )
{
	stream << moment.M1 << ", " << moment.M2 << ", " << moment.M3 << ", " << moment.M4 << ", " << moment.M5 << ", ";
	stream << moment.M6 << ", " << moment.M7 << ", " << moment.M8 << ", " << moment.M9 << ", " << moment.M10 << std::endl;
	return stream;
}

inline std::ostream& MomentInvariant::Header(std::ostream& stream )
{
	stream << "M1, M2, M3, M4, M5, M6, M7, M8, M9, M10" << std::endl;
	return stream;
}


#define MOMENT_X_DIMM 4
#define MOMENT_Y_DIMM 4

struct Moment
{
	double	xy[ MOMENT_X_DIMM ][ MOMENT_Y_DIMM ];

	double M00()	{ return xy[0][0]; }
	double M10()	{ return xy[1][0]; }
	double M20()	{ return xy[2][0]; }
	double M30()	{ return xy[3][0]; }

	double M01()	{ return xy[0][1]; }
	double M11()	{ return xy[1][1]; }
	double M21()	{ return xy[2][1]; }
	double M31()	{ return xy[3][1]; }

	double M02()	{ return xy[0][2]; }
	double M12()	{ return xy[1][2]; }
	double M22()	{ return xy[2][2]; }
	double M32()	{ return xy[3][2]; }

	double M03()	{ return xy[0][3]; }
	double M13()	{ return xy[1][3]; }
	double M23()	{ return xy[2][3]; }
	double M33()	{ return xy[3][3]; }

	void Clear();
};


inline void Moment::Clear()
{
	for( int i = 0; i < MOMENT_X_DIMM; ++i )
	{
		for( int j = 0; j < MOMENT_Y_DIMM; ++j )
		{
			xy[ i ][ j ] = 0.0;
		}
	}
}

#endif // MOMENTDESC_H
