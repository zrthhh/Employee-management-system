#include"workerManager.h"
#include"boss.h"
#include"employee.h"
#include"manager.h"
#include"worker.h"



WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//�ļ����������
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}

	//�ļ����ڣ��ж��Ƿ�Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ�գ�" << endl;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}

	//�ļ����ڣ���Ϊ��
	int num = this->get_EmpNum();
	cout << "ְ������Ϊ��" << num << endl;
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
	cout << "*****��ӭʹ��ְ������ϵͳ��*****" << endl;
	cout << "******** 0.�˳�����ϵͳ ********" << endl;
	cout << "******** 1.����ְ����Ϣ ********" << endl;
	cout << "******** 2.��ʾְ����Ϣ ********" << endl;
	cout << "******** 3.ɾ����ְְ�� ********" << endl;
	cout << "******** 4.�޸�ְ����Ϣ ********" << endl;
	cout << "******** 5.����ְ����Ϣ ********" << endl;
	cout << "******** 6.���ձ������ ********" << endl;
	cout << "******** 7.��������ĵ� ********" << endl;
	cout << "********************************" << endl;
	cout << endl;
}

void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
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
	cout << "����������ְ������:" << endl;
	int addNum = 0;
	cin >> addNum;

	if (addNum > 0)
	{
		//�����¿ռ��С
		int newSize = this->m_EmpNum + addNum;

		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize + 4];

		//��ԭ�ռ����ݷŵ��¿ռ���
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//����������
		for (int i = 0; i < addNum; i++)
		{
			int m_id;
			string m_name;
			int m_dSelect;

			cout << "�������" << i + 1 << "��ְ�����:" << endl;
			cin >> m_id;

			cout << "�������" << i + 1 << "����ְ������:" << endl;
			cin >> m_name;

			cout << "�������ְ����λ:" << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			cin >> m_dSelect;

			Worker* worker = NULL;
			switch (m_dSelect)
			{
			case 1://��ͨԱ��
				worker = new Employee(m_id, m_name, 1);
				break;
			case 2://����
				worker = new Manager(m_id, m_name, 2);
				break;
			case 3://�ϰ�
				worker = new Boss(m_id, m_name, 3);
				break;
			default:
				break;
			}
			newSpace[this->m_EmpNum + i] = worker;
		}
		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;

		//�����¿ռ��ָ��
		this->m_EmpArray = newSpace;

		//����ְ������
		this->m_EmpNum = newSize;

		//����ְ����Ϊ�յı�־
		this->m_FileIsEmpty = false;

		//��ʾ��Ϣ
		cout << "�ɹ����" << addNum << "����ְ��!" << endl;

		//���浽�ı�
		this->save();
	}
	else
	{
		cout << "��������" << endl;
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
		//���ݲ�ͬ����id������ͬ����
		if (did == 1) {
			worker = new Employee(id, name, did);
		}
		else if (did == 2) {
			worker = new Manager(id, name, did);
		}
		else {
			worker = new Boss(id, name, did);
		}
		//�����������
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}


void WorkerManager::Show_Emp()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//���ö�̬���ó���ӿ�
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
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		//����ְ�����ɾ��
		cout << "��������Ҫɾ����ְ�����" << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1) {
			//����ǰ��
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;
			this->save();
			cout << "ɾ���ɹ�" << endl;
		}
		else {
			cout << "����ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}
	}
	system("pause");
	system("cls");
}


void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "�������޸�ְ�����" << endl;
		int id;
		cin >> id;

		int index = this->IsExist(id);
		if (index != -1)
		{
			//���ҵ���ŵ�ְ��
			delete this->m_EmpArray[index];
			int newid = 0;
			string newname;
			int dSelect;
			cout << "���ң�" << id << "��ְ�����������µ�ְ���ţ�" << endl;
			cin >> newid;

			cout << "��������������" << endl;
			cin >> newname;

			cout << "�������λ��" << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
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
			//�������ݵ�����
			this->m_EmpArray[index] = worker;
			cout << "�޸ĳɹ�" << endl;

			//���浽�ļ�
			this->save();
		}
		else
		{
			cout << "���޴��ˣ��޸�ʧ��" << endl;
		}
	}
	system("pause");
	system("cls");
}


void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ���Ϊ��" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ:" << endl;
		cout << "1.��ְ����Ų���" << endl;
		cout << "2.��ְ����������" << endl;

		int select = 0;
		cin >> select;

		bool flag = false;

		if (select == 1)
		{
			//���ձ�Ų���
			int id;
			cout << "��������ҵ�ְ����ţ�" << endl;
			cin >> id;

			int index = IsExist(id);
			if (index != -1)
			{
				cout << "���ҳɹ�" << endl;
				this->m_EmpArray[index]->showInfo();
				flag = true;
			}
			else
			{
				cout << "����ʧ��" << endl;
			}
		}
		else
		{
			//����������
			cout << "�����������:" << endl;
			string name;
			cin >> name;
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "���ҳɹ���ְ����ϢΪ:" << endl;
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
		}
		if (flag == false)
		{
			cout << "����ʧ��" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ:" << endl;
		cout << "1.����ְ��������" << endl;
		cout << "2.����ְ���Ž���" << endl;

		int select = 0;
		cin >> select;
		//ѡ������
		for (int i = 0; i < m_EmpNum; i++) {
			int minOrmax = i;
			for (int j = i + 1; j < m_EmpNum; j++) {
				if (select == 1)//����
				{
					if (this->m_EmpArray[minOrmax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrmax = j;
					}
				}
				else//����
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
			cout << "����ɹ��������Ľ��Ϊ:" << endl;
			this->save();
			this->Show_Emp();
		}
	}
}


void WorkerManager::Clean_File()
{
	cout << "ȷ����գ�" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//��ģʽios::trunc ������ڣ�ɾ���ļ������´���
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
			cout << "��ճɹ�" << endl;
		}
	}
	system("pause");
	system("cls");
}