#include"workerManager.h"
#include"boss.h"
#include"employee.h"
#include"manager.h"
#include"worker.h"



WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//文件不存在情况
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}

	//文件存在，判断是否为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空！" << endl;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}

	//文件存在，不为空
	int num = this->get_EmpNum();
	cout << "职工人数为：" << num << endl;
	this->m_EmpNum = num;

	this->m_EmpArray = new Worker * [num];
	this->init_Emp();
	
}

WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
			}
		}

		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}

void WorkerManager::show_Menu()
{
	cout << "********************************" << endl;
	cout << "*****欢迎使用职工管理系统！*****" << endl;
	cout << "******** 0.退出管理系统 ********" << endl;
	cout << "******** 1.增加职工信息 ********" << endl;
	cout << "******** 2.显示职工信息 ********" << endl;
	cout << "******** 3.删除离职职工 ********" << endl;
	cout << "******** 4.修改职工信息 ********" << endl;
	cout << "******** 5.查找职工信息 ********" << endl;
	cout << "******** 6.按照编号排序 ********" << endl;
	cout << "******** 7.清空所有文档 ********" << endl;
	cout << "********************************" << endl;
	cout << endl;
}

void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();
}


void WorkerManager::Add_Emp()
{
	cout << "请输入增加职工数量:" << endl;
	int addNum = 0;
	cin >> addNum;

	if (addNum > 0)
	{
		//计算新空间大小
		int newSize = this->m_EmpNum + addNum;

		//开辟新空间
		Worker** newSpace = new Worker * [newSize + 4];

		//将原空间内容放到新空间下
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//输入新数据
		for (int i = 0; i < addNum; i++)
		{
			int m_id;
			string m_name;
			int m_dSelect;

			cout << "请输入第" << i + 1 << "个职工编号:" << endl;
			cin >> m_id;

			cout << "请输入第" << i + 1 << "个新职工姓名:" << endl;
			cin >> m_name;

			cout << "请输入该职工岗位:" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> m_dSelect;

			Worker* worker = NULL;
			switch (m_dSelect)
			{
			case 1://普通员工
				worker = new Employee(m_id, m_name, 1);
				break;
			case 2://经理
				worker = new Manager(m_id, m_name, 2);
				break;
			case 3://老板
				worker = new Boss(m_id, m_name, 3);
				break;
			default:
				break;
			}
			newSpace[this->m_EmpNum + i] = worker;
		}
		//释放原有空间
		delete[] this->m_EmpArray;

		//更改新空间的指向
		this->m_EmpArray = newSpace;

		//更新职工人数
		this->m_EmpNum = newSize;

		//更新职工不为空的标志
		this->m_FileIsEmpty = false;

		//提示信息
		cout << "成功添加" << addNum << "名新职工!" << endl;

		//保存到文本
		this->save();
	}
	else
	{
		cout << "输入有误" << endl;
	}
	system("pause");
	system("cls");
}

int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int did;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		num++;
	}
	return num;
}

void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int did;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		Worker* worker = NULL;
		//根据不同部门id创建不同对象
		if (did == 1) {
			worker = new Employee(id, name, did);
		}
		else if (did == 2) {
			worker = new Manager(id, name, did);
		}
		else {
			worker = new Boss(id, name, did);
		}
		//存放在数组中
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}


void WorkerManager::Show_Emp()
{
	//判读文件是否为空
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//利用多态调用程序接口
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

int WorkerManager::IsExist(int id)
{
	int index = -1;
	
	for (int i = 0; i < this->m_EmpNum; i++) {
		if (this->m_EmpArray[i]->m_Id == id) {
			index = i;
			break;
		}
	}
	return index;
}


void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		//按照职工编号删除
		cout << "请输入想要删除的职工编号" << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1) {
			//数据前移
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;
			this->save();
			cout << "删除成功" << endl;
		}
		else {
			cout << "查找失败，未找到该职工" << endl;
		}
	}
	system("pause");
	system("cls");
}


void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入修改职工编号" << endl;
		int id;
		cin >> id;

		int index = this->IsExist(id);
		if (index != -1)
		{
			//查找到编号的职工
			delete this->m_EmpArray[index];
			int newid = 0;
			string newname;
			int dSelect;
			cout << "查找：" << id << "号职工，请输入新的职工号：" << endl;
			cin >> newid;

			cout << "请输入新姓名：" << endl;
			cin >> newname;

			cout << "请输入岗位：" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newid, newname, dSelect);
				break;
			case 2:
				worker = new Manager(newid, newname, dSelect);
				break;
			case 3:
				worker = new Boss(newid, newname, dSelect);
				break;
			default:
				break;
			}
			//更新数据到数组
			this->m_EmpArray[index] = worker;
			cout << "修改成功" << endl;

			//保存到文件
			this->save();
		}
		else
		{
			cout << "查无此人，修改失败" << endl;
		}
	}
	system("pause");
	system("cls");
}


void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者为空" << endl;
	}
	else
	{
		cout << "请输入查找的方式:" << endl;
		cout << "1.按职工编号查找" << endl;
		cout << "2.按职工姓名查找" << endl;

		int select = 0;
		cin >> select;

		bool flag = false;

		if (select == 1)
		{
			//按照编号查找
			int id;
			cout << "请输入查找的职工编号：" << endl;
			cin >> id;

			int index = IsExist(id);
			if (index != -1)
			{
				cout << "查找成功" << endl;
				this->m_EmpArray[index]->showInfo();
				flag = true;
			}
			else
			{
				cout << "查找失败" << endl;
			}
		}
		else
		{
			//按姓名查找
			cout << "输入查找姓名:" << endl;
			string name;
			cin >> name;
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功，职工信息为:" << endl;
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
		}
		if (flag == false)
		{
			cout << "查找失败" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式:" << endl;
		cout << "1.按照职工号升序" << endl;
		cout << "2.按照职工号降序" << endl;

		int select = 0;
		cin >> select;
		//选择排序
		for (int i = 0; i < m_EmpNum; i++) {
			int minOrmax = i;
			for (int j = i + 1; j < m_EmpNum; j++) {
				if (select == 1)//升序
				{
					if (this->m_EmpArray[minOrmax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrmax = j;
					}
				}
				else//降序
				{
					if (this->m_EmpArray[minOrmax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOrmax = j;
					}
				}
			}
			if (i != minOrmax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrmax];
				this->m_EmpArray[minOrmax] = temp;
			}
			cout << "排序成功，排序后的结果为:" << endl;
			this->save();
			this->Show_Emp();
		}
	}
}


void WorkerManager::Clean_File()
{
	cout << "确认清空？" << endl;
	cout << "1.确认" << endl;
	cout << "2.返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//打开模式ios::trunc 如果存在，删除文件并重新创建
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;

				delete[] this->m_EmpArray;
				this->m_EmpArray = NULL;
				this->m_EmpNum = 0;
				this->m_FileIsEmpty = true;
			}
			cout << "清空成功" << endl;
		}
	}
	system("pause");
	system("cls");
}