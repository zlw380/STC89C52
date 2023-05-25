#include <REGX52.H>

sbit DS1302_SCLK = P3^6;
sbit DS1302_IO = P3^4;
sbit DS1302_CE = P3^5;

//宏定义，增强可读性
#define DS1302_SECOND 0x80
#define DS1302_MINUTE 0x82
#define DS1302_HOUR 0x84
#define DS1302_DATE 0x86
#define DS1302_MONTH 0x88
#define DS1302_DAY 0x8A
#define DS1302_YEAR 0x8C
#define DS1302_WP 0x8E

//用此数组来作为DS1302时钟的缓存
//当向DS1302写入时间时，将该数组的数据传入
//当从DS1302读取时间时，将读取到的时间存入该数组
unsigned char DS1302_Time[] = {23,05,19,23,59,55,5};

/**
  * @brief	初始化DS1302
  * @param	无
  * @retval	无
  */
void DS1302_Init(){
	
	DS1302_CE = 0;		//使能置0
	DS1302_SCLK = 0;	//时钟置0
}

/**
  * @brief	向DS1302写入时间信息（年/月/日……）
  * @param	command：命令字，clockMsg：时间信息，传入函数后转为BCD码按位与
  * @retval	无
  */
void DS1302_WriteByte(unsigned char command,unsigned char clockMsg){
	
	int i,j;
	DS1302_CE = 1;
	
	for(i = 0;i < 8;i++){
		DS1302_IO = command & (0x01 << i);
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}
	
	for(j = 0;j < 8;j++){
		DS1302_IO = clockMsg & (0x01 << j);
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}
	DS1302_CE = 0;
}

/**
  * @brief	从DS1302读取时间信息（年/月/日……）
  * @param	command：命令字
  * @retval	根据命令字获取到的时间信息（年/月/日/时/分/秒/周几）
  */
unsigned char DS1302_ReadByte(unsigned char command){
	//定义一个字符变量用来接收从DS1302获取的一组8位时钟数据
	unsigned char clockMsg = 0x00;
	unsigned char msgBit;
	int i,j;
	//将传入的命令字最低位置1，其他位不变
	//这样做是为了在使用命令字的宏定义的时候
	//将向DS1302写入数据的命令变更为从DS1302读取数据
	//因为宏定义是将写入数据的命令字定义成常量的
	//而这里是读取的函数，遂将最低位置1，变更成读取的命令字实现宏定义的复用
	command |= 0x01;
	DS1302_CE = 1;
	
	for(i = 0;i < 8;i++){
		DS1302_IO = command & (0x01 << i);
		DS1302_SCLK = 1;
		if(i < 7){
			DS1302_SCLK = 0;
		}
	}
	
	for(j = 0;j < 8;j++){
		DS1302_SCLK = 0;
		if(j < 7){
			DS1302_SCLK = 1;	
		}
		//先触发一个下降沿，DS1302才会将一位数据发送到IO线上
		if(DS1302_IO == 0){
			msgBit = 0x00;
		}else{
			msgBit = 0x01;
		}
		clockMsg |= (msgBit << j);
		/*
		教程的代码是这样把传过来的数据赋给变量的，这种写法确实更简洁
		if(DS1302_IO){clockMsg |= (0x01 << j);}
		*/
		/*
		把时钟的下降与上升沿控制放在后面是错误的X
		DS1302_SCLK = 0;
		if(j < 7){
			DS1302_SCLK = 1;
		}
		*/
	}
	DS1302_CE = 0;
	DS1302_IO = 0;
	return clockMsg;
}
	
/**
  * @brief	//给DS1302设置全部时间信息，包括年月日时分秒周几。
  * @param	//无，直接通过数组类型全局变量写入
  * @retval	//无
  */
void DS1302_SetTime(){
	//DS1302_WriteByte(DS1302_WP,0x00);	//关闭写保护
	//同样地，向DS1302传入时间信息时，
	//时间参数实际上是以十进制的形式发送过去的。
	//这里的公式将BCD码转成了十进制，如年份23,23/10*16 + 23%10 = 35
	//因为如果直接将23传进去，WriteByte函数内就会认为这是十进制的23，而不是十六进制的0x23或是BCD码23。
	//就会将十进制23转成BCD码并进行按位与操作，这样数据就失真了。
	DS1302_WriteByte(DS1302_YEAR,DS1302_Time[0]/10*16 + DS1302_Time[0]%10);
	DS1302_WriteByte(DS1302_MONTH,DS1302_Time[1]/10*16 + DS1302_Time[1]%10);
	DS1302_WriteByte(DS1302_DATE,DS1302_Time[2]/10*16 + DS1302_Time[2]%10);
	DS1302_WriteByte(DS1302_HOUR,DS1302_Time[3]/10*16 + DS1302_Time[3]%10);
	DS1302_WriteByte(DS1302_MINUTE,DS1302_Time[4]/10*16 + DS1302_Time[4]%10);
	DS1302_WriteByte(DS1302_SECOND,DS1302_Time[5]/10*16 + DS1302_Time[5]%10);
	DS1302_WriteByte(DS1302_DAY,DS1302_Time[6]/10*16 + DS1302_Time[6]%10);
	//DS1302_WriteByte(DS1302_WP,0x80);	//打开写保护
}

/**
  * @brief	//从DS1302获取全部的时间信息，包括年月日时分秒周几。
  * @param	//无
  * @retval	//无返回值，获取到的时间信息直接赋给全局类型数组元素。
  */
void DS1302_GetTime(){
	unsigned char tempClockMsg;
	tempClockMsg = DS1302_ReadByte(DS1302_YEAR);
	DS1302_Time[0] = tempClockMsg/16*10 + tempClockMsg%16;
	tempClockMsg = DS1302_ReadByte(DS1302_MONTH);
	DS1302_Time[1] = tempClockMsg/16*10 + tempClockMsg%16;
	tempClockMsg = DS1302_ReadByte(DS1302_DATE);
	DS1302_Time[2] = tempClockMsg/16*10 + tempClockMsg%16;
	tempClockMsg = DS1302_ReadByte(DS1302_HOUR);
	DS1302_Time[3] = tempClockMsg/16*10 + tempClockMsg%16;
	tempClockMsg = DS1302_ReadByte(DS1302_MINUTE);
	DS1302_Time[4] = tempClockMsg/16*10 + tempClockMsg%16;
	tempClockMsg = DS1302_ReadByte(DS1302_SECOND);
	DS1302_Time[5] = tempClockMsg/16*10 + tempClockMsg%16;
	tempClockMsg = DS1302_ReadByte(DS1302_DAY);
	DS1302_Time[6] = tempClockMsg/16*10 + tempClockMsg%16;
}
