#include<iostream>
#include<string>
#include<fstream>
#include"workerManager.h"
using namespace std;

/*����ϵͳ����Ҫʵ�ֵĹ���
* 1.�˳��������
* 2.����ְ����Ϣ
* 3.��ʾְ����Ϣ
* 4.ɾ����ְְ��
* 5.�޸�ְ����Ϣ
* 6.����ְ����Ϣ
* 7.���ձ�Ž�������
* 8.��������ĵ�
*/



int main()
{
	//ʵ����
	WorkerManager wm;
	
	int choice = 0;
	while (true)
	{
		//չʾ�˵�
		wm.show_Menu();
		cout << "���������ѡ��" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0://�˳�ϵͳ
			wm.ExitSystem();
			break;
		case 1://���ְ��
			wm.Add_Emp();
			break;
		case 2://��ʾְ��
			wm.Show_Emp();
			break;
		case 3://ɾ��ְ��
			wm.Del_Emp();
			break;
		case 4://�޸�ְ��
			wm.Mod_Emp();
			break;
		case 5://����ְ��
			wm.Find_Emp();
			break;
		case 6://����ְ��
			wm.Sort_Emp();
			break;
		case 7://����ļ�
			wm.Clean_File();
			break;
		default:
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}