#include "LCD1602.h"
#include "matrixKey.h"
#include "Delay.h"

void main(){
	
	unsigned char keyNum;
	//unsigned char password;
	unsigned int length = 0;
	//密码初始值为一个字符型数组，内容为字符串"xxxx"
	unsigned char key[4] = "xxxx";
	unsigned char *p = key;
	int i;
	
	LCD_Init();
	LCD_ShowString(1,1,"PassWord:");
	//LCD_ShowString(1,13,p);
	LCD_ShowString(2,1,p);
	
	while(1){
		//LCD_ShowString(2,13,p);
		keyNum = matrixKey();//循环扫描获取键值
		//LCD_ShowNum(1,10,keyNum,2);
		//如果按下的是数字键
		if(keyNum){
			//LCD_ShowNum(2,15,keyNum,2);
			if(keyNum <= 10){//如果S1-S10按键按下，输入密码
				//password = keyNum % 10;
				//将返回值转为字符类型
				if(keyNum == 10){keyNum = '0';}
				else if(keyNum == 1){keyNum = '1';}
				else if(keyNum == 2){keyNum = '2';}
				else if(keyNum == 3){keyNum = '3';}
				else if(keyNum == 4){keyNum = '4';}
				else if(keyNum == 5){keyNum = '5';}
				else if(keyNum == 6){keyNum = '6';}
				else if(keyNum == 7){keyNum = '7';}
				else if(keyNum == 8){keyNum = '8';}
				else if(keyNum == 9){keyNum = '9';}
				//密码长度小于4时在屏幕的第二行正常显示输入的数字
				if(length < 4){
					LCD_ShowString(1,14,"   ");
					LCD_ShowChar(2,length+1,keyNum);
					//将返回的键值赋给密码中对应的位，如密码长度为0时，键值赋给密码第一位，对应的数组下标索引也为0
					key[length] = keyNum;
					//LCD_ShowString(1,13,p);
					//密码长度加1 
					length++;
				}else{
					//LCD_ShowString(2,10,"err");
					//密码长度大于等于4时将密码重置为字符串"xxxx"
					/*for(i = 0;i < 4;i++){
						key[i] = 'x';
					}
					LCD_ShowString(2,1,p);*/
					//将密码长度重置为0
					/*length = 0;*/
					//setTimeout(1000);
					//LCD_ShowString(2,10,"000");
				}
			}else{
				//如果按下的不是数字键
				if(keyNum == 11){
					//返回值为11时代表提交密码
					LCD_ShowString(2,1,p);
					//如果输入的密码为"1111"则密码正确，屏幕显示"OK!"，同时将密码长度置0。
					if(key[0] == '1' && key[1] == '1' && key[2] == '1' && key[3] == '1'){
						LCD_ShowString(1,14,"OK!");
						for(i = 0;i < 4;i++){
							key[i] = 'x';
						}
						length = 0;
						LCD_ShowString(2,1,p);
					}else{
						//如果输入的密码不为"1111"则密码错误，屏幕显示"ERR"，同时将密码长度置0。
						LCD_ShowString(1,14,"ERR");
						for(i = 0;i < 4;i++){
							key[i] = 'x';
						}
						length = 0;
						LCD_ShowString(2,1,p);
					}
				}
				//如果返回值为12代表退格
				if(keyNum == 12){
					if(length){
						//将最近输入的一位删除并置"x"
						key[length-1] = 'x';
						LCD_ShowString(2,1,p);
						//减去一位密码长度
						length--;
					}
				}
				if(keyNum == 16){//返回值为16，清空
					LCD_ShowString(1,14,"   ");
					for(i = 0;i < 4;i++){
						key[i] = 'x';
					}
					length = 0;
					LCD_ShowString(2,1,p);
				}
			}
		}
	}
}