#include <stdio.h>
#include <time.h>
#include "E101.h"

	
 int straight();
 int turn_right();
 int turn_left();
 int reverse();
 
 
 int main(){
 	init();
 	
 	while (1){
 
 	take_picture();
 	sleep1(0,100);
 	
 	
		int sum = 0;
 		int pix; // pixel
 		char white; // whiteness of that pixel
 		char signal; // siginal of that pixel
		int num_white_pixels;
		float k_P = 0.5;
		int P_signal = 0;
 		
 	for (pix=0,pix<320,pix++){
 		w = get_pixel(pix,120,3);
		if(white>127){ // sets pixel to white
 		signal=1;
		num_white_pixels++;	
		}
		else{ // sets pixel to black
 		signal=0;
		}
		if (num_white_pixels=0){// no white pixels
		reverse();
		}
 		sum = sum + (pix-160)*signal;
 		
		P_signal = sum * k_P;
		}
   
  	 
   
 
	if (sum=0){ // line is in the middle
		straight(int P_signal);
	}
	if (sum<0){ // line is to the left
		turn_left(int P_signal);
	}
	if sum>0){ // line is to the right
		turn_right(int P_signal);
	}
 
 
	int straight(P_signal){ // drives the robot straight ahead
		print("Direction = Straight\n");
		printf("Proportional Signal = %d\n" , P_signal);
		set_motor(1, -60);
		set_motor(2, 60);
		sleep1(0,100);
	}
 
	int turn_left(P_signal){ // turns left
		print("Direction = Left\n");
		printf("Proportional Signal = %d\n" , P_signal);
		set_motor(1, 60);
		set_motor(2, 60);
		sleep1(0,100);
	}
	int turn_right(P_signal){ // turns right
		print("Direction = Right\n");
		printf("Proportional Signal = %d\n" , P_signal);
		set_motor(1, -60);
		set_motor(2, -60);
		sleep1(0,100);
	}
	int reverse (){ // reverses the robot
		print("Direction = Reverse\n");
		set_motor(1, -60);
		set_motor(2, 60);
		sleep1(0,100);
	}
}	

