#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QImage>

#include <QString>

#include <opencv2/core/core.hpp>

class ImageViewer : public QWidget
{
	Q_OBJECT
private:
	unsigned int	m_width;
	unsigned int	m_height;

	QImage			m_image;
	cv::Mat			m_imageCV;

public:
	explicit ImageViewer( QWidget *parent = 0 );
	~ImageViewer();

	bool		OpenFile	( const QString& fileName );
	void		SetImage	( cv::Mat& image );


	void		paintEvent	( QPaintEvent *event );
signals:

public slots:

};

#endif // IMAGEVIEWER_H
