#include <REGX52.H>
#include <stdio.h>
#include "Delay.h"

unsigned char displayNumber[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void staticDisplay(unsigned char location,unsigned char num){
	
	if(location == 1){
		P2_4 = 0;
		P2_3 = 0;
		P2_2 = 0;
	}else if(location == 2){
		P2_4 = 0;
		P2_3 = 0;
		P2_2 = 1;
	}else if(location == 3){
		P2_4 = 0;
		P2_3 = 1;
		P2_2 = 0;
	}else if(location == 4){
		P2_4 = 0;
		P2_3 = 1;
		P2_2 = 1;
	}else if(location == 5){
		P2_4 = 1;
		P2_3 = 0;
		P2_2 = 0;
	}else if(location == 6){
		P2_4 = 1;
		P2_3 = 0;
		P2_2 = 1;
	}else if(location == 7){
		P2_4 = 1;
		P2_3 = 1;
		P2_2 = 0;
	}else if(location == 8){
		P2_4 = 1;
		P2_3 = 1;
		P2_2 = 1;
	}else{
		printf("Error!\n");
	}
	
	P0 = displayNumber[num];
	
	setTimeout(1);
	P0 = 0x00;
}