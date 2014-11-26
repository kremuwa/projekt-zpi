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

using namespace std;

class reader {
	int curFrame;
	int totalFrames;
	ifstream trjFile;
	string pcdPath;
	vector < pair<double, vector<pcl::people::PersonCluster<pcl::PointXYZRGBA> > > > bboxes;
public:
	reader(int frames);
	void startReading(string& trjPath);
	pair < pcl::PointCloud<pcl::PointXYZRGBA>, pair<double, vector <pcl::people::PersonCluster<pcl::PointXYZRGBA > > > > read();
	void jumpTo(int frame);
	int getCurFrame();
	int getTotalFrames();
	void stopReading();
private:
	string createFilePath(string& directoryPath, string& fileName)
};

#endif READER_H