#include <iostream>
#include <string>
#include <future>
#include <unistd.h>

using namespace std;

string task1(string prompt) {
  string input;
  cout << prompt;
  getline(cin, input);
  return input;
}

int main() {
  future<string> input = async(task1, "> ");

  int x = 0;

  while (input.wait_for(chrono::seconds(0)) != future_status::ready) {
    x++;
    usleep(1000);
  }

  cout << x << endl;
}
