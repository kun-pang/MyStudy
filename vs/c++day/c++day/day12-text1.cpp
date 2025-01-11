/*2023—7—31*/
/* 学生类 */

/*
属性--姓名、学号
行为--显示姓名、学号
*/

#include <iostream>
#include <string>

using namespace std;

//学生类
//学生类
class Students{
	//公有访问权限
public:
	//属性
	string name;		//姓名
	int num;			//学号

	//行为
	void studenXX(){
		system("cls");
		cout << "姓名：" << name << " 学号：" << num << endl;
	}
	//通过行为赋值
	void setName(){
		string name1 = getName();
		name = name1;
	}
	/*void steName1(string name1){
		name = name1;
	}*/
	string getName(){
		string name1;
		cin >> name1;
		return name1;
	}
	void setNum(){
		int num1= getNum();
		num = num1;
	}
	int getNum(){
		int num1;
		cin >> num1;
		return num1;
	}


};

int main12t1(){
	//学生类实例化
	Students s1;

	cout << "请输入姓名" << endl; 
	/*cin >> s1.name;*/
	s1.setName();
	cout << "请输入学号" << endl; 
	/*cin >> s1.num;*/
	s1.setNum();

	/*s1.steName1("张三");*/

	/*s1.name = "张三丰";
	s1.num = 2111030833;*/
	s1.studenXX();

	system("pause");
	return 0;
}