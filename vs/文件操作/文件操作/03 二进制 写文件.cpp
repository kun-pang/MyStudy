/*2023-8-8*/

//写文件
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

	2、3可以一起写
*/

//二进制方式写文件主要利用流对象调用成员函数write
//函数原型：ostream & write(const char * buffer, int len);
//参数解释：字符指针buffer指向内存中一段存储空间。len是读写的字节数



#include <iostream>

#include <fstream>	//1、包含头文件

using namespace std;

class KUN{
public:
	char m_Name[64];
	double m_Age;
	char m_TeChang[70];
	char m_Ge[100];
};

void test(){
	//2、创建流对象 
	ofstream ofs("蔡徐坤.txt",ios::binary | ios::out);

	//3、打开文件
	
	/*ofs.open("蔡徐坤.txt",ios::binary | ios::out);*/
	
	//4、写数据
	KUN k = {"蔡徐坤", 2.5, "唱、跳、rap、篮球", "鸡你太美！" };
	ofs.write((const char *)&k, sizeof(k));
	/*ofs << endl << "鸡你太美！" << endl;*/
	
	//5、关闭文件
	ofs.close();
}

int main(){
	test();

	system("pause");
	return 0;
}