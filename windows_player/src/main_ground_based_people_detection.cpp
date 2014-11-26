#include "Player.h"

enum { COLS = 640, ROWS = 480 };

int main (int argc, char** argv) {

  VisualiserT viewer("Wykrywanie smiesznych ludzi w srodowisku domowym");
  viewer.addText("copyright tra ta ta.", 40, 5);

  Player play(&viewer);

  //play.pause();
  //play.pause();

  boost::this_thread::sleep(boost::posix_time::milliseconds(3000));

  play.play();

  std::cout << "press 'Q' to quit" << std::endl;
  viewer.spin();

  //viewer.spinOnce();
  //while (!viewer.wasStopped()) { }

  return 0;
}

