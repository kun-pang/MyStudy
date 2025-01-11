//管理类 主要回应用户操作  实现对文件的控制


#include "workerManager.h"

WorkerManager::WorkerManager(){
	ifstream ifs;
	ifs.open(FILENAME, ios::in);	//读文件

	//文件不存在
	if(!ifs.is_open()){
		cout << "文件不存在！" << endl;

		//初始化属性
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件为空
	//通过是否到文件末尾，来判断数据是否为空
	char ch;
	ifs >> ch;
	if(ifs.eof()){
		cout << "文件为空！" << endl;
		//初始化属性
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}


	//文件存在，也记录数据
	int num = this->get_EmpNum();
	cout << "职工人数:" << num <<  endl;
	this->m_EmpNum = num;

	//开辟空间
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//将文件中的数据，放入数组中
	this->init_Emp();
	this->m_FileIsEmpty = false;

	ifs.close();
}

void WorkerManager::ShowMeun(){
	cout << "******************************" << endl;
	cout << "*****欢迎使用职工管理系统*****" << endl;
	cout << "******************************" << endl;	
	cout << "******* 0.退出管理程序 *******" << endl;	
	cout << "******* 1.增加职工信息 *******" << endl;
	cout << "******* 2.显示职工信息 *******" << endl;
	cout << "******* 3.删除离职职工信息 ***" << endl;
	cout << "******* 4.修改职工信息 *******" << endl;
	cout << "******* 5.查找职工信息 *******" << endl;	
	cout << "******* 6.按照编号排序 *******" << endl;	
	cout << "******* 7.清空所有文档 *******" << endl;	
	cout << "******************************" << endl;	
}


void WorkerManager::ExitSystem(){
	cout << "欢迎使用本系统！" << endl;
	system("pause");
	exit(0);
}


void WorkerManager::Add_Emp(){
	cout << "请输入添加人数：" << endl;

	//保存用户输入的数量
	int addNum = 0;

	cin >> addNum;

	//判断输入的人数是否有效
	if(addNum > 0){
		//添加
		//计算总人数（需要开辟空间大小）
		int newSize = addNum + this->m_EmpNum;		//新添加人数 + 已经存储的人数

		//开辟新空间
		Worker ** newSpace = new Worker*[newSize];

		//将原来的数据拷贝到新数组中
		if(this->m_EmpArray != NULL){
			for(int i = 0; i < this->m_EmpNum; i++ ){
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//添加新数据
		F:for(int i = 0; i < addNum; i++){
			int id;//职工编号
			string name;//职工姓名
			int dSelect; //岗位编号

			cout << "请输入第" << i + 1 << "个新员工编号；"  << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个新员工姓名；"  << endl;
			cin >> name;
			cout << "请输入第" << i + 1 << "个新员工岗位；"  << endl;
			cout << "1、老板" << endl;
			cout << "2、经理" << endl;
			cout << "3、员工" << endl;
			cin >> dSelect;

			//判断添加的数据是否已经存在
			int red = this->IsChongFu(id);

			if(red == -1){
				Worker * worker = NULL;

				switch(dSelect){
				case 1:
					worker = new Boss(id, name, 1);
					break;
				case 2:
					worker = new Manger(id, name, 2);
					break;
				case 3:
					worker = new Employee(id, name, 3);
					break;
				default:
					break;
				}

				//将创建的职工保存到数组中
				newSpace[this->m_EmpNum + i] = worker;
			}else{
				cout << "请重新输入：" << endl;
				goto F;
			}
		}

		//释放原有的空间(加[]是因为释放的是数组)
		delete[] this->m_EmpArray;

		//更改空间指向
		this->m_EmpArray = newSpace;

		//更改新空间人数
		this->m_EmpNum = newSize;
		this->m_FileIsEmpty = false;

		cout << "添加成功" << addNum << "名新员工!" << endl;

		//保存文件
		this->save();
	
	}else{
		cout << "输入有误！" << endl;
	}

	//按任意键清屏
	system("pause");
	system("cls");
}

void WorkerManager::save(){
	ofstream ofs;
	ofs .open(FILENAME, ios::out);		//写文件的形式打开

	//将数组中的数据写入
	for(int i = 0; i < this->m_EmpNum; i++){
		ofs << this->m_EmpArray[i]->m_ID << "\t"
			<< this->m_EmpArray[i]->m_Name << "\t"
			<< this->m_EmpArray[i]->m_DeptID << endl;
	}

	//关闭文件
	ofs.close();
}

int WorkerManager::get_EmpNum(){
	ifstream ifs;
	ifs.open(FILENAME, ios::in);	//读文件

	int id;
	string name;
	int did;

	int num = 0;

	while(ifs >> id && ifs >> name && ifs >> did){
		num++;
	}


	return num;

}

void WorkerManager::init_Emp(){
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	
	int id;
	string name;
	int did;

	int index = 0;

	while(ifs >> id && ifs >> name && ifs >> did){
		
		Worker *woker = NULL;
		switch(did){
		case 1:	//老板
			woker = new Boss(id, name, did);
			break;
		case 2://员工
			woker = new Employee(id, name, did);
			break;
		case 3://经理
			woker = new Manger(id, name, did);
			break;
		}
		this->m_EmpArray[index] = woker;

		index++;

	}
	ifs.close();
}

void WorkerManager::Show_Emp(){
	//判断 文件是否存在 或者 存在但是数据是否为空
	if(this->m_FileIsEmpty){
		cout << "文件不存在或者文件为空！" << endl;
	}else{
		for(int i = 0; i < this->m_EmpNum; i++){
			//利用多态
			this->m_EmpArray[i]->showInfo();
		}
	}

	system("pause");
	system("cls");
}

int WorkerManager::IsExist(int id){
	int index = -1;

	for(int i = 0; i < this->m_EmpNum; i++){
		if(this->m_EmpArray[i]->m_ID == id){
			index = i;
			break;
		}
	}

	return index;
}

void WorkerManager::Del_Emp(){
	if(this->m_FileIsEmpty){
		cout << "文件不存在或者文件为空！" << endl;
	}else{
		cout << "请输入想要删除的职工的编号：" << endl;
		int id;
		cin >> id;

		int index = -1;
		index = this->IsExist(id);
		
		if(index != -1){
			for(int i = 0; i < this->m_EmpNum; i++){
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;

			this->save();
			cout << "删除成功！" << endl;
		}else{
			cout << "该编号的员工不存在!" << endl;
		}
		
	}

	system("pause");
	system("cls");
}

void WorkerManager::Mod_Emp(){
	if(this->m_FileIsEmpty){
		cout << "文件不存在或者文件为空！" << endl;
	}else{
		cout << " 请输入想要修改职工的编号："<< endl;
		int id;
		cin >> id;

		int index = this->IsExist(id);

		if(index != -1){
			int newId;
			string name;
			int dSelect = 0;

			delete this->m_EmpArray[index];

			cout << "请修改编号为" << id << "的职工信息"<< endl;
			cout << "编号：" << endl;
			cin >> newId;

			cout << "姓名：" << endl;
			cin >> name;

			cout << "岗位：" << endl;
			cout << "1、老板" << endl;
			cout << "1、经理" << endl;
			cout << "1、员工" << endl;
			cin >> dSelect;

			Worker *worker = NULL;
			switch(dSelect){
			case 1:
				worker = new Boss(newId, name, dSelect);
				break;
			case 2:
				worker = new Manger(newId, name, dSelect);
				break;
			case 3:
				worker = new Employee(newId, name, dSelect);
				break;
			}

			this->m_EmpArray[index] = worker;

			this->save();

			cout << "修改成功！" << endl;

		}else{
			cout << "修改失败，查无此人！" << endl;
		}

	}

	system("pause");
	system("cls");
}

int WorkerManager::IsChongFu(int id){
	int red = -1;
	
	//不存在
	if(this->m_FileIsEmpty){
		return red;
	}else{//存在
		for(int i = 0; i < this->m_EmpNum; i++){
			if(this->m_EmpArray[i]->m_ID == id ){
				cout << "编号重复！" << endl;
				red = 1;
				return red;
			}else{
				return red;
			}
		}
	}
	
}

void WorkerManager::Find_Emp(){
	if(this->m_FileIsEmpty){
		cout << "文件不存在 或者 文件为空！" << endl;
	}else{
		cout << "请输入查找方式：" << endl;
		cout << "1、编号查找" << endl;
		cout << "2、姓名查找" << endl;

		int select = 0;
		cin >> select;

		if(select == 1){
			int id;
			cout << "请输入查找的职工编号:" << endl;
			cin >> id;

			int red = this->IsExist(id);
			if(red != -1){
				cout << "查找成功，信息如下：" << endl;
				this->m_EmpArray[red]->showInfo();
			}else{
				cout << "查找失败，查无此人！" << endl;
			}
		}else if(select == 2){
			string name;
			cout << "请输入查找的职工姓名:" << endl;
			cin >> name;

			//判断文件是否存在该姓名
			bool flag = false;
			for(int i = 0; i < this->m_EmpNum; i++){
				if(this->m_EmpArray[i]->m_Name == name){
					this->m_EmpArray[i]->showInfo();

					flag = true;
				}
			}

			if(!flag){
				cout << "不存在该姓名的员工！" << endl;
			}

		}else{
			cout << "输入有误！" << endl;
		}
	}
	
	system("pause");
	system("cls");
}

void WorkerManager::Sort_Emp(){
	if(this->m_FileIsEmpty){
		cout << "文件不存在 或者 文件为空！" << endl;
		system("pause");
		system("cls");
	}else{
		cout << "请输入想要排序的方式：" << endl;
		cout << "1、升序" << endl;
		cout << "2、降序" << endl;

		int select = 0;
		cin >> select;

		//利用选择排序的方式
		for(int i = 0; i < this->m_EmpNum; i++){
			int minOrMax = i;		//先认定 最大值 或者 最小值 是当前的下标
			
			for(int j = i + 1; j < this->m_EmpNum; j++){
				if(select == 1){	//升序
					if(this->m_EmpArray[minOrMax]->m_ID > this->m_EmpArray[j]->m_ID){
							minOrMax = j;
					}
				}else{				//降序
					if(this->m_EmpArray[minOrMax]->m_ID < this->m_EmpArray[j]->m_ID){
							minOrMax = j;
					}
				}
			}
			

			//每次外层循环总能把 最大值 或者 最小值 位置固定在数组前面
			if(minOrMax != i){
				Worker * t = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = t;
			}
		}

		cout << "排序成功！" << endl;
		this->Show_Emp();
		this->save();

	}
}

void WorkerManager::Clean_Emp(){
	cout << "是否清空文件：" << endl;
	cout << "1、是" << endl;
	cout << "0、否" << endl;

	int select = 0;
	cin >> select;

	if(select == 1){
		//删除文件重建
		ofstream ofs(FILENAME, ios::trunc); 
		ofs.close();

		if(this->m_EmpArray != NULL){
			//删除堆区每个职工对象
			for(int i = 0; i < this->m_EmpNum; i++){
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//删除堆区数组指针
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;

		}

		cout << "清空成功！" << endl;
	}

	system("pause");
	system("cls");
}


WorkerManager::~WorkerManager(){
	if(this->m_EmpArray != NULL){
			//删除堆区每个职工对象
			for(int i = 0; i < this->m_EmpNum; i++){
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//删除堆区数组指针
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
		}
}