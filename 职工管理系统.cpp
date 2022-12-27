#include<iostream>
#include<string>
#include<fstream>
#include"workerManager.h"
using namespace std;

/*管理系统中需要实现的功能
* 1.退出管理程序
* 2.增加职工信息
* 3.显示职工信息
* 4.删除离职职工
* 5.修改职工信息
* 6.查找职工信息
* 7.按照编号进行排序
* 8.清空所有文档
*/



int main()
{
	//实例化
	WorkerManager wm;
	
	int choice = 0;
	while (true)
	{
		//展示菜单
		wm.show_Menu();
		cout << "请输入你的选择：" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0://退出系统
			wm.ExitSystem();
			break;
		case 1://添加职工
			wm.Add_Emp();
			break;
		case 2://显示职工
			wm.Show_Emp();
			break;
		case 3://删除职工
			wm.Del_Emp();
			break;
		case 4://修改职工
			wm.Mod_Emp();
			break;
		case 5://查找职工
			wm.Find_Emp();
			break;
		case 6://排序职工
			wm.Sort_Emp();
			break;
		case 7://清空文件
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