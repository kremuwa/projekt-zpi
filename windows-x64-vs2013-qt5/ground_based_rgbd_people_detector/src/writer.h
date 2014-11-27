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