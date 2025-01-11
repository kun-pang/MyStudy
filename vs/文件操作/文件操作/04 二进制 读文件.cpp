/*2023-8-8*/


//二进制方式读文件主要利用流对象调用成员函数red
//函数原型：istream & read(char * buffer, int len);
//参数解释：字符指针buffer指向内存中一段存储空间。len是读写的字节数

//写怎么定义的数据，读就要有这些定义数据

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
	ifstream ifs("蔡徐坤.txt",ios::binary | ios::in);

	//判断文件是否打开
	if(!ifs.is_open()){
		cout << "文件没有打开" << endl;
		return;
	}
	
	//4、读数据
	KUN k;
	ifs.read((char *)&k, sizeof(k));

	cout << k.m_Name << endl << k.m_Age << endl << k.m_TeChang << endl  << k.m_Ge << endl;
	
	//5、关闭文件
	ifs.close();
}

int main(){
	test();

	system("pause");
	return 0;
}