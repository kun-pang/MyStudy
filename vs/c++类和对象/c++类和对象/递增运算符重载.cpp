//2023-8-5

//递增（递减）运算符重载

//对自定义数据类型进行递增（递减）

//前置递增运算符 `++` 会先对操作数进行递增操作，然后返回递增后的值。
//后置递增运算符 `++` 会先返回操作数的原始值，然后再对操作数进行递增操作。

#include <iostream>

using namespace std;

//自定义整型数据
class MyIntger{
	friend ostream& operator<<(ostream &cout, MyIntger &myInt);
	friend MyIntger& operator--(MyIntger &myInt);
	friend MyIntger operator--(MyIntger &myInt,int);
public:
	//初始化列表初始化数据
	MyIntger():m_Num(0){
		
	}

	//前置++
	//MyIntger& 是因为返回的是它本身的值，
	//如果不加引用 ，返回的是系统拷贝的值，在执行++（++a）时会发现，
	//加完后，在打印这个值会发现和初值一样
	MyIntger& operator++(){
		//先 加
		m_Num++;
		//后 返回值（本身*this）
		return *this;
	}

	//后置++
	//operator++(int )  int 占位符
	//不加引用 是因为t是临时变量 函数运行完会销毁
	MyIntger operator++(int ){	
		//先 记录本身
		MyIntger t = *this;
		//后 加加
		m_Num++;
		return t;
	}


private:
	int m_Num;
};

//重载<< 
ostream& operator<<(ostream &cout, MyIntger &myInt){
	//cout << myInt;		无限调用递归
	cout << myInt.m_Num;
	return cout;
}

//全局的方式前置--
MyIntger& operator--(MyIntger &myInt){
	//先减
	myInt.m_Num--;
	//后返回本身
	return myInt;
}

//后置--
MyIntger operator--(MyIntger &myInt,int){
	//先记录
	MyIntger t = myInt;
	//后减减
	myInt.m_Num--;
	return t;
}

void text1(){
	MyIntger myInt;

	cout << ++myInt << endl;
	cout << myInt << endl;
	
	//证明加不加引用的区别
	//cout << ++(++myInt) << endl;
	//cout << myInt << endl;
	
}

void text2(){
	MyIntger myInt;
	cout << myInt++ << endl;
	cout << myInt << endl;
}

void text3(){
	MyIntger myInt;
	cout << --myInt << endl;
	cout << myInt << endl;

	//cout << --(--myInt) << endl;
	//cout << myInt << endl;
}

void text4(){
	MyIntger myInt;
	cout << myInt-- << endl;
	cout << myInt << endl;

	//cout << (myInt--)-- << endl;
	//cout << myInt << endl;

	//MyIntger myInt1;
	//cout << (myInt1++)++ << endl;
	//cout << myInt1 << endl;
	//后置递增运算符 `++` 只能应用于可修改的左值，
	//而 `(a++)` 的结果是一个右值，不能再次应用递增运算符。
}

int main(){
	/*text1();*/

	/*text2();*/

	/*text3();*/

	text4();

	int a = 0;

	/*cout << (a++)++ << endl; 错误 a++ 是表达式 在后置运算时编译器不能识别 */

	//int a = 0;

	//cout << ++(++a) << endl;
	//cout << a << endl;
	////对同一个数据a进行操作

	system("pause");
	return 0;
}