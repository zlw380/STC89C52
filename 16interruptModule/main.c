#include <REGX52.H>
#include "Timer0.h"
#include "Key.h"
#include <INTRINS.H>

unsigned char ledMod;

void main(){
	
	unsigned char keyNum = 0;
	P2 = 0xFE;
	
	Timer0_Init();
	
	while(1){
		//检测独立按键键值
		keyNum = pressKey();
		//如果检测到有独立按键被按下
		if(keyNum != 0){
			//如果按下K1
			if(keyNum == 1){
				//LED模式自增1
				ledMod++;
				if(ledMod >= 2){
					//如果已经是模式1，则归零
					ledMod = 0;
				}
			}
			
		}
	}
}


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
	if(t0Count >= 500){
		t0Count = 0;
		if(ledMod == 0){
			P2 = _crol_(P2,1);
		}else if(ledMod == 1){
			P2 = _cror_(P2,1);
		}
	}
}