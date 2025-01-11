//2023-8-5

//c++会给一个类添加至少4个函数
//1、默认无参构造函数，无函数体
//2、默认析构函数，无函数体
//3、默认拷贝函数，对属性值拷贝
//4、赋值运算符“operator=” 对属性进行值拷贝

//赋值运算符的重载
	
#include <iostream>

using namespace std;


class Person{
public:
	Person(int age):m_Age(new int(age)){
		
	}

	//Person(const Person &p){
	//	//深拷贝
	//	if(m_Age != NULL){
	//		delete m_Age;
	//		m_Age = NULL;
	//	}
	//	m_Age = new int(*p.m_Age);
	//}
	//当你不提供自定义的赋值运算符重载函数时，
	//C++会为类自动生成默认的赋值运算符重载函数。
	//默认的赋值运算符重载函数会逐个复制类的成员变量，
	//但对于指针成员变量而言，只会进行浅拷贝，即复制指针本身而不是指针指向的内容。


	~Person(){
		//手动释放堆区内存
		if(m_Age != NULL){
			delete m_Age;
			m_Age = NULL;
		}
	}

	Person& operator=(Person &p){
		//深拷贝
		//判断传入的数据堆区是否为空
		if(m_Age != NULL){
			delete m_Age;
			m_Age = NULL;
		}

		m_Age = new int(*p.m_Age);		//*this
		
		//链式思想
		return *this;

	}

	int *m_Age;

};

void text(){
	Person p1(18);
	Person p2(20);
	Person p3(20);

	//正常用的是浅拷贝，释放内存时会同时释放同一内存两次，从而报错
	p2 = p1;

	p3 = p2 = p1;

	cout << "p1的年龄：" << *p1.m_Age << endl;
	cout << "p2的年龄：" << *p2.m_Age << endl;
	cout << "p3的年龄：" << *p3.m_Age << endl;
}

int main(){
	text();
	
	system("pause");
	return 0;
}


