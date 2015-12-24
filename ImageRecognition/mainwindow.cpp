#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	m_viewer = new ImageViewer( this );
	m_viewer->move( 20, 20 );

	m_viewer->OpenFile( "pip1.jpg" );
}

MainWindow::~MainWindow()
{
	delete ui;

	delete m_viewer;
}
