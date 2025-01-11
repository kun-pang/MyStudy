/*2023—7—14*/
/*程序流程结构 */


/*程序结构
	选择结构	if语句、三目运算符（表达式1？表达式2：表达式3）、switch语句
	嵌套结构	
	循环结构	while语句
*/

#include <iostream>

using namespace std;

int main3(){
	//三目运算符
	//num1 大于 num2 则输出num1 否则输出num2 
	int num1 = 1;
	int num2 = 2;
	int num0 = 0;
	num0 = (num1 > num2 ? num1 : num2);
	(num1 < num2 ? num1 : num2) = 10;		//在c++中三目运算符返回的变量，可以继续赋值
	cout << "num0 = " << num0 << endl;
	cout << "num1 = " << num1 << endl;
	cout << "num2 = " << num2 << endl;
	cout << endl;

	//switch语句  只能判断整型、枚举类型、字符型，不能判断区间和小数
	//电影打分
	//10-9 经典
	//8-7 非常好
	//6-5 不错
	//5-0 烂片
	int score;		//分数
	cout << "请给《八角笼中》打分！" << endl;
	cin >> score;
	switch(score){
	case 10:
		cout << "您认为这是一个经典的电影！" << endl;
		break;		//退出这个分支 如果没有将会继续执行
	case 9:
		cout << "您认为这是一个经典的电影！" << endl;
		break;
	case 8:
		cout << "您认为这是一个非常好的电影！" << endl;
		break;
	case 7:
		cout << "您认为这是一个非常好的电影！" << endl;
		break;
	case 6:
		cout << "您认为这是一个不错的电影！" << endl;
		break;
	case 5:
		cout << "您认为这是一个不错的电影！" << endl;
		break;
	default:
		cout << "您认为这是一个烂片！" << endl;
		break;
	}
	switch((num1 > num2 ? num2 : num1)){
	case 2:
		cout << "三目运算符+switch" << endl;
	}
	cout << endl;

	//while语句  避免括号里的条件让语句死循环
	//打印0-9数字到屏幕上
	int num3 = 9;
	while(num3 >= 0){
		cout << num3 << "  ";
		num3--;
	}
	cout << endl;

	system("pause");

	return 0;
}