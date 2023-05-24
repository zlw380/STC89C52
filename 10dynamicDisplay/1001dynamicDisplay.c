#include <REGX52.H>
#include <stdio.h>
#include <INTRINS.H>

unsigned char displayNumber[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
	
void staticDisplay(unsigned char location,unsigned char num);
void setTimeout(unsigned int delayTime);

void main(){
	
	while(1){
		//��Ҫ����ʱ����
		//��Ϊ�������ʾ����λѡ��ѡ����һ������ܵ���
		//���ѡ��ѡ���������е��ļ��ε���
		//����һ��λѡʱ��֮ǰ��ѡ���źţ���P0�ڸ���ֵ����û�и���
		//��˻�����һ�������������������֮ǰ��ѡ���ݣ����֣��Ĳ�Ӱ��
		//��һ�ε���staticDisplay����ʱ��P0�ڸ���ֵû���㣬����֮ǰ�ģ�������һ���������ʾ�����־ʹ������ε��������������

		//��������Ҫ��Ӱ����
		//������ʱ��ʹÿ������ܵ������ȶ���ʾһ����
		//��ʱ��ÿ���������ʾǰһ����ܵĶ�ѡ�źţ����֣�ֻ��һ˲����P0���¸���ֵ��û��
		//�������ȶ���ʾ��������ʾ������һ����
		//�����ʹ�󽵵��˲�Ӱ�����ȣ������Կ��Թ۲쵽Щ��Ĳ�Ӱ

		//�����ڴ˻������ٽ�ÿһ�ζ�ѡ�����ʾ����
		//��������һ��λѡ���������ϲ�����Ӱ����Ϊѡ�������ܵ���֮��P0���Ѿ��ǿյ���
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
	//λѡ��ͨ��138������ѡ�������һ�������
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
	//��ѡ�����ݴ��������ѡ�����������е��ļ���
	P0 = displayNumber[num];
	//��ʱ��ʹ������������ȶ�����һ����
	setTimeout(1);
	//Ϩ�������������
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
