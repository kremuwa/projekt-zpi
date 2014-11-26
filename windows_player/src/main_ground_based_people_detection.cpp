#include "Player.h"

enum { COLS = 640, ROWS = 480 };

int main (int argc, char** argv) {

  //boost::this_thread::sleep(boost::posix_time::milliseconds(1000));

  Player play = Player();
  play.initialize("reader.mockup.trajectory");
  play.play();

  // symuluje powiedzmy nieskonczonej petli utrzymujacej GUI przy zyciu.
  boost::this_thread::sleep(boost::posix_time::milliseconds(40000));

  return 0;
}