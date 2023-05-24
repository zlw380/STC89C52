#include <REGX52.H>

/**
  * @brief  定时器0初始化，1毫秒@11.0592MHZ
  * @param  无
  * @retval 无
  */
void Timer0_Init(){

	ET0 = 1;
	//允许总中断
	EA = 1;
	//配置定时器0中断优先级
	//只设置了IP寄存器，配置T0中断为低优先级
	PT0 = 0;
	
	//AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
}

/*
//该函数响应定时器0的中断，当触发T0中断时，执行该中断子程序
void Timer0_Routine() interrupt 1{
	
	static unsigned int t0Count = 0;
	
	//每次T0中断后计数器值置0，因此T0计数器需重新赋值
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	
	t0Count++;
	//驱动LCD屏实时显示数字会导致比较大的延迟
	//LCD_Init();
	//LCD_ShowNum(1,1,t0Count,5);
	if(t0Count >= 1000){
		t0Count = 0;
	}
}
*/