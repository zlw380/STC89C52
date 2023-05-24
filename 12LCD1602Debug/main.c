#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"

void main(){
	
//	char str[] = "keqing";
//	char *star = str;
	
	/*
	LCD_Init();
	LCD_ShowChar(1,1,'A');
	LCD_ShowString(2,1,star);
	LCD_ShowNum(1,3,777,3);
	LCD_ShowSignedNum(1,7,-66,2);
	LCD_ShowHexNum(1,11,0xA8,2);
	LCD_ShowBinNum(2,8,0xAA,8);
	*/
	
	int result = 1+1;
	LCD_Init();
	LCD_ShowNum(1,1,result,3);
	
	while(1){
		result++;
		setTimeout(1000);
		LCD_ShowNum(1,1,result,3);
	}
}