//2023-8-4


//定义：让一个函数或者一个类 访问另一个类中的私有成员

//关键字friend

//三种实现方式
	//全局函数做友元
	//类做友元
	//成员函数做友元




#include <iostream>
#include <string>

using namespace std;

//声明建筑类
class Building;
//好基友2类
class GoodGay2 {
public:
	GoodGay2();

	void textq1();
	void textq2();


public:
	Building* building;
};

//建筑类
class Building{

	////全局函数做友元
	////声明友元(类中声明)
	//friend void goodGay(Building &b);
	////类做友元
	//friend class GoodGay;
	//成员函数做友元
	//注：friend声明的类（我的好朋友） 必须在本类（我）前面 且类中函数涉及到本类（我）的私有成员变量时，必须在类外定义
	friend void GoodGay2::textq1();

public:
	Building(){
		m_SittingRoom = "客厅" ;
		m_BedRoom = "卧室";
	}

public:
	string m_SittingRoom;	//客厅
private:
	string m_BedRoom;		//卧室
};

////好基友类
//class GoodGay{
//public:
//	GoodGay();
//
//	//访问好友建筑
//	void visit(){
//		cout << "好基友正在访问：" << building->m_SittingRoom << endl;
//
//		cout << "好基友正在访问：" << building->m_BedRoom << endl;
//	}
//	~GoodGay();
//
//public:
//	Building *building;
//};
//
////类外定义函数
//GoodGay::GoodGay(){
//	building = new Building;
//}
//
//
//
//
//
////全局函数
////好基友函数
//void goodGay(Building &b){
//
//	cout << "好基友正在访问：" << b.m_SittingRoom << endl;
//
//	//如果没有对本函数进行友元声明，那么不可以调用私有成员
//	cout << "好基友正在访问：" << b.m_BedRoom << "哦~吼~吼~" << endl;
//}

GoodGay2::GoodGay2(){
		building = new Building;
}


void GoodGay2::textq1() {
	cout << "正在访问：" << building->m_SittingRoom << endl;
	cout << "正在访问：" << building->m_BedRoom << endl;
}

void GoodGay2::textq2() {
	cout << "正在访问：" << building->m_SittingRoom << endl;
}



//void text(){
//	Building b;
//	goodGay(b);
//}
//
//void text1(){
//	GoodGay g;
//	g.visit();
//	
//}

void text2(){
	GoodGay2 g;
	g.textq1();
	g.textq2();
	
}


int main(){
	/*text();*/
	/*text1();*/
	text2();

	system("pause");
	return 0;
}