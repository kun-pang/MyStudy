/*2023—7—15*/
/*敲桌子*/

/*	
	1-100
	十位、个位含有数字7 打印“敲桌子”
	7的倍数也打印“敲桌子”
	不满足上述条件则打印数字
*/
#include <iostream>

using namespace std;


//获取数字变量、个位、十位
//for循环来实现数字的增加
//内置if语句进行判断是否含7或者为7倍数
//满足条件，而输出敲桌子
//不满足则打印数字
int main4t1(){
	int num = 0;
	int num_ge = 0;
	int num_shi = 0;

	for(;num <= 100; num++){
		if(num < 10){				//其实不用个、十、百这样分   把它分成满足7的倍数、个位有7、十位有7条件的数（用||）与不满足条件的数更好
			if(num == 7){
				cout << "敲桌子" << endl;
			}else{
				cout << num << endl;
			}
		}else if(num <100){
			num_ge = num %10;
			num_shi = num / 10;
			if(num % 7 == 0){
				cout << "敲桌子" << endl;
			}else if(num_ge == 7 || num_shi == 7){
				cout << "敲桌子" << endl;
			}else{
				cout << num << endl;
			}
		}else{
			cout << num << endl;
			cout << "输出完毕" << endl;
		}

	}


	system("pause");

	return 0;
}