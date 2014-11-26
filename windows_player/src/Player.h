#pragma once

#include "base.h"


class Reader {
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
};

// -----------------------------------------------


class Player {
	static const bool debug = true;
	boost::mutex mutex;
	bool pause_toggle;
public:
	VisualiserT *viewer;
	int current_frame;
	int total_frames;
	Reader *reader;

	Player(VisualiserT *_viewer);
	~Player();

	void initialize(std::string file);
	void jumpTo(int frame);
	int getCurFrame();
	int getTotalFrames();

	void play();
	void pause();
	void stop();
	void drawLine(cubeStruct cube, bool showName);
	void drawCube(cubeStruct cube);

	std::string randomString(size_t len);
};

