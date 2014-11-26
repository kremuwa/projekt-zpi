#ifndef WRITER_H
#define WRITER_H
#include <string>
#include <fstream>
#include <pcl/console/parse.h>
#include <pcl/point_types.h>
#include <pcl/common/time.h>
#include <pcl/visualization/pcl_visualizer.h> 
#include <pcl/io/openni_grabber.h>
#include <pcl/sample_consensus/sac_model_plane.h>
#include <pcl/people/ground_based_people_detection_app.h>

using namespace std;

class writer {
	int curFrame;
	ofstream trjFile;
	clock_t startTime; 
	string pcdPath;

public:
	void writer::write(pcl::PointCloud<pcl::PointXYZRGBA> pointCloud, vector <pcl::people::PersonCluster<pcl::PointXYZRGBA > >);
	void startWriting(string& pcdPath, string& trjPath);
	void stopWriting();
	long getCurFrame();

private:
	string createFileName(int i);
	string createFilePath(string& directoryPath, string& fileName);
	bool dirExists(string& path);
	bool fileExists(string& path);
	double diffclock(clock_t clock1, clock_t clock2);
};

#endif WRITER_H