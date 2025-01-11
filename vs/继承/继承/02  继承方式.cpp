/*2023-8-6*/

//继承方式：public（公共继承） private（私有继承） protected（保护继承）

/*
public继承：
						父类的public			父类的private				父类的protected

在子类的表示权限		   public					无							protected

子类能否访问				能						不能							能



protected继承：
						父类的public			父类的private				父类的protected

在子类的表示权限		   protected				无							protected

子类能否访问				能						不能							能



private继承：
						父类的public			父类的private				父类的protected

在子类的表示权限		   private					无							private

子类能否访问				能						不能							能

*/

//权限访问 私有 >  保护 > 公有
//加友元全都可以

#include <iostream>

using namespace std;

//父类
class Father{
public:
	int a;
protected:
	int b;
private:
	int c;
};

//子类
//公有继承
class Son1 : public Father{
public:
	void func(){
		a = 100;		//父类的公有成员   公有继承下  在子类变成了公有成员
		b = 10;			//父类的保护成员   公有继承下  在子类变成了保护成员
		//c = 1;		//父类的私有成员   公有继承下  子类无法访问
	}
};

void text1(){
	Son1 s1;
	cout << s1.a <<endl;
	//cout << s1.b << end;		保护成员 无法在类外访问	
}

//保护继承
class Son2 : protected Father{
public:
	void func(){
		a = 100;		//父类的公有成员   保护继承下  在子类变成了保护成员
		b = 10;			//父类的保护成员   保护继承下  在子类变成了保护成员
		//c = 1;		//父类的私有成员   保护继承下  子类无法访问
	}
};

void text2(){
	Son2 s2;
	//cout << s2.a <<endl;		保护成员 无法在类外访问	
	//cout << s2.b << end;		保护成员 无法在类外访问	
}

//私有继承
class Son3 : private Father{
	friend class  GrandSon1;	//友元类   友元函数是声明明普通函数的（所以才要类外定义）
public:
	void func(){
		a = 100;		//父类的公有成员   私有继承下  在子类变成了私有成员
		b = 10;			//父类的保护成员   私有继承下  在子类变成了私有成员
		//c = 1;		//父类的私有成员   私有继承下  子类无法访问
	}
};

void text3(){
	Son3 s3;
	//cout << s3.a <<endl;		私有成员 无法在类外访问	
	//cout << s3.b << end;		私有成员 无法在类外访问	
}

//孙子类
class GrandSon1 : public Son3{
public:
	void func(){
		a = 100;		//在Son3中已经是私有成员  即使是公有继承也无法访问
		b = 1;
		//c = 1;		// 私有成员无法在孙子类中直接访问
	}
};

int main(){
	/*text1();*/
	/*text2();*/
	text3();

	system("pause");
	return 0;
}

//cout << '' << ""; 区别：使用单引号（'）表示字符字面量，而使用双引号（"）表示字符串字面量