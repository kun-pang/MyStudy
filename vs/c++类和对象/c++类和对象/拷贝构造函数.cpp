/*2023—8—1  2023-8-2*/
/* 类和对象 */

//拷贝构造函数调用时机

//1、使用一个已经创建完毕的对象来初始化一个新的对象
		
//2、值传递的方式给函数参数传值

//3、值的方式返回局部对象

#include <iostream>

using namespace std;

//类、结构体
//人类
class Person1{
public:
	Person1(){
		cout << "默认构造函数！" << endl;
	}

	Person1(int age){
		p_Age = age;
		cout << "有参构造函数！" << endl;
	}

	Person1(const Person1 &p){
		p_Age = p.p_Age;
		cout << "拷贝构造函数！" << endl;
	}

	~Person1(){
		cout << "析构函数！" << endl;
	}
	int p_Age;
};

//声明函数
void text1();
void text2();
void text3();

void doWork01(Person1 p);
Person1 doWork02();

int main14(){
	/*text1();*/
	/*text2();*/
	text3();

	system("pause");
	return 0;
}


//函数的定义
//1、使用一个已经创建完毕的对象来初始化一个新的对象
void text1(){
	Person1 p1(10);
	Person1 p2(p1);

	cout << "p2的年龄：" << p2.p_Age << endl;
}

//2、值传递的方式给函数参数传值
//相当于隐式转换法  Person1 p =p3(这个p3是编译器复制的);
void doWork01(Person1 p){
	cout << "p的年龄：" << p.p_Age << endl;
}
void text2(){
	Person1 p3(10);
	doWork01(p3);

}

//3、值的方式返回局部对象
Person1 doWork02(){
	Person1 p;
	cout  << "doWork02中的p：" <<  &p << endl;
	return p;		//doWork02()运行完以后就释放p，所以返回的p实际上是系统重新创建的
}

void text3(){
	Person1 p4 = doWork02();
	cout  << "p4：" << &p4 << endl;
	cout  << "doWork02()返回值：" << &doWork02() << endl;
}