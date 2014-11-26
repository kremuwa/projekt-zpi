#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QFileDialog>
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

	void openAndPlayTrajectory();
	void pauseTrajectory();
	void stopTrajectory();
	void jumpToTrajectory(int frame);

private:
	Ui::MainWindow ui;
	Algorithm algorithm;

	Player myPlayer;
};

#endif // MAINWINDOW_H
