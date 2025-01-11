#include <iostream>				//可以省略，加上的话必须加  #pragma once	
#include "workerManager.h"
#include "worker.h"
#include "boss.h"
#include "employee.h"
#include "manger.h"

using namespace std;

int main(){
	//实例化管理类对象
	WorkerManager wm;

	int n = 0;		//存储用户选择


	while(1){
		wm.ShowMeun();
		cout << endl;
		cout << "请选择功能：" << endl;
		cin >> n;

		switch(n){
		case 0:		//退出系统
			wm.ExitSystem();
			break;
		case 1:		//增加职工
			wm.Add_Emp();
			break;
		case 2:		//显示职工
			wm.Show_Emp();
			break;
		case 3:		//删除职工
			wm.Del_Emp();
			break;
		case 4:		//修改职工
			wm.Mod_Emp();
			break;
		case 5:		//查找职工
			wm.Find_Emp();
			break;
		case 6:		//排序职工
			wm.Sort_Emp();
			break;
		case 7:		//清空职工
			wm.Clean_Emp();
			break;
		default:
			system("cls");
			break;
		}
	}


	system("pause");
	return 0;
}