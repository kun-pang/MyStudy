/*2023-8-6*/

//多继承语法（“吕布语法”）

//语法： class 子类 ： 继承方式 父类1， 继承方式 父类2...{}；

//多继承会引发父类中有同名成员出现，需要加作用域区分

#include <iostream>

using namespace std;
//公共类1
class Base1{
public:
	Base1(){
		m_A = 100;
	} 

	int m_A;
};

//公共类2
class Base2{
public:
	Base2(){
		m_A = 200;
	} 

	int m_A;
};

//子类 
class Son : public Base1, public Base2{
public:
	int m_C;
};

void text(){
	Son s;
	cout << "Son的空间大小"  << sizeof(Son) << endl;

	//不加作用域  会出现二义性
	cout << "Base1下的m_A:"	<< s.Base1::m_A << endl;
	cout << "Base2下的m_A:"	<< s.Base2::m_A << endl;

}

int main(){
	
	text();

	system("pause");
	return 0;
}