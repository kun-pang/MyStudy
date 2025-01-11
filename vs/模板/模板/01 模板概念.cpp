/*2023-8-20*/

//泛型编程（所用技术就是模板） 和 STL技术

//模板：创建通用模具，提高复用性

//模板特点：
//		不能直接使用，只是一个框架
//		模板的通用不是万能的

//模板分类：类模板 和 函数模板

//函数模板：
//		建立一个通用函数，返回值类型和形参类型可以不具体制定，可以用一个 虚拟的类型 来表示
//	  语法：
//		template<typename T>			//template -- 声明创建模板   typename -- 表示其后面的符号是一种数据类型，可以换成class关键字    T -- 通用的数据类型，可用其他字符替换，一般为大写字母 
//		函数的声明或者定义



#include <iostream>

using namespace std;

//函数模板
template<typename T>
//交换函数
void mySwap(T &a, T &b){		
	T t = a;
	a = b;
	b = t;
}

void test01(){
	int a = 10;
	int b = 20;

	//函数模板使用方式
	//1、自动类型推导
	mySwap(a,b);

	cout << "a = " << a <<  endl;
	cout << "b = " << b <<  endl;

	double c = 1.1;
	double d = 2.2;

	//2、显示指定类型
	mySwap<double>(c,d);

	cout << "c = " << c <<  endl;
	cout << "d = " << d <<  endl;
}

int main(){

	test01();

	system("pause");
	return 0;
}