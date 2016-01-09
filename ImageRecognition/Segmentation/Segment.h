#ifndef SEGMENT_H
#define SEGMENT_H

#include <limits>
#include <vector>

struct BoundingBox
{
	unsigned short minX;
	unsigned short minY;
	unsigned short maxX;
	unsigned short maxY;

	BoundingBox()
	{
		minX = std::numeric_limits<unsigned short>::max();
		minY = std::numeric_limits<unsigned short>::max();
		maxX = std::numeric_limits<unsigned short>::min();
		maxY = std::numeric_limits<unsigned short>::min();
	}
};

struct Pixel
{
	unsigned short X;
	unsigned short Y;

	bool operator==( Pixel pix2 )
	{
		if( X == pix2.X && Y == pix2.Y )
			return true;
		return false;
	}
};


class Segment
{
private:
	BoundingBox			m_boundingBox;
	std::vector<Pixel>	m_region;
public:
	Segment();

	std::vector<Pixel>&		GetRegion()			{ return m_region; }
	BoundingBox&			GetBoundingBox()	{ return m_boundingBox; }
};

#endif // SEGMENT_H
