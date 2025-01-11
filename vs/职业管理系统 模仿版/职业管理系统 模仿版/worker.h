#pragma once		//防止头文件重复
#include <iostream>
#include <string>

using namespace std;

//职工类
class Worker{
public:

	//显示个人信息
	virtual void showInfo() = 0;

	//获取岗位信息
	virtual string getDeptName() = 0;

	//职工编号
	int m_ID;

	//职工姓名
	string m_Name;	
	
	//部门编号
	int m_DeptID;
};
