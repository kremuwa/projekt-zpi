#include "Player.h"

enum { COLS = 640, ROWS = 480 };

int main (int argc, char** argv) {

  boost::this_thread::sleep(boost::posix_time::milliseconds(2000));

  Player play = Player();
  play.play();

  // symuluje powiedzmy nieskonczonej petli utrzymujacej GUI przy zyciu.
  boost::this_thread::sleep(boost::posix_time::milliseconds(15000));

  return 0;
}