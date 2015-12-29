#ifndef EXTRACTBLUE_H
#define EXTRACTBLUE_H

#include "ScaleColor.h"

class ExtractBlue : public ScaleColor
{
private:

public:
	ExtractBlue()
	: ScaleColor( "Składowa czerwona", 0.0f, 0.0f, 1.0f )
	{}

};


#endif // EXTRACTBLUE_H
