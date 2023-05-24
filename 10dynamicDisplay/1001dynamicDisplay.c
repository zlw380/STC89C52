#include <REGX52.H>
#include <stdio.h>
#include <INTRINS.H>

unsigned char displayNumber[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
	
void staticDisplay(unsigned char location,unsigned char num);
void setTimeout(unsigned int delayTime);

void main(){
	
	while(1){
		//需要加延时函数
		//因为数码管显示是先位选，选择哪一个数码管点亮
		//后段选，选择该数码管中的哪几段点亮
		//当下一次位选时，之前段选的信号（给P0口赋的值）还没有更新
		//因此会在下一个点亮的数码管中留下之前段选数据（数字）的残影，
		//上一次调用staticDisplay函数时给P0口赋的值没清零，还是之前的，这样上一个数码管显示的数字就串到本次点亮的数码管上了

		//这样就需要消影操作
		//先设置时延使每个数码管的数字稳定显示一毫秒
		//此时，每个数码管显示前一数码管的段选信号（数字）只有一瞬，给P0重新赋完值就没了
		//但会再稳定显示本该它显示的数字一毫秒
		//这样就大大降低了残影的亮度，但是仍可以观察到些许的残影

		//所以在此基础上再将每一次段选后的显示清零
		//即可在下一次位选后的数码管上不留残影，因为选择该数码管点亮之后P0就已经是空的了
		staticDisplay(1,3);
		//setTimeout(1);
		staticDisplay(2,2);
		//setTimeout(1);
		staticDisplay(3,0);
		//setTimeout(1);
		staticDisplay(4,1);
		//setTimeout(1);
		staticDisplay(5,2);
		//setTimeout(1);
		staticDisplay(6,2);
		//setTimeout(1);
		staticDisplay(7,0);
		//setTimeout(1);
		staticDisplay(8,2);
		//setTimeout(1);
	};
}

void staticDisplay(unsigned char location,unsigned char num){
	//位选，通过138译码器选择点亮哪一个数码管
	if(location == 1){
		P2_4 = 0;
		P2_3 = 0;
		P2_2 = 0;
	}else if(location == 2){
		P2_4 = 0;
		P2_3 = 0;
		P2_2 = 1;
	}else if(location == 3){
		P2_4 = 0;
		P2_3 = 1;
		P2_2 = 0;
	}else if(location == 4){
		P2_4 = 0;
		P2_3 = 1;
		P2_2 = 1;
	}else if(location == 5){
		P2_4 = 1;
		P2_3 = 0;
		P2_2 = 0;
	}else if(location == 6){
		P2_4 = 1;
		P2_3 = 0;
		P2_2 = 1;
	}else if(location == 7){
		P2_4 = 1;
		P2_3 = 1;
		P2_2 = 0;
	}else if(location == 8){
		P2_4 = 1;
		P2_3 = 1;
		P2_2 = 1;
	}else{
		printf("Error!\n");
	}
	//段选，根据传入的数字选择点亮数码管中的哪几段
	P0 = displayNumber[num];
	//延时，使数码管中数字稳定点亮一毫秒
	setTimeout(1);
	//熄灭数码管中数字
	P0 = 0x00;
}

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
