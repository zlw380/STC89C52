#include <REGX52.H>

void main(){
	
//	P2 = 0xFE;

	while(1){
		if(P3_1 == 0){
			P2_0 = 0;
		}else{
			P2_0 = 1;
		}
		if(P3_0 == 0){
			P2_1 = 0;
		}else{
			P2_1 = 1;
		}
		if(P3_2 == 0){
			P2_2 = 0;
		}else{
			P2_2 = 1;
		}
		if(P3_3 == 0){
			P2_3 = 0;
		}else{
			P2_3 = 1;
		}
	}
}