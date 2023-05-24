#include <REGX52.H>
#include <INTRINS.H>

void delayTime(unsigned int sec);

void main(){
	P2 = 0xFE;
	delayTime(200);
	P2 = 0xFD;
	delayTime(200);
	P2 = 0xFB;
	delayTime(200);
	P2 = 0xF7;
	delayTime(200);
	P2 = 0xEF;
	delayTime(200);
	P2 = 0xDF;
	delayTime(200);
	P2 = 0xBF;
	delayTime(200);
	P2 = 0x7F;
	delayTime(200);
}

void delayTime(unsigned int sec)		//@11.0592MHz
{
	unsigned char i, j;

	//Ñ­»·sec¸ö1ºÁÃë
	while(sec){
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
		sec--;
	}
	
}
