//2023-8-3

//静态成员

//定义：在类的成员变量和成员函数前面加上关键字static

//分类：
//		静态成员变量：
//			a.1、所有对象共享同一份数据（静态成员变量）		一变全变
//			a.2、在编译阶段分配内存			全局区
//			a.3、类内声明，类外初始化
//		静态成员函数：
//			b.1、所有对象共享同一个函数（静态成员函数）
//			b.2、静态成员函数只能访问静态成员变量



#include <iostream>

using namespace std;

class Person{
public:

	//b.1、所有对象共享同一个函数（静态成员函数）
	//b.2、静态成员函数只能访问静态成员变量
	static void fun1(){
		m_A = 200;		//静态成员函数可以访问静态成员变量
		/*a = 1; 错误 */	//静态成员函数不可以访问非静态成员变量
		
		//静态static成员函数它只属于类本身不属于每一个对象实例，独立存在。
		//非静态成员，仅当实例化对象之后才存在。
		//静态成员函数产生在前，非静态成员函数产生在后，静态函数无法访问一个不存在的东西。

		cout << "m_A = " << m_A << endl;
		cout << "fun1的调用" << endl;
	}

	int a;

	//a.1、所有对象共享同一份数据（静态成员变量）		一变全变
	//a.2、在编译阶段分配内存			全局区
	//a.3、类内声明，类外初始化
	static int m_A;
	static int m_B;

	//静态成员变量和静态成员函数也有访问权限
private:
	static void fun2(){
		cout << "fun2的调用" << endl;
	}

	static int m_C;

	
};

//类外初始化
int Person::m_A = 1;
int Person::m_B;
int Person::m_C = 2;

void text1(){
	//所有对象共享同一份数据（静态成员变量）
	Person p1;

	cout << p1.m_A << endl;

	Person p2;
	p2.m_A = 100;

	cout << p1.m_A << endl;
}

void text2(){
	//静态成员变量两种访问方式

	//1、通过对象
	Person p1;
	
	cout << p1.m_B << endl;
	//2、通过类名

	cout << Person::m_B << endl;
	/*cout << Person::m_C << endl; 错误 */	//类外无法访问私有的静态成员变量
}

void text3(){
	//静态成员函数两种访问方式
	//1、通过对象
	Person p;
	p.fun1();

	//2、通过类名
	Person::fun1();
	//Person::fun2(); 错误	类外无法访问私有的静态成员函数
}

int main(){
	/*text1();*/
	/*text2();*/
	text3();

	system("pause");
	return 0;
}