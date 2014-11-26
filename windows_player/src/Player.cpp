#include "Player.h"

// debug only! debug only! debug only! debug only! debug only! debug only! debug only! debug only! debug only! debug only! debug only! debug only! debug only!
// debug only! debug only! debug only! debug only! debug only! debug only! debug only! debug only! debug only! debug only! debug only! debug only! debug only!
Reader::Reader(){
	this->current_frame = 0;
	this->total_frames = 2;
}
Reader::~Reader(){}
int Reader::getCurFrame(){return this->current_frame;}
int Reader::getTotalFrames(){return this->total_frames;}
void Reader::jumpTo(int frame){std::cout << "Jump to " << frame << std::endl;}
void Reader::startReading(std::string file){std::cout << "startReading " << file << std::endl;}
void Reader::stopReading(){std::cout << "stopReading, bitch" << std::endl;}

frameStruct Reader::read() {
	frameStruct klatka;
	klatka.cloud = new PointCloudT();
	klatka.frame_time = 5000;

	cubeStruct cube1;
	cubeStruct cube2;

	if (this->current_frame == 0){
		cube1.name = "(iter 1) Pierwszy czlowieczek";
		cube1.x_min = 2;
		cube1.x_max = 2.5;
		cube1.y_min = 1.3;
		cube1.y_max = 2.3;
		cube1.z_min = 2.2;
		cube1.z_max = 2.4;

		cube2.name = "(iter 1) Drugi humanoid";
		cube2.x_min = 4;
		cube2.x_max = 4.5;
		cube2.y_min = 1.3;
		cube2.y_max = 3.3;
		cube2.z_min = 3.2;
		cube2.z_max = 3.4;
	}
	else {
		cube1.name = "(iter 2) Pierwszy czlowieczek";
		cube1.x_min = 2;
		cube1.x_max = 2.5;
		cube1.y_min = 1.3;
		cube1.y_max = 2.3;
		cube1.z_min = 2.2;
		cube1.z_max = 2.4;

		cube2.name = "(iter 2) Drugi humanoid";
		cube2.x_min = 4;
		cube2.x_max = 4.5;
		cube2.y_min = 1.3;
		cube2.y_max = 3.3;
		cube2.z_min = 3.2;
		cube2.z_max = 3.4;
	}

	std::vector<cubeStruct> wektorLudzi = {cube1, cube2};

	this->current_frame += 1;

	klatka.people = wektorLudzi;

	return klatka;
}
// debug only! debug only! debug only! debug only! debug only! debug only! debug only! debug only! debug only! debug only! debug only! debug only! debug only!
// debug only! debug only! debug only! debug only! debug only! debug only! debug only! debug only! debug only! debug only! debug only! debug only! debug only!


Player::Player() {
	//this->viewer = _viewer;
	this->reader = new Reader();
	this->mutex.initialize();
	this->pause_toggle = false;
	this->debug = true;
}

