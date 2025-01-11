/*2023-8-20*/

//函数模板注意事项：
//		1、自动类型推导，必须推导出一致的数据类型T，才可以使用
//		2、模板必须要确定出T的数据类型，才可以使用


#include <iostream>

using namespace std;


template<typename T>
//交换函数
void mySwap(T &a, T &b){		
	T t = a;
	a = b;
	b = t;
}

template<typename T, typename B>
//交换函数2
void mySwap1(T &a, B &b){		
	B t = a;
	a = b;
	b = t;
}

template<typename T>
//打印函数
void func(){
	cout << "abc" << endl;
}


void test01(){
	int a = 1;
	int b = 2;
	double c = 3.1;

	//1、自动类型推导，必须推导出一致的数据类型T，才可以使用
	//mySwap(a,b);	//正确
	//mySwap(a, c);	//错误 数据类型不确定以及不匹配
	mySwap1(a,c);

	//2、模板必须要确定出T的数据类型，才可以使用
	//func();			//错误  无法推断数据类型
	func<int>();
}

int main(){

	test01();

	system("pause");
	return 0;
}