#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../src/camera.hpp"

extern "C" int init(int verbosity);
extern "C" int take_picture();
extern "C" char get_pixel(int x, int y, int color);

int main(int argc, char* argv[]) {
  init(2);

  int threshold = 20;

  if (argc > 1) {
    threshold = atoi(argv[1]);
  }

  Camera camera;
  camera.init(320, 240, threshold);
  
  while (true) {
    camera.process_image();

    printf(
      "%d %d %d\n",
      camera.could_find_line_ahead(),
      camera.could_find_line_left(),
      camera.could_find_line_right()
    );

    camera.print_image();
    camera.can_see_red();

    usleep(1000 * 1000);
  }
}
