#include <stdio.h>
#include <time.h>
#include "E101.h"

 
 
int main(){
 	init();
 	
	
	
 	while (1){ // infinte loop
 
 	take_picture();
 	//display_picture(0,5000);
 	
 	
 // Horizontal scan vairibles
		int sum_H = 0;
 		int pix_H; // pixel
 		char white_H; // whiteness of that pixel on the Horizontal Line
 		char sig_H[320]; // siginal of that pixel
		int num_white_pixels_H = 0;
		
// Vertial Left scan Varibles
		int pix_VL;
 		char white_VL; // whiteness of that pixel on the vertical Line
		int num_white_pixels_VL = 0;
		
// Vertial Right scan Varibles
		
 		int pix_VR;
 		char white_VR; // whiteness of that pixel on the vertical Line
		int num_white_pixels_VR = 0;
 			
		
		
// other Varibles
		int debug = 0; // Turns on all the print statements

//P
		float k_P = 0.0085;
		int P_signal = 0.0;


		
		
 // for the Horizontal Line
 		
		for (pix_H=0;pix_H<320;pix_H++){
			white_H = get_pixel(120,pix_H,3);
	
			if(white_H>127){ // sets pixel to white
			sig_H[pix_H]=1;
			num_white_pixels_H++;	
			}
			else{ // sets pixel to black
			sig_H[pix_H]=0;
			}
// Error siginal Cacaulations
			
// P Signal
			sum_H = sum_H + (pix_H-160)*sig_H[pix_H];
			P_signal = sum_H * k_P;

		
// for Vertical Left Line 
		for (pix_VL=0;pix_VL<240;pix_VL++){
			white_VL = get_pixel(pix_VL,40,3);
			if(white_VL>127){ // sets pixel to white
			num_white_pixels_VL++;	
			}
		
		}	
				
// For Vertiacal Right Line

		for (pix_VR=0;pix_VR<240;pix_VR++){
			white_VR = get_pixel(pix_VR,200,3);
			if(white_VR>127){ // sets pixel to white
			num_white_pixels_VR++;	
			}
			
		}	

		
//Sets up Initial Motor speeds using PID stuff
	 	if (debug == 1){
			printf("White Pixels HORIZONTAL = %d\n" , num_white_pixels_H);
			printf("White Pixels V LEFT = %d\n" , num_white_pixels_VL);
			printf("White Pixels V RIGHT = %d\n" , num_white_pixels_VR);
		}
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

	// setting Motor speed based on Image	
  		
		if (num_white_pixels_VL > 15 && num_white_pixles_H >150 ){ //this is at a turn option
			if (debug == 1){
				printf("Direction = LEFT TURN \n");
				printf("Proportional Signal = %d\n" , P_signal);
				printf("Motor 1 = %d \n Motor 2 =%d \n", v1, v2) ;
			}
			v1 =-180;
			v2 = 200;
			set_motor(1,v1);
			set_motor(2,v2);
			sleep1(0,400000);
		}
			
		if (num_white_pixels_H>0 ){ //if this is not above 0 then we dont have a siginal
			if (debug == 1){
				printf("Direction = Foward\n");
				printf("Proportional Signal = %d\n" , P_signal);
				printf("Motor 1 = %d \n Motor 2 =%d \n", v1, v2) ;
			}	
			set_motor(1,v1);
			set_motor(2,v2);
			sleep1(0,5000);
		}
			
		
		
			
		else { // no white pixels so we must go back to find the line
			if (debug == 1){
				printf("Direction = Reverse\n");
				printf("Motor 1 = %d \n Motor 2 =%d \n", -v1, -v2) ;
			}
			v1 =-180;
			v2 = 200;
			set_motor(1, v1);
			set_motor(2, v2);
			//set_motor(1, -v1*1.1);
			//set_motor(2, -v2*1.0);
			sleep1(1,0);
		}
		
	}
	
}

 	

