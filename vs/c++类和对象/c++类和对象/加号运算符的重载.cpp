//2023-8-4

//运算符重载：对已有的运算符重新进行定义，赋予其另一种功能，以适用不同的数据类型

//加号运算符的重载

#include <iostream>

using namespace std;

//人类
class Person{
public:
	//1、成员函数重载+  (关键字operator)
	Person operator+(Person &p){
		Person t;
		t.m_A = this->m_A + p.m_A;
		t.m_B = this->m_B + p.m_B;
		return t;
	}
	Person operator+(int p) const {	//不加& 是因为传入的是常量
		Person t;
		t.m_A = this->m_A + p;
		t.m_B = this->m_B + p;
		return t;
	}
public:
	int m_A;
	int m_B;
};

//2、全局函数重载+
//Person operator+(Person &p1, Person &p2){
//	Person t;
//	t.m_A = p1.m_A + p2.m_A;
//	t.m_B = p1.m_B + p2.m_B;
//	return t;
//}
//
//Person operator+(Person &p1, int p2){
//	Person t;
//	t.m_A = p1.m_A + p2;
//	t.m_B = p1.m_B + p2;
//	return t;
//}

void text(){
	Person p1;
	p1.m_A = 10;
	p1.m_B = 20;

	Person p2;
	p2.m_A = 10;
	p2.m_B = 20;
	
	//成员函数重载的本质为 Person p3 = p1.operator+(p2);
	//全局函数重载的本质为 Person p3 = operator+(p1,p2);

	Person p3 = p1 + p2;		//没有Person + Person

	cout  << p3.m_A << endl << p3.m_B << endl;

	//运算符重载 也可以发生函数重载
	Person p4 = p1 + 10;		//没有Person + int 

	cout  << p4.m_A << endl << p4.m_B << endl;
}


int main(){
	text();

	system("pause");
	return 0;
}

//注意：对于内置的数据类型的表达式的运算符是不可以更改的  只能改自定义的数据类型
//不要滥用运算符重载（与本意不同，如用加表示减）