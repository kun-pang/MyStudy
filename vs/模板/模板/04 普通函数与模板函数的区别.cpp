/*2023-8-22*/

//普通函数和模板函数的区别
//普通函数调用可以发生自动类型转换（隐式类型转换）
//模板函数调用，如果是 自动类型推导 ，则不会发生隐式类型转换
//如果利用 显示指定类型 的方式，则可以发生隐式转换


#include <iostream>

using namespace std;

//普通相加函数
int myAdd01(int a, int b){
	return a + b;
}

//函数相加模板
template<typename T>
T myAdd02(T a, T b){
	return a + b;
}



void test01(){
	int a = 66;
	int b = 20;
	char c = 'c';

	//普通函数发生隐式转换
	cout << myAdd01(a, c) << endl;

	//模板函数自动类型推导 不会发生隐式类型转换
	//cout << myAdd02(a, c) << endl;

	//模板函数显示指定类型 会发生隐式类型转换
	cout << myAdd02<int>(a, c) << endl;
}

int main(){

	test01();

	system("pause");
	return 0;
}