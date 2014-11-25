#include "Player.h"


Player::Player(VisualiserT *_viewer) {
	this->viewer = _viewer;
}

Player::~Player(){
	this->viewer = NULL;
}

void Player::initialize(std::string file){
	std::cout << "initialize " << file << std::endl;
}

void Player::jumpTo(int frame){
	this->reader->jumpTo(frame);
}

int Player::getCurFrame() {
	this->current_frame = this->reader->getCurFrame();
	return this->current_frame;
}

int Player::getTotalFrames() {
	this->total_frames = this->reader->getTotalFrames();
	return this->total_frames;
}




void Player::play(){
	std::cout << "play" << std::endl;
}

void Player::pause(){
	std::cout << "pause" << std::endl;
}

void Player::stop(){
	std::cout << "stop" << std::endl;
}


std::string Player::randomString(size_t length) {
	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset)-1);
		return charset[rand() % max_index];
	};
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);
	return str;
}

void Player::drawLine(cubeStruct cube) {
	PointT p1;
	PointT p2;
	p1.x = cube.x_min;
	p1.y = cube.y_min;
	p1.z = cube.z_min;
	p2.x = cube.x_max;
	p2.y = cube.y_max;
	p2.z = cube.z_max;

	/*this->viewer->addLine(p1, p2, (double)0, (double)255, (double)0, (const std::string)(cube.name + \
		boost::lexical_cast<std::string>(p1.x) + \
		boost::lexical_cast<std::string>(p1.y) + \
		boost::lexical_cast<std::string>(p1.z) + \
		boost::lexical_cast<std::string>(p2.x) + \
		boost::lexical_cast<std::string>(p2.y) + \
		boost::lexical_cast<std::string>(p2.z)));*/

	this->viewer->addLine(p1, p2, (double)0, (double)255, (double)0, (const std::string)this->randomString(6));
}

void Player::drawCube(cubeStruct cube) {

	cubeStruct line;
	line.name = "line";

	// 0,0,0 -> 1,0,0
	line.x_min = cube.x_min;
	line.y_min = cube.y_min;
	line.z_min = cube.z_min;

	line.x_max = cube.x_max;
	line.y_max = cube.y_min;
	line.z_max = cube.z_min;

	this->drawLine(line);

	// 0,0,0 -> 0,1,0
	line.x_min = cube.x_min;
	line.y_min = cube.y_min;
	line.z_min = cube.z_min;

	line.x_max = cube.x_min;
	line.y_max = cube.y_max;
	line.z_max = cube.z_min;

	this->drawLine(line);

	// 0,0,0 -> 0,0,1
	line.x_min = cube.x_min;
	line.y_min = cube.y_min;
	line.z_min = cube.z_min;

	line.x_max = cube.x_min;
	line.y_max = cube.y_min;
	line.z_max = cube.z_max;

	this->drawLine(line);

	// 1,0,0 -> 1,1,0
	line.x_min = cube.x_max;
	line.y_min = cube.y_min;
	line.z_min = cube.z_min;

	line.x_max = cube.x_max;
	line.y_max = cube.y_max;
	line.z_max = cube.z_min;

	this->drawLine(line);

	// 1,1,0 -> 0,1,0
	line.x_min = cube.x_max;
	line.y_min = cube.y_max;
	line.z_min = cube.z_min;

	line.x_max = cube.x_min;
	line.y_max = cube.y_max;
	line.z_max = cube.z_min;

	this->drawLine(line);

	// 1,0,0 -> 1,0,1
	line.x_min = cube.x_max;
	line.y_min = cube.y_min;
	line.z_min = cube.z_min;

	line.x_max = cube.x_max;
	line.y_max = cube.y_min;
	line.z_max = cube.z_max;

	this->drawLine(line);

	// 1,0,1 -> 1,1,1
	line.x_min = cube.x_max;
	line.y_min = cube.y_min;
	line.z_min = cube.z_max;

	line.x_max = cube.x_max;
	line.y_max = cube.y_max;
	line.z_max = cube.z_max;

	this->drawLine(line);

	// 1,0,1 -> 0,0,1
	line.x_min = cube.x_max;
	line.y_min = cube.y_min;
	line.z_min = cube.z_max;

	line.x_max = cube.x_min;
	line.y_max = cube.y_min;
	line.z_max = cube.z_max;

	this->drawLine(line);

	// 0,0,1 -> 0,1,1
	line.x_min = cube.x_min;
	line.y_min = cube.y_min;
	line.z_min = cube.z_max;

	line.x_max = cube.x_min;
	line.y_max = cube.y_max;
	line.z_max = cube.z_max;

	this->drawLine(line);

	// 1,1,1 -> 0,1,1
	line.x_min = cube.x_max;
	line.y_min = cube.y_max;
	line.z_min = cube.z_max;

	line.x_max = cube.x_min;
	line.y_max = cube.y_max;
	line.z_max = cube.z_max;

	this->drawLine(line);

	// 1,1,0 -> 1,1,1
	line.x_min = cube.x_max;
	line.y_min = cube.y_max;
	line.z_min = cube.z_min;

	line.x_max = cube.x_max;
	line.y_max = cube.y_max;
	line.z_max = cube.z_max;

	this->drawLine(line);

	// 0,1,0 -> 0,1,1
	line.x_min = cube.x_min;
	line.y_min = cube.y_max;
	line.z_min = cube.z_min;

	line.x_max = cube.x_min;
	line.y_max = cube.y_max;
	line.z_max = cube.z_max;

	this->drawLine(line);
}



// debug only!
// debug only!
// debug only!


int Reader::getCurFrame(){
	return 10;
}

int Reader::getTotalFrames(){
	return 123;
}

void Reader::jumpTo(int frame){
	std::cout << "Jump to " << frame << std::endl;
}