//2023-8-4

//左移运算符重载

//输出自定义属性

#include <iostream>

using namespace std;

class Person{
	//friend void operator<<(ostream &cout, Person &p);
	friend ostream& operator<<(ostream &cout, Person &p);
public:

	//成员函数重载<<
	//不利于成员函数重载<< 原因是会变成 operator<<(cout)  简化为 p << cout
	void operator<<(ostream &cout){
		cout << this->m_A << " " << this->m_B;
	}
public:
	Person(){
		m_A = 10;
		m_B = 20;
	}
private:
	int m_A;
	int m_B;
};

//全局函数重载<<
//只能单个输出，不能连着输出（链式）
//void operator<<(ostream &cout, Person &p){
//	cout << p.m_A << " " << p.m_B;
//
//}

//第一个引用是因为不能调用ostream拷贝构造函数
//第二个引用是因为输出流对象cout 全局只有一份 只能用别称 所以这里的cout可以换成别的
ostream & operator<<(ostream &cout, Person &p){
	cout << p.m_A << " " << p.m_B;
	return cout;

}

//ostream & operator<<(ostream &out, Person &p){
//	out << p.m_A << " " << p.m_B;
//	return cout;
//
//}

void text(){
	Person p;

	//cout << p.m_B;		p.m_B 整型 内置数据类型
	cout << p ;				//p 自定义的数据类型
	cout << p << "nihao" << endl;		//cout << p 返回的是cout	
	cout << endl;
	p << cout;

	
}

int main(){
	text();

	system("pause");
	return 0;
}

