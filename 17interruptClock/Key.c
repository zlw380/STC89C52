#include <REGX52.H>
#include "Delay.h"

/**
  * @brief  获取独立按键键码
  * @param  无
  * @retval 按下按键的键码，范围0~4，无按键按下时，返回值为0
  */
unsigned char pressKey(){
	unsigned char keyNumber = 0;
	if(P3_1 == 0){
		setTimeout(30);
		while(P3_1 == 0);
		setTimeout(30);
		keyNumber = 1;
	}
	if(P3_0 == 0){setTimeout(30);while(P3_0 == 0);setTimeout(30);keyNumber = 2;}
	if(P3_2 == 0){setTimeout(30);while(P3_2 == 0);setTimeout(30);keyNumber = 3;}
	if(P3_3 == 0){setTimeout(30);while(P3_3 == 0);setTimeout(30);keyNumber = 4;}
	return keyNumber;
}
