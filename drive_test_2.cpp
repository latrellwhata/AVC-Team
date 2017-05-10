#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "../src/motors.hpp"
#include "../lib/inih/cpp/INIReader.h"

extern "C" int init(int verbosity);
// extern "C" void set_motor(int motor, int speed);

Motors motors;

void terminate(int);

int main(int argc, char* argv[]) {
  init(2);

  signal(SIGTERM, terminate);
  signal(SIGINT, terminate);

  // Read the settings stored in the .ini file. Doing this allows us to tweak
  // parameters without compiling any code.
  INIReader config("./avc.ini");

  // Check for errors parsing the .ini settings file
  if (config.ParseError() < 0) {
    std::cout << "Can't load 'test.ini'\n";
    exit(1);
  }

  motors.init(
    // Minimum speed. Value to send to motors when speed is just above zero.
    config.GetInteger("motors", "min_speed", 0),
    
    // Maximum speed
    config.GetInteger("motors", "max_speed", 255),

    // Wheel speed coefficients, to adjust for physical errors with the robot
    config.GetReal("motors", "left_multiplier", 1),
    config.GetReal("motors", "right_multiplier", 1)
  );

  motors.set_velocities(100, 0);

  for (double speed = 0; speed < 255; speed += 5) {
    // std::cout << speed << std::endl;
    
    // set_motor(1, speed);
    // set_motor(2, speed);

    usleep(1000 * 1000);
  }
}

void terminate(int signum) {
  motors.set_velocities(0, 0);
  exit(signum);
}
