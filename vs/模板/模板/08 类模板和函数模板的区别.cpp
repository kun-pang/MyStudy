/*2023-8-23*/

//类模板和函数模板的区别
//1、类模板的调用没有自动类型推导的方式
//2、类模板在模板参数列表中可以有默认参数 

#include <iostream>
#include <string>

using namespace std;

//模板参数列表  <typename T, class B>
template<typename T, class B = int >
class Person{
public:

	Person(T name, B age):m_Name(name), m_Age(age){
		
	}

	void showPerson(){
		cout << "name: " << this->m_Name << "  age:" << this->m_Age << endl;
	}

	//姓名
	T m_Name;
	//年龄
	B m_Age;
};





void test01(){
	//Person p1("孙悟空", 999);	//错误 在c++17版本之前无法用自动类型推导	
	
	Person<string , int> p1("孙悟空", 999);	//显示指定类型推导

	Person<string> p2("Tom", 20);		
	//在模板参数列表 <typename T, class B = int >  默认了B为int 
	//Person<string>如果不写 默认为int

	p1.showPerson();
	p2.showPerson();
}


int main(){

	test01();

	system("pause");
	return 0;
}