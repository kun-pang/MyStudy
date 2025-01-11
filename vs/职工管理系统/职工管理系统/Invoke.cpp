//调用函数

#include "tou.h"

void doAdd(Base &base){
	base.add();
}

void doDisplay(Base &base){
	base.display();
}

void doRemove(Base &base){
	base.remove();
}

void doModify(Base &base, int a){
	base.modify(a);
}

void doSeek(Base &base){
	base.seek();
}

void doSort(Base &base){
	base.sort();
}

void empty(){
	system("cls");

	for(int i = 0; i < 100; i++){
		if(Boss::m_Boss[i] != nullptr){
			delete Boss::m_Boss[i];
			Boss::m_Boss[i] = nullptr;
		}
	}

	for(int i = 0; i < 100; i++){
		if(Employee::m_Employee[i] != nullptr){
			delete Employee::m_Employee[i];
			Employee::m_Employee[i] = nullptr;
		}
	}

	for(int i = 0; i < 100; i++){
		if(Manger::m_Manger[i] != nullptr){
			delete Manger::m_Manger[i];
			Manger::m_Manger[i] = nullptr;
		}
	}

	cout << "清除完毕！" << endl;

	system("pause");
	system("cls");
	meun();
	return;

}
