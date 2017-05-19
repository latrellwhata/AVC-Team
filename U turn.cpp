#include  <stdio.h>
#include <time.h>
#include "E101.h"



int  main (){
init();

	set_motor(1,-180);
	set_motor(2,200);
	
	sleep1(1,0);
	set_motor(1,0);
	set_motor(2,0);
	return 1;
}
