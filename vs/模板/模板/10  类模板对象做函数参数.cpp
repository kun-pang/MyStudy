/*2023-8-23*/

//类模板实例化出的对象，向函数传参的方式

//向函数传参的方式
//1、指定传入的类型 --直接显示对象的数据类型
//2、参数模板化		--将类中的参数变成模板进行传递
//3、整个类模板化	--将整个对象类型 模板化进行传递


#include <iostream>
#include <string>

using namespace std;


//类模板
template<typename T1, class T2 >
class Person{
public:

	Person(T1 name, T2 age){
		this->m_Name = name;
		this->m_Age = age;
	}

	void showPerson(){
		cout << "name:" << this->m_Name << " age:" << this->m_Age << endl;
	}

	T1 m_Name;
	T2 m_Age;
};

//1、指定传入的类型 --直接显示对象的数据类型（常用）
//void printPerson(Person<string, int > &p){
//	p.showPerson();
//}

//2、参数模板化		--将类中的参数变成模板进行传递
//template<typename T1, class T2 >
//void printPerson(Person<T1, T2 > &p){
//	p.showPerson();
//
//	//查看数据类型
//	cout << "T1的数据类型：" << typeid(T1).name() << endl;
//	cout << "T2的数据类型：" << typeid(T2).name() << endl;
//}

//3、整个类模板化	--将整个对象类型 模板化进行传递
template<typename T>
void printPerson(T &p){
	p.showPerson();
	cout << "T的数据类型：" << typeid(T).name() << endl;
}

void test01(){
	Person<string, int > p("沙悟净", 123);

	
	printPerson(p);

}


int main(){

	test01();

	system("pause");
	return 0;
}