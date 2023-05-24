
#include "LCD1602.h"
#include "matrixKey.h"

unsigned char keyNum = 0;

void main(){
	
	LCD_Init();
	LCD_ShowString(1,1,"MatrixKey!");
	LCD_ShowNum(2,1,keyNum,3);
	while(1){
		//不断地扫描矩阵键盘并给keyNum赋值
		keyNum = matrixKey();
		//只有当keyNum不为0时刷新LCD屏
		if(keyNum){
			LCD_ShowNum(2,1,keyNum,3);
		}
	}
}