/*2023-8-8*/

//制作流程：煮水-冲泡-倒入杯中-加入辅料

//优化方案：每个步骤单独写一个纯虚函数 在父类中写一个调用全部纯虚函数的成员函数
//			在外面写一个工作函数 用于获取传入的变量和调用父类的成员函数

#include <iostream>
#include <string>

using namespace std;

//冲泡类 抽象类
class Chong{
public:
	virtual void func() = 0;
};

//冲咖啡类
class ChongCoffee : public Chong{
public:
	virtual void func(){
		cout << "煮水" << endl;
		cout << "冲泡咖啡" << endl;
		cout << "倒入杯中" << endl;
		cout << "加糖和牛奶" << endl;
		cout << "咖啡已经冲泡好！" << endl;
	}
};

//冲茶类
class ChongTea : public Chong{
public:
	virtual void func(){
		cout << "煮水" << endl;
		cout << "冲泡茶叶" << endl;
		cout << "倒入杯中" << endl;
		cout << "加柠檬" << endl;
		cout << "茶已经冲泡好！" << endl;
	}
};

void text(){
	int  a;		//获取用户选项

	cout << "请选择您要和的饮料：" << endl;
	cout << "      1、咖啡       " << endl;
	cout << "      2、茶         " << endl;
	cin >> a;

	Chong *s = new ChongCoffee;		//咖啡
	Chong *c = new ChongTea;		//茶

	switch(a){
	case 1:
		s->func();
		delete s;
		s = NULL;
		 break;
	case 2:
		c->func();
		delete c;
		c = NULL;
		 break;	
	default:
		cout << "该产品本店没有！" << endl;
		break;	
	}
}

int main(){
	text();

	system("pause");
	return 0;
}