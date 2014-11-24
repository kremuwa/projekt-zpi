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