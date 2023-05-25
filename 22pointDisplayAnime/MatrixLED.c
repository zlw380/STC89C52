#include <REGX52.H>
#include "Delay.h"

#define MATRIX_LED_PORT P0

//unsigned char pointDisplay[] = {0xFF,0xAA};

//重新声明特殊位P3_5
sbit RCK = P3^5;	//RCLK	上升沿锁存
//P3口地址为0xB0，0xB0与0x05进行异或运算得0xB5
//因此该语句其实就相当于 sbit RCLK = 0xB5;
//最后的操作数仍为物理地址
sbit SCK = P3^6;	//SRCLK 上升沿移位
sbit SER = P3^4;	//SER	

/**
  * @brief	点阵屏初始化
  * @param	无
  * @retval	无
  */
void matrixLED_Init(){
	SCK = 0;
	RCK = 0;
}

/**
  * @brief	74HC595写入一个字节
  * @param	要写入的字节
  * @retval	无
  */
void _74HC595_WriteByte(unsigned char byte){
	/*
	SER = byte & 0x80;	//非0进1，当右侧值不为0时，就将这一位赋1
	//将传入的八位数据和1000 0000相与
	//当最高位为1时得到1000 0000，为0时得到0000 0000
	//这样就可以获得最高位的数据
	SCK = 1;
	SCK = 0;	//移位后清零，以便下次移位
	
	SER = byte & 0x40;	//获取第二高位
	SCK = 1;
	SCK = 0;
	SER = byte & 0x20;
	SCK = 1;
	SCK = 0;
	SER = byte & 0x10;
	SCK = 1;
	SCK = 0;
	SER = byte & 0x08;
	SCK = 1;
	SCK = 0;
	SER = byte & 0x04;
	SCK = 1;
	SCK = 0;
	SER = byte & 0x02;
	SCK = 1;
	SCK = 0;
	SER = byte & 0x01;	//获取最低位
	SCK = 1;
	SCK = 0;
	*/
	//使用循环语句编写，将0x80依次向右移位即可
	unsigned char i;
	for(i = 0;i < 8;i++){
		SER = byte & (0x80 >> i);
		SCK = 1;
		SCK = 0;
	}
	RCK = 1;	//锁存到输出缓存
	RCK = 0;
}

/**
  * @brief	LED点阵屏显示一列数据
  * @param	column 要选择的列，范围：0-7，0在最左边； 
  * @param	point 选择列显示的数据（哪几个点），高位在上，1为亮，0为灭；
  * @retval 无
  */
void matrixLED_ShowColumn(unsigned char column,unsigned char point){
	/*这里不需再进行枚举，也不再让column从1开始
	if(column == 1){
		P0 = 0x7F;
	}else if(column == 2){
		P0 = 0xBF;
	}else if(column == 3){
		P0 = 0xDF;
	}else if(column == 4){
		P0 = 0xEF;
	}else if(column == 5){
		P0 = 0xF7;
	}else if(column == 6){
		P0 = 0xFB;
	}else if(column == 7){
		P0 = 0xFD;
	}else if(column == 8){
		P0 = 0xFE;
	}
	*/
	_74HC595_WriteByte(point);	//相当于数码管段选，所以后面需要消影操作。
	//设要显示第一列时，column = 0。显示后面几列时，就按序移位再取反即可。相当于数码管位选
	MATRIX_LED_PORT = ~(0x80 >> column);
	
	//_74HC595_WriteByte(point);	//相当于数码管段选，所以后面需要消影操作。
	setTimeout(1);
	//_74HC595_WriteByte(0x00);	//段清零
	MATRIX_LED_PORT = 0xFF;		//位清零
}
