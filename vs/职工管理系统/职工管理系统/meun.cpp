//菜单函数

#include "tou.h"

void meun(){
	int m;		//选择变量
	int n = 0;
	int a = 0;
	//实例化类
	Boss b;
	Employee e;
	Manger ma;

	cout << "******************************" << endl;
	cout << "******* 1.增加职工信息 *******" << endl;
	cout << "******* 2.显示职工信息 *******" << endl;
	cout << "******* 3.删除离职职工信息 ***" << endl;
	cout << "******* 4.修改职工信息 *******" << endl;
	cout << "******* 5.查找职工信息 *******" << endl;	
	cout << "******* 6.按照编号排序 *******" << endl;	
	cout << "******* 7.清空所有文档 *******" << endl;	
	cout << "******* 0.退出管理程序 *******" << endl;	
	cout << "******************************" << endl;	
	
	cout<< endl;
	cout << "请选择功能：" << endl;
	cin >> m;

	switch(m){
	case 1:

		cout << "想增加的岗位：" << endl;
		cout << "1.老板" << endl;
		cout << "2.经理" << endl;
		cout << "3.员工" << endl;
		cin >>n;

		if(n == 1){
			doAdd(b);
		}else if(n == 2){
			doAdd(ma);
		}else if(n == 3){
			doAdd(e);
		}else{
			cout << "输入无效！" << endl;

			system("cls");

			meun();
		}

		break;
	case 2:
		n = 0;
		cout << "想查看的岗位：" << endl;
		cout << "1.老板" << endl;
		cout << "2.经理" << endl;
		cout << "3.员工" << endl;
		cin >>n;

		if(n == 1){
			doDisplay(b);
		}else if(n == 2){
			doDisplay(ma);
		}else if(n == 3){
			doDisplay(e);
		}else{
			cout << "输入无效！" << endl;

			system("cls");

			meun();
		}
		break;
	case 3:
		n = 0;
		cout << "想删除的岗位人员：" << endl;
		cout << "1.老板" << endl;
		cout << "2.经理" << endl;
		cout << "3.员工" << endl;
		cin >>n;

		if(n == 1){
			doRemove(b);
		}else if(n == 2){
			doRemove(ma);
		}else if(n == 3){
			doRemove(e);
		}else{
			cout << "输入无效！" << endl;

			system("cls");

			meun();
		}

		break;
	case 4:
		n = 0;
		cout << "想删除的岗位人员：" << endl;
		cout << "1.老板" << endl;
		cout << "2.经理" << endl;
		cout << "3.员工" << endl;
		cin >> n;

		cout << "请输入想要修改的编号：" << endl;
		cin >> a;


		if(n == 1){
			doModify(b,a);
		}else if(n == 2){
			doModify(ma,a);
		}else if(n == 3){
			doModify(e,a);
		}else{
			cout << "输入无效！" << endl;

			system("cls");

			meun();
		}
		break;
	case 5:
		n = 0;
		cout << "想查找的岗位人员：" << endl;
		cout << "1.老板" << endl;
		cout << "2.经理" << endl;
		cout << "3.员工" << endl;
		cin >>n;

		if(n == 1){
			doSeek(b);
		}else if(n == 2){
			doSeek(ma);
		}else if(n == 3){
			doSeek(e);
		}else{
			cout << "输入无效！" << endl;

			system("cls");

			meun();
		}
		break;
	case 6:
		n = 0;
		cout << "想排序的岗位人员：" << endl;
		cout << "1.老板" << endl;
		cout << "2.经理" << endl;
		cout << "3.员工" << endl;
		cin >>n;

		if(n == 1){
			doSort(b);
		}else if(n == 2){
			doSort(ma);
		}else if(n == 3){
			doSort(e);
		}else{
			cout << "输入无效！" << endl;

			system("cls");

			meun();
		}
		break;

	case 7:
		empty();
		break;
	case 0:
		exit();
		break;
	default:
		cout << "输入无效！" << endl;
		return;
	}
}
