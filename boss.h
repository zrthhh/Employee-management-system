#pragma once
#include<iostream>
#include"worker.h"
using namespace std;

//�ϰ���
class Boss :public Worker
{
public:
	Boss(int id, string name, int did);

	virtual void showInfo();

	virtual string getDeptName();
};
