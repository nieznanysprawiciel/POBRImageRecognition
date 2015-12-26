#ifndef MEDIANFILTER_H
#define MEDIANFILTER_H

#include "../ImageProcessor.h"

class MedianFilter : public ImageProcessor
{
private:
	unsigned int	m_threshold;
public:
	MedianFilter();
	virtual ~MedianFilter();

	virtual void Process() override;
};

#endif // MEDIANFILTER_H
