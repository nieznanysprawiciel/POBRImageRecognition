#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ProcessingList.h"
#include "Processors/MedianFilter.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	m_viewer = new ImageViewer( ui->viewerScrollArea );

	m_viewer->OpenFile( "pip1.jpg" );

	m_processingList = new ProcessingList();
	ImageProcessor* newProc = new MedianFilter();
	m_processingList->AddProcessor( newProc, 0 );
	m_processingList->AddProcessor( newProc, 0 );
	m_processingList->AddProcessor( newProc, 0 );

	ui->processorsList1->setModel( m_processingList );
}

MainWindow::~MainWindow()
{
	delete ui;

	delete m_viewer;
}
