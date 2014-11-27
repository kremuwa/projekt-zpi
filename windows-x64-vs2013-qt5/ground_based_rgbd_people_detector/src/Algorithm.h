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


#pragma once


#include "base.h"

#include <QThread>
#include <QDebug>
#include <QMutex>



#include "writer.h"

typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

// declarations of global variables

extern boost::mutex cloud_mutex;

// declarations of global functions (used as boost's callback functions)

void cloud_cb_(const PointCloudT::ConstPtr &callback_cloud, PointCloudT::Ptr& cloud, bool* new_cloud_available_flag);

void pp_callback(const pcl::visualization::PointPickingEvent& event, void* args);

// definitions of auxiliary structures

struct callback_args
{

	// structure used to pass arguments to the callback function

	PointCloudT::Ptr clicked_points_3d;
	pcl::visualization::PCLVisualizer::Ptr viewerPtr;

};

class Algorithm : public QThread
{

public:

	// name of the file with trained SVM

	std::string svm_filename;

	// parameters change'able from GUI

	float min_confidence;
	float min_height;
	float max_height;
	float dist;

	std::string currentFile;

	// booleans used to steer the behaviour of run() function

	bool isStopped;
	bool isJustStopped;
	bool isAlgorithmEnabled;
	bool isAlgorithmJustEnabled;
	bool isRecordingEnabled;
	bool isRecordingJustEnabled;

	/*QMutex mutexIsStopped;
	QMutex mutexIsJustStopped;
	QMutex mutexIsAlgorithmEnabled;
	QMutex mutexIsAlgorithmJustEnabled;
	QMutex mutexIsRecordingEnabled;
	QMutex mutexIsRecordingJustEnabled;*/

	pcl::visualization::PCLVisualizer *viewer;

	writer myWriter;

	std::string currentTRJdir;
	std::string currentPCDdir;

	int person_nr;

	Algorithm();

	void playFromKinect();
	void playFromFile(std::string filename = "");
	void stopPlaying();
	void startAlgorithm();
	void stopAlgorithm();
	void startRecording(std::string PCDfilepath, std::string TRJfilepath);
	void stopRecording();

	void setMinConf(float a);
	void setMinHeight(float a);
	void setMaxHeight(float a);
	void setDist(float a);

	void run();

	int if_same_person(std::vector<Eigen::Vector4f> centroids, Eigen::Vector3f person, float thresold);

};