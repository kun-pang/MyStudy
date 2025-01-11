/*2023—7—24*/
/*函数的分文件编写 */



//""表示调用自定义文件
//<>表示官方的标准库文件
#include "day_8.h"

void swap_1(int a, int b){
	cout << "交换前：" << endl;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	int t = a;
	a = b;
	b = t;
	cout << "交换后：" << endl;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

}

//传入的是值
void swap01(int a, int b){
	int t = a;
	a = b;
	b = t;
	cout << "swap01 a = " << a << endl;
	cout << "swap01 b = " << b << endl;
}

//传入的是地址数据
void swap02(int *p1, int *p2){
	int t = *p1;
	*p1 = *p2;
	*p2 = t;
	cout << "swap02 *p1 = " << *p1 << endl;
	cout << "swap02 *p2 = " << *p2 << endl;
}