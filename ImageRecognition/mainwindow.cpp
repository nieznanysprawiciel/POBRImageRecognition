#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ProcessingList.h"
#include "ImageLogic.h"
#include "Segmentation/SegmantationLogic.h"
#include "Processors/MedianFilter.h"
#include "Processors/LowPassFilter.h"
#include "Processors/ExtractBlue.h"
#include "Processors/ExtractGreen.h"
#include "Processors/ExtractRed.h"
#include "Processors/ChannelToGreyScale.h"
#include "Processors/ConvertToHSL.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	m_viewer = new ImageViewer( ui->viewerScrollArea );
	m_logic = new ImageLogic;
	m_processingList = new ProcessingList;
	m_segmentLogic = new SegmentationLogic;

	ui->processorsList1->setModel( m_processingList );

	InitializeProcessingList();
	InitializeSignals();
}

MainWindow::~MainWindow()
{
	ui->processorsList1->setModel( nullptr );
	ui->segmentsList->setModel( m_segmentLogic->GetSegmentsModel() );

	delete m_segmentLogic;
	delete m_viewer;
	delete m_processingList;
	delete m_logic;

	delete ui;
}


void	MainWindow::InitializeProcessingList()
{
//	ImageProcessor* newProc1 = new LowPassFilter();
//	ImageProcessor* newProc2 = new LowPassFilter();
//	ImageProcessor* newProc3 = new LowPassFilter();

//	m_processingList->AddProcessor( newProc1, 0 );
//	m_processingList->AddProcessor( newProc2, 0 );
//	m_processingList->AddProcessor( newProc3, 0 );

//	ImageProcessor* colorFilter = new ExtractRed();
//	m_processingList->AddProcessor( colorFilter, 0 );

//	ImageProcessor* HSL = new ConvertToHSL();
//	m_processingList->AddProcessor( HSL, 0 );

//	ImageProcessor* luminanceToGrey = new LuminanceToGreyScale();
//	m_processingList->AddProcessor( luminanceToGrey, 0 );
}

void	MainWindow::InitializeSignals()
{
	connect( ui->processImage, SIGNAL( clicked() ), this, SLOT( Processing() ) );
	connect( ui->segmentationButton, SIGNAL( clicked() ), this, SLOT( Segmentation() ) );
	connect( ui->actionLoad, SIGNAL( triggered() ), this, SLOT( LoadImage() ) );
	connect( ui->processorsList1, SIGNAL( clicked(QModelIndex) ), this, SLOT( ProcessorCliecked(QModelIndex) ) );
	connect( ui->segmentsList, SIGNAL( clicked(QModelIndex) ), this, SLOT( SegmentClicked(QModelIndex) ) );
}


void	MainWindow::Processing()
{
	m_logic->ProcessImages( m_processingList );
	m_viewer->SetImage( m_logic->GetLastImage() );
}

void	MainWindow::Segmentation()
{
	auto& image = m_logic->GetSegmentsImage();
	m_segmentLogic->MakeSegmentation( image );
	m_viewer->SetImage( image );

	ui->segmentsList->setModel( m_segmentLogic->GetSegmentsModel() );
}

void	MainWindow::LoadImage()
{
	QString filePath = QFileDialog::getOpenFileName( this, tr("Open File"), "", tr("Images (*.png *.tiff *.jpg)") );

	std::string path = filePath.toStdString();
	m_logic->LoadImage( path );
	m_viewer->SetImage( m_logic->GetSourceImage() );
	m_viewer->UnsetRect();
}

void	MainWindow::ProcessorCliecked( const QModelIndex& index )
{
	auto& image = m_logic->GetImage( index.row() );
	m_viewer->SetImage( image );
}

void	MainWindow::SegmentClicked( const QModelIndex& index )
{
	auto& segmentsVec = m_segmentLogic->GetSegments();
	auto& segment = segmentsVec[ index.row() ];
	auto& boundingBox = segment->GetBoundingBox();

	m_viewer->SetBoundingRect( boundingBox );
}


