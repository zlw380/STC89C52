#include <REGX52.H>
#include <INTRINS.H>
#include <stdio.h>

unsigned char LEDStatus = 0x01;

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

void main(){
	//P2 = LEDStatus;
	P2 = ~LEDStatus;
	
	while(1){
		if(P3_1 == 0){
			setTimeout(30);
			while(P3_1 == 0);
			setTimeout(30);
			if(LEDStatus == 0x80){
				LEDStatus = 0x01;
			}else{
				LEDStatus = LEDStatus << 1;
			}
			
			//P2 = LEDStatus;
			P2 = ~LEDStatus;

			//printf("%x\n",LEDStatus);
			
		}
		if(P3_0 == 0){
			setTimeout(30);
			while(P3_0 == 0);
			setTimeout(30);
			if(LEDStatus == 0x01){
				LEDStatus = 0x80;
			}else{
				LEDStatus = LEDStatus >> 1;	
			}
			
			//P2 = LEDStatus;
			P2 = ~LEDStatus;
			
		}
	}
}