/*2023—7—24*/
/*函数的分文件编写 */

/*函数的分文件编写 
1、创建一个.h的头文件
2、创建一个.cpp的源文件
3、在头文件中声明函数
4、在源文件中定义函数	
*/

#include <iostream>

using namespace std;

void swap_1(int a, int b);
void swap01(int a, int b);
void swap02(int *p1, int *p2);


//头文件一般不放mian函数，防止代码
//int main(){
//	int a = 10;
//	int b = 20;
//	swap_1(a, b);
//
//
//	system("pause");
//
//	return 0;
//}