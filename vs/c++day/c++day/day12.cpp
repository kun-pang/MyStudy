/*2023—7—31*/
/* 类和对象 */

/* 类和对象 
c++三大特性：封装、继承、多态
封装
	将属性和行为作为一个整体，表现生活中的事物
	将属性和行为加以权限控制

访问权限
	public			公有（公共）权限		类内、类外都可以访问
	private			私有权限				类内可以访问、类外不可以访问	继承中子类可以访问父类的保护
	protected		保护权限				类内可以访问、类外不可以访问	继承中子类不可以访问父类的私有

class与struct区别
	class	默认为private
	struct  默认为public

将成员属性设置为私有
	1、可以自己控制读写权限
	2、对于写可以检测数据的有效性
*/

#include <iostream>
#include <string>

using namespace std;

//宏定义常量
//#define PI 3.1415
const double PI = 3.1415;

 
//函数定义
void HH();


//结构体
struct C1{
	int a;
private:
	int b;	
};


//类
//类中的属性、行为统一称为 成员
//属性 也叫成员属性 成员变量
//行为 也叫成员函数 成员方法
//圆类  求圆的周长(circumference)
//圆的周长公式： 2 * PI * r
//class 类名   定义一个类
class Circle_C{
	//访问权限
	//公共权限
public:
	//属性
	double r;	//半径
	
	//行为（函数）
	double circle_c(){	//周长
		return 2 * PI * r;
	}
};

//人类1
class Person{
	//属性
public:
	string name;		//姓名
private:
	int password;			//银行卡密码
protected:
	string car;				//所拥有的车

	//行为
public:
	void func(){
		name = "张三";
		password = 111111;
		car = "拖拉机";
	}
	void func1(){
		cout << name << " " << password << " " << car << endl;
	}
};

//人类2
class Preson0{
public:
	//设置
	void setName(string name){
		p_Name = name;
	}
	void setLover(string lover){
		p_Lover = lover;
	}
	void setAge(int age){
		if(age <= 120 && age >= 0){
			p_Age = age;
		}else{
			cout << "输入的年龄有误！" << endl;
			p_Age = 0;	//初始化
			return;
		}
	}
	//获取
	string getName(){
		return p_Name;
	}
	int getAge(){
		return p_Age;
	}
	int getPhone(){
		p_Phone = 11111;
		return p_Phone;
	}
private:
	//姓名 可读可写
	string p_Name;
	//年龄 可读可写
	int p_Age;
	//情人 只写
	string p_Lover;
	//开发者电话 只读
	int p_Phone;
};

class C2{
	int b;
};



int main12(){
	//创建一个具体的圆（对象）
	//实例化（通过一个类创建一个对象）
	Circle_C c1;

	//给圆对象赋值
	c1.r = 2;

	cout << "圆的周长为：" << c1.circle_c() << endl;
	HH();


	//人类实例化
	Person p1;
	/*p1.password = 1111;
	p1.car = "奔驰";			私有、保护的成员不能访问*/
	p1.name = "王五";
	p1.func1();
	p1.func();
	p1.func1();
	HH();

	
	//class与struct区别
	C1 a1;
	C2 a2;

	a1.a = 1;
	//a2.b;	//不能访问
	HH();


	//成员私有化
	Preson0 p0;		//Preson0实例化
	int age;		//年龄
	/*p0.p_Name;*/
	p0.setName("张三");
	p0.setLover("李四");
	/*p0.setPhone();*/ //只读不能写
	cout << "姓名："  << p0.getName() << endl;
	cout << "电话："  << p0.getPhone() << endl;
	/*cout << "情人："  << p0.getLover() << endl;*/	//只写不能读
	cout << "请输入年龄（0~120）：" << endl;
	cin >> age;
	p0.setAge(age);
	cout << "年龄：" << p0.getAge() << endl;

	system("pause");
	return 0;
}


//换行
void HH(){
	system("pause");
	system("cls");
}