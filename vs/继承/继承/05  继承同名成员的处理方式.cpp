/*2023-8-6*/

//继承同名成员的处理方式

//访问子类同名成员  直接访问

//访问父类同名成员  要加作用域 


#include <iostream>

using namespace std;

class Base{
public:
	Base(){
		m_A = 100;
	}
	void func(){
		cout << "Base下的void func()调用！" << endl;
	}

	//重载
	void func(int a){
		cout << "Base下的void func(int a)调用！" << endl;
	}

	int m_A;
	
};

//子类 继承于  公共类
class Son : public Base{
public:
	Son(){
		m_A = 200;
	}
	void func(){
		cout << "Son下的void func()调用！" << endl;
	}
	int m_A;
};

//同名成员属性
void text1(){
	Son s;

	cout << "Son下的m_A:" << s.m_A << endl;
	cout << "Base下的m_A:" << s.Base::m_A << endl;
}

//同名成员函数
void text2(){
	Son s;

	s.func();
	s.Base::func();

	//s.func(100);  错误  一旦子类出现与父类同名的函数，那么子类会将继承的所有同名函数全部隐藏，无法访问
	s.Base::func(100);
}

int main(){
	
	//text1();
	text2();

	system("pause");
	return 0;
}