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
class MomentCompute;


enum AppState
{
	Initial,
	Processed,
	Segmented,
	Recognized
};


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

	AppState			m_state;

	ImageViewer*		m_viewer;

	ProcessingList*		m_logoProcessingList;
	ProcessingList*		m_textProcessingList;
	ImageLogic*			m_logic;
	SegmentationLogic*	m_segmentLogic;
	MomentCompute*		m_momentCompute;

private slots:
	void	Processing();
	void	Segmentation();
	void	Moments();
	void	LoadImage();
	void	ProcessorCliecked( const QModelIndex& index );
	void	SegmentClicked1( const QModelIndex& index );
	void	SegmentClicked2( const QModelIndex& index );
	void	MomentClicked( const QModelIndex& index );
};



#endif // MAINWINDOW_H
