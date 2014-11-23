#pragma once

#include <pcl/console/parse.h>
#include <pcl/point_types.h>
#include <pcl/common/time.h>
#include <pcl/visualization/pcl_visualizer.h> 
#include <pcl/io/openni_grabber.h>
#include <pcl/sample_consensus/sac_model_plane.h>
#include <pcl/people/ground_based_people_detection_app.h>

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

// declarations of global variables

extern boost::mutex cloud_mutex;
extern int person_nr;

// declarations of global functions

void cloud_cb_(const PointCloudT::ConstPtr &callback_cloud, PointCloudT::Ptr& cloud, bool* new_cloud_available_flag);

void pp_callback(const pcl::visualization::PointPickingEvent& event, void* args);

int if_same_person(std::vector<Eigen::Vector4f> centroids, Eigen::Vector3f person, float thresold);

// definitions of auxiliary structures

struct callback_args {

	// structure used to pass arguments to the callback function

	PointCloudT::Ptr clicked_points_3d;
	pcl::visualization::PCLVisualizer::Ptr viewerPtr;

};

void mainLoop(pcl::visualization::PCLVisualizer *viewer, PointCloudT::Ptr cloud, float dist);

class Algorithm
{

public:

	Eigen::VectorXf ground_coeffs;
	float voxel_size;
	std::string svm_filename;
	Eigen::Matrix3f rgb_intrinsics_matrix;
	float min_confidence;
	float min_height;
	float max_height;
	float dist;
	PointCloudT::Ptr cloud;
	bool new_cloud_available_flag;
	bool algorithmEnabled;

	pcl::Grabber* interface;

	pcl::visualization::PCLVisualizer *viewer;

	//static boost::mutex cloud_mutex;

	enum { COLS = 640, ROWS = 480 };

	Algorithm(pcl::visualization::PCLVisualizer *_viewer);

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

};