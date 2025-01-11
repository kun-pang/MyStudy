#include "employee.h"

//可以用初始化列表
Employee::Employee(int id, string name, int did){
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeptID = did;
}

void Employee::showInfo(){
	cout << "职工编号：" << this->m_ID
		<< "\t职工姓名：" << this->m_Name
		<< "\t职工岗位：" << this->getDeptName()
		<< "\t职工职责：完成经理交给的任务！" << endl;
}

string Employee::getDeptName(){
	return "员工";
}