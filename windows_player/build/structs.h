#pragma once

#include <string>
#include <utility>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h> 

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