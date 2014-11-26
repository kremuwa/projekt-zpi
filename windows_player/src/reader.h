#ifndef READER_H
#define READER_H
#include <string>
#include <fstream>
#include <pcl/console/parse.h>
#include <pcl/point_types.h>
#include <pcl/common/time.h>
#include <pcl/visualization/pcl_visualizer.h> 
#include <pcl/io/openni_grabber.h>
#include <pcl/sample_consensus/sac_model_plane.h>
#include <pcl/people/ground_based_people_detection_app.h>
#include "structs.h"

using namespace std;

typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloudT;
typedef pcl::people::PersonCluster<PointT> PeopleClusterT;
typedef pcl::visualization::PCLVisualizer VisualiserT;

class reader {
	int curFrame;
	int totalFrames;
	ifstream trjFile;
	string pcdPath;
	vector < pair<int, vector<cubeStruct> > > bboxes;
public:
	reader(int frames);
	void startReading(string& trjPath);
	frameStruct read();
	void jumpTo(int frame);
	int getCurFrame();
	int getTotalFrames();
	void stopReading();
private:
	string createFilePath(string& directoryPath, string& fileName);
	void parseLine(string line);
	vector<string> explode(const string& str, const char delimiter);
};

#endif READER_H