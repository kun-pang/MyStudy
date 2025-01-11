#pragma once
#include <iostream>
#include <cmath>
#include "day12-text3-point.h"		//调用另一个类

using namespace std;

//定义圆类
//声明成员函数和成员变量
class Circle{
public:
	//set半径
	void setR(double r);
	//计算点与圆心的距离
	void yuanXinJu(Point &p1);

private:
	double c_Ox;		//圆心x轴
	double c_Oy;		//圆心y轴
	double c_r;		//圆心半径
};