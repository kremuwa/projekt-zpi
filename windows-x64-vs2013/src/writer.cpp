#include "writer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <time.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

using namespace std;

void writer::startWriting(string& pcd_path, string& trjPath) {
	startTime = clock();
	curFrame = 1;
	pcdPath = pcd_path;

	if (dirExists(pcd_path)) {
		int fileNum = 0;

		while (fileExists(createFilePath(trjPath, createFileName(fileNum))) == true) {
			fileNum++;
		}

		trjFile.open(createFilePath(trjPath, createFileName(fileNum)));
		if (trjFile.is_open()) {
			trjFile << pcdPath << endl;
		}
		else
		{
			cout << "nie udalo sie otworzyc pliku" << endl;
		}
	}
}
void writer::write(pcl::PointCloud<pcl::PointXYZRGBA> pointCloud, vector <pcl::people::PersonCluster<pcl::PointXYZRGBA > > bboxes) {
	string path = createFilePath(pcdPath, to_string(curFrame));
	pcl::io::savePCDFileASCII(path, pointCloud);
	
	pair<double, vector<pcl::people::PersonCluster<pcl::PointXYZRGBA> > > bboxPair;
	double time = diffclock(clock(), startTime);
	bboxPair = make_pair(time, bboxes);

	// #1 jakieœ tam zapisywanie czasu oraz bboxow do plików 
	
	curFrame++;
}

string writer::createFileName(int i) {
	SYSTEMTIME st;
	GetSystemTime(&st);
	std::ostringstream ossMessage;
	ossMessage << st.wYear << st.wMonth << st.wDay << i;
	return ossMessage.str();
}

string writer::createFilePath(string& directoryPath, string& fileName) {
	if (directoryPath.back() != '\\') {
		return directoryPath + "\\" + fileName;
	}
	return directoryPath + fileName;
}

void writer::stopWriting() {
	trjFile.close();
}

long writer::getCurFrame() {
	return curFrame;
}

bool writer::dirExists(string& dirName_in) {
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  
	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;  
	return false;
}

bool writer::fileExists(string& path){
	DWORD ftyp = GetFileAttributesA(path.c_str());
	return !(ftyp == INVALID_FILE_ATTRIBUTES && GetLastError() == ERROR_FILE_NOT_FOUND);
}

double writer::diffclock(clock_t clock1, clock_t clock2) {
	double diffticks = clock1 - clock2;
	double diffms = diffticks / (CLOCKS_PER_SEC / 1000);
	return diffms;
}