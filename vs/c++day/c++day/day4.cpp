/*2023—7—15*/
/*程序流程结构 */


/*程序结构
	选择结构	if语句、三目运算符（表达式1？表达式2：表达式3）、switch语句
	嵌套结构	
	循环结构	while语句、do-while语句、for语句
*/

#include <iostream>

using namespace std;

int main4(){
	//do-while 语句  先执行循环语句，在判断
	//在屏幕输出0-9的数字

	int num = 0;

	while(num){
		cout << num << endl;
		num++;
	}				//数字0，为假
	/*do{
		cout << num << endl;
		num++;
	}while( num );  加加以后变成1，即真*/
	cout << endl;
	do{
		cout << num << endl;
		num++;
	}while( num < 10);
	cout << endl;

	//for循环  for循环中间三个可以分在其他地方书写
	//打印数字0-9
	for(int i = 0; i < 10; i++){
		cout << i << endl;
	}
	cout << endl;

	system("pause");

	return 0;
}