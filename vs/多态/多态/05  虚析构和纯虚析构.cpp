/*2023-8-8*/

//虚析构和纯虚析构

//多态的使用时，如果子类中有属性开辟到堆区，那么父类指针在释放时无法调用到子类的析构代码

//解决方式：将父类中的析构函数改为虚析构或者纯虚析构

//虚析构和纯虚析构共性：
//	可以解决父类指针释放子类对象
//	都需要有具体的函数实现

//虚析构和纯虚析构区别：
//	如果是纯虚析构，该类属于抽象类，无法实例化对象

//虚析构的语法
//virtual ~ 类名（）{}

//纯虚析构的语法啊
//类内声明	virtual ~ 类名（） = 0；
//类外实现	类名：： ~类名（）{}
	

#include <iostream>
#include <string>

using namespace std;

//动物类 抽象类
class Animal{
public:
	Animal(){
		cout << "Animal的构造函数!" << endl;
	}

	virtual void speak() = 0;

	//虚析构
	/*virtual ~Animal(){
		cout << "Animal的析构函数!" << endl;
	}*/

	//纯虚析构
	//如果是纯虚析构，该类属于抽象类，无法实例化对象
	virtual ~Animal() = 0;
};

Animal::~Animal(){
	cout << "Animal的析构函数!" << endl;
}

class Cat : public Animal{
public:
	Cat(string name){
		cout << "Cat的构造函数!" << endl;
		m_Name = new string(name);
	}

	virtual void speak(){
		cout  << *m_Name << "小猫在叫！" << endl;
	}

	~Cat(){
		if(m_Name != NULL){
			cout << "Cat的析构函数!" << endl;
			delete m_Name;
			m_Name = NULL;
		}
	}

	string *m_Name;
};

void text(){
	//如果在Anima写虚析构或者纯虚析构 那么Cat中的堆区无法释放
	Animal *a = new Cat("Tom");
	a->speak();
	delete a;

	/*Animal &a = Cat("Tom");*/
}

int main(){
	text();

	system("pause");
	return 0;
}