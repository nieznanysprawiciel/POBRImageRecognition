#include "ImageViewer.h"

#include <QPainter>
#include "opencv/cv.h"
#include <opencv2/imgproc/imgproc.hpp>

ImageViewer::ImageViewer(QWidget *parent) :
	QWidget(parent)
{
	m_width = 1000;
	m_height = 800;
	resize( m_width, m_height );
}

ImageViewer::~ImageViewer()
{

}


bool		ImageViewer::OpenFile( const QString& fileName )
{
	QImage newImage( fileName );
	if ( !newImage.isNull() )
	{
		m_image = newImage;
		m_width = newImage.width();
		m_height = newImage.height();
		return true;
	}

	return false;
}

void		ImageViewer::SetImage	( cv::Mat& image )
{
	m_width = image.cols;
	m_height = image.rows;

	cv::cvtColor( image, m_imageCV, CV_BGR2RGB );
	m_image = QImage( (uchar*)m_imageCV.data, m_imageCV.cols, m_imageCV.rows, m_imageCV.step1(), QImage::Format_RGB888 );

	repaint();
}


void		ImageViewer::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QPainter painter(this);

	QRect copyRect( 0, 0, m_width, m_height );
	painter.drawImage( copyRect, m_image );
}


