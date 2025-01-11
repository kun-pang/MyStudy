/*2023—8—2*/


//构造函数的调用规则

/*
	默认情况下，c++编译器至少会给一个类添加3个函数
		1、默认构造函数（无参，函数体为空）
		2、默认析构函数（无参，函数体为空）
		3、默认拷贝函数，对属性进行值拷贝
*/

/*
	规则如下：
		1、如果用户自己定义了有参构造函数，那么编译器不会提供无参构造函数，但是会提供默认拷贝构造函数
		2、如果用户自己定义了拷贝构造函数，那么编译器将不会提供其他构造函数
*/


#include <iostream>

using namespace std;

//人类
class Person{
public:

	/*Person(){
		cout << "调用默认构造函数！" << endl;
	}*/

	/*Person(int a){
		age = a;
		cout << "调用有参构造函数！" << endl;
	}*/

	Person(const Person &p){
		age = p.age;
		cout << "调用拷贝构造函数！" << endl;
	}

	~Person(){
		cout << "调用析构构造函数！" << endl;
	}

	int age;
};

//测试函数
//1、如果用户自己定义了有参构造函数，那么编译器不会提供无参构造函数，但是会提供默认拷贝构造函数
//void text10(){
//	/*Person p; 错误  编译器不会提供无参构造函数 */
//	Person p1(18);
//	Person p2(p1);
//
//	cout << "p2年龄:" << p2.age << endl;
//}

//2、如果用户自己定义了拷贝构造函数，那么编译器将不会提供其他构造函数
void text20(){
	/*Person p1(28);
	Person p3;  错误  编译器将不会提供其他构造函数  */
	/*Person p2(p1);*/
}

int main2382(){
	/*text10();*/

	system("pause");
	return 0;
}