/*2023-8-24*/

//类模板和友元函数
//全局函数作友元类内实现 - 直接在类内声明友元函数即可
//全局函数作友元类外实现 - 需要提前让编译器知道全局函数的存在


#include <iostream>
#include <string>

using namespace std;

template<typename T1, typename T2 >
class Person;

//和类成员函数做友元类似
template<typename T1, typename T2 >
void showPerson0(Person<T1, T2> &p){
	 cout << "name:" << p.m_Name << std::endl;
      cout << "age:" << p.m_Age << std::endl;
}

//类模板
template<typename T1, typename T2 >
class Person{
	//声明友元全局函数  类内直接实现
	 friend void showPerson(Person<T1, T2> &p) {
        cout << "name:" << p.m_Name << std::endl;
        cout << "age:" << p.m_Age << std::endl;
    }

	 //类外实现
	 //加空模板 让之变为模板函数
	 friend void showPerson0<>(Person<T1, T2> &p);


public:
	Person(T1 name, T2 age){
		this->m_Name = name;
		this->m_Age = age;
	}

	
private:
	T1 m_Name;
	T2 m_Age;
};

//错误 会出现“ 1 个无法解析的外部命令”的错误 
//原因:类中声明的为普通函数friend void showPerson0(Person<T1, T2> &p);而类外实现却是模板函数
//如果将类中声明改为模板函数friend void showPerson0<>(Person<T1, T2> &p); 任然报错
//但是模板是调用时创建，所以要先让编译器知道
//template<typename T1, typename T2 >
//void showPerson0(Person<T1, T2> &p){
//	 cout << "name:" << p.m_Name << std::endl;
//      cout << "age:" << p.m_Age << std::endl;
//}




void test01(){
	Person<string, int> p("tom", 2);
	//showPerson(p);
	showPerson0(p);
}


int main(){

	test01();

	system("pause");
	return 0;
}