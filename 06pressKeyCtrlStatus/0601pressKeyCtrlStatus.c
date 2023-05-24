#include <REGX52.H>
#include <INTRINS.H>

void setTimeout(unsigned int delayTime)		//@11.0592MHz
{
	unsigned char i, j;

	while(delayTime){
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
		delayTime--;
	}
	
}


void main(){
	//触点按下后会发生信号抖动，需要软件消抖
	while(1){
		//按下按钮
		if(P3_1 == 0){
			setTimeout(30);//消抖
			//按下时一直循环
			while(P3_1 == 0){
			}
			setTimeout(30);
			//如不消抖，则会重新执行if语句再次取反。
			//松开后P20口寄存器取反
			P2_0 = !P2_0;
			P2_1 = !P2_1;
			P2_2 = !P2_2;
		}
	}
	
}