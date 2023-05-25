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

void main(){

	int i;
	SCK = 0;
	RCK = 0;
	
	//P0 = 0x00;
	//_74HC595_WriteByte(0x0F);
	
	while(1){
		//爱心图形
		
		matrixLED_ShowColumn(0,0x38);
		matrixLED_ShowColumn(1,0x44);
		matrixLED_ShowColumn(2,0x42);
		matrixLED_ShowColumn(3,0x21);
		matrixLED_ShowColumn(4,0x21);
		matrixLED_ShowColumn(5,0x42);
		matrixLED_ShowColumn(6,0x44);
		matrixLED_ShowColumn(7,0x38);
		
		/*
		for(i = 0;i < 8;i++){
			matrixLED_ShowColumn(0-i,0x38);
			matrixLED_ShowColumn(1-i,0x44);
			matrixLED_ShowColumn(2-i,0x42);
			matrixLED_ShowColumn(3-i,0x21);
			matrixLED_ShowColumn(4-i,0x21);
			matrixLED_ShowColumn(5-i,0x42);
			matrixLED_ShowColumn(6-i,0x44);
			matrixLED_ShowColumn(7-i,0x38);
			setTimeout(500);
		}
		*/
 	}
}

/*
个人理解可位寻址与不可位寻址：
使用sbit关键字声明可位寻址特殊寄存器中的特殊位时
如 sbit P0_1 = 0x81; 或 sbit P0_1 = P0^1; 即声明P0寄存器的第1位
编译器会自动根据该可位寻址特殊寄存器的首地址加上表示地址单元中第几位的数字进行位寻址

而在单片机系统中，操作任意寄存器或者某一位的数据时，必须给出其物理地址
即就算是声明后的地址单元，最后也需要转化为物理地址（0xXX）作为指令中的操作数
这样由于每个SFR都有八位，就没有足够的物理地址来表示每个的SFR中的每一位了
只能在每八个SFR选择一个SFR作为可位寻址的SFR。

如 地址为0x80的P0口，可以使用0x80至0x87作为其位寻址的物理地址，
表示0x80这个地址单元中的第0位到第7位
但这样一来就无法使用物理地址表示0x81到0x87这7个地址单元中的每一位了
所以下一个能够位寻址的SFR就为地址单元是0x88的TCON



可位寻址/不可位寻址：
在单片机系统中，操作任意寄存器或者某一位的数据时，必须给出其物理地址，
又因为一个寄存器里有8位，所以位的数量是寄存器数量的8倍，
单片机无法对所有位进行编码，故每8个寄存器中，只有一个是可以位寻址的。
对不可位寻址的寄存器，若要只操作其中一位而不影响其它位时，可用“&=”、“|=”、“^=”的方法进行位操作
*/