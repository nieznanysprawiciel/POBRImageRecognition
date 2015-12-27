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

private slots:
	void	Processing();
	void	LoadImage();
};

#endif // MAINWINDOW_H
