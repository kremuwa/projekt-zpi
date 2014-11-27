/*

Project: People RGB-D Detector
Authors: Grzegorz Wójcicki, Micha³ Urbanek, Grzegorz Kozub, Mateusz Pasieka, Krzysztof Gieroñ, Jacek Pawelczak

Copyright(c) <YEAR>, <OWNER>
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met :

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and / or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.IN NO EVENT
SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT(INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/


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
		QDir().mkdir(dir + QString("/pcd"));

		algorithm.startRecording((dir + tr("/pcd")).toStdString(), dir.toStdString());
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

void MainWindow::playTrajectoryFromList(QModelIndex index)
{

	myPlayer.initialize(filemodel->fileInfo(index).absoluteFilePath().toStdString());

	myPlayer.play();

}