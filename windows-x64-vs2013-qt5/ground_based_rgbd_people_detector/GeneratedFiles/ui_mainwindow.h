/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QColumnView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionPlayFromFile;
    QAction *actionPlayFromKinect;
    QAction *actionStopPlaying;
    QAction *actionStartAlgorithm;
    QAction *actionStopAlgorithm;
    QAction *actionStartRecording;
    QAction *actionStopRecording;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QColumnView *columnView;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(740, 589);
        actionPlayFromFile = new QAction(MainWindow);
        actionPlayFromFile->setObjectName(QStringLiteral("actionPlayFromFile"));
        actionPlayFromKinect = new QAction(MainWindow);
        actionPlayFromKinect->setObjectName(QStringLiteral("actionPlayFromKinect"));
        actionStopPlaying = new QAction(MainWindow);
        actionStopPlaying->setObjectName(QStringLiteral("actionStopPlaying"));
        actionStartAlgorithm = new QAction(MainWindow);
        actionStartAlgorithm->setObjectName(QStringLiteral("actionStartAlgorithm"));
        actionStopAlgorithm = new QAction(MainWindow);
        actionStopAlgorithm->setObjectName(QStringLiteral("actionStopAlgorithm"));
        actionStartRecording = new QAction(MainWindow);
        actionStartRecording->setObjectName(QStringLiteral("actionStartRecording"));
        actionStopRecording = new QAction(MainWindow);
        actionStopRecording->setObjectName(QStringLiteral("actionStopRecording"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        columnView = new QColumnView(centralwidget);
        columnView->setObjectName(QStringLiteral("columnView"));

        gridLayout->addWidget(columnView, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionPlayFromKinect);
        toolBar->addAction(actionPlayFromFile);
        toolBar->addAction(actionStopPlaying);
        toolBar->addAction(actionStartAlgorithm);
        toolBar->addAction(actionStopAlgorithm);
        toolBar->addAction(actionStartRecording);
        toolBar->addAction(actionStopRecording);

        retranslateUi(MainWindow);
        QObject::connect(actionPlayFromKinect, SIGNAL(triggered()), MainWindow, SLOT(playFromKinect()));
        QObject::connect(actionPlayFromFile, SIGNAL(triggered()), MainWindow, SLOT(playFromFile()));
        QObject::connect(actionStartAlgorithm, SIGNAL(triggered()), MainWindow, SLOT(startAlgorithm()));
        QObject::connect(actionStopAlgorithm, SIGNAL(triggered()), MainWindow, SLOT(stopAlgorithm()));
        QObject::connect(actionStartRecording, SIGNAL(triggered()), MainWindow, SLOT(startRecording()));
        QObject::connect(actionStopRecording, SIGNAL(triggered()), MainWindow, SLOT(stopRecording()));
        QObject::connect(actionStopPlaying, SIGNAL(triggered()), MainWindow, SLOT(stopPlaying()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionPlayFromFile->setText(QApplication::translate("MainWindow", "playFromFile", 0));
#ifndef QT_NO_TOOLTIP
        actionPlayFromFile->setToolTip(QApplication::translate("MainWindow", "Lets You choose an *.oni file and starts to play it. You can then start the algorithm.", 0));
#endif // QT_NO_TOOLTIP
        actionPlayFromKinect->setText(QApplication::translate("MainWindow", "playFromKinect", 0));
#ifndef QT_NO_TOOLTIP
        actionPlayFromKinect->setToolTip(QApplication::translate("MainWindow", "Checks if there is a Kinect device plugged in and starts to capture and display data using the sensor. You can then start the algorithm.", 0));
#endif // QT_NO_TOOLTIP
        actionStopPlaying->setText(QApplication::translate("MainWindow", "stopPlaying", 0));
#ifndef QT_NO_TOOLTIP
        actionStopPlaying->setToolTip(QApplication::translate("MainWindow", "Stops playing showing data from any source", 0));
#endif // QT_NO_TOOLTIP
        actionStartAlgorithm->setText(QApplication::translate("MainWindow", "startAlgorithm", 0));
#ifndef QT_NO_TOOLTIP
        actionStartAlgorithm->setToolTip(QApplication::translate("MainWindow", "Starts to perform the algorithm on chosen the source and to visualize its results.", 0));
#endif // QT_NO_TOOLTIP
        actionStopAlgorithm->setText(QApplication::translate("MainWindow", "stopAlgorithm", 0));
#ifndef QT_NO_TOOLTIP
        actionStopAlgorithm->setToolTip(QApplication::translate("MainWindow", "Stops the algorithm and visualization", 0));
#endif // QT_NO_TOOLTIP
        actionStartRecording->setText(QApplication::translate("MainWindow", "startRecording", 0));
#ifndef QT_NO_TOOLTIP
        actionStartRecording->setToolTip(QApplication::translate("MainWindow", "Once the algorithm is running, You can start to record its results. After choosing this option, You have to choose where to store the recording", 0));
#endif // QT_NO_TOOLTIP
        actionStopRecording->setText(QApplication::translate("MainWindow", "stopRecording", 0));
#ifndef QT_NO_TOOLTIP
        actionStopRecording->setToolTip(QApplication::translate("MainWindow", "Stop the recording process", 0));
#endif // QT_NO_TOOLTIP
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
