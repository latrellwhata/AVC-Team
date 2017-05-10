# include <stdio.h>
# include <time.h>

extern "C" int init_hardware();
extern "C" int connect_to_server( char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);

char server_ip[] = "130.195.6.196";
int server_port = 1024;
char server_password[] = "Please";

int main() {
  init_hardware();

  connect_to_server(server_ip, server_port);
  send_to_server(server_password);

  char message[24];
  receive_from_server(message);
  send_to_server(message);
}
