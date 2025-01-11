/*2023—7—14*/
/* 猜数字 */

#include <iostream>
#include <cstdlib>		//rand（）函数的头文件
#include <ctime>		//time()的头文件

using namespace std;

//系统提供0-100随机数
//玩家猜数字
//猜错 数字过大或者过小，提醒玩家
//猜对 恭喜玩家
int main3t(){
	double num1;		//系统随机数字
	double num2;		//玩家猜测的数字
	int i = 0;			//用于记录猜测次数
	int head = 0;       //记录范围左边界
	int tail = 100;    //记录范围右边界

	// 设置随机种子
	srand(time(NULL));

	//生成0-100随机数
	num1 = rand()%101;		//rand（）%a  生成0~（a-1）的数据数，rand（）%a+1 生成0+1~a-1+1的随机数
							//注意：rand()函数生成的随机数是伪随机数，
							//每次程序运行时，相同的种子会生成相同的随机数序列。
							//因此，为了获取更好的随机性，通常会使用不同的种子，例如基于时间的种子。
	//获取玩家数值
	cout << "请输入0-100中任意一个数字：" << endl;
	cin >> num2;

	
	//查看答案
	if(num2 == 101){
		cout << num1 << endl;
	}

	//break 可以退出循环
	while(num2 != num1){
		if(num2 > num1){
			cout << "您猜的数字大于正确答案." << endl;
			cout << "请您重新输入" << head << "-" << num2 << "之间的数字:" << endl;  
			tail = num2;
			cin >> num2;
			i++;
		}else{
			cout << "您猜的数字小于正确答案." << endl;
			cout << "请您重新输入" << num2 << "-" << tail << "之间的数字:" << endl;
			head = num2;
			cin >> num2;
			i++;
		}
	}
	cout  << "您在猜测" << i << "次以后成功猜对了！"  << endl;

	system("pause");

	return 0;
}