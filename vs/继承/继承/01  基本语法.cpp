/*2023-8-6*/

//继承基本知识

//子类继承一部分父类的属性或者行为

//继承的作用：减少重复代码

//继承的语法：class 子类 : 继承方式 父类{}；

//子类  也称 派生类
//父类  也称 基类

#include <iostream>

using namespace std;

//父类
class Father{
public:
	void fangZi(){
		cout << "继承的房子" << endl;
	}

	void canZhuo(){
		cout << "继承的餐桌" << endl;
	}
	void fengShan(){
		cout << "继承的风扇" << endl;
	}

};

class Son : public Father{
public:
	void shouJi(){
		cout << "私有的手机" << endl;
	}
};

void text(){
	Son s;
	s.canZhuo();
	s.fangZi();
	s.fengShan();
	s.shouJi();


}

int main(){
	text();

	system("pause");
	return 0;
}
