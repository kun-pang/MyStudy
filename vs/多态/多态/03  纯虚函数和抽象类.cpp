/*2023-8-8*/

//纯虚函数和抽象类

//在多态中，通常父类虚函数的实现是毫无实际意义的，主要的都是调用子类的重写内容

//因此可以将此虚函数改为纯虚函数

//纯虚函数的语法：	virtual 返回值类型 函数名（参数列表）= 0；

//当类有了纯虚函数，这个类也叫做抽象类

//抽象类特点：
//	1、无法实例化对象
//	2、子类必须重写抽象类中的纯虚函数，否则也属于抽象类


#include <iostream>
#include <string>

using namespace std;

//公共类 抽象类
class Base{
public:
	//纯虚函数
	//抽象类特点：
	//	1、无法实例化对象
	//	2、子类必须重写抽象类中的纯虚函数，否则也属于抽象类
	virtual void func() = 0;
};

//子类 公有继承 公共类
class Son : public Base{
public:
	virtual void func(){
		cout << "q" << endl;
	}
};

void text(){
	//1、无法实例化对象
	//Base s;
	//new Base;

	//2、子类必须重写抽象类中的纯虚函数，否则也属于抽象类
	//Son s;

	Base *s = new Son;
	s->func();
}

int main(){
	text();

	system("pause");
	return 0;
}