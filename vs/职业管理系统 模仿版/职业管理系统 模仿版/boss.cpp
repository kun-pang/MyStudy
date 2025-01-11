#include "boss.h"

Boss::Boss(int id, string name, int did){
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeptID = did;
}

void Boss::showInfo(){
	cout << "职工编号：" << this->m_ID
		<< "\t职工姓名：" << this->m_Name
		<< "\t职工岗位：" << this->getDeptName()
		<< "\t职工职责：管理公司所有业务！" << endl;
}

string Boss::getDeptName(){
	return "老板";
}