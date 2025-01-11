/*2023-8-24*/

//类模板成员函数的类外实现


#include <iostream>
#include <string>

using namespace std;


//类模板
template<typename T1, typename T2 >
class Person{
public:
	Person(T1 name, T2 Age);

	void showPerson();

	T1 m_Name;
	T2 m_Age;
};

//类外定义
//Person<T1, T2>:: 是告诉编译器这个一个类模板的成员函数
//Person:: 是告诉编译器这是一个普通类成员函数
template<typename T1, typename T2 >
Person<T1, T2>::Person(T1 name, T2 age){
	this->m_Name = name;
	this->m_Age = age;
}

template<typename T1, typename T2 >
void Person<T1, T2>::showPerson(){
	cout << "name:" << this->m_Name << " age:" << this->m_Age << endl; 
}


void test01(){
	Person<string, int> p("Tom", 20);
	p.showPerson();
}


int main(){

	test01();

	system("pause");
	return 0;
}