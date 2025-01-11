/*2023-8-6*/

//菱形继承（钻石继承）

//意义：两个派生类继承同一个基类
//又有某个类继承于者两个派生类

/*举例（虚构）
1、羊继承了动物的数据，驼也继承了动物数据，草泥马（羊驼）继承了羊和驼的数据
当草泥马使用数据的时候，会参数二义性。
2、草泥马继承了两份来自动物的数据，其实我们只需要一份就够了

*/

#include <iostream>

using namespace std;

//动物类
class Animal{
public:
	int m_Age;
};

//利用虚继承 解决菱形继承问题
//虚继承  class 子类 ： virtual 继承方式 父类{}；
//
//Animal 称为虚基类
//可以利用 开发人员命令提示符 进行查看底层
//羊类  公有继承 动物类
class Yang : virtual public Animal{};

//驼类  公有继承 动物类
class Tuo : virtual public Animal{};

//羊驼类 公有继承 羊类 和 驼类
class YangTuo : public Yang, public Tuo{};

void text(){
	YangTuo yt;
	Yang y;

	//yt.m_Age = 18;  出现错误 有两份来自动物类的m_Age

	yt.Yang::m_Age = 18;
	yt.Tuo::m_Age = 20;
	//yt.Yang::m_Age = 18;
	
	//加作用域区分
	//当加上virtual以后 羊驼类继承了虚基类指针（也可以理解为yt.Tuo::m_Ag与yt.Yang::m_Age 共享了）
	cout << "yt.Yang::m_Age = " << yt.Yang::m_Age << endl;
	cout << "yt.Tuo::m_Age =" << yt.Tuo::m_Age << endl;
	cout << "yt.m_Age =" << yt.m_Age << endl;

	y.m_Age = 1;
	cout << "y.m_Age =" << y.m_Age << endl;
	cout << "yt.m_Age =" << yt.m_Age << endl;

}

int main(){
	
	text();

	system("pause");
	return 0;
}