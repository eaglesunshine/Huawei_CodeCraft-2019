#pragma once
#ifndef __CROSS_H__
#define __CROSS_H__

#include <vector>
using namespace std;

class Cross
{
public:
	int id;				//路口id
	int idReal;			//真id
	int road1;			//道路id，-1表示没有路
	int road2;			//道路id
	int road3;			//道路id
	int road4;			//道路id
	vector<int> StartCar;

	////备份
	//vector<int> backup_StartCar;

	////备份
	//vector<int> backup_StartCar2;

	bool init(vector<int> crossData);	//道路信息初始化
	void addStartCar(int carId);
	void subStartCar(vector<int> carCut);
	void renew();
};

#endif 