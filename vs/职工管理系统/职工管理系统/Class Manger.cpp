//经理类
#include "tou.h"

void Manger::Responsibility(){
	cout << "完成老板交给的任务，并且下发任务给员工！" << endl;
}

//初始化
Base* Manger::m_Manger[100] = { nullptr };

void Manger::add(){
	system("cls");

	cout << "请输入员工信息：" << endl;

	for(int i = 0; i < 100; i++){
		//判断数组前面是否为存在数据
		if(Manger::m_Manger[i] != nullptr){
			continue;
		}else{
			Manger::m_Manger[i] = new Base;
			cout << "编号：";
			cin >> Manger::m_Manger[i]->m_ID;
			cout << "姓名：";
			cin >> Manger::m_Manger[i]->m_Name;
			Manger::m_Manger[i]->m_Post = "员工";

			
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

Manger::~Manger(){
	for(int i = 0; i < 100; i++){
		if(Manger::m_Manger[i] != nullptr){
			delete Manger::m_Manger[i];
			Manger::m_Manger[i] = nullptr;
		}
	}
}

void Manger::display(){
	system("cls");

	cout << "经理信息如下：" << endl;
	for(int i = 0; i < 100; i++){
		if(Manger::m_Manger[i] != nullptr){
			cout << "编号：" << Manger::m_Manger[i]->m_ID << "  ";
			cout << "姓名：" << Manger::m_Manger[i]->m_Name << "  ";
			cout << "岗位：" << Manger::m_Manger[i]->m_Post << "  ";
			cout << "职责：";
			Manger::Responsibility();
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


void Manger::remove(){
	system("cls");

	int m;

	if(Manger::m_Manger[0] == nullptr){
		cout << "暂无人员信息！" << endl;

		system("pause");
		meun();
		return;
	}

	
	cout << "请输入想要删除人员的编号：" << endl;
	cin >> m;

	bool numOfEmployees = false;

	for(int i = 0; i < 100; i++){
		if(Manger::m_Manger[i] != nullptr && Manger::m_Manger[i]->m_ID == m){
			//`Boss::m_Boss[i]` 并不是指针，而是数组中的一个元素。
			//因此，`delete` 运算符只会销毁数组元素指向的对象，并不会影响数组本身。
			delete Manger::m_Manger[i];
			Manger::m_Manger[i] = nullptr;

			for(int j = i; j < 99; j++){
				Manger::m_Manger[j] = Manger::m_Manger[j + 1];
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
void Manger::modify(int t){
	system("cls");

	if(Manger::m_Manger[0] == nullptr){
		cout << "暂无人员信息！" << endl;

		system("pause");
		meun();
		return;
	}

	int n = 0;			//定义变量
	int m = 0;			//记录与要修改编号一致的位置
	int j = 0;

	for(int i = 0; i < 100; i++){
		if(Manger::m_Manger[i]->m_ID == t){
			m = i;
			cout << "编号：" << Manger::m_Manger[i]->m_ID << "  ";
			cout << "姓名：" << Manger::m_Manger[i]->m_Name << "  ";
			cout << "岗位：" << Manger::m_Manger[i]->m_Post << "  ";
			cout << "职责：";
			Manger::Responsibility();

			delete Manger::m_Manger[i];
			Manger::m_Manger[i] = nullptr;

			for(int j = i; j < 99; j++){
				Manger::m_Manger[j] = Manger::m_Manger[j + 1];
			}

			break;
		}
	}

	//询问是否跟换岗位
	cout << "是否对该工人跟换岗位，如果是，请选择更换的岗位：" << endl;
	cout << "1.更换成员工岗位" << endl;
	cout << "2.更换成老板岗位" << endl;
	cout << "0.不进行更换" << endl;
	cin >> n;
	if(n == 1){
		for(int i = 0; i < 100; i++){
			if(Employee::m_Employee[i] == nullptr){
				cout << "是否对其他信息进行修改：" << endl;
				cout << "1.是" << endl;
				cout << "0.否" << endl;
				cin >> j;
				if(j == 1){
					Employee::m_Employee[i] = new Base;
					cout << "请输入修改的信息：" << endl;
					cout << "编号：" << endl;
					cin >> Employee::m_Employee[i]->m_ID;
					cout << "姓名：" << endl;
					cin >> Employee::m_Employee[i]->m_Name;
					Employee::m_Employee[i]->m_Post = "员工";

					break;
				}else{
					Employee::m_Employee[i]->m_ID = Manger::m_Manger[m]->m_ID;
					Employee::m_Employee[i]->m_Name = Manger::m_Manger[m]->m_Name;
					Employee::m_Employee[i]->m_Post = "员工";

					break;
				}
				
			}
		}
	}else if(n == 2){
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
					Boss::m_Boss[i]->m_ID = Manger::m_Manger[m]->m_ID;
					Boss::m_Boss[i]->m_Name = Manger::m_Manger[m]->m_Name;
					Boss::m_Boss[i]->m_Post = "老板";

					break;
				}
				
			}
		}
	}else{
		cout << "请输入要修改的信息：" << endl;
		cout << "编号：" << endl;
		cin >> Manger::m_Manger[m]->m_ID;
		cout << "姓名：" << endl;
		cin >> Manger::m_Manger[m]->m_Name;

	}

	system("cls");
	meun();
	system("pause");
}

//查找员工
void Manger::seek(){
	system("cls");

	if(Manger::m_Manger[0] == nullptr){
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
			if(Manger::m_Manger[i]->m_ID == m){
				cout << "编号：" << Manger::m_Manger[i]->m_ID << endl;
				cout << "姓名：" << Manger::m_Manger[i]->m_Name << endl;
				cout << "岗位：" << Manger::m_Manger[i]->m_Post << endl;
				Manger::Responsibility();

				break;
			}
		}

	}else{
		cout << "请输入要查找的姓名：" << endl;
		cin >> name;


		for(int i = 0; i < 100; i++){
			if(Manger::m_Manger[i]->m_Name == name){
				cout << "编号：" << Manger::m_Manger[i]->m_ID << "  ";
				cout << "姓名：" << Manger::m_Manger[i]->m_Name << "  ";
				cout << "岗位：" << Manger::m_Manger[i]->m_Post << "  ";
				Manger::Responsibility();
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
void Manger::sort(){
	system("cls");

	if(Manger::m_Manger[0] == nullptr){
		cout << "暂无人员信息！" << endl;

		system("pause");
		meun();
		return;
	}

	int size = sizeof(Manger::m_Manger) / sizeof(Manger::m_Manger[0]);

	for(int i = 0; i < size - 1; i++){
		for(int j = 0; j < size - i - 1; j++){
			if(Manger::m_Manger[j] && Manger::m_Manger[j + 1] && Manger::m_Manger[j]->m_ID > Manger::m_Manger[j + 1]->m_ID){
				Base *temp = Manger::m_Manger[j];
				Manger::m_Manger[j] = Manger::m_Manger[j + 1];
				Manger::m_Manger[j + 1] = temp;
			}
		}
	}

	cout << "排序完毕！" << endl;
	system("pause");
	system("cls");
	meun();
	return;
}