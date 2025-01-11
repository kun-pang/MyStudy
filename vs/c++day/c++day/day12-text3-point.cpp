#include "day12-text3-point.h"

//Point:: 告诉编译器在这个类的域下成员函数
//set点坐标
void Point::setP(double x, double y){
	p_x = x;
	p_y = y;
}
//get点坐标
double Point::getX(){
	return p_x;
}
double Point::getY(){
	return p_y;
}

