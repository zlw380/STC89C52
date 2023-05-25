#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Delay.h"

//unsigned char second,minute,hour;

void main(){
	
	LCD_Init();
	DS1302_Init();
	LCD_ShowString(1,1,"  -  -    week:");
	LCD_ShowString(2,1,"  :  :  ");
	//DS1302_WriteByte(0x8E,0x00);	//解除写保护
	/*
	这里给DS1302秒寄存器传的参数是以BCD码的形式传送的，同样地，DS1302回传到单片机的秒数也是以BCD码的形式。
	进位也是按BCD码的规则进的，而转十进制时是按二进制转十进制的规则来转的。
	比如，给1302传送的秒数初值0x03中的0和3是分开采用BCD码，即0000和0011
	而秒数随时钟从0x09增加到0x10时（依然是BCD码）
	如果按二进制规则，BCD码也会从0000 1001增加到0000 1010
	而在BCD码中1010是不合法的，因为1010转换为十进制是10，而10并不能作为个位数
	所以这里会直接进位，进位后的BCD码为0001 0000，当作二进制数转换为十进制就是16
	这就是为什么屏幕显示会从009直接跳到016的原因
	
	同理，屏显也会从025跳到032
	25对应的BCD码为0001 1001，进位后即为0010 0000，当作二进制数的话对应的十进制数恰好是32
	
	所以，要想让屏显正常显示秒数，就要把BCD码转十进制，而不是像之前那样把BCD码按二进制数转换为十进制数
	*/
	//DS1302_WriteByte(0x80,0x50);	//这里的0x03实际上是BCD码形式传输
	
	DS1302_SetTime();

	while(1){
		//LCD_ShowString(1,1,"TEST");
		/*
		second = DS1302_ReadByte(0x81);
		minute = DS1302_ReadByte(0x83);
		hour = DS1302_ReadByte(0x85);
		*/
		/*
		在本程序中：
		BCD码转十进制公式
		（有歧义，实际上就是将回传的BCD码以十进制形式代入公式计算出结果并使用显示十进制整型的函数打印在屏幕上）：
		DEC=BCD/16*10+BCD%16; （2位BCD）
		同时该公式也只能用于转换两位的BCD码，因为两位BCD码相当于两位16进制数，
		转换为十进制整数后除以16能够保证得到的值是一个个位数，再乘以10即为二位BCD码/16进制数的高位
		所以该公式适用的BCD码最大值为0x99，对应的十进制数是153，
		转为BCD码就是九次逢16进1，高位为9，再加上余下的9为低位，即为（0x）99
		
		所以如果是三位BCD码那么公式就要变为对应的十进制整数除以16的平方为最高位了
		比如0x100，对应的十进制为256,256/(16*16) = 1，1即为最高位……
		
		十进制转BCD码（同理）：
		BCD=DEC/10*16+DEC%10; （2位BCD）
		其实这里直接显示十六进制数就可以匹配BCD码了
		*/
		//LCD_ShowNum(2,7,second / 16 * 10 + second % 16,2);
		//LCD_ShowNum，该函数为让LCD显示变量的十进制整型值
		//因此这里要显示的second变量实际上已经是以十进制形式参与运算了，然后通过公式将其转为看似为2位BCD码的十进制数
		//比如回传的BCD码为0x85，其对应的十进制数是133，将133代入公式133/16*10 + 133%16 = 85，于是便会显示85
		//LCD_ShowHexNum(2,1,second,3);
		//setTimeout(50);
		//LCD_ShowNum(2,4,minute / 16 * 10 + minute % 16,2);
		//LCD_ShowNum(2,1,hour / 16 * 10 + hour % 16,2);
		
		DS1302_GetTime();
		LCD_ShowNum(1,1,DS1302_Time[0],2);
		//LCD_ShowChar(1,3,'-');
		LCD_ShowNum(1,4,DS1302_Time[1],2);
		//LCD_ShowChar(1,6,'-');
		LCD_ShowNum(1,7,DS1302_Time[2],2);
		//LCD_ShowString(1,11,"week:");
		LCD_ShowNum(1,16,DS1302_Time[6],1);
		
		LCD_ShowNum(2,1,DS1302_Time[3],2);
		//LCD_ShowChar(2,3,':');
		LCD_ShowNum(2,4,DS1302_Time[4],2);
		//LCD_ShowChar(2,6,':');
		LCD_ShowNum(2,7,DS1302_Time[5],2);
	}
}