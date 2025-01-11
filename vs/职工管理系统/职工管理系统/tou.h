/*2023-8-13*/

//头文件
#pragma once	//防止头文件重复包含
#include <iostream>
#include <string>

using namespace std;

//函数声明
void meun();
void exit();
void empty();


//类声明
//公共类
class Base{
public:

	virtual void Responsibility();		//员工职责

	virtual void add();					//增加员工

	virtual void display();				//显示员工

	virtual void remove();				//删除员工

	virtual void seek();				//查找员工

	virtual void sort();				//排序员工


	virtual void modify(int t);				//修改员工
	

	int m_ID;			//编号
	string m_Name;		//姓名
	string m_Post;		//岗位
};

//老板类
class Boss : public Base{
public:
	virtual void Responsibility();		//员工职责

	virtual void add();					//增加员工

	virtual void display();				//显示员工

	virtual void remove();				//删除员工

	virtual void modify(int t);			//修改员工

	virtual void seek();				//查找员工

	virtual void sort();				//排序员工

	~Boss();							//析构函数

	static Base *m_Boss[100];			//老板数组
};

//经理类
class Manger : public Base{
public:
	virtual void Responsibility();		//员工职责

	virtual void add();					//增加员工

	virtual void display();				//显示员工

	virtual void remove();				//删除员工

	virtual void modify(int t);			//修改员工

	virtual void seek();				//查找员工

	virtual void sort();				//排序员工

	~Manger();

	static Base *m_Manger[100];			//经理数组
};

//员工类
class Employee : public Base{
public:
	virtual void Responsibility();		//员工职责

	virtual void add();					//增加员工

	virtual void display();				//显示员工

	virtual void remove();				//删除员工

	virtual void modify(int t);			//修改员工

	virtual void seek();				//查找员工

	virtual void sort();				//排序员工

	~Employee();

	static Base *m_Employee[100];		//员工数组
};


//函数声明
void doAdd(Base &base);
void doDisplay(Base &base);
void doRemove(Base &base);
void doModify(Base &base, int a);
void doSeek(Base &base);
void doSort(Base &base);


