#ifndef WRITER_H
#define WRITER_H

#include "base.h"

using namespace std;

class writer {
	int curFrame;
	ofstream trjFile;
	clock_t startTime; 
	string pcdPath;

public:
	void writer::write(PointCloudT pointCloud, vector < pair<string, PeopleClusterT > > );
	void startWriting(string& pcdPath, string& trjPath);
	void stopWriting();
	long getCurFrame();

private:
	string createFileName(int i);
	string createFilePath(string& directoryPath, string& fileName, string& ext);
	bool dirExists(string& path);
	bool fileExists(string& path);
	double diffclock(clock_t clock1, clock_t clock2);
	void copyToCubeStruct(cubeStruct*, pcl::people::PersonCluster < PointT>, string Name);
};

#endif WRITER_H