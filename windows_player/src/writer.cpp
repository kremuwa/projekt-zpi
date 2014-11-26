#include "writer.h"

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

void writer::write(PointCloudT pointCloud, vector < pair<string, PeopleClusterT > > bboxes) {
	string path = createFilePath(pcdPath, to_string(curFrame));
	pcl::io::savePCDFileASCII(path, pointCloud);
	
	int time = diffclock(clock(), startTime);
	trjFile << time << "\t";

	for (int i = 0; i < bboxes.size(); i++) {
		pair<string, PeopleClusterT > personPair = bboxes[i];
		string personName = personPair.first;
		PeopleClusterT personCluser = personPair.second;
		cubeStruct pStruct;
		copyToCubeStruct(&pStruct, personCluser, personName);

		trjFile << personName << " " << pStruct.x_min << " " << pStruct.x_max << " "
			<< pStruct.y_min << " " << pStruct.y_max << " " << pStruct.z_min << " " << pStruct.z_max << "\t";
	}
	
	trjFile << endl;
	curFrame++; 
}

void writer::copyToCubeStruct(cubeStruct* pStruct, pcl::people::PersonCluster < PointT> pCluser, string pname) {
	(*pStruct).name = pname;
	(*pStruct).x_min = pCluser.getMin()(0);
	(*pStruct).y_min = pCluser.getMin()(1);
	(*pStruct).z_min = pCluser.getMin()(2);
	(*pStruct).x_max = pCluser.getMax()(0);
	(*pStruct).y_max = pCluser.getMax()(1);
	(*pStruct).z_max = pCluser.getMax()(2);
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