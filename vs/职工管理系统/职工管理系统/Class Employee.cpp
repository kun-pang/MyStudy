//员工类
#include "tou.h"

void Employee::Responsibility(){
	cout << "完成经理交给的任务！" << endl;
}

Base* Employee::m_Employee[100] = { nullptr };

void Employee::add(){
	system("cls");

	cout << "请输入员工信息：" << endl;

	for(int i = 0; i < 100; i++){
		if(Employee::m_Employee[i] != nullptr){
			continue;
		}else{
			Employee::m_Employee[i] = new Base;
			cout << "编号：";
			cin >> Employee::m_Employee[i]->m_ID;
			cout << "姓名：";
			cin >> Employee::m_Employee[i]->m_Name;
			Employee::m_Employee[i]->m_Post = "员工";

			
			//询问是否还继续输入数据
			int n = 0;
			cout << "是否继续输入数据：" << endl;
			cout << "1.是" << endl;
			cout << "0.否" << endl;
			cin >> n;
			if(n == 1){
				system("cls");

				cout << "请输入员工信息：" << endl;
			}else{
				system("cls");

				meun();
				return;
			}
		}

	}
}

Employee::~Employee(){
	for(int i = 0; i < 100; i++){
		if(Employee::m_Employee[i] != nullptr){
			delete Employee::m_Employee[i];
			Employee::m_Employee[i] = nullptr;
		}
	}
}

void Employee::display(){
	system("cls");

	cout << "员工信息如下：" << endl;
	for(int i = 0; i < 100; i++){
		if(Employee::m_Employee[i] != nullptr){
			cout << "编号：" << Employee::m_Employee[i]->m_ID << "  ";
			cout << "姓名：" << Employee::m_Employee[i]->m_Name << "  ";
			cout << "岗位：" << Employee::m_Employee[i]->m_Post << "  ";
			cout << "职责：";
			Employee::Responsibility();
			cout << endl;
		}else{
			cout << "之后为空!" << endl;
			system("pause");
			system("cls");

			meun();
			return;
		}
	}
}


void Employee::remove(){
	system("cls");

	int m;

	if(Employee::m_Employee[0] == nullptr){
		cout << "暂无人员信息！" << endl;

		system("pause");
		meun();
		return;
	}

	
	cout << "请输入想要删除人员的编号：" << endl;
	cin >> m;

	bool numOfEmployees = false; 

	for(int i = 0; i < 100; i++){
		if(Employee::m_Employee[i] != nullptr && Employee::m_Employee[i]->m_ID == m){
			delete Employee::m_Employee[i];
			Employee::m_Employee[i] = nullptr;

			for(int j = i; j < 99; j++){
				Employee::m_Employee[j] = Employee::m_Employee[j + 1];
			}

			numOfEmployees = true;
			cout << "删除完毕！" << endl;
			break;
		}

	}

	if (!numOfEmployees) {
		cout << "查无此人！" << endl;
	}

	system("cls");
	meun();
	system("pause");
}


