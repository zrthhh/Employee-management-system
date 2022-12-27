#pragma once
#include<iostream>
#include"worker.h"
using namespace std;
#include<fstream>
#define FILENAME "empFile.txt"



class WorkerManager
{
public:
	WorkerManager();

	//展示菜单
	void show_Menu();

	//退出系统
	void ExitSystem();

	//增加职工
	void Add_Emp();

	//信息保存到文件中
	void save();

	//统计人数
	int get_EmpNum();

	//初始化员工
	void init_Emp();

	//显示职工
	void Show_Emp();

	//删除职工
	void Del_Emp();

	//查看职工是否存在
	int IsExist(int id);

	//修改职工信息
	void Mod_Emp();

	//查找职工
	void Find_Emp();

	//排序职工
	void Sort_Emp();

	//清空文件
	void Clean_File();


	~WorkerManager();

	//记录文件中人的个数
	int m_EmpNum;

	//员工数组的指针
	Worker** m_EmpArray;

	//标志文件是否为空
	bool m_FileIsEmpty;
};
