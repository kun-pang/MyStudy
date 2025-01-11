/*2023-8-23*/

//类模板	创建一个通用类 类中成员 数据类型可以不确定
/*	template<typename T>
	类
	*/

#include <iostream>
#include <string>

using namespace std;

template<typename T, class B>
class Person{
public:

	Person(T name, B age):m_Name(name), m_Age(age){
		
	}

	//姓名
	T m_Name;
	//年龄
	B m_Age;
};






void test01(){
	Person<string, int > p1("孙悟空", 999);

	cout << p1.m_Name << " " << p1.m_Age << endl;
}


int main(){

	test01();

	system("pause");
	return 0;
}