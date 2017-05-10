# AVC-Team;
#include <stdio.h>
#include <time.h>
#include "E101.h"

//straight drive

int main(){
    init();
    set_motor(1,150);
    sleep1(0,500000);
    set_motor(2, -150);
    sleep1(0,500000);
return 0;}
