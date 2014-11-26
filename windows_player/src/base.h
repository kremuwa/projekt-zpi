#pragma once

#include <pcl/point_types.h>
#include <pcl/console/parse.h>
#include <pcl/common/time.h>
#include <pcl/visualization/pcl_visualizer.h> 
#include <pcl/io/openni_grabber.h>
#include <pcl/sample_consensus/sac_model_plane.h>
#include <pcl/people/ground_based_people_detection_app.h>
#include <pcl/people/person_cluster.h>

#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <sstream>
#include <fstream>

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