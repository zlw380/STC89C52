#include <REGX52.H>
#include "UART.h"
#include "Delay.h"
#include "LCD1602.h"
#include "matrixKey.h"

unsigned char key = 0;

void main(){
	UART_Init();
	LCD_Init();
	LCD_ShowString(1,1,"RECE:");
	LCD_ShowString(2,1,"SEND:");
	
	while(1){
		//UART_SendByte(0x77);
		key = matrixKey();	//扫描键值
		if(key != 0){		//键值不为0时向上位机发送此键值
			UART_SendByte(key);
			key = 0;		//键值清零
		}
	}
}

void UARTInterrupt() interrupt 4{
	if(TI == 1){
		LCD_ShowNum(2,6,key,2);		//键值发送完成后在LCD上显示发送的键值
		//P2 = 0xF0;
	}else if(RI == 1){
		//P2 = ~SBUF;
		LCD_ShowHexNum(1,6,SBUF,2);	//在LCD上显示接收的16进制数
		UART_SendByte(SBUF);		//将接收的16进制数再发送给上位机
		//SBUF = SBUF;
		//while(TI == 0);
		//TI = 0;
		RI = 0;
	}
}

/*
在进入串口中断服务函数后，貌似无法再进行串口中断的嵌套。
表现为：
单片机接收到上位机发来的数据触发串口中断，进入到处理RI == 1时的分支语句中。
而后单片机在将接收到的数据再次发送给上位机时，数据发送完毕后貌似无法重入中断服务函数
并进入到处理TI == 1的分支中。
*/
