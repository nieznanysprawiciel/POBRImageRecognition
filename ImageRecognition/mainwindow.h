#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ImageViewer.h"

namespace Ui {
class MainWindow;
}

class ImageProcessor;
class ProcessingList;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *ui;

	ImageViewer*		m_viewer;

	ProcessingList*		m_processingList;
};

#endif // MAINWINDOW_H
