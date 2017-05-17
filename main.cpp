#include <stdio.h>
#include <time.h>
#include "E101.h"

 
 
 int main(){
 	init();
 	
 	while (1){
 
 	take_picture();
 	sleep1(0,100);
 	
 	
		int sum = 0;
 		int pix; // pixel
 		char white; // whiteness of that pixel
 		char sig[320]; // siginal of that pixel
		int num_white_pixels = 0;
		float k_P = 0.5;
		int P_signal = 0;
		float multi = 0.4;
		
 		
 	for (pix=0;pix<320;pix++){
 		white = get_pixel(pix,120,3);
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
			printf("White Pixles = %d\n" , num_white_pixels);
			int v1 = 60+P_signal*multi;
			int v2 = 60-P_signal*multi;
		
		if (v1>255){ //makes sure motor speed is between the accepted values
			v1 = 200;
		}
		if (v1>-255){ //makes sure motor speed is between the accepted values
			v1 = -200;
		}
		if (v2>255){ //makes sure motor speed is between the accepted values
			v2 = 200;
		}
		if (v2>-255){ //makes sure motor speed is between the accepted values
			v2 = -200;
		}
		
			
  		
		if (num_white_pixels>0){ //if this is not above 0 then we dont have a siginal
			printf("Direction = Foward\n");
			printf("Proportional Signal = %d\n" , P_signal);
			printf("Motor 1 = %d \n Motor 2 =%d", v1, v2) ;
			set_motor(1,v1);
			set_motor(2,v2);
		}
		else { // no white pixels so we must go back to find the line
			printf("Direction = Reverse\n");
			printf("Motor 1 = %d \n Motor 2 =%d", -v1, -v2) ;
			set_motor(1, -v1);
			set_motor(2, -v2);
		}
	}
}

 	

