#pragma once
#ifndef __DISPATCH_H__
#define __DISPATCH_H__

#include <vector>
#include <set>
#include <map>
#include "Car.h"
#include "Road.h"
#include "Cross.h"
#include "presetAnswer.h"
#include "Floyd.h"
#include "Backup_data.h"
using namespace std;

class Dispatch
{
public:
	int RANUM;
	int car0, carSize;
	int road0, roadSize;
	int cross0, crossSize;
	bool isDeadlock=false;
	int EmptyCarportNumber = 0;
	vector<int> oldPT;
	int roadCarNumber = 0;

	int T = 0;		//系统调度时间
	int Tsum = 0;	//系统总调度时间
	int Tpri = 0;	//优先车辆调度时间
	int Tsumpri = 0; //优先车辆总调度时间
	int TE = 0;		//最终调度时间
	int TEsum = 0;  //最终总调度时间

	//空闲路和拥挤路，用历史流量识别出来的，用于死锁处理，初赛的处理方式
	vector<int> freeRoads;
	vector<int> busyRoads;

	//主备份&主回滚
	int lastLockTime = 0;
	vector<Backup_data> BackupData;
	//bool mainBackup(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime);
	//bool mainRollback(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime, const Graph_DG &OriginalCarGraph);
	vector<int> setFlagDeadCar(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, vector<vector<int>> &CarDeadRoadId);
	vector<int> setFlagDeadCar2(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, vector<vector<int>> &CarDeadRoadId);
	void changeDeadCarRoute(Car &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, const Graph_DG &OriginalCarGraph);
	void changeDeadCarRoute2(Car &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, const Graph_DG &OriginalCarGraph, vector<int> &CarDeadRoadId);
	//备份&回滚1
	//int backup_GlobalTime = 0;
	//int backup_roadCarNumber = 0;
	//int backup_EmptyCarportNumber = 0;
	//void Backup(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime);
	//void Rollback(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime, const Graph_DG &OriginalCarGraph);
	void givePT(vector<Car> &CAR);
	void recoveryPT(vector<Car> &CAR);
	//备份&回滚2
	//int backup_GlobalTime2 = 0;
	//int backup_roadCarNumber2 = 0;
	//int backup_EmptyCarportNumber2 = 0;
	//void Backup2(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime);
	//void Rollback2(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime, const Graph_DG &OriginalCarGraph);

	//主函数
	void dispathINIT(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime, int TT);  //T0时刻调度
	void setState(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime);
	int dispathMAIN(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime, int TT, int bsetTime);
	bool isAllEnd(vector<Car> &CAR);
	bool isAllTerminate(vector<Car> &CAR);
	void printOUT(vector<Car> &CAR);
	bool isRoadOver(int roadID, int dir, vector<Road> &ROAD, vector<Car> &CAR);
	bool isConflict(int nowOrder, int carID, vector<int> &roadAll, vector<int> &dir, vector<Road> &ROAD, vector<Car> &CAR);	
	void resetRoadCarNumber();
	void addRoadCarNumber();
	void subRoadCarNumber();	
	bool subEndCarPT(vector<Car> &CAR, int count);
	int gainWaitNum(vector<Car> &CAR);
	bool clearSF(vector<Car> &tempCar);

	//发车函数
	bool moveToNextRoad(int roadNum, vector<Car> &CAR, vector<Road> &ROAD, vector<Cross> &CROSS, int &GlobalTime);
	bool moveOnTheRoad(int num, vector<Car> &CAR, vector<Road> &ROAD, vector<Cross> &CROSS, int &GlobalTime);
	bool moveCarportPriorityCar(int num, vector<Car> &CAR, vector<Road> &ROAD, vector<Cross> &CROSS, int &GlobalTime);
	bool moveCarport(int num, vector<Car> &CAR, vector<Road> &ROAD, vector<Cross> &CROSS, int &GlobalTime); //路上车调度结束，开始调度车库内等待的车
	bool moveCarportCarPriorityToRoad(int roadId, int dir, vector<Car> &CAR, vector<Road> &ROAD, vector<Cross> &CROSS, int &GlobalTime);
	bool moveCarport2(int crossNum, vector<Car> &CAR, vector<Road> &ROAD, vector<Cross> &CROSS, int &GlobalTime);

