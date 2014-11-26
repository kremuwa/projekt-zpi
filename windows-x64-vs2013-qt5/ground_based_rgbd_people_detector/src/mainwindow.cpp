#include "mainwindow.h"
#include "Algorithm.h"

using namespace std;

MainWindow::MainWindow()
: QMainWindow()
{
	algorithm.start();
	ui.setupUi(this);

	QString root = "";
	dirmodel = new QFileSystemModel(this);
	dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);

	ui.treeView->setModel(dirmodel);

	dirmodel->setRootPath(QDir::currentPath());

	filemodel = new QFileSystemModel(this); 
	filemodel->setFilter(QDir::NoDotAndDotDot | QDir::Files);

	QStringList filters;
	filters << "*.trj";

	filemodel->setNameFilters(filters);
	filemodel->setNameFilterDisables(false);

	filemodel->setRootPath(QDir::currentPath());

	ui.listView->setModel(filemodel);

}

MainWindow::~MainWindow()
{

}

void MainWindow::playFromKinect() {

	algorithm.playFromKinect();

}

void MainWindow::playFromFile() {
	
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open *.oni file"), QString(), tr("ONI Files (*.oni)"));
	
	if (!fileName.isEmpty())
	{
		algorithm.playFromFile(fileName.toStdString());
	}

}

void MainWindow::stopPlaying() {

	algorithm.stopPlaying();

}

void MainWindow::startAlgorithm() {

	algorithm.startAlgorithm();

}

void MainWindow::stopAlgorithm() {

	algorithm.stopAlgorithm();

}

void MainWindow::startRecording() {

	QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Directory to save Your trajectory"), QString(), QFileDialog::ShowDirsOnly);

	if (!dir.isEmpty())
	{
		QDir().mkdir(dir + tr("pcd"));

		algorithm.startRecording((dir + tr("pcd")).toStdString(), dir.toStdString());
	}

}

void MainWindow::stopRecording() {

	algorithm.stopRecording();

}

void MainWindow::playTrajectory()
{

	QString fileName = QFileDialog::getOpenFileName(this, tr("Open *.trj file"), QString(), tr("ONI Files (*.trj)"));
	
	if (!fileName.isEmpty())
	{
		myPlayer.initialize(fileName.toStdString());

		myPlayer.play();
	}

}

void MainWindow::pauseTrajectory()
{

	// actually it toggles pause

	myPlayer.pause();

}

void MainWindow::stopTrajectory()
{

	myPlayer.stop();

}

void MainWindow::jumpToTrajectory(int frame)
{

	myPlayer.jumpTo(frame);

}

void MainWindow::listDirectory(QModelIndex index)
{

	QString path = dirmodel->fileInfo(index).absoluteFilePath();
	ui.listView->setRootIndex(filemodel->setRootPath(path));

}