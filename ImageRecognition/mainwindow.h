#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ImageViewer.h"


namespace Ui {
class MainWindow;
}

class ImageProcessor;
class ProcessingList;
class ImageLogic;
class SegmentationLogic;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();


	void	InitializeProcessingList();
	void	InitializeSignals();
private:
	Ui::MainWindow *ui;

	ImageViewer*		m_viewer;

	ProcessingList*		m_processingList;
	ImageLogic*			m_logic;
	SegmentationLogic*	m_segmentLogic;

private slots:
	void	Processing();
	void	Segmentation();
	void	Moments();
	void	LoadImage();
	void	ProcessorCliecked( const QModelIndex& index );
	void	SegmentClicked( const QModelIndex& index );
};

#endif // MAINWINDOW_H
