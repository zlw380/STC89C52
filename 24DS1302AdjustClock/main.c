#include <REGX52.H>
#include "DS1302.h"
#include "LCD1602.h"
#include "Key.h"
#include "Timer0.h"

//定义独立按键键值，模式，时间设置选择变量，时间设置闪烁标志位
unsigned char keyNumber,MODE,timeSetSelect,timeSetFlashFlag;

//时间显示模式，不断从DS1302读取时间信息并显示
void timeShow(){
	DS1302_GetTime();
	LCD_ShowNum(1,1,DS1302_Time[0],2);
	LCD_ShowNum(1,4,DS1302_Time[1],2);
	LCD_ShowNum(1,7,DS1302_Time[2],2);
	//LCD_ShowNum(1,16,DS1302_Time[6],1);
	LCD_ShowNum(2,1,DS1302_Time[3],2);
	LCD_ShowNum(2,4,DS1302_Time[4],2);
	LCD_ShowNum(2,7,DS1302_Time[5],2);
}

//时间设置模式
void timeSet(){
	if(keyNumber == 2){
		timeSetSelect++;
		//时间设置选择位取余，该位等于0-5时值不变，等于6时清零
		timeSetSelect %= 6;
	}
	if(keyNumber == 3){
		DS1302_Time[timeSetSelect]++;
		//参数合法性检查
		if(DS1302_Time[0] > 99){DS1302_Time[0] = 0;}
		if(DS1302_Time[1] > 12){DS1302_Time[1] = 1;}
		//检查月份，若为1 3 5 7 8 10 12月，大于31归1，若为4 6 9 11月，大于30归1 ，若为2月，分润平年，分别大于29与28归1
		if(DS1302_Time[1] == 1 || DS1302_Time[1] == 3 || DS1302_Time[1] == 5 ||
		DS1302_Time[1] == 7 || DS1302_Time[1] == 8 ||
		DS1302_Time[1] == 10 || DS1302_Time[1] == 12){
			if(DS1302_Time[2] > 31){DS1302_Time[2] = 1;}
		}else if(DS1302_Time[1] == 4 || DS1302_Time[1] == 6 ||
		DS1302_Time[1] == 9 || DS1302_Time[1] == 11){
			if(DS1302_Time[2] > 30){DS1302_Time[2] = 1;}
		}else if(DS1302_Time[1] == 2){
			//如果是闰年则日大于29时归1，若不是闰年则日大于28归1
			if(DS1302_Time[0]%4 == 0 || DS1302_Time[0] == 0){
				if(DS1302_Time[2] > 29){DS1302_Time[2] = 1;}
			}else if(DS1302_Time[0]%4 && DS1302_Time[0] != 0){
				if(DS1302_Time[2] > 28){DS1302_Time[2] = 1;}
			}
		}
		
		if(DS1302_Time[3] > 23){DS1302_Time[3] = 0;}
		if(DS1302_Time[4] > 59){DS1302_Time[4] = 0;}
		if(DS1302_Time[5] > 59){DS1302_Time[5] = 0;}
		
	}
	if(keyNumber == 4){
		DS1302_Time[timeSetSelect]--;
		//参数合法性检查
		//unsigned char无符号字符型最大值为255，因此减到255时直接置日期最大值
		if(DS1302_Time[0] == 255){DS1302_Time[0] = 99;}
		if(DS1302_Time[1] < 1){DS1302_Time[1] = 12;}
		
		if(DS1302_Time[1] == 1 || DS1302_Time[1] == 3 || DS1302_Time[1] == 5 ||
		DS1302_Time[1] == 7 || DS1302_Time[1] == 8 ||
		DS1302_Time[1] == 10 || DS1302_Time[1] == 12){
			if(DS1302_Time[2] < 1){DS1302_Time[2] = 31;}
		}else if(DS1302_Time[1] == 4 || DS1302_Time[1] == 6 ||
		DS1302_Time[1] == 9 || DS1302_Time[1] == 11){
			//选择小月下日期时，日期等于31时自动置30
			if(DS1302_Time[2] < 1 || DS1302_Time[2] == 31){DS1302_Time[2] = 30;}
		}else if(DS1302_Time[1] == 2){		
			if(DS1302_Time[0]%4 == 0 || DS1302_Time[0] == 0){
				//2月下闰年时，日期小于1或大于29，都会被置为29
				if(DS1302_Time[2] < 1 || DS1302_Time[2] > 29){DS1302_Time[2] = 29;}
			}else if(DS1302_Time[0]%4 && DS1302_Time[0] != 0){
				//2月下平年时，日期小于1或大于28，都会被置为28
				if(DS1302_Time[2] < 1 || DS1302_Time[2] > 28){DS1302_Time[2] = 28;}
			}
		}
		
		if(DS1302_Time[3] == 255){DS1302_Time[3] = 23;}
		if(DS1302_Time[4] == 255){DS1302_Time[4] = 59;}
		if(DS1302_Time[5] == 255){DS1302_Time[5] = 59;}
	}
	
	//修改时间后更新显示
	//注意这里不要把前面的时间读取函数复制过来，不然你按下按键1时间还是会变化
	//因为此时并没有把修改后的时间写入DS1302，而只是再从DS1302读取了一次原有的
	
	//闪烁显示：当时间设置选择对位且闪烁标志位置1时，用空字符串覆盖数显达到隐藏的效果。
	//否则正常显示
	if(timeSetSelect == 0 && timeSetFlashFlag == 1){
		LCD_ShowString(1,1,"  ");
	}else{
		LCD_ShowNum(1,1,DS1302_Time[0],2);
	}
	if(timeSetSelect == 1 && timeSetFlashFlag == 1){
		LCD_ShowString(1,4,"  ");
	}else{
		LCD_ShowNum(1,4,DS1302_Time[1],2);
	}
	if(timeSetSelect == 2 && timeSetFlashFlag == 1){
		LCD_ShowString(1,7,"  ");
	}else{
		LCD_ShowNum(1,7,DS1302_Time[2],2);
	}
	if(timeSetSelect == 3 && timeSetFlashFlag == 1){
		LCD_ShowString(2,1,"  ");
	}else{
		LCD_ShowNum(2,1,DS1302_Time[3],2);
	}
	if(timeSetSelect == 4 && timeSetFlashFlag == 1){
		LCD_ShowString(2,4,"  ");
	}else{
		LCD_ShowNum(2,4,DS1302_Time[4],2);
	}
	if(timeSetSelect == 5 && timeSetFlashFlag == 1){
		LCD_ShowString(2,7,"  ");
	}else{
		LCD_ShowNum(2,7,DS1302_Time[5],2);
	}
	
	//LCD_ShowNum(1,16,DS1302_Time[6],1);
	//LCD_ShowNum(1,15,timeSetFlashFlag,2);
}

