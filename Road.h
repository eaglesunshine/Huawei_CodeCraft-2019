#pragma once
#ifndef __ROAD_H__
#define __ROAD_H__

#include <vector>
using namespace std;

class Road
{
public:
	int id;				//道路id
	int idReal;			//真id
	int length;			//道路长度
	int speed;			//最高限速
	int channel;		//车道数目
	int from;			//起始路口id
	int to;				//终点路口id
	int isDuplex;		//是否双向：1：双向；0：单向
	vector<vector<vector<int>>> WaitCar; //哪个方向哪个转向进入的第几个车的id	

	int roadCar[2][10][100];//from-to方向/to-from上的车辆位置：在哪个车道的哪个位置
	
	//道路拥挤情况
	int nowCarNum=0;		//当前时刻路上的车辆数目
	int allCarNum = 0;		//从开始到当前时刻的车辆数目
	int nowNum[2] = {0};		//当前时刻路上正/反向的车辆数目
	int allNum[2] = {0};		//从开始到当前时刻正/反向的车辆数目
	float crowding[2] = {0};		//当前时刻道路上正/反向的拥挤度

	////备份
	//int backup_roadCar[2][10][100];//from-to方向/to-from上的车辆位置：在哪个车道的哪个位置
	//int backup_nowCarNum = 0;		//当前时刻路上的车辆数目
	//int backup_allCarNum = 0;		//从开始到当前时刻的车辆数目
	//int backup_nowNum[2] = { 0 };		//当前时刻路上正/反向的车辆数目
	//int backup_allNum[2] = { 0 };		//从开始到当前时刻正/反向的车辆数目
	//float backup_crowding[2] = { 0 };		//当前时刻道路上正/反向的拥挤度

	////备份
	//int backup_roadCar2[2][10][100];//from-to方向/to-from上的车辆位置：在哪个车道的哪个位置
	//int backup_nowCarNum2 = 0;		//当前时刻路上的车辆数目
	//int backup_allCarNum2 = 0;		//从开始到当前时刻的车辆数目
	//int backup_nowNum2[2] = { 0 };		//当前时刻路上正/反向的车辆数目
	//int backup_allNum2[2] = { 0 };		//从开始到当前时刻正/反向的车辆数目
	//float backup_crowding2[2] = { 0 };		//当前时刻道路上正/反向的拥挤度

	bool init(vector<int> roadData);			//道路信息初始化
	void addWaitCar(int way, int direction, int carId);
	void subWaitCar(int way, int direction, vector<int> carCut);
	void clearWaitCar(int way);

	void addRoadCar(int direction, int lane, int position, int carId);
	void subRoadCar(int direction, int lane, int carId);
	void renew();
	int getNowCarNum();    //获取当前路上车辆数
};

#endif 