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
		
		int v1 = 70+P_signal*multi;
		int v2 = 70-P_signal*multi;
  		
		if (num_white_pixels!=0){ //if no white pixels, we lost the line
		printf("Direction = Foward\n");
		printf("Proportional Signal = %d\n" , P_signal);
		printf("Motor 1 = %d \n Motor 2 =%d", v1, v2) ;
		set_motor(1,v1);
		set_motor(2,v2);
		}
		else {
		printf("Direction = Reverse\n");
		printf("Motor 1 = %d \n Motor 2 =%d", -v1, -v2) ;
		set_motor(1, -v1);
		set_motor(2, -v2);
		}
	}
}

 	

