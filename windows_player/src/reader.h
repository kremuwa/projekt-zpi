#ifndef READER_H
#define READER_H

#include "base.h"

using namespace std;

class Reader {
	int curFrame;
	int totalFrames;
	ifstream trjFile;
	string pcdPath;
	vector < pair<int, vector<cubeStruct> > > bboxes;
public:
	Reader();
	~Reader();
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