/*2023—7—27*/
/* 内存模型  引用*/


/* 内存模型 
堆区		由程序员分配和释放，如果程序员不释放，程序结束时由操作系统回收
栈区		编译器自动分配释放，存放参数值、局部变量，程序结束时由操作系统回收
代码区		存放项目或者源文件（函数）的二进制代码，由操作系统管理--共享、只读
全局区		存放全局变量、静态变量、常量
*/

/*引用
作用：给变量起别名
语法：数据类型 &别名 = 原名；

引用做函数参数
可以简化指针修改指针
*/


#include <iostream>

using namespace std;

//全局变量
int g_a = 0;
int g_b = 0;

//const修饰的全局变量  全局常量
const int t_b =20;

//声明函数
int* func();

int* func1();

void func2();

void func3();
//声明交换函数
void swap1(int a, int b);
void swap2(int *a, int *b);
void swap3(int &a, int &b);

int main10(){
	//全局区
	//局部变量--栈区
	int a = 10;
	int b = 20;

	cout << "局部变量a的地址：" << (int)&a << endl;
	cout << "局部变量b的地址：" << (int)&b << endl;

	cout << "全局变量g_a的地址：" << (int)&g_a << endl;
	cout << "全局变量g_b的地址：" << (int)&g_b << endl;

	//静态变量（static修饰）
	static int h_a = 10;

	cout << "静态变量h_a的地址：" << (int)&h_a << endl;

	//常量
	//字符串常量（用""包裹的）
	cout << "字符串常量的地址：" << (int)&"niHao!" << endl;

	//const修饰的局部变量(局部常量)--栈区   const修饰的全局变量
	const int t_a = 10;
	int const s_a = 20;			//都是const修饰局部变量  只是修饰的位置不同
								//使用方法和访问方式是一样的		

	cout << "const修饰的局部变量t_a的地址：" << (int)&t_a << endl;
	cout << "const修饰的局部变量s_a的地址：" << (int)&s_a << endl;
	cout << "const修饰的全局变量t_b的地址：" << (int)&t_b << endl;
	cout << endl;

	//栈区 - - 函数中不要返回局部变量地址
	int *p = func();

	cout << *p <<endl;		//第一次编译器会保存一次局部地址
	cout << *p <<endl;		//第二次乱码
	cout << endl;

	//堆区
	int *p0 = func1();

	cout << *p0 << endl;
	cout << *p0 << endl;
	//手动对堆区的数据进行释放  delete关键字 
	delete p0;

	cout << *p0 << endl;

	func2();
	cout << endl;

	//引用
	func3();

	//swap1(a,b);		//不会影响实参
	//swap2(&a,&b);
	swap3(a,b);
	cout << "a = " << a << "  b = " << b << endl;

	
	system("pause");
	return 0;
}


int* func(){		//形参也会放在栈区
	int a = 10;		//函数执行完后自动释放
	return &a;		//返回局部变量地址
}

int* func1(){		//用new堆区开辟数据
	int *p = new int(20);		//new 数据类型(初始值)			*p 接受地址
								//new返回的是该数据类型的指针
	return p;
}

void func2(){
	//在堆区new数组
	int *p = new int[4];	//new返回的是数组的首地址

	for(int i = 0; i < 4; i++){
		p[i] = i;
	}

	for(int i = 3; i >= 0; i--){
		cout << p[i] << endl;
	}

	//释放new的数组
	delete[] p;
}

void func3(){
	int a = 10;
	int c = 20;
	//创建引用
	int &b = a;

	/*int &d;   引用必须初始化*/
	

	cout << "a= " << a << " b= " << b <<endl;

	b = 100;

	cout << "a= " << a << " b= " << b <<endl;

	//int &b = c;		//一旦初始化，不能更改引用
	b = c;				//这是赋值操作
	cout << "a= " << a << " b= " << b <<endl;
	c = 30;
	cout << "a= " << a << " b= " << b <<endl;
	cout << "c= " << c << endl;
	
	cout << endl;
}
//值传递
void swap1(int a, int b){
	int t = a;
	a = b;
	b = t;
}
//地址传递
void swap2(int *a, int *b){
	int t = *a;
	*a = *b;
	*b = *a;
}
//引用做函数参数
void swap3(int &a, int &b){
	int t = a;
	a = b;
	b = t;
}