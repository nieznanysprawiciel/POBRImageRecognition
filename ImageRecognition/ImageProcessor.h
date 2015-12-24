#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H


#include <string>

class ImageProcessor
{
private:
protected:
	std::string		m_name;
public:
	ImageProcessor( const std::string& name );
	virtual ~ImageProcessor();

	const std::string& GetName()	{ return m_name; }

	virtual void Process() = 0;
};

#endif // IMAGEPROCESSOR_H
