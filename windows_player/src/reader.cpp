#include "reader.h"

using namespace std;

Reader::Reader() {}
Reader::~Reader() {}

void Reader::startReading(string& trjPath) {
	try {
		trjFile.open(trjPath);

		if (trjFile.is_open() == true) {
			getline(trjFile, pcdPath);

			string line;
			while (getline(trjFile, line)) {
				this->parseLine(line);
			}
		
			totalFrames = this->bboxes.size();
			curFrame = 1;
		}
		else {
			cout << "Nie znaleziono pliku .trj" << endl;
			this->totalFrames = -1;
		}
	}
	catch (...){
		throw;
	}
}

void Reader::parseLine(string line) {
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

vector<string> Reader::explode(const string& str, const char delimiter)
{
	vector<string> elements;
	stringstream stream(str);
	string item;
	while (getline(stream, item, delimiter))
		elements.push_back(item);

	return elements;
}

frameStruct Reader::read() {
	frameStruct result;
	if (curFrame <= totalFrames)
	{
		string path = createFilePath(pcdPath, to_string(curFrame));
		PointCloudT::Ptr cloud(new PointCloudT);
		if (pcl::io::loadPCDFile<PointT>(path, *cloud) == -1)
		{
			cout << "Wyst¹pi³ b³¹d podczas wczytywania pliku: " << path;
		}
		
		result.cloud = cloud.get();
		result.frame_time = bboxes[curFrame].first;
		result.people = bboxes[curFrame].second;
		curFrame++;
	}
	return result;
}


int Reader::getTotalFrames() {
	return totalFrames;
}

int Reader::getCurFrame() {
	return curFrame;
}

void Reader::jumpTo(int frame) {
	curFrame = frame;
}

void Reader::stopReading() {
	trjFile.close();
	bboxes.clear();
}

string Reader::createFilePath(string& directoryPath, string& fileName) {
	if (directoryPath.back() != '\\') {
		return directoryPath + "\\" + fileName;
	}
	return directoryPath + fileName;
}