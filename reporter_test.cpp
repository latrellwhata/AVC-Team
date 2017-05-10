#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <math.h>
#include "../lib/json.hpp"
#include "../src/utils.hpp"

using namespace std;
using json = nlohmann::json;

class Reporter {
  public:
    void init(string _host, int _port) {
      addr = _host.c_str();
      port = to_string(_port).c_str();

      //Ensure that servinfo is clear
      memset(&hints, 0, sizeof hints); // make sure the struct is empty

      //setup hints
      hints.ai_family = AF_UNSPEC; // don't care IPv4 or IPv6
      hints.ai_socktype = SOCK_STREAM; // TCP stream sockets

      //Setup the structs if error print why
      int res;
      if ((res = getaddrinfo(addr, port, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(res));
        return;
      }

      //setup the socket
      if ((s = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1) {
        perror("Failed to open socket");
      }

      cout << servinfo->ai_addr << endl;
      cout << servinfo->ai_addrlen << endl;
      int status = connect(s, servinfo->ai_addr, servinfo->ai_addrlen);
      cout << "connection finished" << endl;

      printf("status: %d\n", status);
      if (status == -1) {
        close(s);
        perror("Failed to connect");
      }
    }
    
    bool send_str(string msg) {
      int len = strlen(msg.c_str());
      int bytes_sent = send(s, msg.c_str(), len, 0);

      return bytes_sent == 0;
    }
    
    bool send_raw(const void *buf, int len) {
      int bytes_sent = send(s, buf, len, 0);
      return bytes_sent == 0;
    }
 
  private:
    addrinfo hints, *servinfo;
    const char *addr;
    const char *port;
    int s; //the socket descriptor
};

int main() {
  Reporter reporter;
  reporter.init("localhost", 1024);
  printf("hi\n");

  int x = 32;
  int y = 24;
  int vx = rand() % 2 ? -1 : 1;
  int vy = rand() % 2 ? -1 : 1;
  bool buf[64 * 48];

  printf("sending data\n");

  long int last_time;
  long int start_time = get_time();

  while (true) {
    if (x <= 4 || x >= 64 - 5) vx = -vx;
    if (y <= 4 || y >= 48 - 5) vy = -vy;
    
    x += vx;
    y += vy;

    for (int i = 0; i < 64 * 48; i++) {
      buf[i] = sqrt(pow(x - i % 64, 2) + pow(y - i / 64, 2)) < 5;
    }

    reporter.send_raw(buf, sizeof(buf));

    long int time = get_time();
    double error = sin((long double) get_time() / 1000 / 1000);
    double noisy_error = error + ((double) (rand() % 100) / 500 - 0.1);
    double turning = -noisy_error * 1.5;
    constrain(-1, 1, &noisy_error);
    constrain(-1, 1, &turning);

    int loop_time = 0;

    if (last_time) {
      loop_time = (int) (time - last_time);
    }

    json line = {
      { "error", noisy_error },
      { "turning", turning },
      { "derivative", turning / (rand() % 4 + 2) },
      { "left", vx < 0 },
      { "right", vx > 0 },
      { "front", vy < 0 },
      { "runTime", time - start_time },
      { "loopTime", loop_time },
      { "stage", "line" }
    };

    reporter.send_str(line.dump());

    last_time = time;

    usleep(100 * 1000);
  }
}