	//分区
	void Batch1(vector<Car> &CAR, int batchNum,int t);
	void Batch2(vector<Car> &CAR, int batchNum, int t);
	vector<int> bathSort(vector<Car> &CAR, vector<int> &bath);
	vector<int> bathSort2(vector<Car> &CAR, vector<int> &bath);

	//限流
	bool controlInitCar(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime);
	bool modifyPlantime(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime);

	//计算道路拥挤度
	void setRoadCarNUm(int Num);
	void computeRoadCrowding(vector<Road> &ROAD);

	//计算时间
	int priorityCarSize=0;
	vector<int> allCarSpeed, priorityCarSpeed;
	vector<int> allCarPlanTime, allCarEndTime, priorityCarPlanTime, priorityCarEndTime;
	set<int> allCarFrom, priorityCarFrom;
	set<int> allCarTo, priorityCarTo;
	double a1, a2, a3, a4, a5;
	void clearData();
	void computeData(vector<Car> &CAR);
	int computeT();		//计算调度时间
	int computeTpri();	//计算优先车辆调度时间
	int computeTE(vector<Car> &CAR);	//计算最终调度时间
	int computeTEsum(vector<Car> &CAR);	//计算最终总调度时间

	//搜索参数
	int searchBestBatchNum(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int batchNum,int t, int limitNum);
	int searchBestLimitNum(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int batchNum, int limitNum);
	int mainLoop1(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime, int TT, int bsetTime);
	int mainLoop2(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime, int TT, int bsetTime);
	//int searchBestTime1(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD);
	int searchBestTime2(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD);
	//int computeRoadCarNUm(vector<Road> &ROAD);


	//带死锁处理
	void dealDeadLock(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, const Graph_DG &OriginalCarGraph, vector<int> &freeRoads, vector<int> &busyRoads, vector<int> &CROSSID);
	void dealDeadLock_back(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, const Graph_DG &OriginalCarGraph, vector<int> &freeRoads, vector<int> &busyRoads, vector<int> &CROSSID);
	int dispathMAIN_withDeal(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime, int TT, int bsetTime, const Graph_DG &OriginalCarGraph, vector<int> &CROSSID);
	int dispathMAIN_withDeal2(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime, int TT, int bestTime, const Graph_DG &OriginalCarGraph, vector<int> &CROSSID);
	int dispathMAIN_withDeal3(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime, int TT, int bestTime, const Graph_DG &OriginalCarGraph, vector<int> &CROSSID);
	bool delayCarPT(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &nowTime,vector<int> &deadCar);
	bool delayCarPT2(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &nowTime, vector<int> &deadCar);
	//void setDeadLockCarRoute(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, vector<vector<int>> &CarDeadRoadId, const Graph_DG &OriginalCarGraph);
	int getCar(int roadID, int dir, vector<Road> &ROAD, vector<Car> &CAR);						//获取道路上第一优先级的车
	vector<int> getCar2(int roadID, int dir, vector<Road> &ROAD, vector<Car> &CAR, int COUNT);  //获取道路上过下个路口的车
	vector<int> getCar3(int roadID, int dir, vector<Road> &ROAD, vector<Car> &CAR, int COUNT);  //获取道路上等待的车
	vector<int> getCar4(int roadID, int dir, vector<Road> &ROAD, vector<Car> &CAR, int COUNT); //获取等待且不过下一路口的
	vector<int> getCar5(int roadID, int dir, vector<Road> &ROAD, vector<Car> &CAR, int COUNT);  //获取道路上的所有车
	vector<int> getDeadCarFirstAll(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD);  //获取所有死锁路上第一优先级的车
	vector<int> getDeadCarID(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD);		//获取死锁车的ID
	void deadLockProcess1(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD);		//把等待死锁车原地打散
	void deadLockProcess2(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD);		//把等待死锁车全部拉到最后处理
	void deadLockProcess3(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD);		//把等待不过路口的车原地打散，把过路口的车全部拉到最后处理
	void setLimitNum(int limitNum);
	void computeRANUM(int nowTime, Car &FirstCar);
	void getFreeBusyRoads(vector<Road> &ROAD);

	//规划
	void dynamicPlanSet(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, const Graph_DG &OriginalCarGraph);

};

#endif 


