#pragma once	//防止头文件重复包含
#include <iostream>
#include <cmath>

using namespace std;

//定义点类
//声明成员函数和成员变量
class Point{
public:
	//set点坐标
	void setP(double x, double y);
	//get点坐标
	double getX();
	double getY();

private:
	double p_x;		//点x轴
	double p_y;		//点y轴
};