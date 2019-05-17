#pragma once
#ifndef __CAR_H__
#define __CAR_H__

#include <vector>
#include "Road.h"
#include "Cross.h"
using namespace std;

class Car
{
public:
	int id;					//车辆id
	int idReal;				//真id
	int from;				//始发地
	int to;					//目的地
	int speed;				//最高速度
	int planTime;			//出发时间
	int priority;			//是否优先
	int preset;				//是否预置

	int PT;                 //供修改的出发时间
	int ATD = -1;			//实际出发时间
	int EndTime;			//已经行驶的时间
	int nowSpeed;			//当前速度
	int maxSpeed;           //可行使最大速度
	int location[3];		//当前位置：在哪条道路的哪条车道的哪个位置上
	int nextRoad;			//下一条道路id
	int nextCross=-1;			//下一个路口
	int nextRoadSpeed;		//下一个道路的速度
	int nextCrossDirection;	//下一个路口转向
	int nextCrossDistance;	//当前位置与下一个路口的距离
	int state = -1;			//车辆行驶状态：0为等待行驶车辆，1为终止状态，-1是还在车库
	int blockDistance;		//与前面阻挡车的距离
	int isReverse = 0;		//是否位于道路的to-from方向
	int toNextRoad = 0;		//是否可以行驶进入下一个路口
	int isTerminate = 0;    //是否到达终点
	int nextReverse;
	int passRoadNumber = 0;
	//int dieCount[150] = { 0 };	//在一个时刻内每条路上的冲突+调度失败计数
	int isReset = 0;
	int LastRoad = -1;
	bool usedToBeDeadCar = false;
	bool changeDeadFlag = false;//死锁回滚标志位，死锁的车，修改完路径，回滚时不修改其路径。
	int deadInRoadId = -1;
	int deadInRoadId_next = -1;
	vector<int> deadRoadId;

	vector<int> maxSP;
	vector<int> reverse;    //在对应道路上的正/反向
	vector<int> direction;	//所经路口时对应道路的方向(直0，左1，右2)，行表示路口，列表示道路，值为转向
	vector<int> route;		//行车路径：道路1，道路2，...，道路N

	////备份
	//int backup_PT;                 //供修改的出发时间
	//int backup_ATD = -1;			//实际出发时间
	//int backup_EndTime;			//已经行驶的时间
	//int backup_nowSpeed;			//当前速度
	//int backup_maxSpeed;           //可行使最大速度
	//int backup_location[3];		//当前位置：在哪条道路的哪条车道的哪个位置上
	//int backup_nextRoad;			//下一条道路id
	//int backup_nextCross = -1;			//下一个路口
	//int backup_nextRoadSpeed;		//下一个道路的速度
	//int backup_nextCrossDirection;	//下一个路口转向
	//int backup_nextCrossDistance;	//当前位置与下一个路口的距离
	//int backup_state = -1;			//车辆行驶状态：0为等待行驶车辆，1为终止状态，-1是还在车库
	//int backup_blockDistance;		//与前面阻挡车的距离
	//int backup_isReverse = 0;		//是否位于道路的to-from方向
	//int backup_toNextRoad = 0;		//是否可以行驶进入下一个路口
	//int backup_isTerminate = 0;    //是否到达终点
	//int backup_nextReverse;
	//int backup_passRoadNumber = 0;
	//int backup_isReset = 0;
	//int backup_LastRoad = -1;
	//bool backup_usedToBeDeadCar = false;
	//vector<int> backup_maxSP;
	//vector<int> backup_reverse;    //在对应道路上的正/反向
	//vector<int> backup_direction;	//所经路口时对应道路的方向(直0，左1，右2)，行表示路口，列表示道路，值为转向
	//vector<int> backup_route;		//行车路径：道路1，道路2，...，道路N

	////备份
	//int backup_PT2;                 //供修改的出发时间
	//int backup_ATD2 = -1;			//实际出发时间
	//int backup_EndTime2;			//已经行驶的时间
	//int backup_nowSpeed2;			//当前速度
	//int backup_maxSpeed2;           //可行使最大速度
	//int backup_location2[3];		//当前位置：在哪条道路的哪条车道的哪个位置上
	//int backup_nextRoad2;			//下一条道路id
	//int backup_nextCross2 = -1;			//下一个路口
	//int backup_nextRoadSpeed2;		//下一个道路的速度
	//int backup_nextCrossDirection2;	//下一个路口转向
	//int backup_nextCrossDistance2;	//当前位置与下一个路口的距离
	//int backup_state2 = -1;			//车辆行驶状态：0为等待行驶车辆，1为终止状态，-1是还在车库
	//int backup_blockDistance2;		//与前面阻挡车的距离
	//int backup_isReverse2 = 0;		//是否位于道路的to-from方向
	//int backup_toNextRoad2 = 0;		//是否可以行驶进入下一个路口
	//int backup_isTerminate2 = 0;    //是否到达终点
	//int backup_nextReverse2;
	//int backup_passRoadNumber2 = 0;
	//int backup_isReset2 = 0;
	//int backup_LastRoad2 = -1;
	//bool backup_usedToBeDeadCar2 = false;
	//vector<int> backup_maxSP2;
	//vector<int> backup_reverse2;    //在对应道路上的正/反向
	//vector<int> backup_direction2;	//所经路口时对应道路的方向(直0，左1，右2)，行表示路口，列表示道路，值为转向
	//vector<int> backup_route2;		//行车路径：道路1，道路2，...，道路N



	bool init(vector<int> carData);	//车辆信息初始化
	vector<int> setRoute(vector<int> routeData);	//设置行驶路径
	void setEndTime(int Time);	//设置车辆已行驶的时间
	void setNowSpeed(int speed);	//设置当前速度

	void updateRoute(int num, int roadId);	//更改第num条道路信息
	void updateLocation(int road, int channel, int position);
	void setATD(int time);
	void setState(int STD);
	void setBlockDistance(int distance);
	bool computeNEXT(vector<Road> &ROAD, vector<Cross> &CROSS);//计算nextRoad,nextRoadSpeed,nextCrossDirection,nextCrossDistance
	void setReverse(int Is);
	void setToNextRoad(int Is);
	void setIsTerminate(int Is);
	void addRverse(int ISR);
	void addMaxSpeed(int SP);
	void isRVER(int ISR);
	void addDieCount(int roadID);
	void addPlanTime();
	void addPlanTime1();
	void addPT(int T);
	void subPT(int T);
	void setPT(int T);
	void renew();
	void dieToZero();
	void setReset(int IS);
	void maxSPClear();
	void reverseClear();
};

#endif 
