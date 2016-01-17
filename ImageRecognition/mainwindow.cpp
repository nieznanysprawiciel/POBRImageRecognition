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
#include "Processors/Threshold.h"
#include "Moment/MomentCompute.h"

#include <QFileDialog>


#include <string>
#include <fstream>

void MomentsToCSV( const std::string& fileName, std::vector<MomentInvariant>& moments );



MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	m_viewer = new ImageViewer( ui->viewerScrollArea );
	m_logic = new ImageLogic;
	m_processingList = new ProcessingList;
	m_segmentLogic = new SegmentationLogic;
	m_momentCompute = new MomentCompute;

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


//======================================================//
	// Zestaw do wyodrębniania żółtego obszaru
	ImageProcessor* HSL = new ConvertToHSL();
	m_processingList->AddProcessor( HSL, 0 );

	ImageProcessor* threshold = new Threshold( "Progowanie saturacji i koloru", 40, 0, 255, 110, 255, 0 );
	m_processingList->AddProcessor( threshold, 0 );
	//
//======================================================//



//======================================================//
//	// Zestaw do wyodrębniania liter
//	ImageProcessor* convertHSL2 = new ConvertToHSL();
//	m_processingList->AddProcessor( convertHSL2, 0 );

//	ImageProcessor* saturationToGrey = new SaturationToGreyScale();
//	m_processingList->AddProcessor( saturationToGrey, 0 );

//	ImageProcessor* satThreshold = new HueThreshold( 0, 110 );
//	m_processingList->AddProcessor( satThreshold, 0 );
//	//
//======================================================//


//	ImageProcessor* hueToGrey = new HueToGreyScale();
//	m_processingList->AddProcessor( hueToGrey, 0 );

//	ImageProcessor* luminanceToGrey = new LuminanceToGreyScale();
//	m_processingList->AddProcessor( luminanceToGrey, 0 );

//	ImageProcessor* saturationToGrey = new SaturationToGreyScale();
//	m_processingList->AddProcessor( saturationToGrey, 0 );

//	ImageProcessor* hueThreshold = new HueThreshold( 160, 255 );
//	m_processingList->AddProcessor( hueThreshold, 0 );


}

void	MainWindow::InitializeSignals()
{
	connect( ui->processImage, SIGNAL( clicked() ), this, SLOT( Processing() ) );
	connect( ui->segmentationButton, SIGNAL( clicked() ), this, SLOT( Segmentation() ) );
	connect( ui->momentButton, SIGNAL( clicked() ), this, SLOT( Moments()) );
	connect( ui->actionLoad, SIGNAL( triggered() ), this, SLOT( LoadImage() ) );
	connect( ui->processorsList1, SIGNAL( clicked(QModelIndex) ), this, SLOT( ProcessorCliecked(QModelIndex) ) );
	connect( ui->segmentsList, SIGNAL( clicked(QModelIndex) ), this, SLOT( SegmentClicked(QModelIndex) ) );
	connect( ui->momentsList, SIGNAL( clicked(QModelIndex) ), this, SLOT( MomentClicked(QModelIndex) ) );

}


void	MainWindow::Processing()
{
	m_logic->ProcessImages( m_processingList );
	m_viewer->SetImage( m_logic->GetLastImage() );
}

void	MainWindow::Segmentation()
{
	auto& image = m_logic->CreateSegmentsImage();
	m_segmentLogic->MakeSegmentation( image );
	m_viewer->SetImage( image );

	ui->segmentsList->setModel( m_segmentLogic->GetSegmentsModel() );
}

void	MainWindow::Moments()
{
	m_momentCompute->ClearMoments();

	auto& segments = m_segmentLogic->GetSegments();
	m_momentCompute->ComputeMoments( segments );
	auto model = m_momentCompute->Predict();

	ui->momentsList->setModel( model );
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

	auto& image = m_logic->GetSegmentsImage();
	m_viewer->SetImage( image );
}

void	MainWindow::MomentClicked( const QModelIndex& index )
{
	auto& moments = m_momentCompute->GetRecognized();
	auto segmentNum = moments[ index.row() ].SegmentNum;

	auto& segmentsVec = m_segmentLogic->GetSegments();
	auto& segment = segmentsVec[ segmentNum ];
	auto& boundingBox = segment->GetBoundingBox();

	m_viewer->SetBoundingRect( boundingBox );

	auto& image = m_logic->GetSourceImage();
	m_viewer->SetImage( image );
}



void MomentsToCSV( const std::string& fileName, std::vector<MomentInvariant>& moments )
{
	if( moments.size() == 0 )
		return;

	std::ofstream file( fileName, std::ios_base::app | std::ios_base::ate | std::ios_base::out );
	if( !file.fail() )
	{
		moments[ 0 ].Header( file );
		for( auto& moment : moments )
			file << moment;

		// Separate diferent images with empty row
		file << std::endl;
	}

}


