/*2023—8—2*/

//初始化列表

//作用：用来初始化属性

//语法：构造函数():属性1（值1），属性2（值2）...{}

#include <iostream>

using namespace std;

class Person{
public:
	//传统初始化
	//Person(int a, int b, int c){
	//	p_A = a;
	//	p_B = b;
	//	p_C = c;
	//}

	//初始化列表  值固定
	/*Person():p_A(10),p_B(20),p_C(30){
		
	}*/

	//值不固定，更加灵活
	Person(int a, int b, int c):p_A(a),p_B(b),p_C(c){
		
	}

	int p_A;
	int p_B;
	int p_C;
};

//测试函数
void text(){
	Person p(10,20,30);
	/*Person p;*/

	cout << "p_A = " << p.p_A << endl;
	cout << "p_B = " << p.p_B << endl;
	cout << "p_C = " << p.p_C << endl;
}

int main(){

	text();

	system("pause");
	return 0;
}