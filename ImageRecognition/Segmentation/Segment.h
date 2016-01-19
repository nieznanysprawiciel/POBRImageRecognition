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

	void TryUpdateMinMaxX( unsigned short row )
	{
		if( row < minX )
			minX = row;
		if( row > maxX )
			maxX = row;
	}

	void TryUpdateMinMaxY( unsigned short row )
	{
		if( row < minY )
			minY = row;
		if( row > maxY )
			maxY = row;
	}

	unsigned short GetWidth()
	{
		return maxX - minX;
	}

	unsigned short GetHeight()
	{
		return maxY - minY;
	}

	bool CheckIfContains( int x, int y )
	{
		if( x >= minX && x <= maxX && y >= minY && y <= maxY )
			return true;
		return false;
	}

	bool CheckIfContains( const BoundingBox& box2 )
	{
		if( !CheckIfContains( box2.minX, box2.minY ) )
			return false;
		if( !CheckIfContains( box2.maxX, box2.maxY ) )
			return false;
		return true;
	}
};

struct Pixel
{
	short X;
	short Y;

	Pixel( short x, short y )
	{
		X = x;
		Y = y;
	}

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
	int					m_segmentNum;
public:
	Segment();

	std::vector<Pixel>&		GetRegion()			{ return m_region; }
	BoundingBox&			GetBoundingBox()	{ return m_boundingBox; }
	int						GetSegNummer()		{ return m_segmentNum; }

	void					SetSegNummer( int nummer )		{ m_segmentNum = nummer; }
};

#endif // SEGMENT_H
