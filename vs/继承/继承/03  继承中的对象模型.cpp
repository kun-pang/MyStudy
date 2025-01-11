/*2023-8-6*/

//继承中的对象模型

#include <iostream>

using namespace std;

//公共类
class Base{
public:
	int m_A;
private:
	int m_C;
protected:
	int m_B;
};

//子类  继承 公共类
class Son : public Base{
public:
	int m_D;
};

//利用 visual Studio 的开发人员命令提示符工具 查看具体的继承情况
//打开 visual Studio 的开发人员命令提示符（Developer Command Prompt for VS 版本号）
//跳转盘符（跳转到项目所在盘符）  盘符：
//跳转到对象源文件  cd ..项目路径
//查看项目文件信息  dir
//查看命名（类的结构）
//cl /d1 reportSingleClassLayout类名 源文件名（可以用tab补全）
//例如：cl /d1 reportSingleClassLayoutSon 1a.cpp
//	reportSingleClassLayout（报告单个类的布局）	  report  报告    Single  单个   Class  类    Layout  布局


void text(){
	//大小为16  4个整型
	//父类中所有权限下的非静态成员属性都会被子类继承下去
	//父类中私有成员属性 是被编译器隐藏 因此不能够访问 但是确实是被继承下来了的
	cout << "Son的占用空间大小：" <<  sizeof(Son) << endl;
}

int main(){
	
	text();

	system("pause");
	return 0;
}