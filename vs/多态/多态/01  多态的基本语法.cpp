/*2023-8-7*/

//多态（多种形态）

//静态多态  函数重载 和 运算符重载 属于静态多态，复用函数名
//			函数地址早绑定 - 编译阶段确定函数地址

//动态多态  派生类 和 虚函数 实现运行时多态
//			函数地址晚绑定 - 运行阶段确定函数地址

//动态多态的满足条件：
//	1、必须要有继承关系
//	2、子类要重写父类的虚函数

//动态多态的使用：
//	父类的指针 或者 引用 执行子类对象



#include <iostream>

using namespace std;

//动物类
class Animal{
public:
	//虚函数 关键词virtual 子类同名同参函数前面可写可不写关键字virtual
	virtual void speak(){
		cout << "动物在说话!" << endl;
	}
};

//猫类 公有继承  动物类
class Cat : public Animal{
public:
	virtual void speak(){	//虚函数的重写   注意：重载是同一作用域 同名不同参   重写是可以不同作用域 同名同参同返回
		cout << "小猫在说话!" << endl;
	}
};

//狗类 公有继承  动物类
class Dog : public Animal{
public:
	void speak(){
		cout << "小狗在说话!" << endl;
	}
};

//说话函数
//不加 virtual（不使用虚函数） 函数地址早绑定  在编译阶段就已经确定好为Animal对象
//加上virtual（使用虚函数）	函数的地址晚绑定 在运行阶段才会确定具体的地址
//父类的指针 或者 引用 执行子类对象
void doSpeak(Animal &animal){	//Animal &animal = cat(向上转型  自动)   c++中允许父子之间进行类型转换
	animal.speak();
}

//void doSpeak1(Cat &cat){	
//	cat.speak();
//}


void text(){
	Cat cat;
	doSpeak(cat);

	Dog dog;
	doSpeak(dog);

	/*Animal animal;
	doSpeak1(animal);  向下转型（手动）*/
}

void text1(){
	//不加virtual 占用空间为1
	//加virtual 占用空间为4   win32的操作平台上 指针占用4个字节
	cout << sizeof(Animal) << endl;
}

int main(){
	/*text();*/
	text1();

	system("pause");
	return 0;
}

/*1. 向上转型（Upcasting）：
- 向上转型是将派生类的指针或引用转换为基类的指针或引用。
- 派生类继承了基类的成员和方法，所以可以将派生类对象视为基类对象使用。
- 向上转型是隐式的，无需使用任何特殊的运算符或关键字。
- 通过向上转型，可以实现多态性（Polymorphism），使得同一个基类指针或引用可以指向不同的派生类对象，从而实现动态绑定。
2. 向下转型（Downcasting）：
- 向下转型是将基类的指针或引用转换为派生类的指针或引用。
- 向下转型是显式的，在需要时使用 `dynamic_cast` 运算符来进行转换。
- 向下转型是有风险的，需要确保基类指针或引用实际指向的对象是派生类对象，否则会导致未定义的行为。
*/