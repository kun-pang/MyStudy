/*2023—7—12*/
/*变量 常量  关键字 标识符命名规则 数据类型*/

/*变量 创建变量——数据类型 变量名 = 值*/
/*关键字 不可以作为变量名作为名称*/
/*标识符命名规则  
*字母、数字、下划线   
*（标识符）取名不能是关键（关键字） 
*（标识符）第一（字符）只能字母、下划线
*标识会分大小写
*命名方式要规范（见名知意 同行或者上下标识意思）
*/
/*数据类型 
*整型	短整型（short） 整型（int） 长整型（long） 长长整型（long long）
*浮点型(实型)   单精度（float） 双精度（double）
*字符型 char 
*转义字符型 \n \\ \t .....
*字符串型  string char
*布尔类型 bool
*
*/

#include <iostream>			//导入c++的标准库
#include <string>

using namespace std;
/* 
*为了引用c++标准库的命名空间，
*约定成俗的取了一个叫是std名字，
*以方便调取标准库里面的变量，函数等。
*/

#define day 8				//宏常量 全局意义上的常量（不可变的量）

int main1(){
	
	//day = 1;	//报错 无妨改值
	const int month = 2;	//const 修饰的变量 也是常量 局部常量
	/*month = 9；//报错 无法更改*/
	int year = 2023;

	cout << "生日是" << year << "年" <<
		month << "月" << day << "日" << endl;
	/*cout 打印字符   << 左移操作符 进行数据的插入   endl 换行*/
	cout << endl;

	float f1 = 3.14f;		//用f提示一下单精度，否则为双精度
	float f2 = 2e2;			//2 * 10^2
	float f3 = 3e-2;		//3 * 0.1^2
	cout << "f1 = " << f1 << endl;
	cout << "f2 = " << f2 << endl;
	cout << "f3 = " << f3 << endl;
	//cout最多显示6位小数
	cout << endl;
	
	cout << "int 占用空间为" << sizeof(month) << "字节" << endl; 
	cout << "int 占用空间为" << sizeof(int) << "字节" << endl;  
	/*sizeof关键字 计算字符占用的空间  sizeof（数据类型/变量）*/
	cout << endl;

	char ch  =  'a';		//char赋值时，只能用单引号，不能用双引号，且单引号里面只能为一个字母 单个字符
	char ch1 =	'A';
	cout << "ch = " << ch << endl;					//ch获取的时a的ASCII码
	cout << "a的ASCII码为" << (int)ch << endl;	//(int)ch  强转为将ch变量整型 以此来查看a的ASCII码
	cout << "A 的ASCII码为" << (int)ch1 << endl;
	char ch_shuzu[4] = "abc";		//定义了char型数组
	string str1 = "abc";	//string 字符串 在<string>头文件中
	cout << "str1 = " << str1 << endl;
	cout << "ch_shuzu[4]= " << ch_shuzu << endl;
	cout << endl;

	cout << "aaa\n";								// \n 换行
	cout << "\\" << endl;							// \\ 打印“\”
	cout << "aaa \tdsadasdasd"<< endl;				// \t 制表符  有8个空格 大于等于8个字符会在后面空8格出来，多出来的字符在后面8个空格中显示
	cout << "aa \tdsadasdasd"<< endl;
	cout << "aaaaaaaa\tdsadasdasd"<< endl;
	cout << "aaaaaaaaa\tdsadasdasd"<< endl;
	cout << endl;

	bool falg1 = true;								//本质是1  只要是非0的数都代表为真
	bool falg2 = false;								//本质是0
	cout << falg1 << endl;
	cout << falg2 << endl;
	cout << endl;

	int a,b;
	float c;
	cout << "请输入整型a的值：" << endl;
	cin >> a;										//获取键盘上的值
	cout << "a = " << a << endl;
	cout << "请给b,c赋值：" << endl;
	cin >> b >> c;										
	cout << "b = " << b << ";c = " << c << endl;
	cout << endl;

	system("pause");		//获取回车  作用是起一个中顿让小屏幕显示。

	return 0;
}