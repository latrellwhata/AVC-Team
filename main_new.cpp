#include <stdio.h>
#include <time.h>
#include "E101.h"

 
 
int main(){
 	init();
 	
 	// test motors code
 	/*
    set_motor(2,150);
    set_motor(1,150);
	//set_motor(2,v2);
 	sleep1(9,0);
 	set_motor(2,0);
 	set_motor(1,0);
	return 1;
 	*/
 	
 	
 	while (1){ // infinte loop
 
 	take_picture();
 	display_picture(0,5000);
 	
 	
 // Horizontal scan vairibles
		int sum_H = 0;
 		int pix_H; // pixel
 		char white_H; // whiteness of that pixel on the Horizontal Line
 		char sig_H[320]; // siginal of that pixel
		int num_white_pixels_H = 0;
		//int num_red_pixels = 0;
		//char red;
		
// Vertial Left scan Varibles
		int pix_VL;
 		int sum_VL = 0;
 		int pix_VL; // pixel
 		char white_VL; // whiteness of that pixel on the vertical Line
 		char sig_VL[240]; // siginal of that pixel
		int num_white_pixels_VL = 0;
		
// Vertial Right scan Varibles
		
 		int pix_VR;
 		int sum_VR = 0;
 		int pix_VR; // pixel
 		char white_VR; // whiteness of that pixel on the vertical Line
 		char sig_VR[240]; // siginal of that pixel
		int num_white_pixels_VR = 0;
 			
		
		
// other Varibles
		
		int count1 =0;
		int count2 =0;
		int count3 =0;
		int debug = 0; // Turns on all the print statements
// PID values	
		int PID_signal = 0
		int current_sig;
		int previous_sig;
//P
		float k_P = 0.0085;
		int P_signal = 0.0;
		
		
//I		
		int I_signal = 0;
		float k_I = 0.5;
		
//D		
		int D_signal = 0;
		float k_D = 0.5;

		
		
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
// Error siginal Cacaulation
			sum_H = sum_H + (pix_H-160)*sig_H[pix_H];
			P_signal = sum_H * k_P;
			}
			sum_H_Difference = current_sum_H-previous_sum_H;
			D_signal = (sum_H_Difference/error_period)*k_D;
			previous_sum_H = current_sum_H;
		
// for Vertical Left Line 
		for (pix_VL=0;pix_VL<240;pix_VL++){
			white_VL = get_pixel(pix_VL,40,3);
	
			if(white_VL>127){ // sets pixel to white
			sig_VL[pix_VL]=1;
			num_white_pixels_VL++;	
			}
			else{ // sets pixel to black
			sig_VL[pix_VL]=0;
			}
		}	
				
// For Vertiacal Right Line

		for (pix_VR=0;pix_VR<240;pix_VR++){
			white_VR = get_pixel(pix_VR,200,3);
	
			if(white_VR>127){ // sets pixel to white
			sig_VR[pix_VR]=1;
			num_white_pixels_VR++;	
			}
			else{ // sets pixel to black
			sig_VR[pix_VR]=0;
			}
		}	

		
//Sets up Initial Motor speeds using PID stuff
	 	if (debug == 1){
			printf("White Pixels HORIZONTAL = %d\n" , num_white_pixels_H);
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
		
		
		//
		if (num_white_pixels_H>=200){ //this is at the white line... ALSO THIS WILL PROBALLY NOT WORK
			v1 = -60;
			v2 = 80
			count1++;
			if (count1==1 && count2==1){
			set_motor(1,v1);
			set_motor(2,v2);
			sleep1(0,500000);
			}
			count2++;
			if (count1 ==2 && count2 =2){
			set_motor(1,v1);
			set_motor(2,v2);
			sleep1(0,500000);
			}		
		}
		
			
		
		
  		
		if (num_white_pixels_H>3 && num_white_pixels_H<200 ){ //if this is not above 0 then we dont have a siginal
			//v1=90;
			//v2=90;
			if (debug == 1){
				printf("Direction = Foward\n");
				printf("Proportional Signal = %d\n" , P_signal);
				printf("Motor 1 = %d \n Motor 2 =%d \n", v1, v2) ;
			}	
			set_motor(1,v1);
			set_motor(2,v2);
			sleep1(0,50000);
		}
		
		
			
		else { // no white pixels so we must go back to find the line
			//v1=90;
			//v2=90;
			if (debug == 1){
				printf("Direction = Reverse\n");
				printf("Motor 1 = %d \n Motor 2 =%d \n", -v1, -v2) ;
			}
			set_motor(1, -v1*1.3);
			set_motor(2, -v2*0.7);
			sleep1(0,5000);
		}
		
	}
	
}

 	

