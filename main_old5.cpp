#include <stdio.h>
#include <time.h>
#include "E101.h"

extern "C++" int connect_to_server( char server[15],int port);
extern "C++" int send_to_server(char message[6]);
extern "C++" int receive_from_server(char message[6]);

int main(){
	
	init();
 		
 	while (1){ // infinte loop
 	
 	bool send = true;
 	
 			if (send ==	true){
			char server[15] = {'1','3','0','.','1','9','5','.','6','.','1','9','6'};
			connect_to_server(server, 1024);
			char message[6] = {'P','l','e','a','s','e'};
			send_to_server(message);
			char password[6];
			receive_from_server(password);
			send_to_server(password);
			send = false;
		}
 
 	take_picture();
 	//display_picture(0,50000);
  	
		int sum = 0;
 		int pix; // pixel
 		char white; // whiteness of that pixel
 		char sig[320]; // siginal of that pixel
		int num_white_pixels = 0;
		float k_P = 0.0085;
		int P_signal = 0.0;
		//float multi = 0.2;
		
 		
 	for (pix=0;pix<320;pix++){
 		white = get_pixel(120,pix,3);
		if(white>127){ // sets pixel to white
 		sig[pix]=1;
		num_white_pixels++;	
		}
		else{ // sets pixel to black
 		sig[pix]=0;
		}
		
 		sum = sum + (pix-160)*sig[pix];
		P_signal = sum * k_P;
		}
		printf("White Pixels = %d\n" , num_white_pixels);
			
			int v1 = 60+P_signal;
			int v2 = 60-P_signal;
		
		
		// makes sure motor values are not too high
		
		
		if (v1>200){ //makes sure motor speed is between the accepted values
			v1 = 200;
		}
		if (v1 < -200){ //makes sure motor speed is between the accepted values
			v1 = -200;
		}
		if (v2>200){ //makes sure motor speed is between the accepted values
			v2 = 200;
		}
		if (v2 < -200){ //makes sure motor speed is between the accepted values
			v2 = -200;
		}
		
		// makes sure motor values are not too low
		
		
		if (v1>= 0 && v1 < 60){ //makes sure motor speed is between the accepted values
			v1 = 60;
		}
		if (v1 <0 && v1 > -60){ //makes sure motor speed is between the accepted values
			v1 = -60;
		}
		if (v2>= 0 && v2 < 60){ //makes sure motor speed is between the accepted values
			v2 = 60;
		}
		if (v2 <0 && v2 > -60){ //makes sure motor speed is between the accepted values
			v2 = -60;
		}
		
		if (num_white_pixels>0){ //if this is not above 0 then we dont have a siginal
			//v1=90;
			//v2=90;
			printf("Direction = Foward\n");
			printf("Proportional Signal = %d\n" , P_signal);
			printf("Motor 1 = %d \n Motor 2 =%d", v1, v2) ;
			set_motor(1,v1);
			set_motor(2,v2);
			sleep1(0,5000);
		}
		else { // no white pixels so we must go back to find the line
			//v1=90;
			//v2=90;
			printf("Direction = Reverse\n");
			printf("Motor 1 = %d \n Motor 2 =%d", -v1, -v2) ;
			set_motor(1, -v1*1.0);
			set_motor(2, -v2*0.5);
			sleep1(0,500);
		}

	}
	
	
}
