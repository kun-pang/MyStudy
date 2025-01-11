/*2023-8-8*/

//文件操作

//程序运行是产生的数据都属于临时数，程序一旦运行结束都会被释放

//通过文件将数据持久化

//c++中对文件操作需要包含头文件<fstream>

//文件类型;
//	文本文件 - 文件以文本的ASCll码形式存储在计算机中
//	二进制文件 - 文件以文本的二进制形式存储在计算机中，用户一般不能直接读懂它们

//操作文件的三大类：
//	1、ofstream：写操作
//	2、ifstream：读操作
//	3、fstream：读写操作

//写文件
/*
	1、包含头文件
		#include <fstream>
	2、创建流对象
		ofstream 对象名;		对象名一般为ofs		ofstream也可以换成fstream
	3、打开文件
		ofs.open（“文件路径”，打开方式）；
	4、写数据
		ofs << "写入的数据" ;
	5、关闭文件
		ofs.close（）；
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
#include <fstream>		//1、包含头文件

using namespace std;

void test(){
	//2、创建流对象 
	ofstream ofs;

	//3、打开文件
	//"\"是转义字符  “\\”才表示单斜杠“\”
	ofs.open("唐三.txt",ios::out);
	/*ofs.open("D:\\c++\\vs\\文件操作\\文件操作\\1.txt",ios::out);*/

	//4、写数据
	ofs << "唐三嘶吼着：" << endl;
	ofs << "“复活吧！我的爱人~~”" << endl;

	//5、关闭文件
	ofs.close();
}

int main(){
	test();

	system("pause");
	return 0;
}