/*2023-8-23*/

//模板局限性
//模板不是万能的，有些特定的数据类型（自定义数据类型）或者数组，需要具体化方式处理

#include <iostream>
#include <string>

using namespace std;


class Person{
public:

	Person(string name, int age):m_Name(name), m_Age(age){
		
	}

	//姓名
	string m_Name;
	//年龄
	int m_Age;
};


////1、重载运算符
//bool operator==(Person &p1, Person &p2){
//	if(p1.m_Age == p2.m_Age && p1.m_Name == p2.m_Name){
//		return true;
//	}else{
//		return false;
//	}
//}

//两个数比较函数
template<typename T>
bool myCompare(T &a, T &b){
	if(a == b){
		return true;
	}else{
		return false;
	}
}

//2、具体化模板
//对于Person类的版本进行具体化实现，优先会调用
template<> bool myCompare(Person &p1, Person &p2){
	if(p1.m_Age == p2.m_Age && p1.m_Name == p2.m_Name){
		return true;
	}else{
		return false;
	}
}



void test01(){
	//int a = 1;
	//int b = 2;

	//if(myCompare(a, b)){
	//	cout << "a == b" << endl;
	//}else{
	//	cout << "a != b" << endl;
	//}

	Person p1("Jon", 21);
	Person p2("TOom", 14);

	//无法正常运行 编译器不知道怎么比较
	//myCompare(p1, p2);

	//解决方法
	//1、重载运算符
	//2、具体化模板

	if(myCompare(p1, p2)){
		cout << "p1 == p2" << endl;
	}else{
		cout << "p1 != p2" << endl;
	}

}


int main(){

	test01();

	system("pause");
	return 0;
}