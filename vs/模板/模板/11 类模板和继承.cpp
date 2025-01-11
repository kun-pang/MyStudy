/*2023-8-24*/

//类模板和继承
//当子类继承的父类是一个类模板时，子类在声明的时候，要指定出父类的数据类型
//如果不指定，编译器无法给子类分配内存
//如果想要灵活指定出父类中的T类型，子类也要变成类模板


#include <iostream>
#include <string>

using namespace std;


//类模板
template<typename T>
class Base{
public:
	Base(){
		cout << "父类的T的数据类型：" << typeid(T).name() << endl;
	}

	T m;
};

//子类
//class Son : public Base{};		//错误，没有指定类型，编译器无法给子类分配内存（开辟空间（字节））
class Son : public Base<int>{};

//如果想要灵活指定出父类中的T类型，子类也要变成类模板
template<typename T, typename T0>
class Son2 : public Base<T>{
public:
	Son2(){
		cout << "子类中T的数据类型：" << typeid(T).name() << endl;
		cout << "子类中T0的数据类型：" << typeid(T0).name() << endl;
	}
	


	T0 k;
};

void test01(){
	Son2<int, char> s;

}


int main(){

	test01();

	system("pause");
	return 0;
}