/*

Project: People RGB-D Detector
Authors: Grzegorz Wójcicki, Micha³ Urbanek, Grzegorz Kozub, Mateusz Pasieka, Krzysztof Gieroñ, Jacek Pawelczak

Copyright(c) <YEAR>, <OWNER>
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met :

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and / or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.IN NO EVENT
SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT(INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/


#include "writer.h"

using namespace std;

void writer::startWriting(string& pcd_path, string& trjPath) {
	startTime = clock();
	curFrame = 1;
	pcdPath = pcd_path;

	if (dirExists(pcd_path)) {
		int fileNum = 0;
		string trjExt = "trj";
		while (fileExists(createFilePath(trjPath, createFileName(fileNum), trjExt)) == true) {
			fileNum++;
		}

		trjFile.open(createFilePath(trjPath, createFileName(fileNum), trjExt));
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
	string pcdExt = "pcd";
	string path = createFilePath(pcdPath, to_string(curFrame), pcdExt);
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

string writer::createFilePath(string& directoryPath, string& fileName, string& ext) {
	if (directoryPath.back() != '\\') {
		return directoryPath + "\\" + fileName + "." + ext;
	}
	return directoryPath + fileName + "." + ext;
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