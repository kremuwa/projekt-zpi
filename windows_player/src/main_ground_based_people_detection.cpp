#include "Player.h"

enum { COLS = 640, ROWS = 480 };

int main (int argc, char** argv) {

  VisualiserT viewer("PCL Viewer");
  viewer.addText("copyright tra ta ta.", 40, 5);

  Player play(&viewer);

  PointT punkt;
  punkt.x = 1;
  punkt.y = 1;
  punkt.z = -2;

  //play.pause();
  //play.pause();

  boost::this_thread::sleep(boost::posix_time::milliseconds(1000));

  play.play();

  std::cout << "press 'Q' to quit" << std::endl;
  viewer.spin();

  //viewer.spinOnce();
  //while (!viewer.wasStopped()) { }

  return 0;
}

