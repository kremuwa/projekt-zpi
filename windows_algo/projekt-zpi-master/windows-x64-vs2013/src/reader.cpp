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

		string line;
		while (getline(trjFile, line)) {
			parseLine(line);
		}
		

		totalFrames = bboxes.size();
		curFrame = 1;
	}
	else {
		cout << "Nie znaleziono pliku .trj" << endl;
		totalFrames = -1;
	}
}

void reader::parseLine(string line) {
	vector<cubeStruct> resultCubes;
	vector<string> cubes = explode(line, '\t');
	istringstream iss(cubes[0]);
	int time;
	iss >> time;
	for (int i = 1; i < cubes.size(); i++) {
		vector<string> coords = explode(cubes[i], ' ');
		cubeStruct cube;
		cube.name = coords[0];
		cube.x_min = atof(coords[1].c_str());
		cube.x_max = atof(coords[2].c_str());
		cube.y_min = atof(coords[3].c_str());
		cube.y_max = atof(coords[4].c_str());
		cube.z_min = atof(coords[5].c_str());
		cube.x_max = atof(coords[6].c_str());
		resultCubes.push_back(cube);
	}
	bboxes.push_back(make_pair(time, resultCubes));
}

vector<string> reader::explode(const string& str, const char delimiter)
{
	vector<string> elements;
	stringstream stream(str);
	string item;
	while (getline(stream, item, delimiter))
		elements.push_back(item);

	return elements;
}

pair<PointCloudT, pair<int, vector<cubeStruct> > > reader::read() {
	pair<PointCloudT, pair<int, vector<cubeStruct> > > result;
	if (curFrame <= totalFrames)
	{
		string path = createFilePath(pcdPath, to_string(curFrame));
		PointCloudT::Ptr cloud(new PointCloudT);
		pair<int, vector<cubeStruct> > bboxPair;

		if (pcl::io::loadPCDFile<PointT>(path, *cloud) == -1)
		{
			cout << "Wyst¹pi³ b³¹d podczas wczytywania pliku: " << path;
		}
		bboxPair = bboxes[curFrame];

		result = make_pair(*cloud, bboxPair);
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
	trjFile.close();
	bboxes.clear();
}

string reader::createFilePath(string& directoryPath, string& fileName) {
	if (directoryPath.back() != '\\') {
		return directoryPath + "\\" + fileName;
	}
	return directoryPath + fileName;
}