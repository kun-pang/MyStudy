/*2023—7—31*/
/* 立方体类(Cube) */

/*
求立方体面积和体积
分别用全局函数和成员函数判断两个立方体是否相等
*/

#include <iostream>

using namespace std;



//定义类
//立方体类
class Cube{
public:
	//set
	void setCube(double l, double w, double h){
		//判断长宽高全为正数
		while(1){
			if(l > 0 && w > 0 && h > 0){
				c_L = l;
				c_W = w;
				c_H = h;
				break;
			}else{
				cout << "有参数为负数，请重新输入长、宽、高:" << endl;
				cin >> l >> w >> h;
			}
		}
	}
	//get面积
	double getS(){
		if(c_L == c_W && c_W == c_H){
			c_S = 6 * c_L * c_L;
		}else{
			c_S = 2 * c_L * c_W + 2 * c_L * c_H + 2 * c_W * c_H;
		}
		return c_S;
	}
	//get体积
	double getV(){
		if(c_L == c_W && c_W == c_H){
			c_V = c_L * c_L * c_L;
		}else{
			c_V = c_L * c_W * c_H;
		}
		return c_V;
	}
	//get长宽高
	double getL(){
		return c_L;
	}
	double getW(){
		return c_W;
	}
	double getH(){
		return c_H;
	}
	//通过成员函数判断
	//自身和传入做对比
	void CubeXd(Cube &c){
		if(c_L == c.getL() && c_W == c.getW() && c_H == c.getH()){
		cout << "两个立方体相等" << endl;
	}else{
		cout << "两个立方体不相等" << endl;
	}
	}

private:
	//长
	double c_L;
	//宽
	double c_W;
	//高
	double c_H;
	//表面积
	double c_S;
	//体积
	double c_V;
};

//声明全局函数
//void CubeXD(double a0, double b0, double c0, double a1, double b1, double c1);
void CubeXD(Cube &c1,Cube &c2);

int main12t2(){
	//Cube实例化
	Cube c1;
	int l,w,h;

	cout << "请输入长、宽、高:" << endl;
	cin >> l >> w >> h;
	c1.setCube(l,w,h);
	cout << "表面积：" << c1.getS() << " 体积：" << c1.getV() << endl;

	//实例化第二个
	Cube c2;
	cout << "请输入长、宽、高:" << endl;
	cin >> l >> w >> h;
	c2.setCube(l,w,h);
	cout << "表面积：" << c2.getS() << " 体积" << c2.getV() << endl;

	//全局函数判断相同
	CubeXD(c1, c2);

	//成员函数判读相同
	c1.CubeXd(c2);

	system("pause");
	return 0;
}

//判断是否相等
void CubeXD(Cube &c1,Cube &c2){
	if(c1.getL() == c2.getL() && c1.getW() == c2.getW() && c1.getH() == c2.getH()){
		cout << "两个立方体相等" << endl;
	}else{
		cout << "两个立方体不相等" << endl;
	}
}
