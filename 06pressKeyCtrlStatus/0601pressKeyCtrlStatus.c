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
	//���㰴�º�ᷢ���źŶ�������Ҫ�������
	while(1){
		//���°�ť
		if(P3_1 == 0){
			setTimeout(30);//����
			//����ʱһֱѭ��
			while(P3_1 == 0){
			}
			setTimeout(30);
			//�粻�������������ִ��if����ٴ�ȡ����
			//�ɿ���P20�ڼĴ���ȡ��
			P2_0 = !P2_0;
			P2_1 = !P2_1;
			P2_2 = !P2_2;
		}
	}
	
}