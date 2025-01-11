/*2023—8—3*/

//类对象作为类成员

//一个类的成员可以是另一个类的对象，那么该成员为 对象成员（类对象作为类成员）


#include <iostream>
#include <string>

using namespace std;

//手机类
class Phone{
public:
	//初始列表创建初始构造函数
	Phone(string name): m_PName(name){
		cout << "Phone 的构造函数！" << endl;
	}

	~Phone(){
		cout << "Phone 的析构函数！" << endl;
	}


	string m_PName;
};

//人类
class Person{
public:
	//m_phone(phone)  =>  Phoen m_phone = phone;  隐式转换法  
	Person(string name, string phone): m_Name(name), m_phone(phone){
		cout << "Person 的构造函数！" << endl;
	}

	~Person(){
		cout << "Person 的析构函数！" << endl;
	}

	string m_Name;		//姓名
		
	Phone m_phone;		//手机
};

//当其他类作为包含类（本类）的成员，构造函数是先调用其他类，在调用包含类；
//析构函数与之相反先调用包含类，在调用其他类

//必须在包含类的前面
//class Phone{
//public:
//	//初始列表创建初始构造函数
//	Phone(string name): m_PName(name){
//		cout << "Phone 的构造函数！" << endl;
//	}
//
//	~Phone(){
//		cout << "Phone 的析构函数！" << endl;
//	}
//
//
//	string m_PName;
//};



void text(){
	Person p("李四","小米");

	cout << p.m_Name << "拿着：" << p.m_phone.m_PName << endl; 
}

int main(){
	text();

	system("pause");
	return 0;
}