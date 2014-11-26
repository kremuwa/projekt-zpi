#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QFileDialog>
#include "ui_mainwindow.h"
#include "Algorithm.h"

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

private:
	Ui::MainWindow ui;
	Algorithm algorithm;
};

#endif // MAINWINDOW_H
