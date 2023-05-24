#include <REGX52.H>
#include <stdio.h>
#include <INTRINS.H>

void staticDisplay(unsigned char location,unsigned char num);
void setTimeout(int delayTime);

void main(){
	//由高位到低位
//	P2_4 = 1;
//	P2_3 = 0;
//	P2_2 = 0;
	/*
	P0_0 = 1;
	P0_1 = 0;
	P0_2 = 1;
	P0_3 = 1;
	P0_4 = 1;
	P0_5 = 1;
	P0_6 = 1;
	P0_7 = 0;
	*/
	//P0 = 0x7D;
	
	while(1){
		staticDisplay(1,1);
		setTimeout(500);
		staticDisplay(2,2);
		setTimeout(500);
		staticDisplay(3,3);
		setTimeout(500);
		staticDisplay(4,4);
		setTimeout(500);
		staticDisplay(5,5);
		setTimeout(500);
		staticDisplay(6,6);
		setTimeout(500);
		staticDisplay(7,7);
		setTimeout(500);
		staticDisplay(8,8);
		setTimeout(500);
	};
}

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
		printf("输入的数据非法!\n");
	}
	
	if(num == 0){
		P0 = 0x3F;
	}else if(num == 1){
		P0 = 0x06;
	}else if(num == 2){
		P0 = 0x5B;
	}else if(num == 3){
		P0 = 0x4F;
	}else if(num == 4){
		P0 = 0x66;
	}else if(num == 5){
		P0 = 0x6D;
	}else if(num == 6){
		P0 = 0x7D;
	}else if(num == 7){
		P0 = 0x07;
	}else if(num == 8){
		P0 = 0x7F;
	}else if(num == 9){
		P0 = 0x6F;
	}else{
		printf("输入的数据非法!\n");
	}
}

void setTimeout(int delayTime)		//@11.0592MHz
{
	unsigned char i, j;

	while(delayTime--){
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
	
}
