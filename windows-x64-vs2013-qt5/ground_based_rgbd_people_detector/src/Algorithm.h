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