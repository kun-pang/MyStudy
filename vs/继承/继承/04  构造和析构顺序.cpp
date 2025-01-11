/*2023-8-6*/

//构造和析构顺序

//父构 ->  子构 -> 子析 -> 父析
//类似栈结构 但不是栈

#include <iostream>

using namespace std;

//公共类
class Base{
public:
	Base(){
		cout << "Base的构造函数!" << endl;
	}
	~Base(){
		cout << "Base的析构函数!" << endl;
	}
};

//子类 继承于  公共类
class Son : public Base{
public:
	Son(){
		cout << "Son的构造函数!" << endl;
	}
	~Son(){
		cout << "Son的析构函数!" << endl;
	}

};


void text(){
	Son s;

}

int main(){
	
	text();

	system("pause");
	return 0;
}