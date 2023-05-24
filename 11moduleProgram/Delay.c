#include <INTRINS.H>

void setTimeout(unsigned int delayTime)		//@11.0592MHz
{
	unsigned char i, j;

	while(delayTime--){
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
	
}