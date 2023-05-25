#ifndef __MATRIXLED_H__
#define __MATRIXLED_H__

void matrixLED_Init();
void _74HC595_WriteByte(unsigned char byte);
void matrixLED_ShowColumn(unsigned char column,unsigned char point);

#endif