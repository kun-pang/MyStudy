//2023-8-3

//c++对象模型

//类的成员变量和成员函数分开存储

//只有非静态成员变量才属于类的对象上



//this指针

//this指针指向被调用的成员函数所属的对象

//作用是 系统方便自己区别同一类型的不同对象（类的实例化出不同的对象）调用同一块代码（非静态成员函数只会诞生一份实例，也就是说同一类型的不同对象调用同一块代码）

//this指针是隐含每一个非静态成员函数内的一种指针

//this指针不需要定义，直接使用

//用途：
//		当形参和成员变量同名，可以this区分
//		在类的非静态成员函数中返回对象本身，可以使用return * this


#include <iostream>

using namespace std;

class Person1{
public:
	int m_Age;		//非静态成员变量  属于类的对象上  出现这个以后，编译器会根据非静态成员变量大小开辟空间

	static int a;	//静态成员变量  不属于类的对象上

	void func(){}	//非静态成员函数  不属于类的对象上

	static void func1(){}	//静态成员函数  不属于类的对象上
};


class Person2{
public:

	Person2(int age){
		//这样写出现乱码，原因是 编译器会把有参构造函数里面的age当成同一个形参age，所有Person2里面的属性age没有赋到值
		//age = age;

		//1、解决名称冲突
		//this指针指向被调用的成员函数所属的对象
		this->age = age;
	}

	//不能连续相加
	void add(Person2 &p){
		this->age += p.age;
	}

	//2、返回对象本身 用*this
	//加引用，保证返回值时，this始终指向p2,*this也就是p2
	//与拷贝构造函数相似
	Person2& add1(Person2 &p){
		this->age += p.age;
		return *this;
	}

	//不加引用，在返回值时，编译器会将数据复制一份，让this指向复制的地方，在进行解指针返回
	Person2 add2(Person2 &p){
		this->age += p.age;
		return *this;
	}

	int age;

};

void text1(){
	Person1 p;
	//空对象占用空间为 ：1
	//c++给空对象分配1的内存空间，是为了区分空对象占用的内存空间
	//每一个空对象都有一个自己的内存空间

	cout << "sizeof(p) = " << sizeof(p) << endl;
}

void text2(){
	Person1 p;
	cout << "sizeof(p) = " << sizeof(p) << endl;
}

void text3(){
	Person2 p(10);

	cout << "p的年龄：" << p.age << endl; 
}

void text4(){
	Person2 p1(10);
	Person2 p2(20);
	Person2 p3(20);

	/*p2.add(p1);*/
	//连续相加  链式编程思想（如：cout）
	//p2.add1(p1)返回的是p2
	p2.add1(p1).add1(p1).add1(p1);
	//p3.add2(p1)返回的是拷贝值（系统生成的）
	p3.add2(p1).add2(p1).add2(p1);

	cout << "p2的年龄：" << p2.age << endl;
	cout << "p3的年龄：" << p3.age << endl;

}

int main(){
	/*text1();*/
	/*text2();*/
	/*text3();*/
	text4();

	system("pause");
	return 0;
}