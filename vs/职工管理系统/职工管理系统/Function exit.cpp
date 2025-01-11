//退出功能

#include "tou.h"

void exit(){

	system("cls");

	int z;		//控制变量
	cout << "是否退出程序" << endl;
	cout << "1. 是" << endl;
	cout << "2. 否" << endl;
s:
	cin >> z;

	if(z == 1){
		cout << "欢迎下次使用！" << endl;
		return;				
	}else if(z == 2){
		system("cls");

		meun();
	}else{
		cout << "无法识别用户操作！" << endl;
		cout << "请重新操作！" << endl;
		goto s;
	}

}