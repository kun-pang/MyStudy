#include "day12-text3-circle.h"


//set半径
void Circle::setR(double r){
	c_Ox = 0;
	c_Oy = 0;
	c_r = r;
}
//计算点与圆心的距离
void Circle::yuanXinJu(Point &p1){
	double x,y;
	x = p1.getX();
	y = p1.getY();
	double i = (x- c_Ox) *  (x- c_Ox)+ (y - c_Oy) * (y - c_Oy);
	double s = sqrt(i);		//在<cmath>中sqrt`函数有多个重载版本，分别接受`long double`、`float`和`double`类型的参数。
	if(s > c_r){
		cout << "点在圆外" << endl;
	}else if(s == c_r){
		cout << "点在圆上" << endl;
	}else{
		cout << "点在圆内" << endl;
	}
}
