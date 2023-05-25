#ifndef __DS1302_H__
#define __DS1302_H__

//头文件中声明数组以供外部调用，数组和函数可不加extern关键字，变量则必须加上
extern unsigned char DS1302_Time[];

void DS1302_Init();
void DS1302_WriteByte(unsigned char command,unsigned char clockMsg);
unsigned char DS1302_ReadByte(unsigned char command);
void DS1302_SetTime();
void DS1302_GetTime();

#endif