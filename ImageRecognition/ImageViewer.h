#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QLabel>
#include <QScrollArea>

#include <QString>

class ImageViewer : public QWidget
{
	Q_OBJECT
private:
	QLabel*			m_imageLabel;
	QScrollArea*	m_scrollArea;


public:
	explicit ImageViewer( QWidget *parent = 0 );
	~ImageViewer();

	bool		OpenFile( const QString& fileName );


	void		paintEvent( QPaintEvent *event );
signals:

public slots:

};

#endif // IMAGEVIEWER_H
