/*2023—7—29*/
/* 引用 函数高级*/


/* 引用
引用做函数的返回值
	1、不要返回局部变量的引用
	2、函数的调用可以做左值 
引用的本质
	在c++内部的实现是一个指针常量
常量引用
	用const修饰形参，防止误操作
*/

/* 函数高级
函数的默认参数
	函数的形参列表中形参可以赋默认值
		返回值类型 函数名（形参 = 默认值）{}
函数的占位参数
	函数的形参列表中可以有占位参数，用来占位，在调用的时候必须填补该位置
		返回值类型 函数名（数据类型）{}
函数的重载
	同一作用域（全局作用域，局部···），同名（函数名称）不同参（形参的个数、类型、顺序）
	函数的返回值不可以作为重载条件
	注意事项:
		引用作为重载条件 
		函数重载遇到默认参数
*/


#include <iostream>

using namespace std;

//定义宏常量

//声明函数
void KongHang();
int& text01();
int& text02();
void func(int &ref);
void s_func();
void showValue1(int & vue);
void showValue2(const int & vue);
//函数如果声明定义分开写，那么1、放在mian函数后面时默认参数必须在写声明中（只用在声明写一次就可以了）
//							  2、放在mian函数前面时默认参数在声明和定义之中二选一就行书写
//函数的默认参数  如果在某个位置已经写了默认参数，那么从那个位置往后，从左到右都必须要有默认值
int  funx(int a, int b,int c = 2);
//int funx01(int a, int b = 2,int c);		错误
//int funx02(int a, int b = 2,int c = 2);	正确
int funx1(int a, int b);
void func1(int a, int);			//int此时就是占位参数
void fun(int a, int = 10);
void cx();
void cx(int a, int b);
void cx(int a,double b);
void cx(double b,int a);
void zc(int &a);
//void zc(int a){
//	cout  << endl;
//}		这种也不能和引用一起重载  二义性
void zc(const int &a);
void xc(int a, int b = 1);
void xc(int a);

//函数的实现
int funx1(int a = 20, int b = 10){
	return a + b;
}

//结构体

//主函数
int main11(){
	int &ret = text01();

	cout << "ret = " << ret << endl;	//第一次编译器会保留
	cout << "ret = " << ret << endl;
	
	int &ret2 = text02();				//ret2就是a的别名

	cout << "ret2 = " << ret2 << endl;	
	cout << "ret2 = " << ret2 << endl;

	text02() = 1000;

	cout << "ret2 = " << ret2 << endl;	
	cout << "text02() = " << text02() << endl;
	cout << endl;

	//引用本质(本质是指针常量 目的是为简化指针操作)
	s_func();

	//常量引用
	int a0 = 30;
	/*int & red = 200;  错误 200没有一段合法的内存空间*/
	const int & red = 200;		//加上const后编译器会把它转换为 int t(名称是编译器随机取的 与red同一空间) = 200; const int & red = t;	
	int & res = a0;

	int a1 = 21;
	int a2 = 22;
	showValue1(a1);
	showValue2(a2);

	cout << "a1 = " << a1 << endl;
	cout << "a2 = " << a2 << endl;
	/*showValue1(100);*/
	showValue2(200);
	cout << endl;

	//函数默认参数
	//如果传了数据进去，那么就用传入的数据；如果没有传入数据，那么就用默认值
	int b0 = 1, b1 = 2, b2 = 3;
	int s0 = 0,s1 = 0, s2;
	s0 = funx(b0,b1);
	s1 = funx(b0,b1,b2);
	s2 = funx1();

	cout << "s0 = " << s0 << "  s1 = " << s1  <<  " s2 =  " <<  s2 << endl;

	//函数的占位参数
	//重载中会应用
	int c = 2;
	func1(10,20);		//调用时的填补
	fun(c);
	fun(10,c);
	fun(10);
	KongHang();

	//函数重载
	cx(1,2);
	cx(1,3.14);
	cx(2.1,1);
	cx();
	KongHang();

	//函数重载的注意事项
	//引用作为重载条件 
	int x = 10;			//状态 可读可写
	const int x1 = 10;	//状态 只读不写
	zc(x);
	zc(x1);
	zc(10);
	//函数重载遇到默认参数
	xc(x,10);	
	/*xc(x);*/	//当函数重载遇到默认参数时，会出现二义性（引用和普通变量也会出现二义性）


	system("pause");
	return 0;
}



//函数
int& text01(){
	int a = 10;		//局部变量 存在栈区 函数使用完就释放
	return a;	
}

int& text02(){
	static int a = 20;	//静态变量(可以被修改) 存在全局区 程序完后系统释放
	return a;
}

//引用本质的函数
//输入的变量发现是引用，转换为 int * const ref = &a; 
void func(int &ref){
	ref = 100;		//ref是引用，转换为*ref = 100
}
void s_func(){
	int a = 10;

	//自动转换为int * const ref  = &a；指针常量是指针指向不能修改，也说明了引用（初始化后）不可以更改 
	int &ref = a;
	ref  = 20;		//内部发现ref是引用，自动转换为* ref = 20；

	cout << "a = " << a << endl;
	cout << "ref = " << ref << endl;

	func(a);
	cout << "a = " << a << endl;
	cout << "ref = " << ref << endl;
	cout << endl;
}

//打印数据
void showValue1(int & vue1){
	cout << "a1 = " << vue1 << endl;
	//函数内出现数据的变化，可能会对函数外的数据有影响
	vue1 = 1000;
	cout << "vue1 = " << vue1 << endl;
}
void showValue2(const int & vue){
	//vue = 1000;		在函数内无进行对特定的数据修改
	cout << "vue = " << vue << endl;
}

//函数的默认值
int  funx(int a, int b,int c){
	return a * c + b + c * c;
}
//int funx1(int a = 20, int b = 10){
//	return a + b;
//}  不能放在后面来声明默认函数

//函数的占用参数
void func1(int a, int){
	//占位参数的数据无法获取
	cout << "占位1" << endl;
}
void fun(int a, int){
	//占位参数也能设置默认参数
	cout << "占位2" << endl;
}


void KongHang(){
	cout << endl;
}

//函数重载
void cx(){
	cout << "个数不同的重载！" << endl;
}
void cx(int a, int b){
	cout << "原函数！" << endl;
}
void cx(int a,double b){
	cout << "类型不同的重载！" << endl;
}
void cx(double b,int a){
	cout << "顺序不同的重载！" << endl;
}
//int cx(){	
//}			不能用返回值类型做重载的条件

//函数重载的注意事项
//引用作为重载条件 
void zc(int &a){
	cout << "非const" << endl;
}
void zc(const int &a){
	cout << "const" << endl;
}
//函数重载遇到默认参数
void xc(int a, int b){
	cout << "1" << endl;
}
void xc(int a){
	cout << "2" << endl;
}
