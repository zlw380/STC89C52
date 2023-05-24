#include <REGX52.H>
#include "Delay.h"
#include "UART.h"

unsigned char sec = 0;

void main(){
	//初始化串口配置
	UART_Init();
	//向串口发送数据
	//UART_SendByte(0x66);
	UART_SendByte(0x11);
	
	while(1){
		//UART_SendByte(0x99);
		UART_SendByte(sec);
		sec++;
		setTimeout(1000);
	}
}

/*
void UartInit(void)		//4800bps@11.0592MHz
{
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
	AUXR &= 0xBF;		//定时器1时钟为Fosc/12,即12T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xF4;		//设定定时初值
	TH1 = 0xF4;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}
*/	

/*
* AUXR.0：为1时串口波特率发生器为定时器2，否则默认定时器1
* AUXR.1：为1可使用内部扩展RAM
* AUXR.2：（定时器2速度控制位）为1则CPU时钟不分频（1T），否则12分频
* AUXR.3：（定时器0控制位）为1用作定时器，为0用作计数器
* AUXR.4：为1定时器2开始计数，为0停止
* AUXR.5：为1则串口1模式0通讯速度为2分频，否则12分频
* AUXR.6：为1则定时器1不分频，否则12分频
* AUXR.7：为1则定时器0不分频，否则12分频
*/
