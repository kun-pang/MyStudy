#pragma once		//防止头文件重复
#include <iostream>
#include <string>
#include "worker.h"

using namespace std;

//职工类
class Manger : public Worker{
public:

	Manger(int id, string name, int did);

	//显示个人信息
	virtual void showInfo();

	//获取岗位信息
	virtual string getDeptName();

	
};