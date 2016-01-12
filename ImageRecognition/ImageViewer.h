#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QImage>
#include <QRect>

#include <QString>
#include "Segmentation/Segment.h"

#include <opencv2/core/core.hpp>

class ImageViewer : public QWidget
{
	Q_OBJECT
private:
	unsigned int	m_width;
	unsigned int	m_height;

	bool			m_drawBoundingBox;
	QRect			m_rectToDraw;

	QImage			m_image;
	cv::Mat			m_imageCV;

public:
	explicit ImageViewer( QWidget *parent = 0 );
	~ImageViewer();

	bool		OpenFile	( const QString& fileName );
	void		SetImage	( cv::Mat& image );
	void		Repaint	();

	void		SetBoundingRect		( BoundingBox& box );
	void		UnsetRect			();


	void		paintEvent	( QPaintEvent *event );
signals:

public slots:

};

#endif // IMAGEVIEWER_H
