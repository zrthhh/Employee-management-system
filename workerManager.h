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

	//չʾ�˵�
	void show_Menu();

	//�˳�ϵͳ
	void ExitSystem();

	//����ְ��
	void Add_Emp();

	//��Ϣ���浽�ļ���
	void save();

	//ͳ������
	int get_EmpNum();

	//��ʼ��Ա��
	void init_Emp();

	//��ʾְ��
	void Show_Emp();

	//ɾ��ְ��
	void Del_Emp();

	//�鿴ְ���Ƿ����
	int IsExist(int id);

	//�޸�ְ����Ϣ
	void Mod_Emp();

	//����ְ��
	void Find_Emp();

	//����ְ��
	void Sort_Emp();

	//����ļ�
	void Clean_File();


	~WorkerManager();

	//��¼�ļ����˵ĸ���
	int m_EmpNum;

	//Ա�������ָ��
	Worker** m_EmpArray;

	//��־�ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;
};
