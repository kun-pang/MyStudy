/*2023—7—18*/
/*数组  函数*/

/*二维数组
比一维多一个维度
定义方式：
			数据类型  数组名[行数][列数]；
			数据类型  数组名[行数][列数] = {{值1，值2}，{值3，值4}....};			一个括号是一行的数据
			数据类型  数组名[行数][列数] = {值1，值2，值4....};						
			数据类型  数组名[][列数] = {值1，值2....};								行数不能省
*/

/*函数
封装重复代码 减少代码量
定义方式：
			返回值类型  函数名）（参数列表）{
				函数体语句
				return 表达式
			}

形式：
		无参（形式参数）有返（return与数据类型（void与其他数据类型））
		有参有返
		无参无返
		有参无返

声明可以有多次，定义只能有一次
*/


#include <iostream>
#include "day_8.h"

using namespace std;

//两个值的加法
int Add(int num1, int num2){		//此处num1，2为形参
	return num1 + num2;
}

//减法的声明
int Sub(int num1 ,int num2);

//交换函数的声明
void swap(int a, int b);

int main7(){
	//定义数组
	int arr0[2][3] = {{1,2,3},{4,5,6}};
	//查看占用空间
	cout << "占用空间：" << sizeof(arr0) << endl;
	cout << "第一行占用空间：" << sizeof(arr0[0]) << endl;
	cout << "单个占用空间：" << sizeof(arr0[0][0]) << endl;
	cout << "总个数：：" << sizeof(arr0) / sizeof(arr0[0][0]) << endl;
	cout << "行数：：" << sizeof(arr0) / sizeof(arr0[0]) << endl;
	cout << "列数：：" << sizeof(arr0[0]) / sizeof(arr0[0][0]) << endl;
	//查看首地址
	cout << "首地址：" << arr0 << endl;
	cout << "第一个地址：" << &arr0[0][0] << endl;
	cout << "第一行地址：" << arr0[0] << endl;					//有无& 都可以
	cout << "第二行第三个地址：" << &arr0[1][2] << endl;
	cout << endl;

	//函数			一写在mian函数之前		二写mian函数之后，必须先声明		规范：首字母大写
	int num1,num2;
	int sum;
	cout << "两个值的加法，请输入值：" << endl;
	cin >> num1 >> num2;

	//调用加法函数体
	sum =  Add(num1, num2);		//此处num1，2为实参
	cout << "sum = " << sum << endl;

	//调用减法函数体
	sum =  Sub(num1, num2);
	cout << "sum = " << sum << endl;
	cout << endl;

	//值传递
	//函数实参将值传到a，b中，然后对于a，b进行数值交换，num1、num2没有变化
	//值传递 形参变而实参不变
	swap(num1, num2);
	cout << "num1 = " << num1 << endl;
	cout << "num2 = " << num2 << endl;

	swap_1(100,200);

	system("pause");

	return 0;
}

//两个值的减法
int Sub(int num1, int num2){
	return num1 - num2;
}

//交换函数
void swap(int a, int b){
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