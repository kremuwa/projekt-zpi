#pragma once

#include <pcl/console/parse.h>
#include <pcl/point_types.h>
#include <pcl/common/time.h>
#include <pcl/visualization/pcl_visualizer.h> 
#include <pcl/io/openni_grabber.h>
#include <pcl/sample_consensus/sac_model_plane.h>
#include <pcl/people/ground_based_people_detection_app.h>




#include <pcl/people/person_cluster.h>
#include <pcl/ModelCoefficients.h>
#include <string>
#include <utility>
#include <iostream>


typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloudT;
typedef pcl::people::PersonCluster<PointT> PeopleClusterT;
typedef pcl::visualization::PCLVisualizer VisualiserT;

typedef struct {
	std::string name;
	double x_min;
	double x_max;
	double y_min;
	double y_max;
	double z_min;
	double z_max;
} cubeStruct;

typedef struct {
	PointCloudT* cloud;
	int frame_time;
	std::vector<cubeStruct> people;
} frameStruct;




// -----------------------------------------------



class Reader {
	int current_frame;
	int total_frames;

public:
	Reader();
	~Reader();
	void startReading(std::string file);
	void stopReading();
	frameStruct read();
	void jumpTo(int frame);
	int getCurFrame();
	int getTotalFrames();
};


class Player {
	static const bool debug = true;
	boost::mutex mutex;
	bool pause_toggle;
public:
	VisualiserT *viewer;
	int current_frame;
	int total_frames;
	Reader *reader;

	Player(VisualiserT *_viewer);
	~Player();

	void initialize(std::string file);
	void jumpTo(int frame);
	int getCurFrame();
	int getTotalFrames();

	void play();
	void pause();
	void stop();
	void drawLine(cubeStruct cube, bool showName);
	void drawCube(cubeStruct cube);

	std::string randomString(size_t len);
};

