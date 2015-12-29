#ifndef EXTRACTRED_H
#define EXTRACTRED_H



#include "ScaleColor.h"

class ExtractRed : public ScaleColor
{
private:

public:
	ExtractRed()
	: ScaleColor( "Składowa czerwona", 1.0f, 0.0f, 0.0f )
	{}

};


#endif // EXTRACTRED_H
