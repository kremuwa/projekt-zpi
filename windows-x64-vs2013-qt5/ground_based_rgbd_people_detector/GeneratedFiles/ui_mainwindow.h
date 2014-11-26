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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButtonPlayFromKinect;
    QPushButton *pushButtonPlayFromFile;
    QPushButton *pushButtonStopPlaying;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButtonStartAlgorithm;
    QPushButton *pushButtonStopAlgorithm;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButtonStartRecording;
    QPushButton *pushButtonStopRecording;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButtonPlayTrajectory;
    QPushButton *pushButtonPauseTrajectory;
    QPushButton *pushButtonStopTrajectory;
    QSlider *horizontalSliderJumpToTrajectory;
    QHBoxLayout *horizontalLayout_2;
    QTreeView *treeView;
    QListView *listView;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(740, 625);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        pushButtonPlayFromKinect = new QPushButton(groupBox_2);
        pushButtonPlayFromKinect->setObjectName(QStringLiteral("pushButtonPlayFromKinect"));

        verticalLayout_2->addWidget(pushButtonPlayFromKinect);

        pushButtonPlayFromFile = new QPushButton(groupBox_2);
        pushButtonPlayFromFile->setObjectName(QStringLiteral("pushButtonPlayFromFile"));

        verticalLayout_2->addWidget(pushButtonPlayFromFile);

        pushButtonStopPlaying = new QPushButton(groupBox_2);
        pushButtonStopPlaying->setObjectName(QStringLiteral("pushButtonStopPlaying"));

        verticalLayout_2->addWidget(pushButtonStopPlaying);


        horizontalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        pushButtonStartAlgorithm = new QPushButton(groupBox_3);
        pushButtonStartAlgorithm->setObjectName(QStringLiteral("pushButtonStartAlgorithm"));

        verticalLayout_3->addWidget(pushButtonStartAlgorithm);

        pushButtonStopAlgorithm = new QPushButton(groupBox_3);
        pushButtonStopAlgorithm->setObjectName(QStringLiteral("pushButtonStopAlgorithm"));

        verticalLayout_3->addWidget(pushButtonStopAlgorithm);


        horizontalLayout->addWidget(groupBox_3);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        pushButtonStartRecording = new QPushButton(groupBox);
        pushButtonStartRecording->setObjectName(QStringLiteral("pushButtonStartRecording"));

        verticalLayout_4->addWidget(pushButtonStartRecording);

        pushButtonStopRecording = new QPushButton(groupBox);
        pushButtonStopRecording->setObjectName(QStringLiteral("pushButtonStopRecording"));

        verticalLayout_4->addWidget(pushButtonStopRecording);


        horizontalLayout->addWidget(groupBox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_4);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        pushButtonPlayTrajectory = new QPushButton(groupBox_4);
        pushButtonPlayTrajectory->setObjectName(QStringLiteral("pushButtonPlayTrajectory"));

        horizontalLayout_4->addWidget(pushButtonPlayTrajectory);

        pushButtonPauseTrajectory = new QPushButton(groupBox_4);
        pushButtonPauseTrajectory->setObjectName(QStringLiteral("pushButtonPauseTrajectory"));

        horizontalLayout_4->addWidget(pushButtonPauseTrajectory);

        pushButtonStopTrajectory = new QPushButton(groupBox_4);
        pushButtonStopTrajectory->setObjectName(QStringLiteral("pushButtonStopTrajectory"));

        horizontalLayout_4->addWidget(pushButtonStopTrajectory);

        horizontalSliderJumpToTrajectory = new QSlider(groupBox_4);
        horizontalSliderJumpToTrajectory->setObjectName(QStringLiteral("horizontalSliderJumpToTrajectory"));
        horizontalSliderJumpToTrajectory->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(horizontalSliderJumpToTrajectory);


        horizontalLayout_3->addWidget(groupBox_4);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        treeView = new QTreeView(centralwidget);
        treeView->setObjectName(QStringLiteral("treeView"));

        horizontalLayout_2->addWidget(treeView);

        listView = new QListView(centralwidget);
        listView->setObjectName(QStringLiteral("listView"));

        horizontalLayout_2->addWidget(listView);


        verticalLayout->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(pushButtonPauseTrajectory, SIGNAL(clicked()), MainWindow, SLOT(pauseTrajectory()));
        QObject::connect(pushButtonPlayFromFile, SIGNAL(clicked()), MainWindow, SLOT(playFromFile()));
        QObject::connect(pushButtonPlayFromKinect, SIGNAL(clicked()), MainWindow, SLOT(playFromKinect()));
        QObject::connect(pushButtonStartAlgorithm, SIGNAL(clicked()), MainWindow, SLOT(startAlgorithm()));
        QObject::connect(pushButtonStartRecording, SIGNAL(clicked()), MainWindow, SLOT(startRecording()));
        QObject::connect(pushButtonStopAlgorithm, SIGNAL(clicked()), MainWindow, SLOT(stopAlgorithm()));
        QObject::connect(pushButtonStopPlaying, SIGNAL(clicked()), MainWindow, SLOT(stopPlaying()));
        QObject::connect(pushButtonStopRecording, SIGNAL(clicked()), MainWindow, SLOT(stopRecording()));
        QObject::connect(pushButtonStopTrajectory, SIGNAL(clicked()), MainWindow, SLOT(stopTrajectory()));
        QObject::connect(horizontalSliderJumpToTrajectory, SIGNAL(valueChanged(int)), MainWindow, SLOT(jumpToTrajectory(int)));
        QObject::connect(pushButtonPlayTrajectory, SIGNAL(clicked()), MainWindow, SLOT(playTrajectory()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Image source", 0));
        pushButtonPlayFromKinect->setText(QApplication::translate("MainWindow", "Grab Frames from Kinect", 0));
        pushButtonPlayFromFile->setText(QApplication::translate("MainWindow", "Grab frames from ONI file", 0));
        pushButtonStopPlaying->setText(QApplication::translate("MainWindow", "Stop grabbing from any source", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Algorithm management", 0));
        pushButtonStartAlgorithm->setText(QApplication::translate("MainWindow", "Start algorithm", 0));
        pushButtonStopAlgorithm->setText(QApplication::translate("MainWindow", "Stop algorithm", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Recording", 0));
        pushButtonStartRecording->setText(QApplication::translate("MainWindow", "Start recording", 0));
        pushButtonStopRecording->setText(QApplication::translate("MainWindow", "Stop recording", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Trajectory player", 0));
        pushButtonPlayTrajectory->setText(QApplication::translate("MainWindow", "Open *.trj and Play", 0));
        pushButtonPauseTrajectory->setText(QApplication::translate("MainWindow", "Pause", 0));
        pushButtonStopTrajectory->setText(QApplication::translate("MainWindow", "Stop", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
