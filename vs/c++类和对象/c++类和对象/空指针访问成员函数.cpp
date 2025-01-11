//2023-8-3

//空指针调用成员函数

#include <iostream>

using namespace std;

class Person{
public:
	void show1(){
		cout << "1" << endl;
	}
	
	void show2(){

		//确保健壮性（代码的可运行性）
		if(this == NULL){
			return;
		}
		
		//age -> 实际上是this->age this接受的是一个NULL（空指针 相当于对象没有实体 无法访问属性）
		cout << "age = " << age << endl;
	}


	int age;
};

void text1(){
	Person *p = NULL;	//创建空指针

	//p->show1();		//空指针能访问

	p->show2();			//空指针不能访问（涉及到this）
}

int main(){
	text1();

	system("pause");
	return 0;
}