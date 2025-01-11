/*2023—7—24*/
/*函数的分文件编写 指针*/

/*函数的分文件编写 
1、创建一个.h的头文件
2、创建一个.cpp的源文件
3、在头文件中声明函数
4、在源文件中定义函数	
*/

//指针
//	定义： 存储地址信息   
//	定义方式：数据类型 * 指针变量名

//空指针
//	指向内存中编号为0的空间
//	用于初始化指针变量
//	空指针指向的内存是不可以访问的

//野指针
//	指向非法的内存空间

//const修饰指针
//	修饰指针，常量指针
//	修饰常量，指针常量
//	即修饰指针，又修饰常量

	//指针与数组
	//	利用指针访问数组中的元素



#include <iostream>
#include "day_8.h"

using namespace std;

int main8(){
	//函数的分文件书写
	int a = 10;
	int b = 20;
	swap_1(a, b);
	cout << endl;

	//指针的定义
	int *p;
	//p指针记录a的地址
	p = &a;
	cout << "p的内容：" << p << endl;
	cout << "a的地址：" << &a << endl;
	cout << "p的地址：" << &p << endl;

	//指针的初步使用
	//解指针（获取指针指向的内存空间）的使用
	*p = a;
	cout << "p指针指向的内存空间：" << *p << endl;
	cout << endl;


	//指针所占内存空间
	//windows 32位操作系统  占4个字节   64位操作系统  占8个字节
	cout << "sizeof(int *) = " << sizeof(int *) << endl;
	cout << "sizeof(p) = " << sizeof(p) << endl;
	cout << "sizeof(double *) = " << sizeof(double *) << endl;
	cout << "sizeof(float *) = " << sizeof(float *) << endl;
	cout << "sizeof(char *) = " << sizeof(char *) << endl;
	cout << endl;

	//空指针
	//c++中null必须大写，因为c++有着严格的大小写定义
	//`null`不是C++语言的关键字或预定义标识符
	//在C++11标准引入之前，通常使用`int * p = NULL;`来将指针初始化为空指针。NULL是一个宏定义，被定义为整数常量0。
	//然而，C++11引入了nullptr关键字，它是一个特殊的空指针常量。
	//使用nullptr可以提供更好的类型安全性，因为它可以被隐式地转换为任何类型的指针。
	//因此，建议使用`int * p = nullptr;`来初始化空指针
	int * x = NULL;
	/* cout << *x << endl; */
	/* * x = 100; */
	//0-255为系统占用空间，不允许访问
	cout << endl;

	//野指针
	//int *z;		//未初始化或者未指明地址
	//*z = 10;	//直接赋值
	//int *p = (int *)0x1100;		//指向的地址非自己声明的

	//const
	char C = 'c';		//假设为去往c景点的旅游路线C
	char D = 'd';		//假设为去往d景点的旅游路线D
	//const修饰指针  常量指针  （旅行团）
	//指针指向（路线）可以修改，指针指向的值（一条路线的目的地）不可以修改
	/*char const *zc = &C;*/
	const char *zc = &C;	//初始化是选择c景点的旅游路线C
	cout << "zc = " << *zc << endl;
	zc = &D;	//指针指向可以修改  更改成选择去往d景点的旅游路线D
	cout << "zc = " << *zc << endl;
	/**zc = 'e';*/	//指针指向的值不可以修改 无法将C路线的目的地更改为e景点
	
	//const修饰常量  指针常量	（自驾游）
	//指针指向（路线）不可以修改，指针指向的值（一条路线的目的地）可以修改
	char * const zd = &D;	//初始化是选择d景点的旅游路线D
	cout << "zd = " << *zd << endl;
	*zd = 'e';		//指针指向的值可以修改 更改成去往e景点的旅游路线D
	cout << "zd = " << *zd << endl;
	/*zd = &C;*/	//指针指向不可以修改  无法将D路线更改为其他路线

	//指针、常量都修饰
	//指针指向的值与指针的指向都不可以更改
	cout << "D = " << D << endl;	//指针修改值是直接修改目的地的值 与前面的普通变量值的修改有区别
	const char * const zz = &D;
	cout << "zz = " << *zz << endl;
	/**zz = 'e';	
	zz = &C;*/
	cout << endl;

	//指针与数组
	int arr[10] = {0,1,2,3,4,5,6,7,8,9};
	int *cq = arr;	//指向的是数组的首地址

	cout << "第三个元素：" << *(cq + 2) << endl; 
	//遍历数组
	for(int i = 0; i < 10; i++){
		cout << "第" << i+1 << "个元素:" << *(cq + i) << endl;
		cout << "第" << i+1 << "个元素:" << cq[i] << endl;
	}
	cout << endl;

	//值传递(不会修改实参)
	int a0 = 10;
	int a1 = 20;
	swap01(a0, a1);
	cout << "a0 = " << a0 << endl;
	cout << "a1 = " << a1 << endl;
	//地址传递(会修改实参)
	swap02(&a0, &a1);
	cout << "地址传递之后 a0 = " << a0 << endl;
	cout << "地址传递之后 a1 = " << a1 << endl;
	cout << endl;

	////获取数组个数
	//int x0 = 1;
	//int *maoPao = new int[x0];	//动态数组

	//cout << "请输入数组的长度：" << endl;
	//cin >> x0;

	////获取数组的数值
	//cout << "请输入长度为" << x0 <<"的数组：" << endl;
	//for(int i = 0; i < x0; i++){
	//	cin >> maoPao[i];
	//}

	////调用冒泡排序的自定义函数
	//MaoPao01(x0, maoPao);

	system("pause");

	return 0;
}