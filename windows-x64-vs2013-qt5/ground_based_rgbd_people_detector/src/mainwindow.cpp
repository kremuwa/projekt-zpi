#include "mainwindow.h"
#include "Algorithm.h"

using namespace std;

MainWindow::MainWindow()
: QMainWindow(), viewer("PCL Viewer"), algorithm(&viewer)
{
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

}

void MainWindow::startAlgorithm() {

}

void MainWindow::stopAlgorithm() {

}

void MainWindow::startRecording() {

}

void MainWindow::stopRecording() {

}