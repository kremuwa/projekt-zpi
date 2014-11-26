#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QFileDialog>
#include <QFileSystemModel>
#include "ui_mainwindow.h"
#include "Algorithm.h"
#include "Player.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();
	~MainWindow();

public slots:
	void playFromKinect();
	void playFromFile();
	void stopPlaying();
	void startAlgorithm();
	void stopAlgorithm();
	void startRecording();
	void stopRecording();

	void playTrajectory();
	void pauseTrajectory();
	void stopTrajectory();
	void jumpToTrajectory(int frame);

	void listDirectory(QModelIndex index);

private:
	Ui::MainWindow ui;
	Algorithm algorithm;

	QFileSystemModel *dirmodel;
	QFileSystemModel *filemodel;

	Player myPlayer;
};

#endif // MAINWINDOW_H
