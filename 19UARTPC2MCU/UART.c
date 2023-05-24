#include <REGX52.H>

/**
  * @brief	串口初始化，4800bps@11.0592MHz
  * @param	无
  * @retval	无
  */
void UART_Init(){	//初始化串口
	
	SCON = 0x40;	//配置串行口控制寄存器
	PCON |= 0x80;	//使能波特率倍速位SMOD
	
	//设置定时器1模式为8位自动重装模式
	/*
	就是十六位记的数多，但每次都需要自己写的代码赋初值，浪费时间。
	双八位就是将十六位分开，一个计数，另一个存放初值，
	每次计数完成后AR会自动将值赋给CNT，不用代码处理，比较快，
	但只有八位所以记的数少了。
	*/
	TMOD &= 0x0F;		
	TMOD |= 0x20;	//设置定时器1模式		
	
	TL1 = 0xF4;		//设定定时初值
	TH1 = 0xF4;		//设定定时器重装值
	
	//TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
	ET1 = 0;		//禁止定时器1中断，只作为波特率发生器
	//允许总中断
	//EA = 1;
	//配置定时器1中断优先级
	//只设置了IP寄存器，配置T1中断为低优先级
	//PT1 = 0;
}

/**
  * @brief	串口发送一个字节数据
  * @param	Byte 要发送的一个字节数据
  * @retval	无
  */
void UART_SendByte(unsigned char byte){
	//给串口缓存写入数据
	SBUF = byte;
	//向串口缓存写入数据后，单片机会自动通过串口向外发送数据
	//当串行发送数据第8位结束时，TI自动置1
	while(TI == 0);
	//手动将TI置0
	TI = 0;
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