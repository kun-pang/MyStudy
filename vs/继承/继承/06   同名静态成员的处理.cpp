/*2023-8-6*/

//同名静态成员（类内声明类外初始化）的处理方式


//访问子类同名成员  直接访问

//访问父类同名成员  要加作用域 


#include <iostream>

using namespace std;

class Base{
public:
	
	static void func(){
		cout << "Base下的void func()调用！" << endl;
	}

	//重载
	static void func(int a){
		cout << "Base下的void func(int a)调用！" << endl;
	}

	static int m_A;
	
};
int Base::m_A = 100;

//子类 继承于  公共类
class Son : public Base{
public:
	
	static void func(){
		cout << "Son下的void func()调用！" << endl;
	}
	static int m_A;
};
int Son::m_A = 200;

//同名成员属性
void text1(){
	//1、通过对象
	cout << "通过对象:" << endl;
	Son s;

	cout << "Son下的m_A:" << s.m_A << endl;
	cout << "Base下的m_A:" << s.Base::m_A << endl;

	//2、通过类名
	cout << "通过类名:" << endl;
	cout << "Son下的m_A:" << Son::m_A << endl;
	cout << "Base下的m_A:" << Son::Base::m_A << endl;		
	//注意Base::m_A 与Son::Base::m_A的区别
	//Base::m_A 直接访问Base作用域下的m_A
	//Son::Base::m_A 通过Son访问父类作用域下的m_A
}

//同名成员函数
void text2(){
	//1、通过对象
	cout << "通过对象:" << endl;
	Son s;

	s.func();
	s.Base::func();

	//2、通过类名
	cout << "通过类名:" << endl;
	Son::func();
	Son::Base::func();
	//Base::func() 直接通过Base类名访问
	//Son::Base::func();  通过Son访问父类Base作用域下的func()

	//s.func(100);  错误  一旦子类出现与父类同名的函数，那么子类会将继承的所有同名函数全部隐藏，无法访问
	s.Base::func(100);


}

int main(){
	
	text1();
	//text2();

	system("pause");
	return 0;
}