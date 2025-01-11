//2023-8-5

//函数调用运算符()重载

//由于重载之后非常像函数，所以也叫仿函数

//没有固定写法，非常灵活	


#include <iostream>
#include <string>

using namespace std;

//打印类
class MyPrintf{
public:
	MyPrintf(){
		cout << "无参构造函数！" << endl;
	}

	MyPrintf(string test){
		cout << test << endl;
		cout << "1" << endl;
	}
	//重载（）
	void operator()(string test){
		cout << test << endl;
	}

};

//加法类
class MyAdd{
public:
	
	////没有固定写法，非常灵活	
	int operator()(int a, int b){
		return a + b;
	}
};

void text(){
	//如果像下面这样调用的是有参构造函数
	MyPrintf p("hi");

	//如果像下面这样先调用的是无参构造函数，在调用“（）”的重载
	MyPrintf p1;

	p1("aa");

	MyAdd myadd;

	cout << myadd(100,100) << endl;

	//匿名对象
	cout << MyAdd()(200,100) << endl;
}

int main(){
	text();

	
	system("pause");
	return 0;
}