//修改员工
void Employee::modify(int t){
	system("cls");

	if(Employee::m_Employee[0] == nullptr){
		cout << "暂无人员信息！" << endl;

		system("pause");
		meun();
		return;
	}

	int n = 0;			//定义变量
	int m = 0;			//记录与要修改编号一致的位置
	int j = 0;

	for(int i = 0; i < 100; i++){
		if(Employee::m_Employee[i]->m_ID == t){
			m = i;
			cout << "编号：" << Employee::m_Employee[i]->m_ID << "  ";
			cout << "姓名：" << Employee::m_Employee[i]->m_Name << "  ";
			cout << "岗位：" << Employee::m_Employee[i]->m_Post << "  ";
			cout << "职责：";
			Employee::Responsibility();

			delete Employee::m_Employee[i];
			Employee::m_Employee[i] = nullptr;

			for(int j = i; j < 99; j++){
				Employee::m_Employee[j] = Employee::m_Employee[j + 1];
			}

			break;
		}
	}

	//询问是否跟换岗位
	cout << "是否对该工人跟换岗位，如果是，请选择更换的岗位：" << endl;
	cout << "1.更换成老板岗位" << endl;
	cout << "2.更换成经理岗位" << endl;
	cout << "0.不进行更换" << endl;
	cin >> n;
	if(n == 1){
		for(int i = 0; i < 100; i++){
			if(Boss::m_Boss[i] == nullptr){
				cout << "是否对其他信息进行修改：" << endl;
				cout << "1.是" << endl;
				cout << "0.否" << endl;
				cin >> j;
				if(j == 1){
					Boss::m_Boss[i] = new Base;
					cout << "请输入修改的信息：" << endl;
					cout << "编号：" << endl;
					cin >> Boss::m_Boss[i]->m_ID;
					cout << "姓名：" << endl;
					cin >> Boss::m_Boss[i]->m_Name;
					Boss::m_Boss[i]->m_Post = "老板";

					

					break;
				}else{
					Boss::m_Boss[i]->m_ID = Employee::m_Employee[m]->m_ID;
					Boss::m_Boss[i]->m_Name = Employee::m_Employee[m]->m_Name;
					Boss::m_Boss[i]->m_Post = "老板";

					break;
				}
				
			}
		}
	}else if(n == 2){
		for(int i = 0; i < 100; i++){
			if(Manger::m_Manger[i] == nullptr){
				cout << "是否对其他信息进行修改：" << endl;
				cout << "1.是" << endl;
				cout << "0.否" << endl;
				cin >> j;
				if(j == 1){
					Manger::m_Manger[i] = new Base;
					cout << "请输入修改的信息：" << endl;
					cout << "编号：" << endl;
					cin >> Manger::m_Manger[i]->m_ID;
					cout << "姓名：" << endl;
					cin >> Manger::m_Manger[i]->m_Name;
					Manger::m_Manger[i]->m_Post = "经理";

					break;
				}else{
					Manger::m_Manger[i]->m_ID = Employee::m_Employee[m]->m_ID;
					Manger::m_Manger[i]->m_Name = Employee::m_Employee[m]->m_Name;
					Manger::m_Manger[i]->m_Post = "经理";

					break;
				}
				
			}
		}
	}else{
		cout << "请输入要修改的信息：" << endl;
		cout << "编号：" << endl;
		cin >> Employee::m_Employee[m]->m_ID;
		cout << "姓名：" << endl;
		cin >> Employee::m_Employee[m]->m_Name;

	}

	system("cls");
	meun();
	system("pause");
}

//查找员工
void Employee::seek(){
	system("cls");

	if(Employee::m_Employee[0] == nullptr){
		cout << "暂无人员信息！" << endl;

		system("pause");
		meun();
		return;
	}

	int n = 0;
	int m = 0;		//记录查找编号
	string name;	//记录查找姓名

F:
	cout << "想要通过一下那种方式查找：" << endl;
	cout << "1.编号" << endl;
	cout << "2.姓名" << endl;
	cin >> n;

	if(n == 1){
		cout << "请输入要查找的编号：" << endl;
		cin >> m;

		for(int i = 0; i < 100; i++){
			if(Employee::m_Employee[i]->m_ID == m){
				cout << "编号：" << Employee::m_Employee[i]->m_ID << endl;
				cout << "姓名：" << Employee::m_Employee[i]->m_Name << endl;
				cout << "岗位：" << Employee::m_Employee[i]->m_Post << endl;
				Employee::Responsibility();

				break;
			}
		}

	}else{
		cout << "请输入要查找的姓名：" << endl;
		cin >> name;


		for(int i = 0; i < 100; i++){
			if(Employee::m_Employee[i]->m_Name == name){
				cout << "编号：" << Employee::m_Employee[i]->m_ID << "  ";
				cout << "姓名：" << Employee::m_Employee[i]->m_Name << "  ";
				cout << "岗位：" << Employee::m_Employee[i]->m_Post << "  ";
				Employee::Responsibility();
				cout << endl;

				break;
			}
		}
	}

	n = 0;
	cout << "是否还有继续查找:" << endl;
	cout << "1.是" << endl;
	cout << "2.否" << endl;
	cin >> n;

	if(n == 1){
		n = 0;
		goto F;
	}else{
		system("pause");
		system("cls");
		meun();
		return;
	}
}


//对员工排序
void Employee::sort(){
	system("cls");

	if(Employee::m_Employee[0] == nullptr){
		cout << "暂无人员信息！" << endl;

		system("pause");
		meun();
		return;
	}

	int size = sizeof(Employee::m_Employee) / sizeof(Employee::m_Employee[0]);

	for(int i = 0; i < size - 1; i++){
		for(int j = 0; j < size - i - 1; j++){
			if(Employee::m_Employee[j] && Employee::m_Employee[j + 1] && Employee::m_Employee[j]->m_ID > Employee::m_Employee[j + 1]->m_ID){
				Base *temp =  Employee::m_Employee[j];
				Employee::m_Employee[j] = Employee::m_Employee[j + 1];
				Employee::m_Employee[j + 1] = temp;
			}
		}
	}

	cout << "排序完毕！" << endl;
	system("pause");
	system("cls");
	meun();
	return;
}