void main(){
	
	LCD_Init();
	DS1302_Init();
	Timer0_Init();
	DS1302_SetTime();
	LCD_ShowString(1,1,"  -  -");
	LCD_ShowString(2,1,"  :  :");
	
	while(1){
		keyNumber = pressKey();
		//当检测到独立按键输入键值为1时，修改MODE的值。
		if(keyNumber == 1){
			//因为mode这里是char变量，有多个位，取反就不是0和1互相切换了，是0和FF。
			if(MODE == 0){
				MODE = 1;
				timeSetSelect = 0;
			} else if(MODE == 1){
				//出现SetTime无法更新时间的原因是在该函数中开了写保护
				//因为如果开了写入保护，控制写入保护的0x8E寄存器也被保护了，
				//你也无法靠写入0x8E来关闭保护，所以你一旦开了写入保护，你就无法关闭了 ---SCUPI
				DS1302_SetTime();
				MODE = 0;
			}
		}
		//根据MODE的值，分别进入显示模式与设置模式。
		if(MODE == 0){
			timeShow();
		} else{
			timeSet();
		}
		//LCD_ShowNum(2,15,timeSetSelect,2);
	}
}

void Timer0_Routine() interrupt 1{
	
	static unsigned int t0Count = 0;
	
	//每次T0中断后计数器值置0，因此T0计数器需重新赋值
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	
	t0Count++;

	if(t0Count >= 700){
		if(MODE == 1){
			//!是逻辑取反，~是按位取反，如0x00按位取反后为0xFF
			timeSetFlashFlag = !timeSetFlashFlag;
		}
		t0Count = 0;
	}
}