#ifndef LOWPASSFILTER_H
#define LOWPASSFILTER_H

#include "MaskFilterBase.h"

class LowPassFilter : public MaskFilterBase
{
private:

public:
	LowPassFilter()
	: MaskFilterBase(	"Filtr dolnoprzepustowy",
						1, 1, 1,
						1, 1, 1,
						1, 1, 1,
						9.0 )
	{}

};



#endif // LOWPASSFILTER_H
