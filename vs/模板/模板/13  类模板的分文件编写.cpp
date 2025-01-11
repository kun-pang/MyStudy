/*2023-8-24*/

//问题：
//类模板中成员函数创建时机是在调用阶段，导致分文件编写时链接不到

//解决方案1：
//直接包含.cpp源文件

//解决方案2：
//将声明和实现写到同一个文件中，变更改后缀名为.hpp,hpp是约定的名称，并不是强制的


#include <iostream>
#include <string>

//当用.h时，因为类模板是调用时创建，
//所以在.h中没有创建Person(T1 name, T2 Age); void showPerson();
//编译器会找不到Person(T1 name, T2 Age);void showPerson();的定义
//#include "13 person.h"

//第一种 直接包含.cpp源文件
//直接告诉编译器定义的位置
//不推荐
//#include "13 person.cpp"

//第二种 将声明和实现写到同一个文件中，变更改后缀名为.hpp,hpp是约定的名称，并不是强制的
#include "13 person.hpp"

using namespace std;


void test01(){
	Person<string, int> p("tom", 2);
	p.showPerson();
}


int main(){

	test01();

	system("pause");
	return 0;
}