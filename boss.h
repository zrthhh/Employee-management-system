#pragma once
#include<iostream>
#include"worker.h"
using namespace std;

//¿œ∞Â¿‡
class Boss :public Worker
{
public:
	Boss(int id, string name, int did);

	virtual void showInfo();

	virtual string getDeptName();
};