Player::~Player(){
	//this->viewer = NULL;
	this->reader = NULL;
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

void Player::initialize(std::string file){
	if (this->debug){std::cout << "initialized " << file << std::endl;}
	this->reader->startReading(file);
}

int Player::getCurFrame() {
	return this->reader->getCurFrame();
}

int Player::getTotalFrames() {
	return this->reader->getTotalFrames();
}

void Player::jumpTo(int frame){
	this->reader->jumpTo(frame);
}

void Player::pause(){
	if (this->debug){ std::cout << "PAUSE [toggle]" << std::endl; }
	if (!this->pause_toggle) {
		if (this->debug){ std::cout << "PAUSE zablokowano" << std::endl; }
		this->pause_toggle = true;
	}else {
		if (this->debug){ std::cout << "PAUSE odblokowano" << std::endl; }
		this->pause_toggle = false;
	}
}

void Player::stop(){
	if (this->debug){ std::cout << "STOPPED!!! " << std::endl; }
	this->pause_toggle = false;
	this->thread.interrupt();
}

void Player::play(){
	this->thread=boost::thread (&play_thread, this);
	// stop dziala, chociaz tyle.
	//boost::this_thread::sleep(boost::posix_time::milliseconds(1500));
	//this->stop();
	thread.join();
}


void play_thread(Player *player){
	if (player->getDebug()){ std::cout << "PLAY THREAD!!! " << std::endl; }

	int currentFrame = player->getCurFrame();
	int totalFrames = player->getTotalFrames();
	int lastFrameTime = 0;
	frameStruct frame;

	VisualiserT viewer("PCL test");
	viewer.addText("copyright GW.", 50, 8);

	while (currentFrame < totalFrames) {
		if (player->getDebug()){ std::cout << "PLAY iteruje sie po klatkce " << currentFrame << std::endl; }
		if (!player->getPause()) {
			//if (this->mutex.try_lock() &&!this->pause_toggle)  
			if (player->getDebug()){ std::cout << "PLAY yo. rysuje " << std::endl; }
			frame = player->reader->read();

			//PointCloudT::Ptr cloud;
			//PointCloudT::Ptr cloud(new PointCloudT);

			boost::shared_ptr<PointCloudT> cloud = boost::make_shared<PointCloudT>(*frame.cloud);
			//cloud = frame.cloud;

			viewer.removeAllPointClouds();
			viewer.removeAllShapes();

			pcl::visualization::PointCloudColorHandlerRGBField<PointT> rgb(cloud);
			viewer.addPointCloud<PointT>(cloud, rgb, "input_cloud");
			viewer.setCameraPosition(-4, -1, -3, 0, -1, 0, 0);

			for (unsigned short int i = 0; i < frame.people.size(); i++){
				player->drawCube(frame.people.at(i), &viewer);
			}

			//w wersji zlaczonej z Grzeskiem K.  boost::this_thread::sleep(boost::posix_time::milliseconds(frame.frame_time - lastFrameTime));
			boost::this_thread::sleep(boost::posix_time::milliseconds(2000));

			lastFrameTime = frame.frame_time;

			currentFrame = player->getCurFrame();

			//this->mutex.unlock();
		}
		else {
			if (player->getDebug()){ std::cout << "PLAY yo. czekam " << std::endl; }
			boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
		}
	}
	std::cout << "press 'Q' to quit" << std::endl;
	viewer.spin();
}







void Player::drawLine(cubeStruct cube, bool showName, VisualiserT *viewer) {
	PointT p1, p2;

	p1.x = cube.x_min;
	p1.y = cube.y_min;
	p1.z = cube.z_min;
	p2.x = cube.x_max;
	p2.y = cube.y_max;
	p2.z = cube.z_max;

	viewer->addLine(p1, p2, (double)0, (double)255, (double)0, (const std::string)this->randomString(6));

	if (showName){
		viewer->addText3D((const std::string)cube.name, p1, 0.1, 1.0, 1.0, 1.0, (const std::string)this->randomString(6));
	}
}

void Player::drawCube(cubeStruct cube, VisualiserT *viewer) {

	cubeStruct line;
	line.name = cube.name;

	// 0,0,0 -> 1,0,0
	line.x_min = cube.x_min;
	line.y_min = cube.y_min;
	line.z_min = cube.z_min;

	line.x_max = cube.x_max;
	line.y_max = cube.y_min;
	line.z_max = cube.z_min;

	this->drawLine(line, true, viewer);

	// 0,0,0 -> 0,1,0
	line.x_min = cube.x_min;
	line.y_min = cube.y_min;
	line.z_min = cube.z_min;

	line.x_max = cube.x_min;
	line.y_max = cube.y_max;
	line.z_max = cube.z_min;

	this->drawLine(line, false, viewer);

	// 0,0,0 -> 0,0,1
	line.x_min = cube.x_min;
	line.y_min = cube.y_min;
	line.z_min = cube.z_min;

	line.x_max = cube.x_min;
	line.y_max = cube.y_min;
	line.z_max = cube.z_max;

	this->drawLine(line, false, viewer);

	// 1,0,0 -> 1,1,0
	line.x_min = cube.x_max;
	line.y_min = cube.y_min;
	line.z_min = cube.z_min;

	line.x_max = cube.x_max;
	line.y_max = cube.y_max;
	line.z_max = cube.z_min;

	this->drawLine(line, false, viewer);

	// 1,1,0 -> 0,1,0
	line.x_min = cube.x_max;
	line.y_min = cube.y_max;
	line.z_min = cube.z_min;

	line.x_max = cube.x_min;
	line.y_max = cube.y_max;
	line.z_max = cube.z_min;

	this->drawLine(line, false, viewer);

	// 1,0,0 -> 1,0,1
	line.x_min = cube.x_max;
	line.y_min = cube.y_min;
	line.z_min = cube.z_min;

	line.x_max = cube.x_max;
	line.y_max = cube.y_min;
	line.z_max = cube.z_max;

	this->drawLine(line, false, viewer);

	// 1,0,1 -> 1,1,1
	line.x_min = cube.x_max;
	line.y_min = cube.y_min;
	line.z_min = cube.z_max;

	line.x_max = cube.x_max;
	line.y_max = cube.y_max;
	line.z_max = cube.z_max;

	this->drawLine(line, false, viewer);

	// 1,0,1 -> 0,0,1
	line.x_min = cube.x_max;
	line.y_min = cube.y_min;
	line.z_min = cube.z_max;

	line.x_max = cube.x_min;
	line.y_max = cube.y_min;
	line.z_max = cube.z_max;

	this->drawLine(line, false, viewer);

	// 0,0,1 -> 0,1,1
	line.x_min = cube.x_min;
	line.y_min = cube.y_min;
	line.z_min = cube.z_max;

	line.x_max = cube.x_min;
	line.y_max = cube.y_max;
	line.z_max = cube.z_max;

	this->drawLine(line, false, viewer);

	// 1,1,1 -> 0,1,1
	line.x_min = cube.x_max;
	line.y_min = cube.y_max;
	line.z_min = cube.z_max;

	line.x_max = cube.x_min;
	line.y_max = cube.y_max;
	line.z_max = cube.z_max;

	this->drawLine(line, false, viewer);

	// 1,1,0 -> 1,1,1
	line.x_min = cube.x_max;
	line.y_min = cube.y_max;
	line.z_min = cube.z_min;

	line.x_max = cube.x_max;
	line.y_max = cube.y_max;
	line.z_max = cube.z_max;

	this->drawLine(line, false, viewer);

	// 0,1,0 -> 0,1,1
	line.x_min = cube.x_min;
	line.y_min = cube.y_max;
	line.z_min = cube.z_min;

	line.x_max = cube.x_min;
	line.y_max = cube.y_max;
	line.z_max = cube.z_max;

	this->drawLine(line, false, viewer);
}