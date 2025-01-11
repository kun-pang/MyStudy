/*2023-8-7*/

//分别利用普通写法 和 多态技术，设计实现两个操作数进行运算的计算器类

//多态优点：
//	代码组织结构清晰
//	可读性强
//	利于前期和后期的扩展以及维护

//开发中提倡 开闭原则
//开闭原则： 对扩展进行开发 对修改进行关闭

#include <iostream>
#include <string>

using namespace std;

//计算器抽象类
class Calculator{
public:

	
	virtual double getNum(){
		return 0;
	}

	

	double m_Num1;		//操作数1
	double m_Num2;		//操作数2
};

//加法类 公有继承 计算器类
class JiaFa : public Calculator{
public:
	JiaFa(){}
	double getNum(){
		return m_Num1 + m_Num2;
	}

};

//减法类
class JianFa : public Calculator{
public:
	JianFa(){}
	double getNum(){
		return m_Num1 - m_Num2;
	}

};

//乘法类
class ChengFa : public Calculator{
public:
	ChengFa(){}
	double getNum(){
		return m_Num1 * m_Num2;
	}

};
//除法类
class ChuFa : public Calculator{
public:
	ChuFa(){}
	double getNum(){
		return m_Num1 / m_Num2;
	}

};
 

void text(){
	string oper;		//符号操作数
	double a;
	double b;

	cout << "输入算式：" << endl;
	cin >> a >> oper >> b;

	if(oper == "+"){
		//父类的指针 或者 引用 执行子类对象
		Calculator *abc = new JiaFa;
		abc->m_Num1 = a;
		abc->m_Num2 = b;

		cout << abc->m_Num1 << "+" << abc->m_Num2 << "=" << abc->getNum() << endl;
		
		delete abc;
		abc = NULL;
	}else if(oper == "-"){
		JianFa c;
		Calculator &cd = c;
		cd.m_Num1 = a;
		cd.m_Num2 = b;

		cout << cd.m_Num1 << "-" << cd.m_Num2 << "=" << cd.getNum() << endl;
	}else if(oper == "*"){
		ChengFa c;
		Calculator &cd = c;
		cd.m_Num1 = a;
		cd.m_Num2 = b;

		cout << cd.m_Num1 << "*" << cd.m_Num2 << "=" << cd.getNum() << endl;
	}else if(oper == "/"){
		ChuFa c;
		Calculator &cd = c;
		cd.m_Num1 = a;
		cd.m_Num2 = b;

		cout << cd.m_Num1 << "/" << cd.m_Num2 << "=" << cd.getNum() << endl;
	}
}

int main(){
	text();

	system("pause");
	return 0;
}