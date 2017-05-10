#include <iostream>
#include <unistd.h>
#include "../src/ir.hpp"

extern "C" int init_hardware();

int main() {
  init_hardware();
  IR ir;
  ir.init(1, 0);

  while (true) {
    int left = ir.get_left();
    int right = ir.get_right();
    int front = ir.get_front();
    int error = ir.get_wall_error();
    bool can_see_wall = ir.can_see_walls();

    std::cout << can_see_wall << '\t' << left << '\t' << right << '\t' << front << '\t' << error << std::endl;
    usleep(50000);
  }
}
