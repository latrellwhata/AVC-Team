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
 		int i; // pixel
 		char w; // whiteness of that pixel
 		char s; // siginal of that pixel
 		
 	for (i=0,i<320,i++){
 		w = get_pixel(i,120,3);
		if(w>127){ // sets pixel to white
 		s=1;
		}
		else{ // sets pixel to black
 		s=0;
		}
		if (s=0){// no white pixels
		reverse();
		}
 		sum = sum + (i-160)*s;
 		}
 	
   
   
   
 
	if (sum=0){ // line is in the middle
		straight(int sum);
	}
	if (sum<0){ // line is to the left
		turn_left(int sum);
	}
	if sum>0){ // line is to the right
		turn_right(int sum);
	}
 
 
	int straight(){ // drives the robot straight ahead
		set_motor(1, -60);
		set_motor(2, 60);
		sleep1(0,100);
	}
 
	int turn_left(sum){ // turns left
		set_motor(1, 60);
		set_motor(2, 60);
		sleep1(0,100);
	}
	int turn_right(sum){ // turns right
		set_motor(1, -60);
		set_motor(2, -60);
		sleep1(0,100);
	}
	int reverse (sum){ // reverses the robot
		set_motor(1, -60);
		set_motor(2, 60);
		sleep1(0,100);
	}
}	

