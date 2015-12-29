#ifndef EXTRACTGREEN_H
#define EXTRACTGREEN_H

#include "ScaleColor.h"

class ExtractGreen : public ScaleColor
{
private:

public:
	ExtractGreen()
	: ScaleColor( "Składowa zielona", 0.0f, 1.0f, 0.0f )
	{}

};

#endif // EXTRACTGREEN_H
