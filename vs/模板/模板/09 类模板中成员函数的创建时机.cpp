/*2023-8-23*/

//类模板中成员函数的创建时机
//普通类成员函数一开始就创建了
//类模板成员函数调用时才开始创建

#include <iostream>
#include <string>

using namespace std;

class Person1{
public:

	void showPerson1(){
		cout << "Person1" << endl;
	}

};

class Person2{
public:

	void showPerson2(){
		cout << "Person2" << endl;
	}

};

//类模板
template<typename T >
class MyPerson{
public:
	T obj;

	void fun1(){
		obj.showPerson1();
	}

	void fun2(){
		obj.showPerson2();
	}
};





void test01(){
	//如果没有指定成员函数 该代码不会报错
	//当指定类型的时候，才会创建成员函数，此时会因为Person1中没有showPerson2()而报错
	MyPerson<Person1>m;
	
	m.fun1();
	//m.fun2();
}


int main(){

	test01();

	system("pause");
	return 0;
}