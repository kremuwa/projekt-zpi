#include "Player.h"

enum { COLS = 640, ROWS = 480 };

int main (int argc, char** argv) {

  boost::this_thread::sleep(boost::posix_time::milliseconds(3000));

  Player play = Player();
  play.play();

  //viewer.spinOnce();
  //while (!viewer.wasStopped()) { }

  return 0;
}