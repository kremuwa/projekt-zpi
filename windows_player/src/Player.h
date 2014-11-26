#pragma once

#include "base.h"
#include "reader.h"


/*class Reader {
	int current_frame;
	int total_frames;

public:
	Reader();
	~Reader();
	void startReading(std::string file);
	void stopReading();
	frameStruct read();
	void jumpTo(int frame);
	int getCurFrame();
	int getTotalFrames();
};*/

// -----------------------------------------------

class Player {
	bool debug;
	boost::thread thread;
	bool pause_toggle;
public:
	int current_frame;
	int total_frames;
	Reader *reader;
	boost::mutex mutex;

	Player();
	~Player();
	bool getDebug(){ return this->debug; };
	bool getPause(){ return this->pause_toggle; };

	void initialize(std::string file);
	void jumpTo(int frame);
	int getCurFrame();
	int getTotalFrames();

	void play();
	void pause();
	void stop();
	void drawLine(cubeStruct cube, bool showName, VisualiserT *viewer);
	void drawCube(cubeStruct cube, VisualiserT *viewer);

	std::string randomString(size_t len);
};

void play_thread(Player *player);