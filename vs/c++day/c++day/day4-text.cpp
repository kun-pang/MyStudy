/*2023—7—15*/
/*水仙花数   一个三位数，其每一位的三次方相加之和等于本身   1^3+5^3+3^3=153 */


#include <iostream>
#include <cmath>		//幂次函数的头文件

using namespace std;

int main4t(){
	int num = 100;		//存取数字的变量
	int snum = 0;       //数字的位数3次幂之和
	int num_ge = 0;		//获取数字个位
	int num_shi = 0;	//获取数字十位
	int num_bai = 0;	//获取数字百位

	num_ge = num % 10;	//取模，得个位
	num_shi = (num / 10) % 10;	//除10取模 得十位
	num_bai = num /100;	//除100 得百位

	snum = static_cast<int>(pow(static_cast<double>(num_ge), 3) + pow(static_cast<double>(num_shi), 3) + pow(static_cast<double>(num_bai), 3));
	/*注：pow（）函数只能接受double型 需要强行转变类型 static_cast<数据类型>（变量）*/

	do{
		num_ge = num % 10;	
		num_shi = (num / 10) % 10;	
		num_bai = num /100;	

		snum = static_cast<int>(pow(static_cast<double>(num_ge), 3) + 
			pow(static_cast<double>(num_shi), 3) + pow(static_cast<double>(num_bai), 3));
		if(num == snum){			//打印水仙花数
			cout << num << endl;
		}
		num_ge = 0;	
		num_shi = 0;	
		num_bai = 0;	
		num ++;
	}while(num < 1000);


	system("pause");

	return 0;
}