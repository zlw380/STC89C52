#include <REGX52.H>
#include "Key.h"
#include "Timer0.h"
#include "LCD1602.h"
#include "Delay.h"
#include "matrixKey.h"

unsigned char sec;
unsigned char min;
unsigned char hour;
unsigned char matrixKeyNum;

void main(){

	unsigned char modifyTime = 0;
	unsigned char tempHour = 0;
	unsigned char tempMin = 0;
	unsigned char tempSec = 0;

	Timer0_Init();
	LCD_Init();
	LCD_ShowString(1,1,"clock:");
	
	while(1){
		LCD_ShowNum(2,1,hour,2);
		LCD_ShowString(2,3,":");
		LCD_ShowNum(2,4,min,2);
		LCD_ShowString(2,6,":");
		LCD_ShowNum(2,7,sec,2);
		matrixKeyNum = matrixKey();
		if(matrixKeyNum == 15 || matrixKeyNum == 16){
			if(matrixKeyNum == 15){
				TR0 = 0;
				/*
				matrixKeyNum = 0; 
				modifyTime++;
				if(modifyTime >= 4)
					modifyTime = 1;
				if(modifyTime == 1){
					//tempHour = hour;
					while(matrixKeyNum == 0 || matrixKeyNum > 2){
						matrixKeyNum = matrixKey();
					}
					if(0 < matrixKeyNum <= 10){
						tempHour = matrixKeyNum;
						matrixKeyNum = 0;
						while(matrixKeyNum == 0 || matrixKeyNum > 3){
							matrixKeyNum = matrixKey();
						}
						hour = tempHour * 10 + matrixKeyNum; 
					}
				}else if(modifyTime == 2){
					min = 0;
				}else if(modifyTime == 3){
					sec = 0;
				}
				*/
			}
			if(matrixKeyNum == 16){
				//modifyTime = 0;
				TR0 = 1;
			}
		}
	}
}

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
		sec++;
		if(sec >= 60){
			sec = 0;
			min++;
		}
		if(min >= 60){
			min = 0;
			hour++;
		}
		if(hour >= 24){
			hour = 0;
			sec = 0;
			min = 0;
		}
	}
}