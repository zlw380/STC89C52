#include <REGX52.H>
#include "Delay.h"
#include "UART.h"
#include "matrixKey.h"
#include "LCD1602.h"

unsigned int receiveChar = 0;

void main(){
	unsigned char key;
	unsigned char sec = 0;
	UART_Init();
	LCD_Init();
	
	while(1){
		key = matrixKey();
		if(key == 16){
			UART_SendByte(sec);
			sec++;
			key = 0;
		}
		//setTimeout(1000);
	}
}

//串口中断服务函数
void UART_Routine() interrupt 4{
	//char receiveChar = 0;
	
	if(TI == 1){
		P2 = 0x0F;
		//TI = 0; 不应在此将TI置0，否则将与UART_SendByte函数中循环语句冲突，会进入死循环。
	}else if (RI == 1){
		//P2 = 0xF0;
		receiveChar = SBUF;
		LCD_ShowHexNum(1,1,receiveChar,2);
		RI = 0;
	}
}