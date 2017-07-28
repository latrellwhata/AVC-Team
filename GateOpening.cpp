# include <stdio.h>
# include <time.h>
# include "E101.h"

extern "C++" int connect_to_server( char server[15],int port);
extern "C++" int send_to_server(char message[6]);
extern "C++" int receive_from_server(char message[6]);

int main(){
	char server[15] = {'1','3','0','.','1','9','5','.','6','.','1','9','6'};
	connect_to_server(server, 1024);
	char message[6] = {'P','l','e','a','s','e'};
	send_to_server(message);
	char password[6];
	receive_from_server(password);
	send_to_server(password);
return 0;
}
