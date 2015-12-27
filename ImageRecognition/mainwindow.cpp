#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ProcessingList.h"
#include "ImageLogic.h"
#include "Processors/MedianFilter.h"
#include "Processors/LowPassFilter.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	m_viewer = new ImageViewer( ui->viewerScrollArea );
	m_logic = new ImageLogic;
	m_processingList = new ProcessingList();

	m_viewer->OpenFile( "pip1.jpg" );

	ui->processorsList1->setModel( m_processingList );

	InitializeProcessingList();
	InitializeSignals();
}

MainWindow::~MainWindow()
{
	delete ui;

	delete m_viewer;
	delete m_processingList;
	delete m_logic;
}


void	MainWindow::InitializeProcessingList()
{
//	ImageProcessor* newProc = new MedianFilter();

//	m_processingList->AddProcessor( newProc, 0 );
//	m_processingList->AddProcessor( newProc, 0 );
//	m_processingList->AddProcessor( newProc, 0 );

	ImageProcessor* newProc = new LowPassFilter();
	m_processingList->AddProcessor( newProc, 0 );
}

void	MainWindow::InitializeSignals()
{
	connect( ui->processImage, SIGNAL( clicked() ), this, SLOT( Processing() ) );
	connect( ui->actionLoad, SIGNAL( triggered() ), this, SLOT( LoadImage() ) );
}


void	MainWindow::Processing()
{
	m_logic->ProcessImages( m_processingList );
}

void	MainWindow::LoadImage()
{
	QString filePath = QFileDialog::getOpenFileName( this, tr("Open File"),
									   "",
									   tr("Images (*.png *.tiff *.jpg)") );

	std::string path = filePath.toStdString();
	m_logic->LoadImage( path );
}



