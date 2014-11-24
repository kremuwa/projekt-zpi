#pragma once

#include <pcl/console/parse.h>
#include <pcl/point_types.h>
#include <pcl/common/time.h>
#include <pcl/visualization/pcl_visualizer.h> 
#include <pcl/io/openni_grabber.h>
#include <pcl/sample_consensus/sac_model_plane.h>
#include <pcl/people/ground_based_people_detection_app.h>




#include <pcl/people/person_cluster.h>
#include <string>
#include <utility>
#include <iostream>

typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloudT;
typedef pcl::people::PersonCluster<PointT> PeopleClusterT;
typedef pcl::visualization::PCLVisualizer VisualiserT;

class Reader {
public:
	Reader();
	~Reader();

	int current_frame;
	int total_frames;

	void startReading(std::string file);
	std::pair < PointCloudT, std::pair<int, std::vector<PeopleClusterT>>> read();
	void jumpTo(int frame);
	int getCurFrame();
	int getTotalFrames();
	void stopReading();
};


class Player {
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
};

