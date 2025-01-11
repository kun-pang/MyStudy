#pragma once		//防止头文件重复
#include <iostream>
#include <fstream>

#include "worker.h"
#include "boss.h"
#include "employee.h"
#include "manger.h"

#define FILENAME "职工人员信息.txt"


using namespace std;

class WorkerManager{
public:
	WorkerManager();

	//展示菜单
	void ShowMeun();

	//退出接口
	void ExitSystem();

	//添加接口
	void Add_Emp();

	//保存文件
	void save();

	//统计文件人数
	int get_EmpNum();

	//初始化员工
	void init_Emp();

	//显示接口
	void Show_Emp();

	//判断文件是否存在该数据
	int IsExist(int id);

	//删除接口
	void Del_Emp();

	//修改接口
	void Mod_Emp();

	//判断文件中编号或者数据是否重复
	int IsChongFu(int id);		//写重复了

	//查找接口
	void Find_Emp();

	//排序接口
	void Sort_Emp();

	//清空文件
	void Clean_Emp();

	~WorkerManager();


	//记录职工人数
	int m_EmpNum;

	//职工数组指针
	//用来存储处虚基类指针
	//使用链表处理更加方便
	Worker ** m_EmpArray;

	//判断文件是否为空的标志
	bool m_FileIsEmpty;
	
};
