//2023-8-3

//const修饰成员函数

/*常函数：
	成员函数后加上const  --常函数
	常函数不可以修改成员属性
	成员属性声明加上 关键字mutable后，常函数中依然可以修改
*/	

/*常对象：
	声明对象前加上const --常对象
	常对象只能调用常函数(可以修改动态变量的值)
*/

#include <iostream>

using namespace std;

class Person{
public:

	//this本质是 指针常量 指针指向是不可以修改的
	//Person * const this
	//函数后加上const后变成   const Person * const this  
	//const修饰的是this指针  让指向的值也不能修改了
	void show1()const{
		//m_a  ->   this->m_a
		//m_a =100;		常函数不可以修改成员属性
		m_b = 100;		//常函数可以修改加上mutable的成员属性
	}

	void show2(){
		
	}

	int m_a;
	mutable int m_b;
};

void text1(){
	Person p;
	

	//常对象
	const Person p1;

	//p1.show2();   常对象不能调用普通成员函数
	p1.show1();
	//p1.m_a = 100;
	p1.m_b ==
	
}

int main(){
	text1();

	system("pause");
	return 0;
}