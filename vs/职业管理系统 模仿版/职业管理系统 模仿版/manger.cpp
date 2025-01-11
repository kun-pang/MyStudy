#include "manger.h"

Manger::Manger(int id, string name, int did){
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeptID = did;
}

void Manger::showInfo(){
	cout << "职工编号：" << this->m_ID
		<< "\t职工姓名：" << this->m_Name
		<< "\t职工岗位：" << this->getDeptName()
		<< "\t职工职责：完成老板交给的任务，并且下发任务给员工！" << endl;
}

string Manger::getDeptName(){
	return "经理";
}