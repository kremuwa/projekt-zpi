#include "reader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <time.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

using namespace std;

reader::reader(int frames) {
	totalFrames = frames;
	curFrame = 1;
}

void reader::startReading(string& trjPath) {
	trjFile.open(trjPath);
	if (trjFile.is_open() == true)
	{
		getline(trjFile, pcdPath);

		// #2 zaczytuje infor o bboxach z wszystkich klatek i zapisuje do vectora bboxes
		

		totalFrames = bboxes.size();
		curFrame = 1;
	}
	else {
		cout << "Nie znaleziono pliku .trj" << endl;
		totalFrames = -1;
	}
}

pair < pcl::PointCloud<pcl::PointXYZRGBA>, pair<double, vector <pcl::people::PersonCluster<pcl::PointXYZRGBA > > > > reader::read() {
	pair < pcl::PointCloud<pcl::PointXYZRGBA>, pair<double, vector <pcl::people::PersonCluster<pcl::PointXYZRGBA > > > > result;
	if (curFrame <= totalFrames)
	{
		string path = createFilePath(pcdPath, to_string(curFrame));
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
		pair<double, vector<pcl::people::PersonCluster<pcl::PointXYZRGBA> > > bbox;

		if (pcl::io::loadPCDFile<pcl::PointXYZ>(path, *cloud) == -1) 
		{
			cout << "Wyst¹pi³ b³¹d podczas wczytywania pliku: " << path;
		}
		bbox = bboxes[curFrame];
			
		result = make_pair(cloud, bbox);
		curFrame++;
	}
	
	return result;
}

int reader::getTotalFrames() {
	return totalFrames;
}

int reader::getCurFrame() {
	return curFrame;
}

void reader::jumpTo(int frame) {
	curFrame = frame;
}

void reader::stopReading() {
	trjFile.close;
	bboxes.clear();
}

string reader::createFilePath(string& directoryPath, string& fileName) {
	if (directoryPath.back() != '\\') {
		return directoryPath + "\\" + fileName;
	}
	return directoryPath + fileName;
}