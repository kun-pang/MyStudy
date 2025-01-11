/*2023-8-8*/

//读文件
/*
	1、包含头文件
		#include <fstream>
	2、创建流对象
		ifstream 对象名;		对象名一般为ifs		ifstream也可以换成fstream
	3、打开文件并判断文件是否打开成功
		ifs.open（“文件路径”，打开方式）；
	4、读数据
		四种读数据方式
	5、关闭文件
		ifs.close（）；
*/

//文件打开方式
/*
		打开方式			解读
		ios::in				为读文件而打开文件
		ios::out			为写文件而打开文件
		ios::ate			初始位置：文件尾 （打开文件末尾）
		ios::app			追加方式写文件
		ios::trunc			如果文件存在先删除，再创建
		ios::binary			二进制方式

		注意：文件打开方式可以配合使用，利用|操作符
		例如：用二进制方式写文件 ios::binary | ios::out
*/

#include <iostream>
#include <string>
#include <fstream>		//1、包含头文件

using namespace std;

void test(){
	//2、创建流对象 
	ifstream ifs;

	//3、打开文件
	
	ifs.open("唐三.txt",ios::in);
	
	//判断文件是否读取成功
	//is_open()返回的是布尔类型
	if(!ifs.is_open()){
		cout << "文件为没有打开成功！" << endl;
		return;
	}

	//4、读数据
	
	//第一种
	//char buf[1024] = { 0 };		//全部初始为0
	////一行一行的读进buf数组中 读完之后会返回false
	////输出是不是一行一行的输出，所以需要endl
	//while(ifs >> buf){
	//	cout << buf << endl;
	//}

	//第二种
	//char buf[1024] = { 0 };
	////ifstream的成员函数getline 需要获取存储字符的指针 以及大小
	//while(ifs.getline(buf, sizeof(buf))){
	//	cout << buf << endl;
	//}

	//第三种
	//string c;
	////全局函数getline  需要获取文件对象 以及字符串名
	//while(getline(ifs, c)){
	//	cout << c << endl;
	//}

	//第四种（不推荐）
	//一个字符一个字符的读取
	char c;
	while((c = ifs.get()) != EOF){		//EOF  end of file  文件末尾
		cout << c ;
	}

	//5、关闭文件
	ifs.close();
}

int main(){
	test();

	system("pause");
	return 0;
}