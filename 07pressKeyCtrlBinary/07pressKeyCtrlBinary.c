#include <REGX52.H>
#include <INTRINS.H>
#include <stdio.h>
#include <stdlib.h>

void setTimeout(unsigned int delayTime)		//@11.0592MHz
{
	unsigned char i, j;

	while(delayTime){
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
		delayTime--;
	}
	
}


void swapRegister(){
	int temp;
	temp = P2_7;
	P2_7 = P2_0;
	P2_0 = temp;
	
	temp = P2_6;
	P2_6 = P2_1;
	P2_1 = temp;
	
	temp = P2_5;
	P2_5 = P2_2;
	P2_2 = temp;
	
	temp = P2_4;
	P2_4 = P2_3;
	P2_3 = temp;
}


/*
void swapSelectRegister(int R1,int R2){
	int temp;
	temp = R2;
	R2 = R1;
	R1 = temp;
}
*/

void main(){
	//定义变量或指针变量必须在函数开始时，否则编译器会报错
	unsigned char ledNums = 0;
	
	while(1){
		if(P3_1 == 0){
			setTimeout(30);
			while(P3_1 == 0);
			setTimeout(30);
			ledNums++;
			P2 = ~ledNums;
			swapRegister();
		}
	}
}