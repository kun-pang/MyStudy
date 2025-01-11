/*2023—7—31*/
/* 点圆关系 */

//设计点类(Point)和圆类(Circle) 判断点圆关系
//点在圆内 点在圆外 点在园内

//注意类与类之间的先后顺序  a调用b，a就在后面，b在前

#include <iostream>
#include <cmath>
#include "day12-text3-circle.h"
#include "day12-text3-point.h"


using namespace std;

////定义点类
//class Point{
//public:
//	//set点坐标
//	void setP(double x, double y){
//		p_x = x;
//		p_y = y;
//	}
//	//get点坐标
//	double getX(){
//		return p_x;
//	}
//	double getY(){
//		return p_y;
//	}
//
//private:
//	double p_x;		//点x轴
//	double p_y;		//点y轴
//};

//定义类
////定义圆类
//class Circle{
//public:
//	//set半径
//	void setR(double r){
//		c_Ox = 0;
//		c_Oy = 0;
//		c_r = r;
//	}
//	//计算点与圆心的距离
//	void yuanXinJu(Point &p1){
//		double x,y;
//		x = p1.getX();
//		y = p1.getY();
//		double i = (x- c_Ox) *  (x- c_Ox)+ (y - c_Oy) * (y - c_Oy);
//		double s = sqrt(i);		//在<cmath>中sqrt`函数有多个重载版本，分别接受`long double`、`float`和`double`类型的参数。
//		if(s > c_r){
//			cout << "点在圆外" << endl;
//		}else if(s == c_r){
//			cout << "点在圆上" << endl;
//		}else{
//			cout << "点在圆内" << endl;
//		}
//	}
//
//private:
//	double c_Ox;		//圆心x轴
//	double c_Oy;		//圆心y轴
//	double c_r;		//圆心半径
//};


//圆心也可以通过点类构建


int main12t3(){
	Point p1;
	Circle c1;
	double x,y,r;
	cout << "请分别输入点的横坐标、纵坐标以及圆的半径：" << endl;
	cin >> x >> y >> r;
	p1.setP(x,y);
	c1.setR(r);
	c1.yuanXinJu(p1);

	system("pause");
	return 0;
}



