#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
// #include "../src/motors.hpp"
// #include "../lib/inih/cpp/INIReader.h"

extern "C" int init(int verbosity);
extern "C" void set_motor(int motor, int speed);

// Motors motors;

void terminate(int);

int main(int argc, char* argv[]) {
  init(2);

  signal(SIGTERM, terminate);
  signal(SIGINT, terminate);

  set_motor(1, 100);
  set_motor(2, 100);

  usleep(1000 * 1000);
}

void terminate(int signum) {
  set_motor(1, 0);
  set_motor(2, 0);
  exit(signum);
}
