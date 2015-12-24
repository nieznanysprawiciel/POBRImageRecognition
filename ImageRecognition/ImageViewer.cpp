#include "ImageViewer.h"

#include <QPainter>


ImageViewer::ImageViewer(QWidget *parent) :
	QWidget(parent)
{
	m_imageLabel = new QLabel;
	m_imageLabel->setBackgroundRole(QPalette::Base);
	m_imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	m_imageLabel->setScaledContents(true);
	m_imageLabel->resize( 1000, 800 );

	m_scrollArea = new QScrollArea;
	m_scrollArea->setBackgroundRole(QPalette::Dark);
	m_scrollArea->setWidget( m_imageLabel );
	//setCentralWidget( m_scrollArea );

	resize( 1000, 800 );
}

ImageViewer::~ImageViewer()
{
	delete m_imageLabel;
	delete m_scrollArea;

}


bool		ImageViewer::OpenFile( const QString& fileName )
{
	QImage image( fileName );
	if ( !image.isNull() )
	{
		m_imageLabel->resize( image.size() );
		m_imageLabel->setPixmap( QPixmap::fromImage( image ) );

		return true;
	}

	return false;
}


void		ImageViewer::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	QPainter painter(this);

	QRect rect = painter.viewport();
	QSize size = m_imageLabel->pixmap()->size();
	size.scale(rect.size(), Qt::KeepAspectRatio);
	painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
	painter.setWindow(m_imageLabel->pixmap()->rect());

	painter.drawPixmap(0, 0, *m_imageLabel->pixmap());
}


