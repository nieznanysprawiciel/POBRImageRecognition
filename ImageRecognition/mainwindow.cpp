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

	m_state = AppState::Initial;

	m_viewer = new ImageViewer( ui->viewerScrollArea );
	m_logic = new ImageLogic;
	m_logoProcessingList = new ProcessingList;
	m_textProcessingList = new ProcessingList;
	m_segmentLogic = new SegmentationLogic;
	m_momentCompute = new MomentCompute;

	ui->processorsList1->setModel( m_logoProcessingList );
	ui->processorsList2->setModel( m_textProcessingList );

	InitializeProcessingList();
	InitializeSignals();
}

MainWindow::~MainWindow()
{
	ui->processorsList1->setModel( nullptr );
	ui->segmentsList1->setModel( nullptr );
	ui->segmentsList2->setModel( nullptr );

	delete m_segmentLogic;
	delete m_viewer;
	delete m_textProcessingList;
	delete m_logoProcessingList;
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
	ImageProcessor* lowPass = new MedianFilter();
	m_logoProcessingList->AddProcessor( lowPass, 0 );

	ImageProcessor* HSL = new ConvertToHSL();
	m_logoProcessingList->AddProcessor( HSL, 0 );

	ImageProcessor* threshold = new Threshold( "Progowanie saturacji i koloru", 40, 0, 255, 110, 255, 0 );
	m_logoProcessingList->AddProcessor( threshold, 1 );
	//
//======================================================//



//======================================================//
	// Zestaw do wyodrębniania liter
	ImageProcessor* median = new MedianFilter();
	m_textProcessingList->AddProcessor( median, 0 );

	ImageProcessor* convertHSL2 = new ConvertToHSL();
	m_textProcessingList->AddProcessor( convertHSL2, 0 );

//	ImageProcessor* saturationToGrey = new SaturationToGreyScale();
//	m_textProcessingList->AddProcessor( saturationToGrey, 0 );

	ImageProcessor* satThreshold = new SaturationThreshold( 0, 95 );
	m_textProcessingList->AddProcessor( satThreshold, 2 );
	//
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
	connect( ui->processorsList1, SIGNAL( clicked(QModelIndex) ), this, SLOT( ProcessorCliecked1(QModelIndex) ) );
	connect( ui->processorsList2, SIGNAL( clicked(QModelIndex) ), this, SLOT( ProcessorCliecked2(QModelIndex) ) );
	connect( ui->segmentsList1, SIGNAL( clicked(QModelIndex) ), this, SLOT( SegmentClicked1(QModelIndex) ) );
	connect( ui->segmentsList2, SIGNAL( clicked(QModelIndex) ), this, SLOT( SegmentClicked2(QModelIndex) ) );
	connect( ui->momentsList, SIGNAL( clicked(QModelIndex) ), this, SLOT( MomentClicked(QModelIndex) ) );

}


void	MainWindow::Processing()
{
	m_logic->ProcessImages( m_logoProcessingList, m_textProcessingList );
	m_viewer->SetImage( m_logic->GetLastImage( 1 ) );
}

void	MainWindow::Segmentation()
{
	auto& image = m_logic->CreateSegmentsImage( 1 );
	m_segmentLogic->MakeSegmentation( image );
	m_viewer->SetImage( image );

	ui->segmentsList1->setModel( m_segmentLogic->GetSegmentsModel( 1 ) );
	ui->segmentsList2->setModel( m_segmentLogic->GetSegmentsModel( 2 ) );
}

void	MainWindow::Moments()
{
	m_momentCompute->ClearMoments();

	auto& segments = m_segmentLogic->GetSegments( 0 );
	m_momentCompute->ComputeMoments( segments );
	auto model = m_momentCompute->Predict();

	ui->momentsList->setModel( model );

	//MomentsToCSV( "moments.csv", m_momentCompute->GetMoments() );
}

void	MainWindow::LoadImage()
{
	QString filePath = QFileDialog::getOpenFileName( this, tr("Open File"), "", tr("Images (*.png *.tiff *.jpg)") );

	std::string path = filePath.toStdString();
	m_logic->LoadImage( path );
	m_viewer->SetImage( m_logic->GetSourceImage() );
	m_viewer->UnsetRect();
}

void	MainWindow::ProcessorCliecked1( const QModelIndex& index )
{
	auto& image = m_logic->GetImage( index.row(), 1 );
	m_viewer->SetImage( image );
}

void	MainWindow::ProcessorCliecked2( const QModelIndex& index )
{
	auto& image = m_logic->GetImage( index.row(), 2 );
	m_viewer->SetImage( image );
}

void	MainWindow::SegmentClicked1( const QModelIndex& index )
{
	auto& segmentsVec = m_segmentLogic->GetSegments( 0 );
	auto& segment = segmentsVec[ index.row() ];
	auto& boundingBox = segment->GetBoundingBox();

	m_viewer->SetBoundingRect( boundingBox );

	auto& image = m_logic->GetSegmentsImage( 1 );
	m_viewer->SetImage( image );
}

void	MainWindow::SegmentClicked2( const QModelIndex& index )
{
	auto& segmentsVec = m_segmentLogic->GetSegments( 1 );
	auto& segment = segmentsVec[ index.row() ];
	auto& boundingBox = segment->GetBoundingBox();

	m_viewer->SetBoundingRect( boundingBox );

	auto& image = m_logic->GetSegmentsImage( 2 );
	m_viewer->SetImage( image );
}

void	MainWindow::MomentClicked( const QModelIndex& index )
{
	auto& moments = m_momentCompute->GetRecognized();
	auto segmentNum = moments[ index.row() ].SegmentNum;

	auto& segmentsVec = m_segmentLogic->GetSegments( 0 );
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


