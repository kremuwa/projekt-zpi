#include "mainwindow.h"
#include "Algorithm.h"

using namespace std;

MainWindow::MainWindow()
: QMainWindow()
{
	algorithm.start();
	ui.setupUi(this);
}

MainWindow::~MainWindow()
{

}

void MainWindow::playFromKinect() {

	algorithm.playFromKinect();

}

void MainWindow::playFromFile() {

	QString fileName = QFileDialog::getOpenFileName(this, tr("Open *.oni file"), QString(), tr("ONI Files (*.oni)"));

	algorithm.playFromFile(fileName.toStdString());

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

	QDir().mkdir(dir + tr("pcd"));

	algorithm.startRecording((dir + tr("pcd")).toStdString(), dir.toStdString());

}

void MainWindow::stopRecording() {

	algorithm.stopRecording();

}

void MainWindow::openAndPlayTrajectory()
{

	QString fileName = QFileDialog::getOpenFileName(this, tr("Open *.trj file"), QString(), tr("ONI Files (*.trj)"));

	myPlayer.initialize(fileName.toStdString());

	myPlayer.play();

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