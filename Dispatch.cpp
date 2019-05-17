#include "Dispatch.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <string.h>
#include <set>
#include <map>
#include <cmath>
#include "Floyd.h"
using namespace std;
#define BADTIME 100000
#define PI 3.1415926
//#define  RANUM 1200   //保持路上车辆数

////主备份
//bool Dispatch::mainBackup(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime)
//{
//	//第一次备份
//	if (backup_GlobalTime == 0 && backup_GlobalTime2 == 0)
//	{
//		Backup(CAR, CROSS, ROAD, GlobalTime);
//		return true;
//	}
//
//	//谁备份的时间最早，就拿谁来存最新的
//	if (backup_GlobalTime > 0 && backup_GlobalTime2 >= 0)
//	{
//		if (backup_GlobalTime == backup_GlobalTime2)
//		{
//			Backup(CAR, CROSS, ROAD, GlobalTime);
//			return true;
//		}
//		if (backup_GlobalTime < backup_GlobalTime2)
//		{
//			Backup(CAR, CROSS, ROAD, GlobalTime);
//			return true;
//		}
//		if (backup_GlobalTime > backup_GlobalTime2)
//		{
//			Backup2(CAR, CROSS, ROAD, GlobalTime);
//			return true;
//		}
//	}
//
//	Backup(CAR, CROSS, ROAD, GlobalTime);
//	return false;
//}
//
////主回滚
//bool Dispatch::mainRollback(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime, const Graph_DG &OriginalCarGraph)
//{
//	//只存在一个备份
//	if (backup_GlobalTime > 0 && backup_GlobalTime2 == 0)
//	{
//		Rollback(CAR, CROSS, ROAD, GlobalTime, OriginalCarGraph);
//		backup_GlobalTime = 0;
//		backup_GlobalTime2 = 0;
//		return true;
//	}
//
//	//存在两个备份，谁备份最早就恢复谁
//	if (backup_GlobalTime > 0 && backup_GlobalTime2 > 0)
//	{
//		if (backup_GlobalTime == backup_GlobalTime2)
//		{
//			Rollback(CAR, CROSS, ROAD, GlobalTime, OriginalCarGraph);
//			backup_GlobalTime = 0;
//			backup_GlobalTime2 = 0;
//			return true;
//		}
//		if (backup_GlobalTime < backup_GlobalTime2)
//		{
//			Rollback(CAR, CROSS, ROAD, GlobalTime, OriginalCarGraph);
//			backup_GlobalTime = 0;
//			backup_GlobalTime2 = 0;
//			return true;
//		}
//		if (backup_GlobalTime > backup_GlobalTime2)
//		{
//			Rollback2(CAR, CROSS, ROAD, GlobalTime, OriginalCarGraph);
//			backup_GlobalTime = 0;
//			backup_GlobalTime2 = 0;
//			return true;
//		}
//	}
//
//	Rollback(CAR, CROSS, ROAD, GlobalTime, OriginalCarGraph);
//	backup_GlobalTime = 0;
//	backup_GlobalTime2 = 0;
//	return false;
//}
//
//void Dispatch::Backup(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime)
//{
//	//dispatch backup
//	this->backup_GlobalTime = GlobalTime;
//	backup_roadCarNumber = roadCarNumber;
//	backup_EmptyCarportNumber = EmptyCarportNumber;
//
//	int i;
//	//CAR backup
//	for (i = 0; i < carSize; i++)
//	{
//		CAR[i].backup_PT = CAR[i].PT;
//		CAR[i].backup_ATD = CAR[i].ATD;
//		CAR[i].backup_EndTime = CAR[i].EndTime;
//		CAR[i].backup_nowSpeed = CAR[i].nowSpeed;
//		CAR[i].backup_maxSpeed = CAR[i].maxSpeed;
//		memcpy(CAR[i].backup_location, CAR[i].location, sizeof(CAR[i].location));
//		CAR[i].backup_nextRoad = CAR[i].nextRoad;
//		CAR[i].backup_nextCross = CAR[i].nextCross;
//		CAR[i].backup_nextRoadSpeed = CAR[i].nextRoadSpeed;
//		CAR[i].backup_nextCrossDirection = CAR[i].nextCrossDirection;
//		CAR[i].backup_nextCrossDistance = CAR[i].nextCrossDistance;
//		CAR[i].backup_state = CAR[i].state;
//		CAR[i].backup_blockDistance = CAR[i].blockDistance;
//		CAR[i].backup_isReverse = CAR[i].isReverse;
//		CAR[i].backup_toNextRoad = CAR[i].toNextRoad;
//		CAR[i].backup_isTerminate = CAR[i].isTerminate;
//		CAR[i].backup_nextReverse = CAR[i].nextReverse;
//		CAR[i].backup_passRoadNumber = CAR[i].passRoadNumber;
//		CAR[i].backup_isReset = CAR[i].isReset;
//		CAR[i].backup_LastRoad = CAR[i].LastRoad;
//		CAR[i].backup_usedToBeDeadCar = CAR[i].usedToBeDeadCar;
//
//		CAR[i].backup_maxSP.clear();
//		CAR[i].backup_maxSP.insert(CAR[i].backup_maxSP.begin(), CAR[i].maxSP.begin(), CAR[i].maxSP.end());
//		CAR[i].backup_reverse.clear();
//		CAR[i].backup_reverse.insert(CAR[i].backup_reverse.begin(), CAR[i].reverse.begin(), CAR[i].reverse.end());
//		CAR[i].backup_direction.clear();
//		CAR[i].backup_direction.insert(CAR[i].backup_direction.begin(), CAR[i].direction.begin(), CAR[i].direction.end());
//		CAR[i].backup_route.clear();
//		CAR[i].backup_route.insert(CAR[i].backup_route.begin(), CAR[i].route.begin(), CAR[i].route.end());
//	}
//
//	//CROSS backup
//	for (i = 0; i < crossSize; i++)
//	{
//		CROSS[i].backup_StartCar.clear();
//		CROSS[i].backup_StartCar.insert(CROSS[i].backup_StartCar.begin(), CROSS[i].StartCar.begin(), CROSS[i].StartCar.end());
//	}
//
//	//ROAD backup
//	for (i = 0; i < roadSize; i++)
//	{
//		memcpy(ROAD[i].backup_roadCar, ROAD[i].roadCar, sizeof(ROAD[i].roadCar));
//		ROAD[i].backup_nowCarNum = ROAD[i].nowCarNum;
//		ROAD[i].backup_allCarNum = ROAD[i].allCarNum;
//		memcpy(ROAD[i].backup_nowNum, ROAD[i].nowNum, sizeof(ROAD[i].nowNum));
//		memcpy(ROAD[i].backup_allNum, ROAD[i].allNum, sizeof(ROAD[i].allNum));
//		memcpy(ROAD[i].backup_crowding, ROAD[i].crowding, sizeof(ROAD[i].crowding));
//	}
//}
//
//void Dispatch::Rollback(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime, const Graph_DG &OriginalCarGraph)
//{
//	//dispatch rollback
//	GlobalTime = this->backup_GlobalTime;
//	roadCarNumber = backup_roadCarNumber;
//	EmptyCarportNumber = backup_EmptyCarportNumber;
//
//	int i;
//	//CAR rollback
//	for (i = 0; i < carSize; i++)
//	{
//		CAR[i].PT = CAR[i].backup_PT;
//		CAR[i].ATD = CAR[i].backup_ATD;
//		CAR[i].EndTime = CAR[i].backup_EndTime;
//		CAR[i].nowSpeed = CAR[i].backup_nowSpeed;
//		CAR[i].maxSpeed = CAR[i].backup_maxSpeed;
//		memcpy(CAR[i].location, CAR[i].backup_location, sizeof(CAR[i].backup_location));
//		CAR[i].nextRoad = CAR[i].backup_nextRoad;
//		CAR[i].nextCross = CAR[i].backup_nextCross;
//		CAR[i].nextRoadSpeed = CAR[i].backup_nextRoadSpeed;
//		CAR[i].nextCrossDirection = CAR[i].backup_nextCrossDirection;
//		CAR[i].nextCrossDistance = CAR[i].backup_nextCrossDistance;
//		CAR[i].state = CAR[i].backup_state;
//		CAR[i].blockDistance = CAR[i].backup_blockDistance;
//		CAR[i].isReverse = CAR[i].backup_isReverse;
//		CAR[i].toNextRoad = CAR[i].backup_toNextRoad;
//		CAR[i].isTerminate = CAR[i].backup_isTerminate;
//		CAR[i].nextReverse = CAR[i].backup_nextReverse;
//		CAR[i].passRoadNumber = CAR[i].backup_passRoadNumber;
//		CAR[i].isReset = CAR[i].backup_isReset;
//		CAR[i].LastRoad = CAR[i].backup_LastRoad;
//		CAR[i].usedToBeDeadCar = CAR[i].backup_usedToBeDeadCar;
//
//		if (CAR[i].changeDeadFlag == true) {
//			CAR[i].changeDeadFlag = false;
//			this->changeDeadCarRoute(CAR[i], CROSS, ROAD, OriginalCarGraph);
//		}
//		else {
//			CAR[i].maxSP.clear();
//			CAR[i].maxSP.insert(CAR[i].maxSP.begin(), CAR[i].backup_maxSP.begin(), CAR[i].backup_maxSP.end());
//			CAR[i].reverse.clear();
//			CAR[i].reverse.insert(CAR[i].reverse.begin(), CAR[i].backup_reverse.begin(), CAR[i].backup_reverse.end());
//			CAR[i].direction.clear();
//			CAR[i].direction.insert(CAR[i].direction.begin(), CAR[i].backup_direction.begin(), CAR[i].backup_direction.end());
//			CAR[i].route.clear();
//			CAR[i].route.insert(CAR[i].route.begin(), CAR[i].backup_route.begin(), CAR[i].backup_route.end());
//		}
//	}
//
//	//CROSS rollback
//	for (i = 0; i < crossSize; i++)
//	{
//		CROSS[i].StartCar.clear();
//		CROSS[i].StartCar.insert(CROSS[i].StartCar.begin(), CROSS[i].backup_StartCar.begin(), CROSS[i].backup_StartCar.end());
//	}
//
//	//ROAD rollback
//	for (i = 0; i < roadSize; i++)
//	{
//		memcpy(ROAD[i].roadCar, ROAD[i].backup_roadCar, sizeof(ROAD[i].backup_roadCar));
//		ROAD[i].nowCarNum = ROAD[i].backup_nowCarNum;
//		ROAD[i].allCarNum = ROAD[i].backup_allCarNum;
//		memcpy(ROAD[i].nowNum, ROAD[i].backup_nowNum, sizeof(ROAD[i].backup_nowNum));
//		memcpy(ROAD[i].allNum, ROAD[i].backup_allNum, sizeof(ROAD[i].backup_allNum));
//		memcpy(ROAD[i].crowding, ROAD[i].backup_crowding, sizeof(ROAD[i].backup_crowding));
//	}
//}
//
//void Dispatch::Backup2(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime)
//{
//	//dispatch backup
//	this->backup_GlobalTime2 = GlobalTime;
//	backup_roadCarNumber2 = roadCarNumber;
//	backup_EmptyCarportNumber2 = EmptyCarportNumber;
//
//	int i;
//	//CAR backup
//	for (i = 0; i < carSize; i++)
//	{
//		CAR[i].backup_PT2 = CAR[i].PT;
//		CAR[i].backup_ATD2 = CAR[i].ATD;
//		CAR[i].backup_EndTime2 = CAR[i].EndTime;
//		CAR[i].backup_nowSpeed2 = CAR[i].nowSpeed;
//		CAR[i].backup_maxSpeed2 = CAR[i].maxSpeed;
//		memcpy(CAR[i].backup_location2, CAR[i].location, sizeof(CAR[i].location));
//		CAR[i].backup_nextRoad2 = CAR[i].nextRoad;
//		CAR[i].backup_nextCross2 = CAR[i].nextCross;
//		CAR[i].backup_nextRoadSpeed2 = CAR[i].nextRoadSpeed;
//		CAR[i].backup_nextCrossDirection2 = CAR[i].nextCrossDirection;
//		CAR[i].backup_nextCrossDistance2 = CAR[i].nextCrossDistance;
//		CAR[i].backup_state2 = CAR[i].state;
//		CAR[i].backup_blockDistance2 = CAR[i].blockDistance;
//		CAR[i].backup_isReverse2 = CAR[i].isReverse;
//		CAR[i].backup_toNextRoad2 = CAR[i].toNextRoad;
//		CAR[i].backup_isTerminate2 = CAR[i].isTerminate;
//		CAR[i].backup_nextReverse2 = CAR[i].nextReverse;
//		CAR[i].backup_passRoadNumber2 = CAR[i].passRoadNumber;
//		CAR[i].backup_isReset2 = CAR[i].isReset;
//		CAR[i].backup_LastRoad2 = CAR[i].LastRoad;
//		CAR[i].backup_usedToBeDeadCar2 = CAR[i].usedToBeDeadCar;
//
//		CAR[i].backup_maxSP2.clear();
//		CAR[i].backup_maxSP2.insert(CAR[i].backup_maxSP2.begin(), CAR[i].maxSP.begin(), CAR[i].maxSP.end());
//		CAR[i].backup_reverse2.clear();
//		CAR[i].backup_reverse2.insert(CAR[i].backup_reverse2.begin(), CAR[i].reverse.begin(), CAR[i].reverse.end());
//		CAR[i].backup_direction2.clear();
//		CAR[i].backup_direction2.insert(CAR[i].backup_direction2.begin(), CAR[i].direction.begin(), CAR[i].direction.end());
//		CAR[i].backup_route2.clear();
//		CAR[i].backup_route2.insert(CAR[i].backup_route2.begin(), CAR[i].route.begin(), CAR[i].route.end());
//	}
//
//	//CROSS backup
//	for (i = 0; i < crossSize; i++)
//	{
//		CROSS[i].backup_StartCar2.clear();
//		CROSS[i].backup_StartCar2.insert(CROSS[i].backup_StartCar2.begin(), CROSS[i].StartCar.begin(), CROSS[i].StartCar.end());
//	}
//
//	//ROAD backup
//	for (i = 0; i < roadSize; i++)
//	{
//		memcpy(ROAD[i].backup_roadCar2, ROAD[i].roadCar, sizeof(ROAD[i].roadCar));
//		ROAD[i].backup_nowCarNum2 = ROAD[i].nowCarNum;
//		ROAD[i].backup_allCarNum2 = ROAD[i].allCarNum;
//		memcpy(ROAD[i].backup_nowNum2, ROAD[i].nowNum, sizeof(ROAD[i].nowNum));
//		memcpy(ROAD[i].backup_allNum2, ROAD[i].allNum, sizeof(ROAD[i].allNum));
//		memcpy(ROAD[i].backup_crowding2, ROAD[i].crowding, sizeof(ROAD[i].crowding));
//	}
//}
//
//void Dispatch::Rollback2(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime, const Graph_DG &OriginalCarGraph)
//{
//	//dispatch rollback
//	GlobalTime = this->backup_GlobalTime2;
//	roadCarNumber = backup_roadCarNumber2;
//	EmptyCarportNumber = backup_EmptyCarportNumber2;
//
//	int i;
//	//CAR rollback
//	for (i = 0; i < carSize; i++)
//	{
//		CAR[i].PT = CAR[i].backup_PT2;
//		CAR[i].ATD = CAR[i].backup_ATD2;
//		CAR[i].EndTime = CAR[i].backup_EndTime2;
//		CAR[i].nowSpeed = CAR[i].backup_nowSpeed2;
//		CAR[i].maxSpeed = CAR[i].backup_maxSpeed2;
//		memcpy(CAR[i].location, CAR[i].backup_location2, sizeof(CAR[i].backup_location2));
//		CAR[i].nextRoad = CAR[i].backup_nextRoad2;
//		CAR[i].nextCross = CAR[i].backup_nextCross2;
//		CAR[i].nextRoadSpeed = CAR[i].backup_nextRoadSpeed2;
//		CAR[i].nextCrossDirection = CAR[i].backup_nextCrossDirection2;
//		CAR[i].nextCrossDistance = CAR[i].backup_nextCrossDistance2;
//		CAR[i].state = CAR[i].backup_state2;
//		CAR[i].blockDistance = CAR[i].backup_blockDistance2;
//		CAR[i].isReverse = CAR[i].backup_isReverse2;
//		CAR[i].toNextRoad = CAR[i].backup_toNextRoad2;
//		CAR[i].isTerminate = CAR[i].backup_isTerminate2;
//		CAR[i].nextReverse = CAR[i].backup_nextReverse2;
//		CAR[i].passRoadNumber = CAR[i].backup_passRoadNumber2;
//		CAR[i].isReset = CAR[i].backup_isReset2;
//		CAR[i].LastRoad = CAR[i].backup_LastRoad2;
//		CAR[i].usedToBeDeadCar = CAR[i].backup_usedToBeDeadCar2;
//
//		if (CAR[i].changeDeadFlag == true) {
//			CAR[i].changeDeadFlag = false;
//			this->changeDeadCarRoute(CAR[i], CROSS, ROAD, OriginalCarGraph);
//		}
//		else {
//			CAR[i].maxSP.clear();
//			CAR[i].maxSP.insert(CAR[i].maxSP.begin(), CAR[i].backup_maxSP2.begin(), CAR[i].backup_maxSP2.end());
//			CAR[i].reverse.clear();
//			CAR[i].reverse.insert(CAR[i].reverse.begin(), CAR[i].backup_reverse2.begin(), CAR[i].backup_reverse2.end());
//			CAR[i].direction.clear();
//			CAR[i].direction.insert(CAR[i].direction.begin(), CAR[i].backup_direction2.begin(), CAR[i].backup_direction2.end());
//			CAR[i].route.clear();
//			CAR[i].route.insert(CAR[i].route.begin(), CAR[i].backup_route2.begin(), CAR[i].backup_route2.end());
//		}
//	}
//
//	//CROSS rollback
//	for (i = 0; i < crossSize; i++)
//	{
//		CROSS[i].StartCar.clear();
//		CROSS[i].StartCar.insert(CROSS[i].StartCar.begin(), CROSS[i].backup_StartCar2.begin(), CROSS[i].backup_StartCar2.end());
//	}
//
//	//ROAD rollback
//	for (i = 0; i < roadSize; i++)
//	{
//		memcpy(ROAD[i].roadCar, ROAD[i].backup_roadCar2, sizeof(ROAD[i].backup_roadCar2));
//		ROAD[i].nowCarNum = ROAD[i].backup_nowCarNum2;
//		ROAD[i].allCarNum = ROAD[i].backup_allCarNum2;
//		memcpy(ROAD[i].nowNum, ROAD[i].backup_nowNum2, sizeof(ROAD[i].backup_nowNum2));
//		memcpy(ROAD[i].allNum, ROAD[i].backup_allNum2, sizeof(ROAD[i].backup_allNum2));
//		memcpy(ROAD[i].crowding, ROAD[i].backup_crowding2, sizeof(ROAD[i].backup_crowding2));
//	}
//}

void Dispatch::givePT(vector<Car> &CAR)
{
	for (int i = 0; i < (int)(CAR.size()); i++)
	{
		oldPT.push_back(CAR[i].PT);
	}
}

void Dispatch::recoveryPT(vector<Car> &CAR)
{
	for (int i = 0; i < (int)(CAR.size()); i++)
	{
		CAR[i].PT = oldPT[i];
	}
}

void Dispatch::computeRoadCrowding(vector<Road> &ROAD)
{
	int num, m, k, j;
	int firstCH = 0;
	for (num = 0; num < roadSize; num++)
	{
		ROAD[num].nowCarNum = 0;
		ROAD[num].nowNum[0] = 0;
		ROAD[num].nowNum[1] = 0;
		for (m = 0; m < 2; m++)
		{
			if (m == 1 && ROAD[num].isDuplex == 0)
				break;
			for (k = 0; k < ROAD[num].channel; k++)
				for (j = 0; j < ROAD[num].length; j++)
				{
					if (ROAD[num].roadCar[m][k][j] != -1)
					{
						if (k == 0)
							++firstCH;
						++ROAD[num].nowCarNum;
						++ROAD[num].nowNum[m];
					}
				}
			ROAD[num].allNum[m] += ROAD[num].nowNum[m];
			//ROAD[num].crowding[m] = 0.8*(float)(firstCH) / (float)(ROAD[num].length) +0.2*( float)(ROAD[num].nowNum[m]) / ( float)(ROAD[num].channel*ROAD[num].length);
			ROAD[num].crowding[m] = (float)(ROAD[num].nowNum[m]) / (float)(ROAD[num].channel*ROAD[num].length);
		}
		ROAD[num].allCarNum += ROAD[num].nowCarNum;
	}
}

void Dispatch::setLimitNum(int limitNum)
{
	RANUM = limitNum;
}

void Dispatch::setRoadCarNUm(int Num)
{
	roadCarNumber = Num;
}

vector<int> Dispatch::getCar2(int roadID, int dir, vector<Road> &ROAD, vector<Car> &CAR,int COUNT)
{
	vector<int> lockCar;
	int i, j;
	int count = 0;
	roadID = roadID - ROAD[0].id;
	for (i = ROAD[roadID].length - 1; i >= 0; i--) //位置从高到低
	{
		for (j = 0; j < ROAD[roadID].channel; j++) //车道从小到大
		{
			if (ROAD[roadID].roadCar[dir][j][i] == -1)
				continue;
			int carID = ROAD[roadID].roadCar[dir][j][i] - car0;
			if (CAR[carID].state == 0 && CAR[carID].toNextRoad == 1)
			{
				lockCar.push_back(carID + car0);
				++count;
			}
			if (count > COUNT)
				return lockCar;
		}
	}
	return lockCar;
}

vector<int> Dispatch::getCar3(int roadID, int dir, vector<Road> &ROAD, vector<Car> &CAR, int COUNT)
{
	vector<int> lockCar;
	int i, j;
	int count = 0;
	roadID = roadID - ROAD[0].id;
	for (i = ROAD[roadID].length - 1; i >= 0; i--) //位置从高到低
	{
		for (j = 0; j < ROAD[roadID].channel; j++) //车道从小到大
		{
			if (ROAD[roadID].roadCar[dir][j][i] == -1)
				continue;
			int carID = ROAD[roadID].roadCar[dir][j][i] - car0;
			if (CAR[carID].state == 0)
			{
				lockCar.push_back(carID + car0);
				++count;
			}
			if (count > COUNT)
				return lockCar;
		}
	}
	return lockCar;
}

vector<int> Dispatch::getCar4(int roadID, int dir, vector<Road> &ROAD, vector<Car> &CAR, int COUNT)
{
	vector<int> lockCar;
	int i, j;
	int count = 0;
	roadID = roadID - ROAD[0].id;
	for (i = ROAD[roadID].length - 1; i >= 0; i--) //位置从高到低
	{
		for (j = 0; j < ROAD[roadID].channel; j++) //车道从小到大
		{
			if (ROAD[roadID].roadCar[dir][j][i] == -1)
				continue;
			int carID = ROAD[roadID].roadCar[dir][j][i] - car0;
			if (CAR[carID].state == 0 && CAR[carID].toNextRoad != 1)
			{
				lockCar.push_back(carID + car0);
				++count;
			}
			if (count > COUNT)
				return lockCar;
		}
	}
	return lockCar;
}

vector<int> Dispatch::getCar5(int roadID, int dir, vector<Road> &ROAD, vector<Car> &CAR, int COUNT)
{
	vector<int> allCar;
	int i, j;
	int count = 0;
	roadID = roadID - ROAD[0].id;
	for (i = ROAD[roadID].length - 1; i >= 0; i--) //位置从高到低
	{
		for (j = 0; j < ROAD[roadID].channel; j++) //车道从小到大
		{
			if (ROAD[roadID].roadCar[dir][j][i] == -1)
				continue;
			int carID = ROAD[roadID].roadCar[dir][j][i] - car0;
			allCar.push_back(carID + car0);
			++count;
			if (count > COUNT)
				return allCar;
		}
	}
	return allCar;
}

//int Dispatch::searchBestTime1(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD)
//{
//	int GlobalTime = 1;
//	vector<Car> bestCAR,tempCAR;
//	bestCAR.insert(bestCAR.begin(), CAR.begin(), CAR.end());
//	int bestTime = dispathMAIN(bestCAR, CROSS, ROAD, GlobalTime, 0, BADTIME);
//	cout << bestTime << endl;
//	int count = 0;
//	while (count < 100)
//	{
//		tempCAR.clear();
//		tempCAR.insert(tempCAR.begin(), bestCAR.begin(), bestCAR.end());
//
//		subEndCarPT(tempCAR, count);
//
//		GlobalTime = 1;
//		int newTime = dispathMAIN(tempCAR, CROSS, ROAD, GlobalTime, 1, bestTime);
//		cout << newTime << endl;
//		if (newTime < bestTime)
//		{
//			bestTime = newTime;
//			swap(tempCAR, bestCAR);
//		}
//		++count;
//	}
//
//	swap(bestCAR, CAR);
//	return bestTime;
//}

int Dispatch::searchBestTime2(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD)
{
	vector<int> ATDneed;
	vector<Car> bestCAR;
	vector<Car> tempCAR;
	vector<Cross> tempCROSS;
	vector<Road> tempROAD;

	tempCAR.insert(tempCAR.begin(), CAR.begin(), CAR.end());
	tempCROSS.insert(tempCROSS.begin(), CROSS.begin(), CROSS.end());
	tempROAD.insert(tempROAD.begin(), ROAD.begin(), ROAD.end());

	int GlobalTime = 1;
	int bestTime = dispathMAIN(tempCAR, tempCROSS, tempROAD, GlobalTime, 0, BADTIME);

	for (int i = 0; i < (int)(tempCAR.size()); i++)
	{
		CAR[i].setPT(tempCAR[i].PT);
		ATDneed.push_back(tempCAR[i].ATD);
	}

	int count = 0;
	while (count < 100)
	{
		tempCAR.clear();
		tempCROSS.clear();
		tempROAD.clear();
		tempCAR.insert(tempCAR.begin(), CAR.begin(), CAR.end());
		tempCROSS.insert(tempCROSS.begin(), CROSS.begin(), CROSS.end());
		tempROAD.insert(tempROAD.begin(), ROAD.begin(), ROAD.end());

		subEndCarPT(tempCAR, count);

		GlobalTime = 1;
		int newTime = dispathMAIN(tempCAR, tempCROSS, tempROAD, GlobalTime, 0, bestTime);
		//int newTime = mainLoop(tempCAR1, tempCROSS1, tempROAD1, GlobalTime, 1, bestTime);
		cout << newTime << endl << endl;

		if (newTime < bestTime)
		{
			bestTime = newTime;
			ATDneed.clear();
			for (int i = 0; i < (int)(tempCAR.size()); i++)
			{
				CAR[i].setPT(tempCAR[i].PT);
				ATDneed.push_back(tempCAR[i].ATD);
			}
		}
		++count;
	}

	for (int i = 0; i < (int)(ATDneed.size()); i++)
	{
		CAR[i].setATD(ATDneed[i]);	
	}

	return bestTime;
}

int Dispatch::mainLoop1(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime, int TT, int bsetTime)
{
	int bestTime = dispathMAIN(CAR, CROSS, ROAD, GlobalTime, 0, BADTIME);
	int count = 0;
	while (bestTime== BADTIME && count < 30)
	{
		++count;
		GlobalTime = 1;
		deadLockProcess1(CAR, CROSS, ROAD);
		int nowTime = dispathMAIN(CAR, CROSS, ROAD, GlobalTime, 1, BADTIME);
		cout << nowTime << endl;
		if (nowTime < BADTIME)
		{
			bestTime = nowTime;
			break;
		}
	}
	return bestTime;
}

int Dispatch::mainLoop2(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime, int TT, int bsetTime)
{
	int bestTime = BADTIME;
	vector<int> deadCar;
	vector<Car> tempCAR;
	vector<Cross> tempCROSS;
	vector<Road> tempROAD;
	int count = 0;
	while (count < 100)
	{
		tempCAR.clear();
		tempCROSS.clear();
		tempROAD.clear();
		tempCAR.insert(tempCAR.begin(), CAR.begin(), CAR.end());
		tempCROSS.insert(tempCROSS.begin(), CROSS.begin(), CROSS.end());
		tempROAD.insert(tempROAD.begin(), ROAD.begin(), ROAD.end());

		if (deadCar.size() > 0)
		{
			for (int i = 0; i < (int)(deadCar.size()); i++)
			{
				int RandomNumber = rand() % 10 + 1;//生成1~5随机数
				tempCAR[deadCar[i] - car0].addPT(RandomNumber);
			}
		}
		
		GlobalTime = 1;
		int tempTime = dispathMAIN(tempCAR, tempCROSS, tempROAD, GlobalTime, 0, BADTIME);
		if (tempTime == BADTIME)
		{
			deadCar.clear();
			deadCar = getDeadCarFirstAll(tempCAR, tempCROSS, tempROAD);
		}

		if (tempTime < BADTIME)
		{
			bestTime = tempTime;
			swap(tempCAR, CAR);
			break;
		}

		++count;
	}

	return bestTime;
}

void Dispatch::deadLockProcess1(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD)
{
	int carNumber = 0, roadOrder = 0;
	vector<int> roadIDS, dir, lockCar;
	for (int num = 0; num < crossSize; num++)
	{//按路口ID升序进行调度各个路口，路口内各道路按道路ID升序进行调度等待的车辆
		roadIDS.clear();
		roadIDS.push_back(CROSS[num].road1);
		roadIDS.push_back(CROSS[num].road2);
		roadIDS.push_back(CROSS[num].road3);
		roadIDS.push_back(CROSS[num].road4);
		sort(roadIDS.begin(), roadIDS.end());

		//获取连接此路口的四个入入口方向道路的正反向
		dir.clear();
		for (int q = 0; q < 4; q++)
		{
			if (roadIDS[q] == -1) //没有路
			{
				dir.push_back(-1);
				continue;
			}
			if ((num + cross0) == ROAD[roadIDS[q] - road0].to)
				dir.push_back(0);
			else
				dir.push_back(1);
		}

		//按序遍历道路的第一优先级车辆
		for (int q = 0; q < 4; q++)
		{
			//当前道路上的车未被调度完
			while (!isRoadOver(roadIDS[q], dir[q], ROAD, CAR))
			{
				//获取等待的车
				lockCar = getCar3(roadIDS[q], dir[q], ROAD, CAR, 200);
				carNumber = (int)(lockCar.size());
				cout << carNumber << "---------------------" << endl;
				for (int i = 0; i < carNumber; i++)
				{
					//应该让死锁的车尽可能地分开来发车，避免相遇——need modify
					//int RandomNumber = rand() % 20 + 1;//生成1~5随机数
					CAR[lockCar[i] - car0].addPT(roadOrder + i);
					//CAR[lockCar[i] - car0].addPT(RandomNumber);
				}
				++roadOrder;
				break;
			}
		}
	}
}

void Dispatch::deadLockProcess2(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD)
{
	int carNumber = 0;
	vector<int> roadIDS, dir, lockCar;
	for (int num = 0; num < crossSize; num++)
	{//按路口ID升序进行调度各个路口，路口内各道路按道路ID升序进行调度等待的车辆
		roadIDS.clear();
		roadIDS.push_back(CROSS[num].road1);
		roadIDS.push_back(CROSS[num].road2);
		roadIDS.push_back(CROSS[num].road3);
		roadIDS.push_back(CROSS[num].road4);
		sort(roadIDS.begin(), roadIDS.end());

		//获取连接此路口的四个入入口方向道路的正反向
		dir.clear();
		for (int q = 0; q < 4; q++)
		{
			if (roadIDS[q] == -1) //没有路
			{
				dir.push_back(-1);
				continue;
			}
			if ((num + cross0) == ROAD[roadIDS[q] - road0].to)
				dir.push_back(0);
			else
				dir.push_back(1);
		}

		//按序遍历道路的第一优先级车辆
		for (int q = 0; q < 4; q++)
		{
			//当前道路上的车未被调度完
			while (!isRoadOver(roadIDS[q], dir[q], ROAD, CAR))
			{
				//获取当前道路上的所有等待的车
				lockCar = getCar3(roadIDS[q], dir[q], ROAD, CAR, 200);
				carNumber = (int)(lockCar.size());
				for (int i = 0; i < carNumber; i++)
				{
					//应该让死锁的车全部拉到最后面再处理
					CAR[lockCar[i] - car0].addPT(9999);
				}
				break;
			}
		}
	}
}

void Dispatch::deadLockProcess3(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD)
{
	int carNumber = 0, roadOrder = 0;
	vector<int> roadIDS, dir, lockCar1, lockCar2;
	for (int num = 0; num < crossSize; num++)
	{//按路口ID升序进行调度各个路口，路口内各道路按道路ID升序进行调度等待的车辆
		roadIDS.clear();
		roadIDS.push_back(CROSS[num].road1);
		roadIDS.push_back(CROSS[num].road2);
		roadIDS.push_back(CROSS[num].road3);
		roadIDS.push_back(CROSS[num].road4);
		sort(roadIDS.begin(), roadIDS.end());

		//获取连接此路口的四个入入口方向道路的正反向
		dir.clear();
		for (int q = 0; q < 4; q++)
		{
			if (roadIDS[q] == -1) //没有路
			{
				dir.push_back(-1);
				continue;
			}
			if ((num + cross0) == ROAD[roadIDS[q] - road0].to)
				dir.push_back(0);
			else
				dir.push_back(1);
		}

		//按序遍历道路的第一优先级车辆
		for (int q = 0; q < 4; q++)
		{
			//当前道路上的车未被调度完
			while (!isRoadOver(roadIDS[q], dir[q], ROAD, CAR))
			{
				//获取当前道路上的等待且过下个路口的车，全部拉远
				lockCar1 = getCar2(roadIDS[q], dir[q], ROAD, CAR, 200);
				carNumber = (int)(lockCar1.size());
				for (int i = 0; i < carNumber; i++)
				{
					//应该让死锁的车全部拉到最后面再处理
					CAR[lockCar1[i] - car0].addPT(9999);
				}

				//获取当前道路上的等待且不过下个路口的车，原地打散
				lockCar2 = getCar3(roadIDS[q], dir[q], ROAD, CAR, 200);
				carNumber = (int)(lockCar2.size());
				for (int i = 0; i < carNumber; i++)
				{
					CAR[lockCar2[i] - car0].addPT(roadOrder + i);
				}
				++roadOrder;
				break;
			}
		}
	}
}

vector<int> Dispatch::getDeadCarID(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD)
{
	vector<int> tempDeadCar, deadCar;

	for (int num = 0; num < crossSize; num++)
	{
		int roadIDS[4] = { CROSS[num].road1,CROSS[num].road2, CROSS[num].road3, CROSS[num].road4 };
		sort(roadIDS, roadIDS + 4); //从小到大排序

		//获取连接此路口的四个入入口方向道路的正反向
		int dir[4];
		for (int q = 0; q < 4; q++)
		{
			if (roadIDS[q] == -1) //没有路
				continue;
			if (ROAD[roadIDS[q] - road0].to == num + cross0)
				dir[q] = 0;
			else
				dir[q] = 1;
		}

		//按序遍历道路的第一优先级车辆
		for (int q = 0; q < 4; q++)
		{
			//当前道路上的车未被调度完
			while (!isRoadOver(roadIDS[q], dir[q], ROAD, CAR))
			{
				//获取第一优先级的车...
				tempDeadCar.clear();
				tempDeadCar = getCar3(roadIDS[q], dir[q], ROAD, CAR, 15);
				deadCar.insert(deadCar.end(), tempDeadCar.begin(), tempDeadCar.end());
				break;
			}
		}
	}
	return deadCar;
}

vector<int> Dispatch::getDeadCarFirstAll(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD)
{
	vector<int> deadCar;
	//int count = 0;
	for (int num = 0; num < crossSize; num++)
	{//按路口ID升序进行调度各个路口，路口内各道路按道路ID升序进行调度等待的车辆

		vector<int> roadIDS;
		roadIDS.push_back(CROSS[num].road1);
		roadIDS.push_back(CROSS[num].road2);
		roadIDS.push_back(CROSS[num].road3);
		roadIDS.push_back(CROSS[num].road4);
		sort(roadIDS.begin(), roadIDS.end());

		//获取连接此路口的四个入入口方向道路的正反向
		vector<int> dir;
		for (int q = 0; q < 4; q++)
		{
			if (roadIDS[q] == -1) //没有路
			{
				dir.push_back(-1);
				continue;
			}
			if ((num + cross0) == ROAD[roadIDS[q] - road0].to)
				dir.push_back(0);
			else
				dir.push_back(1);
		}

		//按序遍历道路的第一优先级车辆
		for (int q = 0; q < 4; q++)
		{
			//当前道路上的车未被调度完
			while (!isRoadOver(roadIDS[q], dir[q], ROAD, CAR))
			{
				//获取等待的第一优先级的车
				int carID = getCar(roadIDS[q], dir[q], ROAD, CAR);
				if (carID == -1)
					break;
				deadCar.push_back(carID);
				//int RandomNumber = rand() % 10 + 1;//生成1~5随机数
				//CAR[carID - car0].addPT(RandomNumber);
				//++count;
				//if (count > 10)
				//	return true;
				break;
			}
		}
	}
	return deadCar;
}

void Dispatch::clearData()
{
	allCarSpeed.clear();
	priorityCarSpeed.clear();
	allCarPlanTime.clear();
	allCarEndTime.clear();
	priorityCarPlanTime.clear();
	priorityCarEndTime.clear();
	allCarFrom.clear();
	priorityCarFrom.clear();
	allCarTo.clear();
	priorityCarTo.clear();
}

void Dispatch::computeData(vector<Car> &CAR)
{
	clearData();

	Tsum = 0;
	Tsumpri = 0;
	priorityCarSize = 0;
	for (int i = 0; i < carSize; i++)
	{
		//存速度，实际出发时间，出发地，终止地
		Tsum += CAR[i].EndTime - CAR[i].planTime;
		allCarSpeed.push_back(CAR[i].speed);
		allCarPlanTime.push_back(CAR[i].planTime);
		allCarEndTime.push_back(CAR[i].EndTime);
		allCarFrom.insert(CAR[i].from);
		allCarTo.insert(CAR[i].to);
		if (CAR[i].priority == 1)
		{
			++priorityCarSize;
			Tsumpri += CAR[i].EndTime - CAR[i].planTime;
			priorityCarSpeed.push_back(CAR[i].speed);
			priorityCarPlanTime.push_back(CAR[i].planTime);
			priorityCarEndTime.push_back(CAR[i].EndTime);
			priorityCarFrom.insert(CAR[i].from);
			priorityCarTo.insert(CAR[i].to);
		}
	}

	//排序
	sort(allCarSpeed.begin(), allCarSpeed.end());
	sort(priorityCarSpeed.begin(), priorityCarSpeed.end());
	sort(allCarPlanTime.begin(), allCarPlanTime.end());
	sort(allCarEndTime.begin(), allCarEndTime.end());
	sort(priorityCarPlanTime.begin(), priorityCarPlanTime.end());
	sort(priorityCarEndTime.begin(), priorityCarEndTime.end());
}

int Dispatch::computeT()
{
	T = allCarEndTime[allCarEndTime.size() - 1];
	return T;
}

//计算优先车辆调度时间
int Dispatch::computeTpri()
{
	Tpri = priorityCarEndTime[priorityCarEndTime.size() - 1] - priorityCarPlanTime[0];
	return Tpri;
}

double toFive(double x)
{
	double a;
	a= (double)((round(x*100000.0))) / (double)(100000.0);
	return a;
}

//计算最终调度时间:TE = a*Tpri + T
int Dispatch::computeTE(vector<Car> &CAR)
{
	if (isDeadlock == true)
		return BADTIME;

	computeData(CAR);

	T = computeT();
	Tpri = computeTpri();

	//0.05*(车辆总数/优先车辆数)
	 double allCarNumber = ( double)(carSize);
	 double priorityCarNumber = ( double)(priorityCarSize);
	a1 = toFive(allCarNumber / priorityCarNumber);

	//0.2375*((所有车辆最高车速/所有车辆最低车速)/(优先车辆最高车速/优先车辆最低车速))
	 double allCarMaxSpeed = ( double)(allCarSpeed[allCarSpeed.size()-1]);
	 double allCarMinSpeed = ( double)(allCarSpeed[0]);
	 double priorityCarMaxSpeed = ( double)(priorityCarSpeed[priorityCarSpeed.size()-1]);
	 double priorityCarMinSpeed = ( double)(priorityCarSpeed[0]);
	a2 = toFive(toFive(allCarMaxSpeed / allCarMinSpeed) / toFive(priorityCarMaxSpeed / priorityCarMinSpeed));


	//0.2375*((所有车辆最晚出发时间/所有车辆最早出发时间)/(优先车辆最晚出发时间/优先车辆最早出发时间))
	 double allCarLastPlanTime = ( double)(allCarPlanTime[allCarPlanTime.size()-1]);
	 double allCarFirstPlanTime = ( double)(allCarPlanTime[0]);
	 double priorityCarLastPlanTime = ( double)(priorityCarPlanTime[priorityCarPlanTime.size()-1]);
	 double priorityCarFirstPlanTime = ( double)(priorityCarPlanTime[0]);
	a3 = toFive(toFive(allCarLastPlanTime / allCarFirstPlanTime) / toFive(priorityCarLastPlanTime / priorityCarFirstPlanTime));

	//0.2375*(所有车辆出发地分布/优先车辆出发地分布)
	 double allCarStartDistribute = ( double)(allCarFrom.size());
	 double priorityCarStartDistribute = ( double)(priorityCarFrom.size());
	a4 = toFive(allCarStartDistribute / priorityCarStartDistribute);

	//0.2375*(所有车辆终止地分布/优先车辆终止地分布)
	 double allCarEndDistribute = ( double)(allCarTo.size());
	 double priorityCarEndDistribute = ( double)(priorityCarTo.size());
	a5 = toFive(allCarEndDistribute / priorityCarEndDistribute);

	//求和
	 double a = (double)(0.05*a1) + (double)(0.2375*a2) + (double)(0.2375*a3) + (double)(0.2375*a4) + (double)(0.2375*a5);

	 cout << "a is " << a << endl;
	 cout << "T is " << T << ", Tpri is " << Tpri << endl;

	//计算最终调度时间
	TE = (int)(round(a*( double)(Tpri)+( double)(T)));

	return TE;
}

//计算最终总调度时间:TESum = b*Tsumpri + Tsum
int Dispatch::computeTEsum(vector<Car> &CAR)
{
	if (isDeadlock == true)
		return BADTIME;

	//0.8*(车辆总数/优先车辆数)
	//0.05*((所有车辆最高车速/所有车辆最低车速)/(优先车辆最高车速/优先车辆最低车速))
	//0.05*((所有车辆最晚出发时间/所有车辆最早出发时间)/(优先车辆最晚出发时间/优先车辆最早出发时间))
	//0.05*(所有车辆出发地分布/优先车辆出发地分布)
	//0.05*(所有车辆终止地分布/优先车辆终止地分布)

	//求和
	 double b = (double)(0.8*a1) + (double)(0.05*a2) + (double)(0.05*a3) + (double)(0.05*a4) + (double)(0.05*a5);

	 cout << "b is " << b << endl;
	 cout << "Tsum is " << Tsum << ", Tsumpri is " << Tsumpri << endl;

	//计算最终调度时间
	TEsum = (int)(round(b*( double)(Tsumpri)+( double)(Tsum)));

	return TEsum;
}

int Dispatch::searchBestBatchNum(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int batchNum, int t, int limitNum)
{
	int GlobalTime = 1;
	int bestBatchNum = batchNum;
	int bestTime = BADTIME;
	int count = 0;
	while (count < 100)
	{
		vector<Car> tempCAR;
		vector<Cross> tempCROSS;
		vector<Road> tempROAD;
		tempCAR.insert(tempCAR.begin(), CAR.begin(), CAR.end());
		tempCROSS.insert(tempCROSS.begin(), CROSS.begin(), CROSS.end());
		tempROAD.insert(tempROAD.begin(), ROAD.begin(), ROAD.end());

		int tempBatchNum = batchNum - 50 + count;
		Batch2(tempCAR, tempBatchNum,t);
		setLimitNum(limitNum);

		GlobalTime = 1;
		int tempTime = dispathMAIN(tempCAR, tempCROSS, tempROAD, GlobalTime, 0, BADTIME);
		
		tempTime = computeTE(tempCAR);
		if (tempTime < bestTime)
		{
			bestBatchNum = tempBatchNum;
			bestTime = tempTime;
		}

		cout << "batchNum " << tempBatchNum << " , Time is " << tempTime << ", bestBatchNum is " << bestBatchNum << ", best time is " << bestTime << endl;
		++count;
	}
	return bestBatchNum;
}

int Dispatch::searchBestLimitNum(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int batchNum,int limitNum)
{
	int GlobalTime = 1;
	int bestLimitNum = limitNum;
	int bestTime = BADTIME;
	int count = 0;
	while (count < 100)
	{
		vector<Car> tempCAR;
		vector<Cross> tempCROSS;
		vector<Road> tempROAD;
		tempCAR.insert(tempCAR.begin(), CAR.begin(), CAR.end());
		tempCROSS.insert(tempCROSS.begin(), CROSS.begin(), CROSS.end());
		tempROAD.insert(tempROAD.begin(), ROAD.begin(), ROAD.end());

		int tempLimitNum = limitNum + 250 - 5*count;
		Batch1(tempCAR, batchNum,1);
		setLimitNum(tempLimitNum);

		GlobalTime = 1;
		int tempTime = dispathMAIN(tempCAR, tempCROSS, tempROAD, GlobalTime, 0, BADTIME);
		//int tempTime= mainLoop(CAR, CROSS, ROAD, GlobalTime, 0, BADTIME);

		if (tempTime < bestTime)
		{
			bestLimitNum = tempLimitNum;
			bestTime = tempTime;
		}

		cout << "limitNum " << tempLimitNum << " , Time is " << tempTime << ", bestLimitNum is " << bestLimitNum << ", best time is " << bestTime << endl;
		++count;
	}
	return bestLimitNum;
}

void Dispatch::resetRoadCarNumber()
{
	roadCarNumber = 0;
}

void Dispatch::addRoadCarNumber()
{
	roadCarNumber = roadCarNumber + 1;
}

void Dispatch::subRoadCarNumber()
{
	roadCarNumber = roadCarNumber - 1;
}

bool Dispatch::controlInitCar(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime)
{
	int i, j, count;
	//扫描当前时刻可发非预置车数量SDCar，预置车数量presetCar
	vector<int> SDCar, presetCar;
	for (i = 0; i < crossSize; i++)
	{
		if ((int)(CROSS[i].StartCar.size()) == 0)
			continue;
		for (j = 0; j < (int)(CROSS[i].StartCar.size()); j++)
		{
			int carID = CROSS[i].StartCar[j] - car0;
			if (CAR[carID].PT <= GlobalTime)
			{
				if (CAR[carID].preset == 0)
					SDCar.push_back(carID);
				if (CAR[carID].preset == 1)
					presetCar.push_back(carID);
			}
		}
	}
	//如果没有可发非预置车，直接GG就好
	if ((int)(SDCar.size()) == 0)
		return false;

	/*****************注释部分是在没有batch()情况需要打开使用的**********************/
	//speedAll存所有的速度种类
	int num;
	set<int, less<int>> speedAll;
	for (num = 0; num < (int)(SDCar.size()); num++)
	{
		speedAll.insert(CAR[SDCar[num]].speed);
	}

	//速度从小到大排序
	count = 0;
	set<int>::iterator it;
	vector<vector<int>> speedIndex;
	for (it = speedAll.begin(); it != speedAll.end(); it++)
	{
		vector<int> tempVEC;
		speedIndex.push_back(tempVEC);
		for (num = 0; num < (int)(SDCar.size()); num++)
		{
			if (CAR[SDCar[num]].speed == *it)
				speedIndex[count].push_back(SDCar[num]);
		}
		++count;
	}

	//将所有索引链接
	vector<int> IndexAll;
	for (i = 0; i < (int)(speedIndex.size()); i++)
	{
		IndexAll.insert(IndexAll.end(), speedIndex[i].begin(), speedIndex[i].end());
	}

	////将所有索引链接
	//vector<int> IndexAll;
	//IndexAll.insert(IndexAll.end(), SDCar.begin(), SDCar.end());

	int N1 = (int)(presetCar.size());  //可发预置车数量
	int N2 = (int)(SDCar.size());	   //可发非预置车数量

	if (N1 >= RANUM)	//可发预置车数目够了，对所有非预置车PT+1
	{
		for (i = 0; i < (int)(IndexAll.size()); i++)
		{
			CAR[IndexAll[i]].addPT(1);
		}
	}

	if (N1 < RANUM)		//可发预置车数目不够，剩下的从非预置车中补充
	{
		int Need = RANUM - N1;	//最大补充数量

		if (N2 <= Need) 		//可发非预置车数量不够
			return false;

		if (N2 > Need)			//可发非预置车数量不够，超出的PT+1
		{
			//保护优先车:优先延迟非优先车
			count = 0;
			for (i = 0; i < (int)(IndexAll.size()); i++)
			{
				if (count >= (N2 - Need))
					break;
				if (CAR[IndexAll[i]].priority == 0)
				{
					CAR[IndexAll[i]].addPT(1);
					++count;
				}
			}
			if (count < (N2 - Need))
			{
				for (i = 0; i < (int)(IndexAll.size()); i++)
				{
					if (count >= (N2 - Need))
						break;
					if (CAR[IndexAll[i]].priority == 1)
					{
						CAR[IndexAll[i]].addPT(0);
						++count;
					}
				}
			}
		}
	}

	return true;
}

bool Dispatch::modifyPlantime(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime)
{
	int i, j;
	//扫描当前时刻可发非预置车数量SDCar，预置车数量presetCar
	vector<int> SDCar, presetCar;
	for (i = 0; i < crossSize; i++)
	{
		if ((int)(CROSS[i].StartCar.size()) == 0)
			continue;
		for (j = 0; j < (int)(CROSS[i].StartCar.size()); j++)
		{
			int carID = CROSS[i].StartCar[j] - car0;
			//注意：有些车PT已达，但是已经在路上了，不算可发车
			if (CAR[carID].PT <= (GlobalTime + 1) && CAR[carID].ATD == -1)
			{
				if (CAR[carID].preset == 0)
					SDCar.push_back(carID);
				if (CAR[carID].preset == 1)
					presetCar.push_back(carID);
			}
		}
	}
	//如果没有可发非预置车，直接GG就好
	if ((int)(SDCar.size()) == 0)
		return false;

	if (roadCarNumber >= RANUM)			//道路上车辆太多,不准发车，对所有非预置车PT+1
	{
		for (i = 0; i < (int)(SDCar.size()); i++)
		{
			int carID = SDCar[i];
			CAR[carID].addPT(1);
		}
		return false;
	}

	int N1 = (int)(presetCar.size());  //可发预置车数量
	int N2 = (int)(SDCar.size());	   //可发非预置车数量

	if (roadCarNumber < RANUM)			//道路上车辆不够,需要补充
	{
		int AllNeed = RANUM - roadCarNumber; //计算需要的总的发车数

		/*****************注释部分是在没有batch()情况需要打开使用的**********************/
		//speedAll存所有的速度种类
		int num, count;
		set<int, less<int>> speedAll;
		for (num = 0; num < (int)(SDCar.size()); num++)
		{
			speedAll.insert(CAR[SDCar[num]].speed);
		}

		//速度从小到大排序
		count = 0;
		set<int>::iterator it;
		vector<vector<int>> speedIndex;
		for (it = speedAll.begin(); it != speedAll.end(); it++)
		{
			vector<int> tempVEC;
			speedIndex.push_back(tempVEC);
			for (num = 0; num < (int)(SDCar.size()); num++)
			{
				if (CAR[SDCar[num]].speed == *it)
					speedIndex[count].push_back(SDCar[num]);
			}
			++count;
		}

		//将所有索引链接
		vector<int> IndexAll;
		for (i = 0; i < (int)(speedIndex.size()); i++)
		{
			IndexAll.insert(IndexAll.end(), speedIndex[i].begin(), speedIndex[i].end());
		}

		////将所有索引链接
		//vector<int> IndexAll;
		//IndexAll.insert(IndexAll.end(), SDCar.begin(), SDCar.end());

		if (N1 >= AllNeed)			//可发预置车数量已够，将所有非预置车PT+1
		{
			for (i = 0; i < (int)(IndexAll.size()); i++)
			{
				CAR[IndexAll[i]].addPT(1);
			}
		}

		if (N1 < AllNeed)			//可发预置车数量不够，还需要从非预置车中补充
		{
			int Need = AllNeed - N1;	//需要的最大非预置车数量

			if (N2 <= Need) 			//可发非预置车不够
				return false;

			if (N2 > Need)				//可发非预置车超出，超出的部分PT+1
			{
				//保护优先车:优先延迟非优先车
				count = 0;
				for (i = 0; i < (int)(IndexAll.size()); i++)
				{
					if (count >= (N2 - Need))
						break;
					if (CAR[IndexAll[i]].priority == 0)
					{
						CAR[IndexAll[i]].addPT(1);
						++count;
					}
				}
				if (count < (N2 - Need))
				{
					for (i = 0; i < (int)(IndexAll.size()); i++)
					{
						if (count >= (N2 - Need))
							break;
						if (CAR[IndexAll[i]].priority == 1)
						{
							CAR[IndexAll[i]].addPT(0);
							++count;
						}
					}
				}
			}
		}

	}

	return true;
}

//未区分优先车、非优先车
void Dispatch::Batch1(vector<Car> &CAR, int batchNum,int t)
{
	int i, j,num, count;

	//t-批次间隔大小

	//speedAll存所有的速度种类
	set<int, less<int>> speedAll;
	for (num = 0; num < (int)(CAR.size()); num++)
	{
		speedAll.insert(CAR[num].speed);
	}

	//速度从小到大排序
	count = 0;
	set<int>::iterator it;
	vector<vector<int>> speedIndex;
	for (it = speedAll.begin(); it != speedAll.end(); it++)
	{
		vector<int> tempVEC;
		speedIndex.push_back(tempVEC);
		for (num = 0; num < (int)(CAR.size()); num++)
		{
			if (CAR[num].speed == *it)
				speedIndex[count].push_back(num);
		}
		++count;
	}

	////各速度批次内按路径"长度"排序
	//for (i = 0; i < (int)(speedIndex.size()); i++)
	//{
	//	//获取同一个批次内所有的route大小种类
	//	set<int, less<int>> routeNumberAll;
	//	for (j = 0; j < (int)(speedIndex[i].size()); j++)
	//	{
	//		routeNumberAll.insert(CAR[speedIndex[i][j]].route.size());
	//	}
	//	//route由短到长排序
	//	set<int>::iterator it;
	//	vector<int> tempID;
	//	for (it = routeNumberAll.begin(); it != routeNumberAll.end(); it++)
	//	{
	//		for (j = 0; j < (int)(speedIndex[i].size()); j++)
	//		{
	//			if (CAR[speedIndex[i][j]].route.size() == *it)
	//				tempID.push_back(speedIndex[i][j]);
	//		}
	//	}
	//	for (j = 0; j < (int)(speedIndex[i].size()); j++)
	//	{
	//		speedIndex[i][j] = tempID[j];
	//	}
	//}

	////各速度批次内按发车时间排序
	//for (i = 0; i < (int)(speedIndex.size()); i++)
	//{
	//	//获取同一个批次内所有的route大小种类
	//	set<int, less<int>> planTimeAll;
	//	for (j = 0; j < (int)(speedIndex[i].size()); j++)
	//	{
	//		planTimeAll.insert(CAR[speedIndex[i][j]].planTime);
	//	}
	//	//route由短到长排序
	//	set<int>::iterator it;
	//	vector<int> tempID;
	//	for (it = planTimeAll.begin(); it != planTimeAll.end(); it++)
	//	{
	//		for (j = 0; j < (int)(speedIndex[i].size()); j++)
	//		{
	//			if (CAR[speedIndex[i][j]].planTime == *it)
	//				tempID.push_back(speedIndex[i][j]);
	//		}
	//	}
	//	for (j = 0; j < (int)(speedIndex[i].size()); j++)
	//	{
	//		speedIndex[i][j] = tempID[j];
	//	}
	//}

	//将所有索引链接
	vector<int> IndexAll;
	for (i = 0; i < (int)(speedIndex.size()); i++)
	{
		IndexAll.insert(IndexAll.end(), speedIndex[i].begin(), speedIndex[i].end());
	}

	//按批次修改plantime
	count = 0;
	int interval = (int)(CAR.size()) / batchNum;
	for (i = 0; i < batchNum - 1; i++)
	for (j = i * interval; j < (i + 1)*interval; j++)
	{
		CAR[IndexAll[count++]].addPT(t*i);
	}
	for (j = (int)(CAR.size()) - interval; j < (int)(CAR.size()); j++)
	{
		CAR[IndexAll[count++]].addPT(t*(batchNum - 1));
	}

	////批次递增
	//int a1 = interval * 0.1;
	//int d = ((int)(CAR.size()) - batchNum * a1)*(2 / (batchNum*(batchNum - 1)));
	//for (i = 0; i < batchNum - 1; i++)
	//	for (j = a1+i * d; j < a1+(i + 1)*d; j++)
	//	{
	//		CAR[IndexAll[count++]].addPT(2 * i);
	//	}
	//for (j = count; j < (int)(CAR.size()); j++)
	//	CAR[IndexAll[count++]].addPT(2 * (batchNum - 1)); 

	////批次递减
	//int a1 = interval * 5;
	//int d = (-(int)(CAR.size()) + batchNum * a1)*(2 / (batchNum*(batchNum - 1)));
	//for (i = 0; i < batchNum - 1; i++)
	//	for (j = a1 - i * d; j < a1 - (i + 1)*d; j++)
	//	{
	//		CAR[IndexAll[count++]].addPT(2 * i);
	//	}
	//for (j = count; j < (int)(CAR.size()); j++)
	//	CAR[IndexAll[count++]].addPT(2 * (batchNum - 1));

	////前期扩容,扩大前10时刻，每个时刻扩大数目100
	//int addClockNum = 100;
	//int addNumber = 50;
	//for (int time = 1; time <= addClockNum; time++)
	//{
	//	count = 0;
	//	for (i = 0; i < (int)(CAR.size()); i++)
	//	{
	//		if (count > addNumber)
	//			break;
	//		if (CAR[i].planTime == time)
	//		{
	//			CAR[i].setPT(CAR[i].planTime);
	//			++count;
	//		}
	//	}
	//}
}

vector<int> Dispatch::bathSort(vector<Car> &CAR, vector<int> &bath)
{
	int num, count, i;

	//speedAll存所有的速度种类
	set<int, less<int>> speedAll;
	for (num = 0; num < (int)(bath.size()); num++)
	{
		speedAll.insert(CAR[bath[num]].speed);
	}

	//速度从小到大排序
	count = 0;
	set<int>::iterator it;
	vector<vector<int>> speedIndex;
	for (it = speedAll.begin(); it != speedAll.end(); it++)
	{
		vector<int> tempVEC;
		speedIndex.push_back(tempVEC);
		for (num = 0; num < (int)(bath.size()); num++)
		{
			if (CAR[bath[num]].speed == *it)
				speedIndex[count].push_back(bath[num]);
		}
		++count;
	}

	//将所有索引链接
	vector<int> IndexAll;
	for (i = 0; i < (int)(speedIndex.size()); i++)
	{
		IndexAll.insert(IndexAll.end(), speedIndex[i].begin(), speedIndex[i].end());
	}

	bath.clear();
	bath.insert(bath.begin(), IndexAll.begin(), IndexAll.end());

	return bath;
}

vector<int> Dispatch::bathSort2(vector<Car> &CAR, vector<int> &bath)
{
	int num, count, i;

	//speedAll存所有的速度种类
	set<int, greater<int>> speedAll;
	for (num = 0; num < (int)(bath.size()); num++)
	{
		speedAll.insert(CAR[bath[num]].speed);
	}

	//速度从大到小排序
	count = 0;
	set<int>::iterator it;
	vector<vector<int>> speedIndex;
	for (it = speedAll.begin(); it != speedAll.end(); it++)
	{
		vector<int> tempVEC;
		speedIndex.push_back(tempVEC);
		for (num = 0; num < (int)(bath.size()); num++)
		{
			if (CAR[bath[num]].speed == *it)
				speedIndex[count].push_back(bath[num]);
		}
		++count;
	}

	//将所有索引链接
	vector<int> IndexAll;
	for (i = 0; i < (int)(speedIndex.size()); i++)
	{
		IndexAll.insert(IndexAll.end(), speedIndex[i].begin(), speedIndex[i].end());
	}

	bath.clear();
	bath.insert(bath.begin(), IndexAll.begin(), IndexAll.end());

	return bath;
}

//区分优先车、非优先车
void Dispatch::Batch2(vector<Car> &CAR, int batchNum, int t)
{
	int i, j, num, count;

	//t-批次间隔大小

	//将车辆按是否优先分为两个批次
	vector<int> bath1, bath2;
	for (num = 0; num < (int)(CAR.size()); num++)
	{
		if (CAR[num].priority == 1)
			bath1.push_back(num);
		if (CAR[num].priority == 0)
			bath2.push_back(num);
	}

	bath1 = bathSort(CAR, bath1);
	bath2 = bathSort(CAR, bath2);	
	
	//链接索引
	vector<int> IndexAll;
	IndexAll.insert(IndexAll.end(), bath1.begin(), bath1.end());
	IndexAll.insert(IndexAll.end(), bath2.begin(), bath2.end());

	//按批次修改plantime
	count = 0;

	bool IS = false;
	int KK = 0;
	int interval = (int)(IndexAll.size()) / batchNum;
	for (i = 0; i < batchNum-1; i++)
	{
		for (j = i * interval; j < (i + 1)*interval; j++)
		{
			if (i == 40)
				break;
			if (CAR[IndexAll[count]].priority == 1)
				CAR[IndexAll[count]].addPT(0);
			if (CAR[IndexAll[count]].priority == 0 && KK==0)  //第一批非优先车
			{
				CAR[IndexAll[count]].addPT(i*t);
			}
			if (CAR[IndexAll[count]].priority == 0 && KK == 1)  //后面批次的非优先车
			{
				CAR[IndexAll[count]].addPT(t*(i));
			}
			++count;
		}
		if (IS == true)
			++KK;
	}		
}

bool Dispatch::isAllEnd(vector<Car> &CAR)
{
	int count = 0;
	for (int i = 0; i < (int)(CAR.size()); i++)
	{
		if (CAR[i].state == 0)
		{
			++count;
			break;
			//cout << "car-" << CAR[i].id << " state==0" << endl;
		}
	}
	if (count == 0) //没有车可被调度，结束了
		return true;
	else
		return false;
}

bool Dispatch::subEndCarPT(vector<Car> &tempCAR, int count)
{
	int i,num;

	int changeNum, rate;
	if (count < 100)
	{
		changeNum = 1000;
		rate = 1;
	}
	if (count > 300 && count < 500)
	{
		changeNum = 10000;
		rate = 5;
	}
	if (count > 1000)
	{
		changeNum = 10000;
		rate = 2;
	}

	////随机选择一些车
	for (i = 0; i < changeNum; i++)
	{
		num = rand() % (int)(tempCAR.size()) + 1;
		tempCAR[num].subPT(rate);
	}

	//cout << endCar[endCar.size() - 1][num] << ":";
	//cout << tempCAR[endCar[endCar.size() - 1][num] - tempCAR[0].id].PT << endl;
	return true;
}

int Dispatch::gainWaitNum(vector<Car> &CAR)
{
	int count = 0;
	for (int i = 0; i < (int)(CAR.size()); i++)
	{
		if (CAR[i].state == 0)
			++count;
	}
	return count;
}

bool Dispatch::clearSF(vector<Car> &tempCar)
{
	for (int num = 0; num < (int)(tempCar.size()); num++)
	{
		tempCar[num].renew();
	}
	return true;
}

bool Dispatch::isAllTerminate(vector<Car> &CAR)
{
	int count = 0;
	for (int i = 0; i < (int)(CAR.size()); i++)
	{
		if (CAR[i].isTerminate == 0)
		{
			++count;
			break;
		}
		//else
			//cout << "car-" << CAR[i].id << " is not terminated. " << endl;
	}
	if (count == 0)
		return true;
	else
		return false;
}

//获取位于roadID路的dir方向道路中的第一优先级等待车
int Dispatch::getCar(int roadID, int dir, vector<Road> &ROAD, vector<Car> &CAR)
{
	int i, j, count, k;
	roadID = roadID - ROAD[0].id;
	//扫描第一辆‘等待+过下一条路+优先+无阻挡’的车，直接返回结果
	for (i = ROAD[roadID].length - 1; i >= 0; i--) //位置从高到低
	{
		for (j = 0; j < ROAD[roadID].channel; j++) //车道从小到大
		{
			if (ROAD[roadID].roadCar[dir][j][i] == -1)
				continue;
			int carID = ROAD[roadID].roadCar[dir][j][i] - car0;
			//扫描前方是否有阻挡
			count = 0;
			if (i < ROAD[roadID].length - 1)
			{
				for (k = i + 1; k < ROAD[roadID].length; k++)
				{
					if (ROAD[roadID].roadCar[dir][j][k] != -1)
					{
						++count;
						break;
					}
				}
			}
			if (CAR[carID].state == 0 && CAR[carID].toNextRoad == 1 && CAR[carID].priority==1 && count==0)
				return (carID + car0);
		}
	}

	//前面扫描失败，重新扫描得到第一辆‘等待+过下一条路’的车即可
	for (i = ROAD[roadID].length - 1; i >= 0; i--) //位置从高到低
	{
		for (j = 0; j < ROAD[roadID].channel; j++) //车道从小到大
		{
			if (ROAD[roadID].roadCar[dir][j][i] == -1)
				continue;
			int carID = ROAD[roadID].roadCar[dir][j][i] - car0;
			//等待+过下一条路，直接返回结果
			if (CAR[carID].state == 0 && CAR[carID].toNextRoad == 1)
				return (carID + car0);
		}
	}

	return -1; //两次扫描失败，这条路上已经没有要过下个路口的车
}

bool Dispatch::isConflict(int nowOrder, int carID, vector<int> &roadAll, vector<int> &dir, vector<Road> &ROAD, vector<Car> &CAR)
{
	//获取当前车辆要去的道路
	int NEXTRoadID = CAR[carID - car0].nextRoad;
	int NEXTReverse = CAR[carID - car0].nextReverse;

	//即将到达终点且没有下一条路，直接放行
	if (CAR[carID - car0].nextCross == CAR[carID - car0].to  && NEXTRoadID == -1)
		return false;

	//即将到达终点且有下一条路，需要看是否有优先车跟它抢车道
	//看其他三条道路的第一优先级是否也有去这条路的车，且优先级比carID大的话就返回false，否则true
	for (int i = 0; i < 4; i++)
	{
		if (i == nowOrder)
			continue;
		if (roadAll[i] == -1) //没有路
			continue;
		int otherRoadID = roadAll[i];
		int otherDri = dir[i];
		int otherCarID = getCar(otherRoadID, otherDri, ROAD, CAR);
		if (otherCarID == -1) //该路上没有可以去下个路口的车
			continue;

		//当前等待被调度的车没有优先权
		if (CAR[carID - car0].priority == 0)
		{
			//如果有优先的车要去这条路的这个方向,直接GG
			if ((CAR[otherCarID - car0].nextRoad == NEXTRoadID)
				&& (CAR[otherCarID - car0].nextReverse == NEXTReverse)
				&& (CAR[otherCarID - car0].priority == 1))
				return true;

			//如果有两辆车抢同一条道路的同一侧向车道,而且另一辆车转向优先级更高，那就冲突
			if ((CAR[otherCarID - car0].nextRoad == NEXTRoadID)
				&& (CAR[otherCarID - car0].nextReverse == NEXTReverse)
				&& (CAR[otherCarID - car0].nextCrossDirection < CAR[carID - car0].nextCrossDirection))
				return true;
		}

		//当前等待被调度的车有优先权
		if (CAR[carID - car0].priority == 1)
		{
			//只有优先的车要去这条路的这个方向，那就按直>左>右判断，转弯方向更高就GG
			if ((CAR[otherCarID - car0].nextRoad == NEXTRoadID)
				&& (CAR[otherCarID - car0].nextReverse == NEXTReverse)
				&& (CAR[otherCarID - car0].priority == 1)
				&& (CAR[otherCarID - car0].nextCrossDirection < CAR[carID - car0].nextCrossDirection))
				return true;
		}
	}
	return false;
}

bool Dispatch::isRoadOver(int roadID,int dir,vector<Road> &ROAD, vector<Car> &CAR)
{
	//当没有可调度车，说明结束
	if (roadID == -1)
		return true;

	int i, j;
	int roadNum = roadID - road0;
	for (i = 0; i < ROAD[roadNum].channel; i++)
	{
		for (j = ROAD[roadNum].length - 1; j >= 0; j--)
		{
			if (ROAD[roadNum].roadCar[dir][i][j] == -1)
				continue;
			int carID = ROAD[roadNum].roadCar[dir][i][j] - car0;
			if (CAR[carID].state == 0)
				return false;
		}
	}
	return true;
}

void Dispatch::dispathINIT(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime, int TT)
{
	int num, m;
	vector<int> carCut;

	car0 = CAR[0].id, carSize = (int)(CAR.size());
	road0 = ROAD[0].id, roadSize = (int)(ROAD.size());
	cross0 = CROSS[0].id, crossSize = (int)(CROSS.size());

	if (TT >= 1)
	{
		EmptyCarportNumber = 0;
		//backup_GlobalTime = 0;
		//backup_GlobalTime2 = 0;
		for (num = 0; num < carSize; num++)
			CAR[num].renew();
		for (num = 0; num < roadSize; num++)
			ROAD[num].renew();
		for (num = 0; num < crossSize; num++)
			CROSS[num].renew();
		/*if (TT > 2)
			subEndCarPT(CAR, 50);*/
		/*if(TT==2)
			recoveryPT(CAR);
		if (TT == 1)
			subEndCarPT(CAR, 50);*/
		resetRoadCarNumber();
	}

	/************************************************T0时刻***************************************/
		//设置进入各条道路的排队队列,T0时刻全部是直行
	
	for (num = 0; num < carSize; num++)
	{
		//将车存入车库，并设置车的下一个道路
		CROSS[CAR[num].from - cross0].addStartCar(CAR[num].id);

		int roadID = CAR[num].route[0] - road0;
		if (CAR[num].from == ROAD[roadID].from) //正向
		{
			CAR[num].addRverse(0);
			CAR[num].isRVER(0);
		}
		if (CAR[num].from == ROAD[roadID].to) //反向
		{
			CAR[num].addRverse(1);
			CAR[num].isRVER(1);
		}
		//计算正反向和最大速度
		for (int i = 0; i < (int)(CAR[num].route.size()); i++)
		{
			int newRoadID = CAR[num].route[i] - road0;
			if (i > 0)
			{
				if (CAR[num].reverse[i - 1] == 0) //上一条路的from-to就是车的行进方向
				{
					int lastRoad = CAR[num].route[i - 1] - road0;
					if (ROAD[lastRoad].to == ROAD[newRoadID].from)
						CAR[num].addRverse(0);
					else
						CAR[num].addRverse(1);
				}
				if (CAR[num].reverse[i - 1] == 1) //上一条路的to-from就是车的行进方向
				{
					int lastRoad = CAR[num].route[i - 1] - road0;
					if (ROAD[lastRoad].from == ROAD[newRoadID].from)
						CAR[num].addRverse(0);
					else
						CAR[num].addRverse(1);
				}
			}

			if (CAR[num].speed < ROAD[CAR[num].route[i] - road0].speed)
				CAR[num].addMaxSpeed(CAR[num].speed);
			else
				CAR[num].addMaxSpeed(ROAD[CAR[num].route[i] - road0].speed);
		}
	}

	//根据优先权，将每个路口车库内的车重新排序：优先车在前，并按planTime升序排列，再在各时间批次内保持ID升序排列
	vector<int> priorityCar, tempCar;
	vector<int>::iterator pos;
	set<int, less<int>> planTimeAll;
	set<int>::iterator it;
	for (num = 0; num < crossSize; num++)
	{
		if (CROSS[num].StartCar.size() == 0)
			continue;
		priorityCar.clear();
		for (int i = 0; i < (int)(CROSS[num].StartCar.size()); i++)
		{
			if (CAR[CROSS[num].StartCar[i]-car0].priority == 1)
				priorityCar.push_back(CROSS[num].StartCar[i]);
		}

		//删除原来的优先车辆
		for (int j = 0; j < (int)(priorityCar.size()); j++)
		{
			pos = find(CROSS[num].StartCar.begin(), CROSS[num].StartCar.end(), priorityCar[j]);
			if (pos != CROSS[num].StartCar.end())
				CROSS[num].StartCar.erase(pos);
		}

		//将优先车辆放在排头
		CROSS[num].StartCar.insert(CROSS[num].StartCar.begin(), priorityCar.begin(), priorityCar.end());

		//将车库的车送入各条路的排队队列
		for (int i = 0; i < (int)(CROSS[num].StartCar.size()); i++)
		{
			int carID = CROSS[num].StartCar[i] - car0;
			if (CAR[carID].PT <= GlobalTime)
			{
				int roadID = CAR[carID].route[0] - road0;
				if (CAR[carID].from == ROAD[roadID].from) //正向
				{
					ROAD[roadID].addWaitCar(0, 0, CAR[carID].id);
				}
				if (CAR[carID].from == ROAD[roadID].to) //正向
				{
					ROAD[roadID].addWaitCar(1, 0, CAR[carID].id);
				}
			}
		}
	}

	//控制初始发车数量
	controlInitCar(CAR, CROSS, ROAD, GlobalTime);

	//对于每条道路，每个方向，每个车道，根据车当前速度，依次选车出行
	for (num = 0; num < roadSize; num++)
	{
		for (m = 0; m < 2; m++)
		{
			if (m == 1 && ROAD[num].isDuplex == 0)
				break;

			if ((int)(ROAD[num].WaitCar[m][0].size()) == 0) //进单向道路的车为空
				continue;

			int carNum = 0, i = 0, flag = 0, lastCarId = 0, count = 0;	//i表示车道id
			carCut.clear();
			while (carNum < (int)(ROAD[num].WaitCar[m][0].size()))
			{
				if (ROAD[num].roadCar[m][i][0] != -1) //车道已满，换下一条车道
				{
					++i;
					flag = 1;
					if (i == ROAD[num].channel)
						break;
					continue;
				}
				int carID = ROAD[num].WaitCar[m][0][carNum] - car0;

				//更新当前速度
				if (CAR[carID].speed > ROAD[num].speed)
					CAR[carID].setNowSpeed(ROAD[num].speed);
				else
					CAR[carID].setNowSpeed(CAR[carID].speed);

				//更新当前位置
				if (count == 0 || flag == 1) //第一辆车或者换道的第一辆车
				{
					CAR[carID].updateLocation(ROAD[num].id, i, CAR[carID].nowSpeed); //更新车的位置
					CAR[carID].setATD(GlobalTime);	//设置实际出发时间
					ROAD[num].addRoadCar(m, i, CAR[carID].location[2] - 1, carID + car0); //更新道路的车辆位置
					lastCarId = carID; //更新上一个位置车辆id
					flag = 0;
					carCut.push_back(carID + car0);
					++carNum;
					++count;
					continue;
				}

				if (CAR[carID].nowSpeed < CAR[lastCarId].location[2])	//空间够
				{
					CAR[carID].updateLocation(ROAD[num].id, i, CAR[carID].nowSpeed);
					CAR[carID].setATD(GlobalTime);
					ROAD[num].addRoadCar(m, i, CAR[carID].location[2] - 1, carID + car0);
					lastCarId = carID;
					carCut.push_back(carID + car0);
					++carNum;
					++count;
					continue;
				}

				CAR[carID].updateLocation(ROAD[num].id, i, CAR[lastCarId].location[2] - 1); //空间不够
				CAR[carID].setATD(GlobalTime);
				ROAD[num].addRoadCar(m, i, CAR[carID].location[2] - 1, carID + car0);
				lastCarId = carID;
				carCut.push_back(carID + car0);
				++carNum;
				++count;
			}

			//清空道路排队车列
			ROAD[num].clearWaitCar(m);
			if (m == 0) //正向
				CROSS[ROAD[num].from - cross0].subStartCar(carCut);
			else //逆向
				CROSS[ROAD[num].to - cross0].subStartCar(carCut);
		}
	}
}

void Dispatch::setState(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime)
{
	int num, m, i, j, k, count;

	//计算nextRoad,nextRoadSpeed,nextCrossDirection,nextCrossDistance
	for (num = 0; num < carSize; num++)
	{
		CAR[num].toNextRoad = 0;
		CAR[num].setState(-1);
		if (CAR[num].isTerminate == 1)
			continue;
		if (CAR[num].ATD > 0)
		{
			CAR[num].computeNEXT(ROAD, CROSS);
			addRoadCarNumber();
		}
	}

	//逐条道路从出口到入口扫描设置车辆状态
	for (num = 0; num < roadSize; num++)
	{
		for (m = 0; m < 2; m++) //双向道路
		{
			if (m == 1 && ROAD[num].isDuplex == 0)
				break;
			for (i = 0; i < ROAD[num].channel; i++) //车道数
			{
				int carID;
				count = 0;

				int sum = accumulate(ROAD[num].roadCar[m][i], ROAD[num].roadCar[m][i] + ROAD[num].length, 0);
				if (sum == -ROAD[num].length)
					continue;

				for (j = ROAD[num].length - 1; j >= 0; j--) //位置
				{
					carID = ROAD[num].roadCar[m][i][j] - car0;

					if (ROAD[num].roadCar[m][i][j] == -1)
						continue;

					if (CAR[carID].isTerminate == 1)
						continue;

					//扫描路上所有车的位置
					count = 0;
					for (k = j + 1; k < ROAD[num].length; k++)
					{
						if (ROAD[num].roadCar[m][i][k] != -1)
						{
							++count;
							break;
						}
					}

					if (count == 0)	//不受阻挡
					{
						if (CAR[carID].nextCrossDistance < CAR[carID].maxSpeed)	//可跨过路口
						{
							CAR[carID].setState(0);	//设置为等待行驶
							CAR[carID].setToNextRoad(1);
							continue;
						}

						//想要下一步到达终点路口的车，前面必须不能有车阻挡，且由于nextRoadSpeed=-1所以不可跨过路口
						if (CAR[carID].nextCrossDistance >= CAR[carID].maxSpeed)	//不可跨过路口
						{
							CAR[carID].setNowSpeed(CAR[carID].maxSpeed);
							int oldPosition = CAR[carID].location[2];
							CAR[carID].updateLocation(ROAD[num].id, i, oldPosition + CAR[carID].nowSpeed); //更新位置
							ROAD[num].subRoadCar(m, i, oldPosition - 1); //删除旧位置
							ROAD[num].addRoadCar(m, i, CAR[carID].location[2] - 1, carID + car0);
							CAR[carID].setState(1);	//设置为终止状态
							CAR[carID].computeNEXT(ROAD, CROSS); //更新状态
							continue;
						}
					}

					//受阻挡

					//确定阻挡车的位置k
					int carIDB = ROAD[num].roadCar[m][i][k] - car0;
					CAR[carID].setBlockDistance(k - j);		//与阻挡车的距离
					if (CAR[carIDB].state == 1)	 //受阻挡且前面是终止车辆
					{
						int oldPosition = CAR[carID].location[2];
						ROAD[num].subRoadCar(m, i, oldPosition - 1); //删除旧位置
						//两车间距足够宽
						if (CAR[carID].maxSpeed <= (CAR[carID].blockDistance - 1))
						{
							CAR[carID].setNowSpeed(CAR[carID].maxSpeed);
							CAR[carID].updateLocation(ROAD[num].id, i, oldPosition + CAR[carID].maxSpeed); //更新位置
							ROAD[num].addRoadCar(m, i, CAR[carID].location[2] - 1, carID + car0);
						}
						//两车间距不够
						if (CAR[carID].maxSpeed > (CAR[carID].blockDistance - 1))
						{
							CAR[carID].setNowSpeed(CAR[carID].blockDistance - 1);//注意：进行了减速，下次可能需要升速
							CAR[carID].updateLocation(ROAD[num].id, i, oldPosition + CAR[carID].nowSpeed); //更新位置
							ROAD[num].addRoadCar(m, i, CAR[carID].location[2] - 1, carID + car0);
						}
						CAR[carID].setState(1);
						CAR[carID].computeNEXT(ROAD, CROSS); //更新状态
					}

					if (CAR[carIDB].state == 0)	 //受阻挡且前面是等待车辆
					{
						int oldPosition = CAR[carID].location[2];
						//两车间距足够宽
						if ((CAR[carID].blockDistance - 1) >= CAR[carID].maxSpeed)
						{
							CAR[carID].updateLocation(ROAD[num].id, i, oldPosition + CAR[carID].maxSpeed); //更新位置
							ROAD[num].subRoadCar(m, i, oldPosition - 1); //删除旧位置
							ROAD[num].addRoadCar(m, i, CAR[carID].location[2] - 1, carID + car0);
							CAR[carID].setState(1);
							CAR[carID].computeNEXT(ROAD, CROSS); //更新状态
						}
						//两车间距不够
						if ((CAR[carID].blockDistance-1) < CAR[carID].maxSpeed)
						{
							CAR[carID].setState(0);
							if (CAR[carID].nextCrossDistance < CAR[carID].maxSpeed)	//可跨过路口
							{
								CAR[carID].setToNextRoad(1);
							}
						}
					}
				}
			}
		}
	}
}

bool Dispatch::moveToNextRoad(int carID, vector<Car> &CAR, vector<Road> &ROAD, vector<Cross> &CROSS, int &GlobalTime)
{
	//等待进入的车都在road.waitcar中排队
	//对于各个方向的车，按前后->车道从小到达排序
	int  m, i, j;
	carID = carID - car0;

	int oldRoadID = CAR[carID].location[0] - road0;
	int oldCHA = CAR[carID].location[1];
	int oldPosition = CAR[carID].location[2];

	//先判断当前道路上是否有终止车辆挡道
	int count = 0;
	for (j = oldPosition; j < ROAD[oldRoadID].length; j++)
	{
		if (ROAD[oldRoadID].roadCar[CAR[carID].isReverse][oldCHA][j] != -1 )
		{
			++count;
			break;
		}
	}

	//去终点路口的车辆（前方不能有车阻挡）
	if (count == 0 && CAR[carID].nextCross == CAR[carID].to)
	{
		CAR[carID].setState(1);
		CAR[carID].setIsTerminate(1);
		CAR[carID].setEndTime(GlobalTime);
		subRoadCarNumber();
		ROAD[oldRoadID].subRoadCar(CAR[carID].isReverse, oldCHA, oldPosition - 1); //将到达终点的车辆移除
		return false;
	}

	//如果有终止车辆挡道
	if (count == 1)
	{
		//当前道路正反向
		m = CAR[carID].isReverse;
		CAR[carID].setBlockDistance(j - oldPosition + 1);		//与阻挡车的距离
		int oldPosition = CAR[carID].location[2];
		ROAD[oldRoadID].subRoadCar(m, oldCHA, oldPosition - 1); //删除旧位置
		//两车间距足够宽
		if (CAR[carID].maxSpeed <= (CAR[carID].blockDistance - 1))
		{
			CAR[carID].updateLocation(ROAD[oldRoadID].id, oldCHA, oldPosition + CAR[carID].maxSpeed); //更新位置
			ROAD[oldRoadID].addRoadCar(m, oldCHA, CAR[carID].location[2] - 1, carID + car0);
		}
		//两车间距不够
		if (CAR[carID].maxSpeed > (CAR[carID].blockDistance - 1))
		{
			CAR[carID].setNowSpeed(CAR[carID].blockDistance - 1);//注意：进行了减速，下次可能需要升速
			CAR[carID].updateLocation(ROAD[oldRoadID].id, oldCHA, oldPosition + CAR[carID].nowSpeed); //更新位置
			ROAD[oldRoadID].addRoadCar(m, oldCHA, CAR[carID].location[2] - 1, carID + car0);
		}
		CAR[carID].setState(1);
		CAR[carID].computeNEXT(ROAD, CROSS); //更新状态

		return false;
	}

	//m存在下一条道路上的正反向
	m = CAR[carID].nextReverse;

	int stopPosition = CAR[carID].nextRoadSpeed - CAR[carID].nextCrossDistance;
	if (stopPosition < 0)
		stopPosition = 0;
	int NextRoadID = CAR[carID].nextRoad - road0;

	if (stopPosition > 0)
	{
		int CHA = -1, POS = -1, isend = 0;
		for (i = 0; i < ROAD[NextRoadID].channel; i++) //在正向车道上寻找可插入位置
		{
			for (j = 0; j < stopPosition; j++)
			{
				if (ROAD[NextRoadID].roadCar[m][i][j] == -1)
				{
					CHA = i; //没有车阻挡
					POS = j;
					if (j == stopPosition - 1) //一个车道全空，结束
					{
						isend = 1;
						break;
					}
					continue;
				}
				if (ROAD[NextRoadID].roadCar[m][i][j] != -1)
				{
					int blockCarID = ROAD[NextRoadID].roadCar[m][i][j] - car0;
					if (CAR[blockCarID].state == 1) //阻挡车已终止
					{
						CHA = i;
						POS = j - 1;
						if (POS > -1)   //搜索到可插入位置就结束
							isend = 1;
						break; //换下一个车道检索
					}
					if (CAR[blockCarID].state == 0) //阻挡车等待
					{
						CHA = -1;
						POS = -1;
						isend = 1; //结束
						break;
					}
				}
			}

			if (isend == 1)
				break;
		}

		if (CHA > -1) //可插入
		{
			if (POS == -1) //下条道路的所有第一个位置全部有终止状态的车
			{
				//更新位置
				CAR[carID].updateLocation(CAR[carID].location[0], oldCHA, ROAD[oldRoadID].length);
				ROAD[oldRoadID].subRoadCar(CAR[carID].isReverse, oldCHA, oldPosition - 1);
				ROAD[oldRoadID].addRoadCar(CAR[carID].isReverse, oldCHA, CAR[carID].location[2] - 1, carID + car0);
				//更新状态
				CAR[carID].setState(1);
				CAR[carID].computeNEXT(ROAD, CROSS); //更新状态
				return false;
			}

			//更新位置
			CAR[carID].updateLocation(ROAD[NextRoadID].id, CHA, POS + 1);
			ROAD[oldRoadID].subRoadCar(CAR[carID].isReverse, oldCHA, oldPosition - 1);
			ROAD[NextRoadID].addRoadCar(m, CHA, POS, carID + car0);
			
			//更新状态
			CAR[carID].setState(1);
			CAR[carID].passRoadNumber += 1;
			CAR[carID].computeNEXT(ROAD, CROSS); //更新状态
			return true;
		}
	}

	if (stopPosition == 0)
	{
		//更新位置
		CAR[carID].updateLocation(CAR[carID].location[0], oldCHA, ROAD[oldRoadID].length);
		ROAD[oldRoadID].subRoadCar(CAR[carID].isReverse, oldCHA, oldPosition - 1);
		ROAD[oldRoadID].addRoadCar(CAR[carID].isReverse, oldCHA, CAR[carID].location[2] - 1, carID + car0);
		//更新状态
		CAR[carID].setState(1);
		CAR[carID].computeNEXT(ROAD, CROSS); //更新状态
		return false;
	}

	return false;
}

bool Dispatch::moveOnTheRoad(int carID, vector<Car> &CAR, vector<Road> &ROAD, vector<Cross> &CROSS, int &GlobalTime)
{
	int  m,j,count;

	int oldRoadID = CAR[carID].location[0] - road0;
	int oldCHA = CAR[carID].location[1];
	int oldPosition = CAR[carID].location[2];

	m = CAR[carID].isReverse;
	//获取阻挡车位置
	count = 0;
	for (j = oldPosition; j < ROAD[oldRoadID].length; j++)
	{
		if (ROAD[oldRoadID].roadCar[m][oldCHA][j] != -1)
		{
			++count;
			break;
		}
	}

	if (count == 0) //不被阻挡
	{
		CAR[carID].setNowSpeed(CAR[carID].maxSpeed);
		int oldPosition = CAR[carID].location[2];
		CAR[carID].updateLocation(ROAD[oldRoadID].id, oldCHA, oldPosition + CAR[carID].nowSpeed); //更新位置
		ROAD[oldRoadID].subRoadCar(m, oldCHA, oldPosition - 1); //删除旧位置
		ROAD[oldRoadID].addRoadCar(m, oldCHA, CAR[carID].location[2] - 1, carID + car0);
		CAR[carID].setState(1);	//设置为终止状态
		CAR[carID].computeNEXT(ROAD, CROSS); //更新状态
		return true;
	}

	if (count == 1) //被阻挡
	{
		CAR[carID].setBlockDistance(j - oldPosition + 1);
		if (CAR[carID].maxSpeed > (CAR[carID].blockDistance-1))		//空间不够
			CAR[carID].setNowSpeed(CAR[carID].blockDistance - 1); 
		if (CAR[carID].maxSpeed <= (CAR[carID].blockDistance - 1))	//空间够大
			CAR[carID].setNowSpeed(CAR[carID].maxSpeed); 	
	}

	//更新位置
	CAR[carID].updateLocation(ROAD[oldRoadID].id, oldCHA, oldPosition + CAR[carID].nowSpeed);
	ROAD[oldRoadID].subRoadCar(m, oldCHA, oldPosition - 1);
	ROAD[oldRoadID].addRoadCar(m, oldCHA, CAR[carID].location[2] - 1, carID + car0);
	//更新状态
	CAR[carID].setState(1);
	CAR[carID].computeNEXT(ROAD, CROSS); //更新状态
	
	return true;
}

//调度第num个车库内等待的优先车
bool Dispatch::moveCarportPriorityCar(int crossNum, vector<Car> &CAR, vector<Road> &ROAD, vector<Cross> &CROSS, int &GlobalTime)
{
	int  i, m, j;

	if ((int)(CROSS[crossNum].StartCar.size()) == 0)
		return false;

	//车库内等待的车划归到请求队列中:StartCar里已经是优先级+ID升序，现在要对PT排序(要保证预置车先发)
	//对于到了PT发车时间而不能发出的车要PT+1(在最后的车库调度时刻)
	set<int, less<int>> tempRoadAll;
	vector<int> waitCar;
	for (i = 0; i < (int)(CROSS[crossNum].StartCar.size()); i++)
	{
		int carID = CROSS[crossNum].StartCar[i] - car0;

		//优先车上路——只扫描车库中排在前面的优先车，一旦扫描到非优先车可以直接退出
		if (CAR[carID].priority == 0)
			break;

		int roadID = CAR[carID].route[0] - road0;
		if (CAR[carID].PT <= GlobalTime)
		{			
			tempRoadAll.insert(roadID);
			waitCar.push_back(carID + car0);
		}	
	}
	if ((int)(waitCar.size()) == 0)
		return false;

	vector<int> roadAll;
	set<int>::iterator it;
	for (it = tempRoadAll.begin(); it != tempRoadAll.end(); it++)
	{
		roadAll.push_back(*it);
	}

	//将只存了优先车的waitCar按PT排序
	//(现在的优先级是都是:实际发车时间为首序，ID为次序，vector里都是到达了发车时间的优先车)
	set<int, less<int>> PTAll;
	vector<int> tempCar;
	for (i = 0; i < (int)(waitCar.size()); i++)
	{
		PTAll.insert(CAR[waitCar[i] - car0].PT);
	}
	for (it = PTAll.begin(); it != PTAll.end(); it++)
	{
		for (i = 0; i < (int)(waitCar.size()); i++)
		{
			if (CAR[waitCar[i] - car0].PT == *it)
				tempCar.push_back(waitCar[i]);
		}
	}
	waitCar.clear();
	waitCar.insert(waitCar.begin(),tempCar.begin(), tempCar.end());

	//将车送入道路排队
	for (i = 0; i < (int)(waitCar.size()); i++)
	{
		int carID = waitCar[i] - car0;
		int roadID = CAR[carID].route[0] - road0;
		if (CAR[carID].from == ROAD[roadID].from) //正向
			ROAD[roadID].addWaitCar(0, 0, waitCar[i]);
		if (CAR[carID].from == ROAD[roadID].to) //反向
			ROAD[roadID].addWaitCar(1, 0, waitCar[i]);
	}

	//开始派车，注意前方阻挡车是终止车还是等待车
	vector<int> carCut;
	for (int q = 0; q < (int)(roadAll.size()); q++)
	{
		int roadID = roadAll[q];
		for (m = 0; m < 2; m++)
		{
			if ((int)(ROAD[roadID].WaitCar[m][0].size()) == 0) //进单向道路的车为空
				continue;

			int carNum = 0, i = 0, flag = 0, lastCarId = -1, count = 0;	//i表示车道id
			carCut.clear();
			while (carNum < (int)(ROAD[roadID].WaitCar[m][0].size()))
			{
				if (ROAD[roadID].roadCar[m][i][0] != -1) //车道已满，换下一条车道
				{
					int carID = ROAD[roadID].roadCar[m][i][0] - car0;
					//根据车道固定进入规则，当前车道被等待车堵头，直接GG
					if (CAR[carID].state == 0)
						break;
					++i;
					flag = 1;
					if (i == ROAD[roadID].channel)
						break;
					continue;
				}

				int carID = ROAD[roadID].WaitCar[m][0][carNum] - car0;

				//更新当前速度
				if (CAR[carID].speed > ROAD[roadID].speed)
					CAR[carID].setNowSpeed(ROAD[roadID].speed);
				else
					CAR[carID].setNowSpeed(CAR[carID].speed);				

				//进入车道的第一辆车
				if (count == 0 || flag == 1) 
				{
					//查询挡道车辆
					int blockPOS = -1;
					for (j = 1; j < CAR[carID].nowSpeed; j++)
					{
						if (ROAD[roadID].roadCar[m][i][j] != -1)
						{
							blockPOS = j + 1;
							break;
						}
					}

					//发现有车挡道
					if (blockPOS != -1)
					{
						if (CAR[carID].nowSpeed > (blockPOS - 1))  //间距不够
						{
							int blockCarID = ROAD[roadID].roadCar[m][i][j] - car0;
							//如果被阻挡车辆是等待的，不影响后面的优先车
							if (CAR[blockCarID].state == 0)
							{
								////清空道路排队车列
								//ROAD[roadID].clearWaitCar(0);
								//ROAD[roadID].clearWaitCar(1);
								////删除车库中已经进入道路的车
								//CROSS[crossNum].subStartCar(carCut);
								//return false;
								++carNum;
								flag = 1;	//如果车道的第一辆车进不去，接下来的车是新的第一辆车
								continue;
							}
							//如果被阻挡车辆是终止的，那就放行
							if (CAR[blockCarID].state == 1)
							{
								CAR[carID].setNowSpeed(blockPOS - 1);
							}						
						}
					}

					CAR[carID].updateLocation(ROAD[roadID].id, i, CAR[carID].nowSpeed); //更新车的位置
					CAR[carID].setATD(GlobalTime);	//设置实际出发时间
					ROAD[roadID].addRoadCar(m, i, CAR[carID].location[2] - 1, carID + car0); //更新道路的车辆位置
					//更新状态
					CAR[carID].setState(1);
					CAR[carID].computeNEXT(ROAD, CROSS); //更新状态
					lastCarId = carID; //更新上一个位置车辆id
					flag = 0;
					carCut.push_back(carID + car0);
					++carNum;
					++count;
					continue;
				}

				//进入车道的非第一辆车
				if (CAR[carID].nowSpeed < CAR[lastCarId].location[2])	//空间够
				{
					CAR[carID].updateLocation(ROAD[roadID].id, i, CAR[carID].nowSpeed);
					CAR[carID].setATD(GlobalTime);
					ROAD[roadID].addRoadCar(m, i, CAR[carID].location[2] - 1, carID + car0);
					//更新状态
					CAR[carID].setState(1);
					CAR[carID].computeNEXT(ROAD, CROSS); //更新状态
					lastCarId = carID;
					carCut.push_back(carID + car0);
					++carNum;
					++count;
					continue;
				}

				CAR[carID].updateLocation(ROAD[roadID].id, i, CAR[lastCarId].location[2] - 1); //空间不够
				CAR[carID].setATD(GlobalTime);
				ROAD[roadID].addRoadCar(m, i, CAR[carID].location[2] - 1, carID + car0);
				//更新状态
				CAR[carID].setState(1);
				CAR[carID].computeNEXT(ROAD, CROSS); //更新状态
				lastCarId = carID;
				carCut.push_back(carID + car0);
				++carNum;
				++count;
			}
			//删除车库中已经进入道路的车
			CROSS[crossNum].subStartCar(carCut);
		}
		//清空道路排队车列
		ROAD[roadID].clearWaitCar(0);
		ROAD[roadID].clearWaitCar(1);
	}
	return true;
}

//调度进入该路该方向的优先车进入
bool Dispatch::moveCarportCarPriorityToRoad(int roadId, int dir, vector<Car> &CAR, vector<Road> &ROAD, vector<Cross> &CROSS, int &GlobalTime)
{
	int i;
	
	int roadID = roadId - road0;
	int crossID=0;

	//获取进入该路该方向的优先车所在路口
	if (dir == 0)
		crossID = ROAD[roadID].from - cross0;
	if (dir == 1)
		crossID = ROAD[roadID].to - cross0;

	//获取优先车
	if ((int)(CROSS[crossID].StartCar.size()) == 0)
		return false;

	//车库内等待的车划归到各条道路的请求队列中
	vector<int> waitCar;
	for (int num = 0; num < (int)(CROSS[crossID].StartCar.size()); num++)
	{
		int carID = CROSS[crossID].StartCar[num] - car0;
		
		//优先车上路——只扫描车库中排在前面的优先车，一旦扫描到非优先车可以直接退出
		if (CAR[carID].priority == 0)
			break;

		int carRoadID = CAR[carID].route[0] - road0;
		if (carRoadID == roadID && CAR[carID].reverse[0]==dir && CAR[carID].PT <= GlobalTime)  //只有要去这条路的这个方向的车才会进入排队序列
			waitCar.push_back(carID + car0);														   
	}
	if (waitCar.size() == 0)
		return false;

	//将只存了优先车的waitCar按PT排序
	//(现在的优先级是都是:实际发车时间为首序，ID为次序，vector里都是到达了发车时间的优先车)
	set<int, less<int>> PTAll;
	set<int>::iterator it;
	vector<int> tempCar;
	for (i = 0; i < (int)(waitCar.size()); i++)
	{
		PTAll.insert(CAR[waitCar[i] - car0].PT);
	}
	for (it = PTAll.begin(); it != PTAll.end(); it++)
	{
		for (i = 0; i < (int)(waitCar.size()); i++)
		{
			if (CAR[waitCar[i] - car0].PT == *it)
				tempCar.push_back(waitCar[i]);
		}
	}
	waitCar.clear();
	waitCar.insert(waitCar.begin(), tempCar.begin(), tempCar.end());

	//将车送入道路排队
	for (i = 0; i < (int)(waitCar.size()); i++)
	{
		ROAD[roadID].addWaitCar(dir, 0, waitCar[i]);
	}

	i = 0;
	int carNum = 0, j=0, flag = 0, lastCarId = -1, count = 0;	//i表示车道id
	vector<int> carCut;
	while (carNum < (int)(ROAD[roadID].WaitCar[dir][0].size()))
	{
		if (ROAD[roadID].roadCar[dir][i][0] != -1) //车道已满，换下一条车道
		{
			int carID = ROAD[roadID].roadCar[dir][i][0] - car0;
			//根据车道固定进入规则，当前车道被等待车堵头，直接GG
			if (CAR[carID].state == 0)
				break;
			++i;
			flag = 1;
			if (i == ROAD[roadID].channel)
				break;
			continue;
		}

		int carID = ROAD[roadID].WaitCar[dir][0][carNum] - car0;

		//更新当前速度
		if (CAR[carID].speed > ROAD[roadID].speed)
			CAR[carID].setNowSpeed(ROAD[roadID].speed);
		else
			CAR[carID].setNowSpeed(CAR[carID].speed);

		//进入车道的第一辆车
		if (count == 0 || flag == 1)
		{
			//查询挡道车辆
			int blockPOS = -1;
			for (j = 1; j < CAR[carID].nowSpeed; j++)
			{
				if (ROAD[roadID].roadCar[dir][i][j] != -1)
				{
					blockPOS = j + 1;
					break;
				}
			}

			//发现有车挡道
			if (blockPOS != -1)
			{
				if (CAR[carID].nowSpeed > (blockPOS - 1))  //间距不够
				{
					int blockCarID = ROAD[roadID].roadCar[dir][i][j] - car0;
					//如果被阻挡车辆是等待的，不影响后面的优先车
					if (CAR[blockCarID].state == 0)
					{
						////清空道路排队车列
						//ROAD[roadID].clearWaitCar(0);
						//ROAD[roadID].clearWaitCar(1);
						////删除车库中已经进入道路的车
						//CROSS[crossID].subStartCar(carCut);
						//return false;
						++carNum;
						flag = 1;	//如果车道的第一辆车进不去，接下来的车是新的第一辆车
						continue;
					}
					//如果被阻挡车辆是终止的，那就放行
					CAR[carID].setNowSpeed(blockPOS - 1);
				}
			}

			CAR[carID].updateLocation(ROAD[roadID].id, i, CAR[carID].nowSpeed); //更新车的位置
			CAR[carID].setATD(GlobalTime);	//设置实际出发时间
			ROAD[roadID].addRoadCar(dir, i, CAR[carID].location[2] - 1, carID + car0); //更新道路的车辆位置
			//更新状态
			CAR[carID].setState(1);
			CAR[carID].computeNEXT(ROAD, CROSS); //更新状态
			lastCarId = carID; //更新上一个位置车辆id
			flag = 0;
			carCut.push_back(carID + car0);
			++carNum;
			++count;
			continue;
		}

		//进入车道的非第一辆车
		if (CAR[carID].nowSpeed < CAR[lastCarId].location[2])	//空间够
		{
			CAR[carID].updateLocation(ROAD[roadID].id, i, CAR[carID].nowSpeed);
			CAR[carID].setATD(GlobalTime);
			ROAD[roadID].addRoadCar(dir, i, CAR[carID].location[2] - 1, carID + car0);
			//更新状态
			CAR[carID].setState(1);
			CAR[carID].computeNEXT(ROAD, CROSS); //更新状态
			lastCarId = carID;
			carCut.push_back(carID + car0);
			++carNum;
			++count;
			continue;
		}

		CAR[carID].updateLocation(ROAD[roadID].id, i, CAR[lastCarId].location[2] - 1); //空间不够
		CAR[carID].setATD(GlobalTime);
		ROAD[roadID].addRoadCar(dir, i, CAR[carID].location[2] - 1, carID + car0);
		//更新状态
		CAR[carID].setState(1);
		CAR[carID].computeNEXT(ROAD, CROSS); //更新状态
		lastCarId = carID;
		carCut.push_back(carID + car0);
		++carNum;
		++count;
	}
	//删除车库中已经进入道路的车
	CROSS[crossID].subStartCar(carCut);
	//清空道路排队车列
	ROAD[roadID].clearWaitCar(dir);

	return true;
}

//路上所有车调度结束，开始调度第num个车库内等待的车
bool Dispatch::moveCarport(int crossNum, vector<Car> &CAR, vector<Road> &ROAD, vector<Cross> &CROSS, int &GlobalTime)
{
	int  num, m, j;

	if ((int)(CROSS[crossNum].StartCar.size()) == 0)
		return false;

	//车库内等待的车划归到各条道路的请求队列中
	set<int, less<int>> tempRoadAll;
	vector<int> waitCar;
	for (num = 0; num < (int)(CROSS[crossNum].StartCar.size()); num++)
	{
		int carID = CROSS[crossNum].StartCar[num] - car0;
		int roadID = CAR[carID].route[0] - road0;
		if (CAR[carID].PT <= GlobalTime)
		{
			tempRoadAll.insert(roadID);
			waitCar.push_back(carID + car0);
		}
	}
	if (waitCar.size() == 0)
		return false;

	vector<int> roadAll;
	set<int>::iterator it;
	for (it = tempRoadAll.begin(); it != tempRoadAll.end(); it++)
	{
		roadAll.push_back(*it);
	}

	//根据优先权，将每个路口车库内的车重新排序：优先车在前，并按PT升序排列，再在各时间批次内保持ID升序排列
	vector<int> priorityCar, tempCar;
	vector<int>::iterator pos;
	set<int, less<int>> PTimeAll;
	for (int i = 0; i < (int)(waitCar.size()); i++)
	{
		if (CAR[waitCar[i] - car0].priority == 1)
			priorityCar.push_back(waitCar[i]);
	}

	//对于优先车，按PT划分批次
	for (int i = 0; i < (int)(priorityCar.size()); i++)
	{
		PTimeAll.insert(CAR[priorityCar[i] - car0].PT);
	}
	tempCar.clear();
	for (it = PTimeAll.begin(); it != PTimeAll.end(); it++)
	{
		for (int i = 0; i < (int)(priorityCar.size()); i++)
		{
			if (CAR[priorityCar[i] - car0].PT == *it)
				tempCar.push_back(priorityCar[i]);
		}
	}
	priorityCar.clear();
	priorityCar.insert(priorityCar.begin(), tempCar.begin(), tempCar.end());

	//删除原来的优先车辆
	for (int j = 0; j < (int)(priorityCar.size()); j++)
	{
		pos = find(waitCar.begin(), waitCar.end(), priorityCar[j]);
		if (pos != waitCar.end())
			waitCar.erase(pos);
	}

	//将非优先车按PT分批次
	PTimeAll.clear();
	for (int i = 0; i < (int)(waitCar.size()); i++)
	{
		PTimeAll.insert(CAR[waitCar[i] - car0].PT);
	}
	tempCar.clear();
	for (it = PTimeAll.begin(); it != PTimeAll.end(); it++)
	{
		for (int i = 0; i < (int)(waitCar.size()); i++)
		{
			if (CAR[waitCar[i] - car0].PT == *it)
				tempCar.push_back(waitCar[i]);
		}
	}
	waitCar.clear();
	waitCar.insert(waitCar.begin(), tempCar.begin(), tempCar.end());

	//链接索引
	waitCar.insert(waitCar.begin(), priorityCar.begin(), priorityCar.end());

	//将车送入道路排队
	for (int i = 0; i < (int)(waitCar.size()); i++)
	{
		int carID = waitCar[i] - car0;
		int roadID = CAR[carID].route[0] - road0;
		if (CAR[carID].from == ROAD[roadID].from) //正向
			ROAD[roadID].addWaitCar(0, 0, waitCar[i]);
		if (CAR[carID].from == ROAD[roadID].to) //反向
			ROAD[roadID].addWaitCar(1, 0, waitCar[i]);
	}

	//开始派车
	vector<int> carCut;
	for (int q = 0; q < (int)(roadAll.size()); q++)
	{
		num = roadAll[q];
		for (m = 0; m < 2; m++)
		{
			if ((int)(ROAD[num].WaitCar[m][0].size()) == 0) //进单向道路的车为空
				continue;

			int carNum = 0, i = 0, flag = 0, lastCarId = -1, count = 0;	//i表示车道id
			carCut.clear();
			while (carNum < (int)(ROAD[num].WaitCar[m][0].size()))
			{
				if (ROAD[num].roadCar[m][i][0] != -1) //车道已满，换下一条车道
				{
					++i;
					flag = 1;
					if (i == ROAD[num].channel)
						break;
					continue;
				}

				int carID = ROAD[num].WaitCar[m][0][carNum] - car0;

				if (CAR[carID].PT > GlobalTime) //未达到planTime不能发车
				{
					++carNum;
					continue;
				}

				//更新当前速度
				if (CAR[carID].speed > ROAD[num].speed)
					CAR[carID].setNowSpeed(ROAD[num].speed);
				else
					CAR[carID].setNowSpeed(CAR[carID].speed);

				//更新当前位置
				if (count == 0 || flag == 1) //第一辆车或者换道的第一辆车
				{
					//查询挡道车辆
					int blockPOS = -1;
					for (j = 1; j < CAR[carID].nowSpeed; j++)
					{
						if (ROAD[num].roadCar[m][i][j] != -1)
						{
							blockPOS = j + 1;
							break;
						}
					}

					if (blockPOS != -1)
					{
						if (CAR[carID].nowSpeed > (blockPOS - 1))  //间距不够
							CAR[carID].setNowSpeed(blockPOS - 1);
					}

					CAR[carID].updateLocation(ROAD[num].id, i, CAR[carID].nowSpeed); //更新车的位置
					CAR[carID].setATD(GlobalTime);	//设置实际出发时间
					ROAD[num].addRoadCar(m, i, CAR[carID].location[2] - 1, carID + car0); //更新道路的车辆位置
					lastCarId = carID; //更新上一个位置车辆id
					flag = 0;
					carCut.push_back(carID + car0);
					++carNum;
					++count;
					continue;
				}

				if (CAR[carID].nowSpeed < CAR[lastCarId].location[2])	//空间够
				{
					CAR[carID].updateLocation(ROAD[num].id, i, CAR[carID].nowSpeed);
					CAR[carID].setATD(GlobalTime);
					ROAD[num].addRoadCar(m, i, CAR[carID].location[2] - 1, carID + car0);
					lastCarId = carID;
					carCut.push_back(carID + car0);
					++carNum;
					++count;
					continue;
				}

				CAR[carID].updateLocation(ROAD[num].id, i, CAR[lastCarId].location[2] - 1); //空间不够
				CAR[carID].setATD(GlobalTime);
				ROAD[num].addRoadCar(m, i, CAR[carID].location[2] - 1, carID + car0);
				lastCarId = carID;
				carCut.push_back(carID + car0);
				++carNum;
				++count;
			}
			//删除车库中已经进入道路的车
			CROSS[crossNum].subStartCar(carCut);
		}
		//清空道路排队车列
		ROAD[num].clearWaitCar(0);
		ROAD[num].clearWaitCar(1);
	}

	//遍历一次waitCar，对于到了时间却没有发出去的非预置车进行PT+1
	for (int i = 0; i < (int)(waitCar.size()); i++)
	{
		int carID = waitCar[i] - car0;
		if (CAR[carID].preset == 0 && CAR[carID].ATD == -1)
			CAR[carID].addPT(1);
	}

	if ((int)(CROSS[crossNum].StartCar.size()) == 0)
		EmptyCarportNumber += 1;

	return true;
}

//路上所有车调度结束，开始调度第num个车库内等待的车
bool Dispatch::moveCarport2(int crossNum, vector<Car> &CAR, vector<Road> &ROAD, vector<Cross> &CROSS, int &GlobalTime)
{
	int  num, m, j;

	if ((int)(CROSS[crossNum].StartCar.size()) == 0)
		return false;

	//车库内等待的车划归到各条道路的请求队列中
	set<int, less<int>> tempRoadAll;
	vector<int> waitCar;
	for (num = 0; num < (int)(CROSS[crossNum].StartCar.size()); num++)
	{
		int carID = CROSS[crossNum].StartCar[num] - car0;
		int roadID = CAR[carID].route[0] - road0;
		if (CAR[carID].PT <= GlobalTime)
		{
			tempRoadAll.insert(roadID);
			waitCar.push_back(carID + car0);
		}
	}
	if (waitCar.size() == 0)
		return false;

	vector<int> roadAll;
	set<int>::iterator it;
	for (it = tempRoadAll.begin(); it != tempRoadAll.end(); it++)
	{
		roadAll.push_back(*it);
	}

	//根据优先权，将每个路口车库内的车重新排序：优先车在前，并按PT升序排列，再在各时间批次内保持ID升序排列
	vector<int> priorityCar, tempCar;
	vector<int>::iterator pos;
	set<int, less<int>> PTimeAll;
	for (int i = 0; i < (int)(waitCar.size()); i++)
	{
		if (CAR[waitCar[i] - car0].priority == 1)
			priorityCar.push_back(waitCar[i]);
	}

	//对于优先车，按PT划分批次
	for (int i = 0; i < (int)(priorityCar.size()); i++)
	{
		PTimeAll.insert(CAR[priorityCar[i] - car0].PT);
	}
	tempCar.clear();
	for (it = PTimeAll.begin(); it != PTimeAll.end(); it++)
	{
		for (int i = 0; i < (int)(priorityCar.size()); i++)
		{
			if (CAR[priorityCar[i] - car0].PT == *it)
				tempCar.push_back(priorityCar[i]);
		}
	}
	priorityCar.clear();
	priorityCar.insert(priorityCar.begin(), tempCar.begin(), tempCar.end());

	//删除原来的优先车辆
	for (int j = 0; j < (int)(priorityCar.size()); j++)
	{
		pos = find(waitCar.begin(), waitCar.end(), priorityCar[j]);
		if (pos != waitCar.end())
			waitCar.erase(pos);
	}

	//将非优先车按PT分批次
	PTimeAll.clear();
	for (int i = 0; i < (int)(waitCar.size()); i++)
	{
		PTimeAll.insert(CAR[waitCar[i] - car0].PT);
	}
	tempCar.clear();
	for (it = PTimeAll.begin(); it != PTimeAll.end(); it++)
	{
		for (int i = 0; i < (int)(waitCar.size()); i++)
		{
			if (CAR[waitCar[i] - car0].PT == *it)
				tempCar.push_back(waitCar[i]);
		}
	}
	waitCar.clear();
	waitCar.insert(waitCar.begin(), tempCar.begin(), tempCar.end());

	//链接索引
	waitCar.insert(waitCar.begin(), priorityCar.begin(), priorityCar.end());

	//将车送入道路排队
	for (int i = 0; i < (int)(waitCar.size()); i++)
	{
		int carID = waitCar[i] - car0;
		int roadID = CAR[carID].route[0] - road0;
		if (CAR[carID].from == ROAD[roadID].from) //正向
			ROAD[roadID].addWaitCar(0, 0, waitCar[i]);
		if (CAR[carID].from == ROAD[roadID].to) //反向
			ROAD[roadID].addWaitCar(1, 0, waitCar[i]);
	}

	//开始派车
	vector<int> carCut;
	for (int q = 0; q < (int)(roadAll.size()); q++)
	{
		num = roadAll[q];
		for (m = 0; m < 2; m++)
		{
			if ((int)(ROAD[num].WaitCar[m][0].size()) == 0) //进单向道路的车为空
				continue;

			int carNum = 0, i = 0, flag = 0, lastCarId = -1, count = 0;	//i表示车道id
			carCut.clear();
			while (carNum < (int)(ROAD[num].WaitCar[m][0].size()))
			{
				if (ROAD[num].roadCar[m][i][0] != -1) //车道已满，换下一条车道
				{
					++i;
					flag = 1;
					if (i == ROAD[num].channel)
						break;
					continue;
				}

				int carID = ROAD[num].WaitCar[m][0][carNum] - car0;

				if (CAR[carID].PT > GlobalTime) //未达到planTime不能发车
				{
					++carNum;
					continue;
				}

				//更新当前速度
				if (CAR[carID].speed > ROAD[num].speed)
					CAR[carID].setNowSpeed(ROAD[num].speed);
				else
					CAR[carID].setNowSpeed(CAR[carID].speed);

				//更新当前位置
				if (count == 0 || flag == 1) //第一辆车或者换道的第一辆车
				{
					//查询挡道车辆
					int blockPOS = -1;
					for (j = 1; j < CAR[carID].nowSpeed; j++)
					{
						if (ROAD[num].roadCar[m][i][j] != -1)
						{
							blockPOS = j + 1;
							break;
						}
					}

					if (blockPOS != -1)
					{
						if (CAR[carID].nowSpeed > (blockPOS - 1))  //间距不够
							CAR[carID].setNowSpeed(blockPOS - 1);
					}

					CAR[carID].updateLocation(ROAD[num].id, i, CAR[carID].nowSpeed); //更新车的位置
					CAR[carID].setATD(GlobalTime);	//设置实际出发时间
					ROAD[num].addRoadCar(m, i, CAR[carID].location[2] - 1, carID + car0); //更新道路的车辆位置
					lastCarId = carID; //更新上一个位置车辆id
					flag = 0;
					carCut.push_back(carID + car0);
					++carNum;
					++count;
					continue;
				}

				if (CAR[carID].nowSpeed < CAR[lastCarId].location[2])	//空间够
				{
					CAR[carID].updateLocation(ROAD[num].id, i, CAR[carID].nowSpeed);
					CAR[carID].setATD(GlobalTime);
					ROAD[num].addRoadCar(m, i, CAR[carID].location[2] - 1, carID + car0);
					lastCarId = carID;
					carCut.push_back(carID + car0);
					++carNum;
					++count;
					continue;
				}

				CAR[carID].updateLocation(ROAD[num].id, i, CAR[lastCarId].location[2] - 1); //空间不够
				CAR[carID].setATD(GlobalTime);
				ROAD[num].addRoadCar(m, i, CAR[carID].location[2] - 1, carID + car0);
				lastCarId = carID;
				carCut.push_back(carID + car0);
				++carNum;
				++count;
			}
			//删除车库中已经进入道路的车
			CROSS[crossNum].subStartCar(carCut);
		}
		//清空道路排队车列
		ROAD[num].clearWaitCar(0);
		ROAD[num].clearWaitCar(1);
	}

	return true;
}

bool Dispatch::delayCarPT2(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &nowTime, vector<int> &deadCar)
{
	int i, j, carID, roadID, count = 0;
	bool isFind = false;
	vector<int>::iterator pos;
	vector<int> modifyCar, tempCar;
	set<int, less<int>> PTAll;
	set<int>::iterator it;

	//找出当前时刻备份车库中PT<=nowTime的车,经过回滚，现在的CAR就是备份的数据
	//将这些车中的非优先车的发车时间延后N个时刻
	int limitNumber = 50;

	bool isFirst = true;
	for (j = 0; j < limitNumber; j++)
	{
		for (i = 0; i < crossSize; i++)
		{
			if ((int)(CROSS[i].StartCar.size()) < limitNumber)
				continue;
			carID = CROSS[i].StartCar[j] - car0;
			roadID = CAR[carID].route[0] - road0;
			if (ROAD[roadID].crowding[CAR[carID].isReverse] < 0.1)
				continue;
			//查找deadCar是否有该元素
			pos = find(deadCar.begin(), deadCar.end(), CROSS[i].StartCar[j]);
			if (pos != deadCar.end())  //找到了
			{
				isFind = true;
				deadCar.erase(pos);
			}
			if (CAR[carID].PT <= nowTime && CAR[carID].priority == 0 && CAR[carID].preset == 0 && isFind == true)
			{
				modifyCar.push_back(carID);
				PTAll.insert(CAR[carID].PT);
				isFind = false;
				++count;
				//CAR[carID].addPT(limitNumber - count);
				if (isFirst == true)
				{
					isFirst = false;
					cout << "PT is modifyed!!---------------" << endl;
				}
			}
		}
	}

	//对车进行PT从小到达排序
	for (it = PTAll.begin(); it != PTAll.end(); it++)
	{
		for (i = 0; i < (int)(modifyCar.size()); i++)
		{
			if (CAR[modifyCar[i]].PT == *it)
				tempCar.push_back(modifyCar[i]);
		}
	}
	modifyCar.clear();
	modifyCar.insert(modifyCar.begin(), tempCar.begin(), tempCar.end());
	if ((int)(modifyCar.size()) > limitNumber)
		modifyCar.erase(modifyCar.begin() + limitNumber, modifyCar.end());

	//修改PT
	int T = 0, N;
	for (N = (int)(modifyCar.size()); N >= 1; N--)
	{
		CAR[modifyCar[T]].addPT(N);
		++T;
	}
	int lastSize = (int)(modifyCar.size());

	//判断是否足够
	if ((int)(modifyCar.size()) == limitNumber)
		return true;

	modifyCar.clear();
	tempCar.clear();
	PTAll.clear();
	isFirst = true;
	for (j = 0; j < limitNumber; j++)
	{
		for (i = 0; i < crossSize; i++)
		{
			if ((int)(CROSS[i].StartCar.size()) < limitNumber)
				continue;
			carID = CROSS[i].StartCar[j] - car0;
			roadID = CAR[carID].route[0] - road0;
			if (ROAD[roadID].crowding[CAR[carID].isReverse] < 0.1)
				continue;
			//查找deadCar是否有该元素
			pos = find(deadCar.begin(), deadCar.end(), CROSS[i].StartCar[j]);
			if (pos == deadCar.end())  //没找到
			{
				isFind = false;
			}
			if (CAR[carID].PT <= nowTime && CAR[carID].priority == 0 && CAR[carID].preset == 0 && isFind == false)
			{
				modifyCar.push_back(carID);
				PTAll.insert(CAR[carID].PT);
				isFind = true;
				++count;
				//if (count == limitNumber-1)
				//{
				//	j = limitNumber;
				//	break;
				//}
				//CAR[carID].addPT(limitNumber - count);
				if (isFirst == true)
				{
					isFirst = false;
					cout << "PT is modifyed!!----*-*-*-*-*-*----*-*-*-*-*-*-*---------" << endl;
				}
			}
		}
	}

	//对车进行PT从小到达排序
	for (it = PTAll.begin(); it != PTAll.end(); it++)
	{
		for (i = 0; i < (int)(modifyCar.size()); i++)
		{
			if (CAR[modifyCar[i]].PT == *it)
				tempCar.push_back(modifyCar[i]);
		}
	}
	modifyCar.clear();
	modifyCar.insert(modifyCar.begin(), tempCar.begin(), tempCar.end());
	if ((int)(modifyCar.size()) > (limitNumber - lastSize))
		modifyCar.erase(modifyCar.begin() + (limitNumber - lastSize), modifyCar.end());

	//修改PT
	T = 0;
	for (N = (int)(modifyCar.size()); N >= 1; N--)
	{
		CAR[modifyCar[T]].addPT(N);
		++T;
	}

	return true;
}

bool Dispatch::delayCarPT(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &nowTime, vector<int> &deadCar)
{
	int i, j, carID, roadID, count = 0;
	bool isFind = false;
	vector<int>::iterator pos;

	//找出当前时刻备份车库中PT<=nowTime的车,经过回滚，现在的CAR就是备份的数据
	//将这些车中的非优先车的发车时间延后N个时刻
	int limitNumber = 50;
	
	int N = 0;
	for (j = 0; j < limitNumber; j++)
	{
		for (i = 0; i < crossSize; i++)
		{
			if ((int)(CROSS[i].StartCar.size()) < limitNumber)
				continue;
			carID = CROSS[i].StartCar[j] - car0;
			roadID = CAR[carID].route[0] - road0;
			if (ROAD[roadID].crowding[CAR[carID].isReverse] < 0.1)
				continue;
			//查找deadCar是否有该元素
			pos = find(deadCar.begin(), deadCar.end(), CROSS[i].StartCar[j]);
			if (pos != deadCar.end())  //找到了
			{
				isFind = true;
				deadCar.erase(pos);
			}
			if (CAR[carID].PT <= nowTime && CAR[carID].priority == 0 && CAR[carID].preset == 0 && isFind == true)
			{
				isFind = false;
				++count;
				if (count > limitNumber)
					return true;
				CAR[carID].addPT(N);
				++N;
				if (N > 30)
					N = 1;
				if (count == 1)
					cout << "PT is modifyed!!---------------" << endl;
			}
		}
	}

	for (j = 0; j < limitNumber; j++)
	{
		for (i = 0; i < crossSize; i++)
		{
			if ((int)(CROSS[i].StartCar.size()) < limitNumber)
				continue;
			carID = CROSS[i].StartCar[j] - car0;
			roadID = CAR[carID].route[0] - road0;
			if (ROAD[roadID].crowding[CAR[carID].isReverse] < 0.1)
				continue;
			//查找deadCar是否有该元素
			pos = find(deadCar.begin(), deadCar.end(), CROSS[i].StartCar[j]);
			if (pos == deadCar.end())  //没找到
			{
				isFind = false;
			}
			if (CAR[carID].PT <= nowTime && CAR[carID].priority == 0 && CAR[carID].preset == 0 && isFind == false)
			{
				isFind = true;
				++count;
				if (count > limitNumber)
					return true;
				CAR[carID].addPT(N);
				++N;
				if (N > 30)
					N = 1;
				if (count == 1)
					cout << "PT is modifyed!!----*-*-*-*-*-*----*-*-*-*-*-*-*---------" << endl;
			}
		}
	}
	return true;
}

//死锁处理_回滚
void Dispatch::dealDeadLock_back(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, const Graph_DG &OriginalCarGraph, vector<int> &freeRoads, vector<int> &busyRoads, vector<int> &CROSSID) {
	vector<int> carIDs;
	for (int num = 0; num < crossSize; num++)
	{//按路口ID升序进行调度各个路口，路口内各道路按道路ID升序进行调度等待的车辆
		//cout << ", cross num is " << num;
		int roadIDS[4] = { CROSS[num].road1,CROSS[num].road2, CROSS[num].road3, CROSS[num].road4 };
		sort(roadIDS, roadIDS + 4); //从小到大排序

		//获取连接此路口的四个入入口方向道路的正反向
		int dir[4];
		for (int q = 0; q < 4; q++)
		{
			if (roadIDS[q] == -1) //没有路
				continue;
			if (ROAD[roadIDS[q] - road0].to == num + cross0)
				dir[q] = 0;
			else
				dir[q] = 1;
		}

		//按序遍历道路的第一优先级车辆
		for (int q = 0; q < 4; q++)
		{
			//当前道路上的车未被调度完
			while (!isRoadOver(roadIDS[q], dir[q], ROAD, CAR))
			{
				//获取第一优先级的车...
				carIDs.clear();
				carIDs = getCar3(roadIDS[q], dir[q], ROAD, CAR, 20);
				if (carIDs.size() == 0)
					break;
				for (int i = 0; i < (int)carIDs.size(); i++) {

					if (CAR[carIDs[i] - car0].preset == 1) {
						continue;
					}
					if (CAR[carIDs[i] - car0].nextCrossDistance < CAR[carIDs[i] - car0].maxSpeed) {//当前时刻要过路口的车，不要修改，情况太多，有bug
						continue;
					}
					if (CAR[carIDs[i] - car0].passRoadNumber == (int)(CAR[carIDs[i] - car0].route.size()) - 1) {//目前这条路是该车的最后一段路，也不要凑热闹了
						continue;
					}
					else if (CAR[carIDs[i] - car0].passRoadNumber == (int)(CAR[carIDs[i] - car0].route.size()) - 2) {//该车的下一条路是要到终点，也不要凑热闹了
						continue;
					}
					else if (CAR[carIDs[i] - car0].passRoadNumber == (int)(CAR[carIDs[i] - car0].route.size()) - 3) {//该车的下下一条路是要到终点，也不要凑热闹了
						continue;
					}
					CAR[carIDs[i] - car0].changeDeadFlag = true;
					Graph_DG deadCarGraph(OriginalCarGraph);
					deadCarGraph.initRoute_DealLock_back(CAR[carIDs[i] - car0], CROSS, ROAD, freeRoads, busyRoads, CROSSID);
					//这里要换成改该车的下一条路、重新计算四个vector
					//计算maxSP和reverse
					int carid = carIDs[i] - car0;
					CAR[carid].maxSP.clear();
					CAR[carid].reverse.clear();
					int roadID = CAR[carid].route[0] - road0;
					if (CAR[carid].from == ROAD[roadID].from) //正向
					{
						CAR[carid].addRverse(0);
					}
					if (CAR[carid].from == ROAD[roadID].to) //反向
					{
						CAR[carid].addRverse(1);
					}
					for (int i = 0; i < (int)(CAR[carid].route.size()); i++)
					{
						int newRoadID = CAR[carid].route[i] - road0;
						if (i > 0)
						{
							if (CAR[carid].reverse[i - 1] == 0) //上一条路的from-to就是车的行进方向
							{
								int lastRoad = CAR[carid].route[i - 1] - road0;
								if (ROAD[lastRoad].to == ROAD[newRoadID].from)
									CAR[carid].addRverse(0);
								else
									CAR[carid].addRverse(1);
							}
							if (CAR[carid].reverse[i - 1] == 1) //上一条路的to-from就是车的行进方向
							{
								int lastRoad = CAR[carid].route[i - 1] - road0;
								if (ROAD[lastRoad].from == ROAD[newRoadID].from)
									CAR[carid].addRverse(0);
								else
									CAR[carid].addRverse(1);
							}
						}

						if (CAR[carid].speed < ROAD[CAR[carid].route[i] - road0].speed)
							CAR[carid].addMaxSpeed(CAR[carid].speed);
						else
							CAR[carid].addMaxSpeed(ROAD[CAR[carid].route[i] - road0].speed);
					}
				}
				break;
			}
		}
	}
}


//死锁处理
void Dispatch::dealDeadLock(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, const Graph_DG &OriginalCarGraph, vector<int> &freeRoads, vector<int> &busyRoads, vector<int> &CROSSID) {
	vector<int> carIDs;
	for (int num = 0; num < crossSize; num++)
	{//按路口ID升序进行调度各个路口，路口内各道路按道路ID升序进行调度等待的车辆
		//cout << ", cross num is " << num;
		int roadIDS[4] = { CROSS[num].road1,CROSS[num].road2, CROSS[num].road3, CROSS[num].road4 };
		sort(roadIDS, roadIDS + 4); //从小到大排序

		//获取连接此路口的四个入入口方向道路的正反向
		int dir[4];
		for (int q = 0; q < 4; q++)
		{
			if (roadIDS[q] == -1) //没有路
				continue;
			if (ROAD[roadIDS[q] - road0].to == num + cross0)
				dir[q] = 0;
			else
				dir[q] = 1;
		}

		//按序遍历道路的第一优先级车辆
		for (int q = 0; q < 4; q++)
		{
			//当前道路上的车未被调度完
			while (!isRoadOver(roadIDS[q], dir[q], ROAD, CAR))
			{
				//获取第一优先级的车...
				carIDs.clear();
				carIDs = getCar3(roadIDS[q], dir[q], ROAD, CAR, 5);
				if (carIDs.size() == 0)
					break;
				for (int i = 0; i < (int)carIDs.size(); i++) {
					if (CAR[carIDs[i] - car0].preset == 1) {
						continue;
					}
					Graph_DG deadCarGraph(OriginalCarGraph);
					deadCarGraph.initRoute_DealLock(CAR[carIDs[i] - car0], CROSS, ROAD, freeRoads, busyRoads, CROSSID);
				}

				break;
			}
		}
	}
}

//带死锁处理的判题器
int Dispatch::dispathMAIN_withDeal(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime, int TT, int bestTime, const Graph_DG &OriginalCarGraph, vector<int> &CROSSID)
{
	//int waitNumber;
	int num, j;
	vector<int> roadIDS, dir;

	//T1时刻初始化
	dispathINIT(CAR, CROSS, ROAD, GlobalTime, TT);
	++GlobalTime;
	//cout << "Inition OVER!" << endl;

	while (!isAllTerminate(CAR)) //未有所有车到达终点车库
	{
		//cout << endl << endl;
		cout << "GlobalTime is " << GlobalTime << endl;

		//if (GlobalTime > 20) {
			dynamicPlanSet(CAR, CROSS, ROAD, OriginalCarGraph);
		//}

		//直接处理可达终点状态的车辆
		setState(CAR, CROSS, ROAD, GlobalTime);

		//调度车库的优先车辆
		if (EmptyCarportNumber < crossSize)
		{
			for (num = 0; num < crossSize; num++)
				moveCarportPriorityCar(num, CAR, ROAD, CROSS, GlobalTime);
		}

		//调度所有道路上等待状态的车辆至终止状态
		while (!isAllEnd(CAR))
		{
			//gain waitNumber
			//waitNumber = gainWaitNum(CAR);
			isDeadlock = true;
			for (num = 0; num < crossSize; num++)
			{//按路口ID升序进行调度各个路口，路口内各道路按道路ID升序进行调度等待的车辆			
				roadIDS.clear();
				roadIDS.push_back(CROSS[num].road1);
				roadIDS.push_back(CROSS[num].road2);
				roadIDS.push_back(CROSS[num].road3);
				roadIDS.push_back(CROSS[num].road4);
				sort(roadIDS.begin(), roadIDS.end());

				//获取连接此路口的四个入入口方向道路的正反向
				dir.clear();
				for (int q = 0; q < 4; q++)
				{
					if (roadIDS[q] == -1) //没有路
					{
						dir.push_back(-1);
						continue;
					}
					if ((num + cross0) == ROAD[roadIDS[q] - road0].to)
						dir.push_back(0);
					else
						dir.push_back(1);
				}

				//按序遍历道路的第一优先级车辆
				for (int q = 0; q < 4; q++)
				{
					//当前道路上的车未被调度完
					while (!isRoadOver(roadIDS[q], dir[q], ROAD, CAR))
					{
						//获取第一优先级的车
						int carID = getCar(roadIDS[q], dir[q], ROAD, CAR);

						if (carID == -1)
							break;

						//备用，防止更新丢失
						int oldRoadID = roadIDS[q] - road0;
						int oldChannel = CAR[carID - car0].location[1];
						int oldPosition = CAR[carID - car0].location[2];

						/*int tempRoad = CAR[carID - car0].nextRoad;
						int tempDir = CAR[carID - car0].nextReverse;*/

						if (isConflict(q, carID, roadIDS, dir, ROAD, CAR)) //如果冲突，就换下一条路遍历
						{
							break;
						}

						//调度车辆
						//bool isEndInNextRoad = false;
						moveToNextRoad(carID, CAR, ROAD, CROSS, GlobalTime);

						if (CAR[carID - car0].state == 0) //调度失败，要去的路上有等待的车辆阻挡
						{
							break;
						}

						//***********setdeadlock*************
						isDeadlock = false;

						if (CAR[carID - car0].state == 1)	//调度成功
						{
							if (oldPosition == 1)
								break;

							for (j = oldPosition - 2; j >= 0; j--)
							{
								if (ROAD[oldRoadID].roadCar[dir[q]][oldChannel][j] == -1)
									continue;
								int newCar = ROAD[oldRoadID].roadCar[dir[q]][oldChannel][j] - car0;
								if (CAR[newCar].state == 0 && CAR[newCar].toNextRoad == 1) //等待下次遍历
								{
									//扫描当前车道是否有终止车阻挡
									int count = 0;
									for (int n = j + 1; n < ROAD[oldRoadID].length; n++)
									{
										if (ROAD[oldRoadID].roadCar[dir[q]][oldChannel][n] != -1)
										{
											++count;
											break;
										}
									}
									//受到阻挡，直接终止
									if (count == 1)
										moveOnTheRoad(newCar, CAR, ROAD, CROSS, GlobalTime);
									//不受阻挡，跳出重新扫描本道路的优先级
									if (count == 0)
										break;
								}
								if (CAR[newCar].state == 0 && CAR[newCar].toNextRoad == 0)
									moveOnTheRoad(newCar, CAR, ROAD, CROSS, GlobalTime);
							}

							////尝试让优先车去头车停在的那条路上
							//if (tempRoad != -1)
							//{
							//	moveCarportCarPriorityToRoad(tempRoad, tempDir, CAR, ROAD, CROSS, GlobalTime);
							//}

							//此路已通，调度要进该路的优先车
							moveCarportCarPriorityToRoad(roadIDS[q], dir[q], CAR, ROAD, CROSS, GlobalTime);

							////调度车库的优先车辆
							//for (num = 0; num < crossSize; num++)
							//	moveCarportPriorityCar(num, CAR, ROAD, CROSS, GlobalTime);
						}

					}
				}
			}
			//deadlock happen
			if (isDeadlock == true)
			{
				cout << "deadlock happen at GlobalTime in " << GlobalTime << endl;
				this->getFreeBusyRoads(ROAD);	//获取freeRoads和busyRoads.	
				this->dealDeadLock(CAR, CROSS, ROAD, OriginalCarGraph, freeRoads, busyRoads, CROSSID);
				return BADTIME;

			}
			/*int nowWaitNumber = gainWaitNum(CAR);
			if (waitNumber == nowWaitNumber)
					return BADTIME;*/

		}

		if (EmptyCarportNumber < crossSize)
		{
			//控制发车数量
			modifyPlantime(CAR, CROSS, ROAD, GlobalTime);
			//调度车库的车辆
			for (num = 0; num < crossSize; num++)
				moveCarport(num, CAR, ROAD, CROSS, GlobalTime);
		}

		//计算拥挤度
		computeRoadCrowding(ROAD);

		resetRoadCarNumber();

		++GlobalTime;

		//computeRANUM(GlobalTime);

		if (GlobalTime > bestTime)
			return 2 * BADTIME;
	}

	return GlobalTime - 1;
}


////带死锁处理的判题器
//int Dispatch::dispathMAIN_withDeal2(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime, int TT, int bestTime, const Graph_DG &OriginalCarGraph, vector<int> &CROSSID)
//{
//	//int waitNumber;
//	int num, j,  dieCount = 0;
//	vector<int> roadIDS, dir, deadCar;
//	vector<float> futureCrowing;
//	vector<vector<int>> CarDeadRoadId;
//	vector<int> deadRoadId;
//	for (int i = 0; i < (int)(CAR.size()); i++) {
//		CarDeadRoadId.push_back(deadRoadId);
//	}
//
//	//T1时刻初始化
//	dispathINIT(CAR, CROSS, ROAD, GlobalTime, TT);
//	++GlobalTime;
//	//cout << "Inition OVER!" << endl;
//
//	while (!isAllTerminate(CAR)) //未有所有车到达终点车库
//	{
//		//cout << endl << endl;
//		//cout << "GlobalTime is " << GlobalTime << endl;
//
//		//if (GlobalTime > 20) 
//			dynamicPlanSet(CAR, CROSS, ROAD, OriginalCarGraph);
//
//		//直接处理可达终点状态的车辆
//		setState(CAR, CROSS, ROAD, GlobalTime);
//
//		//调度车库的优先车辆
//		if (EmptyCarportNumber < crossSize)
//		{
//			for (num = 0; num < crossSize; num++)
//				moveCarportPriorityCar(num, CAR, ROAD, CROSS, GlobalTime);
//		}		
//
//		//调度所有道路上等待状态的车辆至终止状态
//		while (!isAllEnd(CAR))
//		{
//			//gain waitNumber
//			//waitNumber = gainWaitNum(CAR);
//			isDeadlock = true;
//			for (num = 0; num < crossSize; num++)
//			{//按路口ID升序进行调度各个路口，路口内各道路按道路ID升序进行调度等待的车辆			
//				roadIDS.clear();
//				roadIDS.push_back(CROSS[num].road1);
//				roadIDS.push_back(CROSS[num].road2);
//				roadIDS.push_back(CROSS[num].road3);
//				roadIDS.push_back(CROSS[num].road4);
//				sort(roadIDS.begin(), roadIDS.end());
//
//				//获取连接此路口的四个入入口方向道路的正反向
//				dir.clear();
//				for (int q = 0; q < 4; q++)
//				{
//					if (roadIDS[q] == -1) //没有路
//					{
//						dir.push_back(-1);
//						continue;
//					}
//					if ((num + cross0) == ROAD[roadIDS[q] - road0].to)
//						dir.push_back(0);
//					else
//						dir.push_back(1);
//				}
//
//				//按序遍历道路的第一优先级车辆
//				for (int q = 0; q < 4; q++)
//				{
//					//当前道路上的车未被调度完
//					while (!isRoadOver(roadIDS[q], dir[q], ROAD, CAR))
//					{
//						//获取第一优先级的车
//						int carID = getCar(roadIDS[q], dir[q], ROAD, CAR);
//
//						if (carID == -1)
//							break;
//
//						//备用，防止更新丢失
//						int oldRoadID = roadIDS[q] - road0;
//						int oldChannel = CAR[carID - car0].location[1];
//						int oldPosition = CAR[carID - car0].location[2];
//
//						/*int tempRoad = CAR[carID - car0].nextRoad;
//						int tempDir = CAR[carID - car0].nextReverse;*/
//
//						if (isConflict(q, carID, roadIDS, dir, ROAD, CAR)) //如果冲突，就换下一条路遍历
//						{
//							break;
//						}
//
//						//调度车辆
//						//bool isEndInNextRoad = false;
//						moveToNextRoad(carID, CAR, ROAD, CROSS, GlobalTime);
//
//						if (CAR[carID - car0].state == 0) //调度失败，要去的路上有等待的车辆阻挡
//						{
//							break;
//						}
//
//						//***********setdeadlock*************
//						isDeadlock = false;
//
//						if (CAR[carID - car0].state == 1)	//调度成功
//						{
//							if (oldPosition == 1)
//								break;
//
//							for (j = oldPosition - 2; j >= 0; j--)
//							{
//								if (ROAD[oldRoadID].roadCar[dir[q]][oldChannel][j] == -1)
//									continue;
//								int newCar = ROAD[oldRoadID].roadCar[dir[q]][oldChannel][j] - car0;
//								if (CAR[newCar].state == 0 && CAR[newCar].toNextRoad == 1) //等待下次遍历
//								{
//									//扫描当前车道是否有终止车阻挡
//									int count = 0;
//									for (int n = j + 1; n < ROAD[oldRoadID].length; n++)
//									{
//										if (ROAD[oldRoadID].roadCar[dir[q]][oldChannel][n] != -1)
//										{
//											++count;
//											break;
//										}
//									}
//									//受到阻挡，直接终止
//									if (count == 1)
//										moveOnTheRoad(newCar, CAR, ROAD, CROSS, GlobalTime);
//									//不受阻挡，跳出重新扫描本道路的优先级
//									if (count == 0)
//										break;
//								}
//								if (CAR[newCar].state == 0 && CAR[newCar].toNextRoad == 0)
//									moveOnTheRoad(newCar, CAR, ROAD, CROSS, GlobalTime);
//							}
//							//此路已通，调度要进该路的优先车
//							moveCarportCarPriorityToRoad(roadIDS[q], dir[q], CAR, ROAD, CROSS, GlobalTime);
//						}
//
//					}
//				}
//			}
//			if (isDeadlock == true)
//				break;
//		}
//		//deadlock happen
//		if (isDeadlock == true)
//		{
//			cout << "deadlock happen at GlobalTime in " << GlobalTime << endl;
//			//this->getFreeBusyRoads(ROAD);	//获取freeRoads和busyRoads.	
//			this->setFlagDeadCar(CAR, CROSS, ROAD, CarDeadRoadId);//设置死锁车辆标志位、设置死锁时的道路，设置死锁时的下一条道路
//			//this->dealDeadLock_back(CAR, CROSS, ROAD, OriginalCarGraph, freeRoads, busyRoads, CROSSID);//后面三个参数其实没用到了，可以删除
//			
//			//获取死锁车
//			deadCar.clear();
//			deadCar = getDeadCarID(CAR, CROSS, ROAD);
//			//deadCar=getDeadCarFirstAll(CAR, CROSS, ROAD);
//			cout<<"deadCar size is "<<(int)(deadCar.size())<<endl;
//
//			////留存拥挤信息
//			//futureCrowing.clear();
//			//for (int i = 0; i < roadSize; i++)
//			//{
//			//	futureCrowing.push_back(ROAD[i].crowding[0]);
//			//	futureCrowing.push_back(ROAD[i].crowding[1]);
//			//}
//
//			//获取修改的路径				
//			int nowTime = GlobalTime;
//			//数据回滚到备份时刻
//			++dieCount;
//			cout << "back_1 time is " << backup_GlobalTime << ", " << "back_2 time is " << backup_GlobalTime2 << endl;
//			mainRollback(CAR, CROSS, ROAD, GlobalTime, OriginalCarGraph);
//			cout << "rollback time is " << GlobalTime << endl;
//			cout << "dieCount is " << dieCount << endl;
//			this->delayCarPT(CAR, CROSS, ROAD, nowTime,deadCar);
//		}
//
//		if (isDeadlock == false)
//		{
//			if (EmptyCarportNumber < crossSize)
//			{
//				//控制发车数量
//				modifyPlantime(CAR, CROSS, ROAD, GlobalTime);
//				//调度车库的车辆
//				for (num = 0; num < crossSize; num++)
//					moveCarport(num, CAR, ROAD, CROSS, GlobalTime);
//			}		
//		}
//
//		//计算拥挤度
//		computeRoadCrowding(ROAD);
//
//		////添加未来的拥挤信息
//		//int count=0;
//		//if (isDeadlock == true)
//		//{
//		//	for (int i = 0; i < roadSize; i++)
//		//	{
//		//		ROAD[i].crowding[0] = 0.3*ROAD[i].crowding[0] + 0.7*futureCrowing[count];
//		//		++count;
//		//		ROAD[i].crowding[1] = 0.3*ROAD[i].crowding[1] + 0.7*futureCrowing[count];
//		//		++count;
//		//	}
//		//}
//
//		//每隔N个时刻备份一次数据
//		int N = 50;
//		if ((GlobalTime%N) == 0)
//			mainBackup(CAR, CROSS, ROAD, GlobalTime);
//
//		resetRoadCarNumber();
//
//		++GlobalTime;
//
//		computeRANUM(GlobalTime,CAR[0]);
//
//		if (GlobalTime > bestTime)
//			return 2 * BADTIME;
//	}
//	cout << "total dieCount is " << dieCount << endl;
//	return GlobalTime - 1;
//}

//带死锁处理的判题器
int Dispatch::dispathMAIN_withDeal3(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime, int TT, int bestTime, const Graph_DG &OriginalCarGraph, vector<int> &CROSSID)
{
	//int waitNumber;
	int num, j, dieCount = 0, nowTime, pos, COUNT = 0, tempCount = 0;
	vector<int> roadIDS, dir, deadCar;
	vector<float> futureCrowing;
	vector<vector<int>> CarDeadRoadIds;
	vector<int> deadRoadId;
	for (int i = 0; i < (int)(CAR.size()); i++) {
		CarDeadRoadIds.push_back(deadRoadId);
	}
	vector<int> canBeChangedDeadCarIDs;

	//T1时刻初始化
	dispathINIT(CAR, CROSS, ROAD, GlobalTime, TT);
	++GlobalTime;
	//cout << "Inition OVER!" << endl;

	while (!isAllTerminate(CAR)) //未有所有车到达终点车库
	{
		//cout << endl << endl;
		cout << "GlobalTime is " << GlobalTime << endl;

		//if (GlobalTime > 20) 
		dynamicPlanSet(CAR, CROSS, ROAD, OriginalCarGraph);

		//直接处理可达终点状态的车辆
		setState(CAR, CROSS, ROAD, GlobalTime);

		//调度车库的优先车辆
		for (num = 0; num < crossSize; num++)
			moveCarportPriorityCar(num, CAR, ROAD, CROSS, GlobalTime);

		//调度所有道路上等待状态的车辆至终止状态
		while (!isAllEnd(CAR))
		{
			//gain waitNumber
			//waitNumber = gainWaitNum(CAR);
			isDeadlock = true;
			for (num = 0; num < crossSize; num++)
			{//按路口ID升序进行调度各个路口，路口内各道路按道路ID升序进行调度等待的车辆			
				roadIDS.clear();
				roadIDS.push_back(CROSS[num].road1);
				roadIDS.push_back(CROSS[num].road2);
				roadIDS.push_back(CROSS[num].road3);
				roadIDS.push_back(CROSS[num].road4);
				sort(roadIDS.begin(), roadIDS.end());

				//获取连接此路口的四个入入口方向道路的正反向
				dir.clear();
				for (int q = 0; q < 4; q++)
				{
					if (roadIDS[q] == -1) //没有路
					{
						dir.push_back(-1);
						continue;
					}
					if ((num + cross0) == ROAD[roadIDS[q] - road0].to)
						dir.push_back(0);
					else
						dir.push_back(1);
				}

				//按序遍历道路的第一优先级车辆
				for (int q = 0; q < 4; q++)
				{
					//当前道路上的车未被调度完
					while (!isRoadOver(roadIDS[q], dir[q], ROAD, CAR))
					{
						//获取第一优先级的车
						int carID = getCar(roadIDS[q], dir[q], ROAD, CAR);

						if (carID == -1)
							break;

						//备用，防止更新丢失
						int oldRoadID = roadIDS[q] - road0;
						int oldChannel = CAR[carID - car0].location[1];
						int oldPosition = CAR[carID - car0].location[2];

						/*int tempRoad = CAR[carID - car0].nextRoad;
						int tempDir = CAR[carID - car0].nextReverse;*/

						if (isConflict(q, carID, roadIDS, dir, ROAD, CAR)) //如果冲突，就换下一条路遍历
						{
							break;
						}

						//调度车辆
						//bool isEndInNextRoad = false;
						moveToNextRoad(carID, CAR, ROAD, CROSS, GlobalTime);

						if (CAR[carID - car0].state == 0) //调度失败，要去的路上有等待的车辆阻挡
						{
							break;
						}

						//***********setdeadlock*************
						isDeadlock = false;

						if (CAR[carID - car0].state == 1)	//调度成功
						{
							if (oldPosition == 1)
								break;

							for (j = oldPosition - 2; j >= 0; j--)
							{
								if (ROAD[oldRoadID].roadCar[dir[q]][oldChannel][j] == -1)
									continue;
								int newCar = ROAD[oldRoadID].roadCar[dir[q]][oldChannel][j] - car0;
								if (CAR[newCar].state == 0 && CAR[newCar].toNextRoad == 1) //等待下次遍历
								{
									//扫描当前车道是否有终止车阻挡
									int count = 0;
									for (int n = j + 1; n < ROAD[oldRoadID].length; n++)
									{
										if (ROAD[oldRoadID].roadCar[dir[q]][oldChannel][n] != -1)
										{
											++count;
											break;
										}
									}
									//受到阻挡，直接终止
									if (count == 1)
										moveOnTheRoad(newCar, CAR, ROAD, CROSS, GlobalTime);
									//不受阻挡，跳出重新扫描本道路的优先级
									if (count == 0)
										break;
								}
								if (CAR[newCar].state == 0 && CAR[newCar].toNextRoad == 0)
									moveOnTheRoad(newCar, CAR, ROAD, CROSS, GlobalTime);
							}
							//此路已通，调度要进该路的优先车
							moveCarportCarPriorityToRoad(roadIDS[q], dir[q], CAR, ROAD, CROSS, GlobalTime);
						}

					}
				}
			}
			if (isDeadlock == true)
				break;
		}
		//deadlock happen
		if (isDeadlock == true)
		{
			cout << "deadlock happen at GlobalTime in " << GlobalTime << endl;
			//this->getFreeBusyRoads(ROAD);	//获取freeRoads和busyRoads.
			canBeChangedDeadCarIDs.clear();
			canBeChangedDeadCarIDs = this->setFlagDeadCar2(CAR, CROSS, ROAD, CarDeadRoadIds);//设置死锁车辆标志位、设置死锁时的道路，设置死锁时的下一条道路
			//this->dealDeadLock_back(CAR, CROSS, ROAD, OriginalCarGraph, freeRoads, busyRoads, CROSSID);//后面三个参数其实没用到了，可以删除

			//获取死锁车
			deadCar.clear();
			deadCar = getDeadCarID(CAR, CROSS, ROAD);
			//deadCar=getDeadCarFirstAll(CAR, CROSS, ROAD);
			cout << "deadCar size is " << (int)(deadCar.size()) << endl;

			//获取修改的路径				
			nowTime = GlobalTime;
			//数据回滚到备份时刻
			++dieCount;

			//数据回滚
			pos = (int)(BackupData.size()) - 1;
			if (abs(nowTime - lastLockTime) < 70)
				++tempCount;
			else
				tempCount = 0;
			int limitCount = 6;
			if (nowTime == lastLockTime)
				++COUNT;
			else
				COUNT = 0;
			cout << "tempCount is " << tempCount << "COUNT is " << COUNT << endl;
			if (tempCount > 10)
			{
				tempCount = 0;
				pos = (int)(BackupData.size()) - 3;
			}
			else
			{
				if (nowTime <= lastLockTime && (int)(BackupData.size()) > 1)  //如果往前死锁，就往最近备份的前一个备份处恢复数据
				{
					int order = ceil((double)(COUNT) / (double)(limitCount));
					if (COUNT == 0)
						order = 1;
					pos = (int)(BackupData.size()) - order;
				}
				if (nowTime > lastLockTime || (int)(BackupData.size()) == 1) //如果往后死锁，就往最近备份的备份处恢复数据
					pos = (int)(BackupData.size()) - 1;
			}
			

			GlobalTime = BackupData[pos].backupTime;
			CAR.clear();
			CAR.insert(CAR.begin(), BackupData[pos].backup_CAR.begin(), BackupData[pos].backup_CAR.end());
			CROSS.clear();
			CROSS.insert(CROSS.begin(), BackupData[pos].backup_CROSS.begin(), BackupData[pos].backup_CROSS.end());
			ROAD.clear();
			ROAD.insert(ROAD.begin(), BackupData[pos].backup_ROAD.begin(), BackupData[pos].backup_ROAD.end());

			//备份删除
			BackupData.erase(BackupData.begin() + pos, BackupData.end());
			if(pos-8>0)
				BackupData.erase(BackupData.begin(), BackupData.begin() + pos-8);

			cout << "rollback time is " << GlobalTime << endl;
			cout << "dieCount is " << dieCount << endl;
			this->delayCarPT2(CAR, CROSS, ROAD, nowTime, deadCar);

			for (int i = 0; i < (int)(canBeChangedDeadCarIDs.size()); i++) {
				CAR[canBeChangedDeadCarIDs[i]].computeNEXT(ROAD, CROSS);
				this->changeDeadCarRoute2(CAR[canBeChangedDeadCarIDs[i]], CROSS, ROAD, OriginalCarGraph, CarDeadRoadIds[canBeChangedDeadCarIDs[i]]);
			}
			lastLockTime = nowTime;
		}
		
		if (isDeadlock == false)
		{
			//控制发车数量
			modifyPlantime(CAR, CROSS, ROAD, GlobalTime);
			//调度车库的车辆
			for (num = 0; num < crossSize; num++)
				moveCarport(num, CAR, ROAD, CROSS, GlobalTime);
		}
		//计算拥挤度
		computeRoadCrowding(ROAD);

		//每隔N个时刻备份一次数据
		int N = 50;
		if ((GlobalTime % N) == 0)
		{
			if ((int)(BackupData.size()) > 8)
				BackupData.erase(BackupData.begin(), BackupData.begin() + (int)(BackupData.size()) - 8);
			Backup_data backup_data;
			backup_data.init(CAR, CROSS, ROAD, GlobalTime);
			BackupData.push_back(backup_data);
		}

		resetRoadCarNumber();

		++GlobalTime;

		computeRANUM(GlobalTime,CAR[0]);

		if (GlobalTime > bestTime)
			return 2 * BADTIME;
	}
	cout << "total dieCount is " << dieCount << endl;
	return GlobalTime - 1;
}

int Dispatch::dispathMAIN(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime, int TT, int bestTime)
{
	//int waitNumber;
	int num,j, k;
	vector<int> roadIDS,dir;

	//T1时刻初始化
	dispathINIT(CAR, CROSS, ROAD, GlobalTime,TT);
	++GlobalTime;
	//cout << "Inition OVER!" << endl;

	while (!isAllTerminate(CAR)) //未有所有车到达终点车库
	{
		//cout << endl << endl;
		cout<< "GlobalTime is " << GlobalTime<< endl;
		//直接处理可达终点状态的车辆
		setState(CAR, CROSS, ROAD, GlobalTime);
		
		//调度车库的优先车辆
		for (num = 0; num < crossSize; num++)
			moveCarportPriorityCar(num, CAR, ROAD, CROSS, GlobalTime);

		//调度所有道路上等待状态的车辆至终止状态
		while (!isAllEnd(CAR))
		{
			//gain waitNumber
			//waitNumber = gainWaitNum(CAR);
			isDeadlock = true;
			for (num = 0; num < crossSize; num++)
			{//按路口ID升序进行调度各个路口，路口内各道路按道路ID升序进行调度等待的车辆			
				roadIDS.clear();
				roadIDS.push_back(CROSS[num].road1);
				roadIDS.push_back(CROSS[num].road2);
				roadIDS.push_back(CROSS[num].road3);
				roadIDS.push_back(CROSS[num].road4);
				sort(roadIDS.begin(), roadIDS.end());

				//获取连接此路口的四个入入口方向道路的正反向
				dir.clear();
				for (int q = 0; q < 4; q++)
				{
					if (roadIDS[q] == -1) //没有路
					{
						dir.push_back(-1);
						continue;
					}
					if ((num + cross0) == ROAD[roadIDS[q] - road0].to)
						dir.push_back(0);
					else
						dir.push_back(1);
				}

				//按序遍历道路的第一优先级车辆
				for (int q = 0; q < 4; q++)
				{
					//当前道路上的车未被调度完
					while (!isRoadOver(roadIDS[q], dir[q], ROAD, CAR))
					{
						//获取第一优先级的车
						int carID = getCar(roadIDS[q], dir[q], ROAD, CAR);

						if (carID == -1)
							break;

						//备用，防止更新丢失
						int oldRoadID = roadIDS[q] - road0;
						int oldChannel = CAR[carID - car0].location[1];
						int oldPosition = CAR[carID - car0].location[2];

						/*int tempRoad = CAR[carID - car0].nextRoad;
						int tempDir = CAR[carID - car0].nextReverse;*/

						if (isConflict(q, carID, roadIDS, dir, ROAD, CAR)) //如果冲突，就换下一条路遍历
						{
							break;
						}

						//调度车辆
						//bool isEndInNextRoad = false;
						moveToNextRoad(carID, CAR, ROAD, CROSS, GlobalTime);

						if (CAR[carID - car0].state == 0) //调度失败，要去的路上有等待的车辆阻挡
						{
							break;
						}

						//***********setdeadlock*************
						isDeadlock = false;

						if (CAR[carID - car0].state == 1)	//调度成功
						{
							if (oldPosition ==1)
								break;

							for (j = oldPosition - 2; j >= 0; j--)
							{
								if (ROAD[oldRoadID].roadCar[dir[q]][oldChannel][j] == -1)
									continue;
								int newCar = ROAD[oldRoadID].roadCar[dir[q]][oldChannel][j] - car0;
								if (CAR[newCar].state == 0 && CAR[newCar].toNextRoad == 1) //等待下次遍历
								{
									//扫描当前车道是否有终止车阻挡
									int count = 0;
									for (int n = j + 1; n < ROAD[oldRoadID].length; n++)
									{
										if (ROAD[oldRoadID].roadCar[dir[q]][oldChannel][n] != -1)
										{
											++count;
											break;
										}
									}
									//受到阻挡，直接终止
									if (count == 1)
										moveOnTheRoad(newCar, CAR, ROAD, CROSS, GlobalTime);
									//不受阻挡，跳出重新扫描本道路的优先级
									if (count == 0)
										break;
								}
								if (CAR[newCar].state == 0 && CAR[newCar].toNextRoad == 0)
									moveOnTheRoad(newCar, CAR, ROAD, CROSS, GlobalTime);
							}
							//此路已通，调度要进该路的优先车
							moveCarportCarPriorityToRoad(roadIDS[q], dir[q], CAR, ROAD, CROSS, GlobalTime);
						}
						
					}
				}
			}			
			//deadlock happen
			if (isDeadlock == true)
			{
				cout << "deadlock happen at GlobalTime in " << GlobalTime << endl;
				return BADTIME;
			}
			/*int nowWaitNumber = gainWaitNum(CAR);
			if (waitNumber == nowWaitNumber)
					return BADTIME;*/			

		}

		//控制发车数量
		//modifyPlantime(CAR, CROSS, ROAD, GlobalTime);

		//调度车库的车辆
		for(num=0;num<crossSize;num++)
			moveCarport2(num, CAR, ROAD, CROSS, GlobalTime);

		//查询道路当前车辆数目和总数目
		computeRoadCrowding(ROAD);

		//将所有车state设置为-1
		for (k = 0; k < carSize; k++)
		{
			CAR[k].toNextRoad = 0;
			CAR[k].setState(-1);
		}
		resetRoadCarNumber();

		++GlobalTime;

		//computeRANUM(GlobalTime);

		if (GlobalTime > bestTime)
			return 2*BADTIME;
	}

	return GlobalTime-1;
}

void Dispatch::computeRANUM(int nowTime, Car &FirstCar)
{
	if (FirstCar.from == 139) {
		//if (nowTime > 0 && nowTime < 300)
		//	RANUM = 6500;
		if (nowTime > 400 && nowTime < 900)
			RANUM = 6000;
		////if (nowTime > 800 && nowTime < 1000)
		////	RANUM = 5000;
		if (nowTime > 900 && nowTime < 1400)
			RANUM = 6500;
		//if (nowTime > 1200)
		//	RANUM = 5500;
	}
	else if (FirstCar.from == 146) {
		//if (nowTime > 0 && nowTime < 300)
	//	RANUM = 6500;
		if (nowTime > 600 && nowTime < 900)
			RANUM = 6300;
		////if (nowTime > 800 && nowTime < 1000)
		////	RANUM = 5000;
		if (nowTime > 900 && nowTime < 1400)
			RANUM = 6500;
		//if (nowTime > 1200)
		//	RANUM = 5500;
	}

	//else
	//{
	//	double x = PI / 3.0 + (PI / 3.0 / 500.0)*(double)(nowTime-500);
	//	double y = 6500.0 - 2500.0 * sin(x);
	//	RANUM = (int)(y);
	//}
}

void Dispatch::dynamicPlanSet(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, const Graph_DG &OriginalCarGraph) {
	int lastRoadID;
	int newRoadID;

	/*这两句是重点，重新规划路径*/
	Graph_DG dynamicGraph(OriginalCarGraph);
	dynamicGraph.initRoute_Dynamic(CAR, CROSS, ROAD);
	/*这两句是重点，重新规划路径*/

	//重置maxSP以及reverse
	for (int num = 0; num < carSize; num++) {

		if (CAR[num].preset == 1) {//预置车辆无需修改
			continue;
		}
		else if (CAR[num].isTerminate == 1) {//到达终点的车辆也无需修改
			continue;
		}

		CAR[num].maxSP.clear();
		CAR[num].reverse.clear();

		for (int i = 0; i < (int)CAR[num].route.size(); i++) {
			if (i == 0) {//第一条路
				int roadID = CAR[num].route[i] - road0;
				if (CAR[num].from == ROAD[roadID].from) {
					CAR[num].addRverse(0);
					//CAR[num].isRVER(0);
				}
				else if (CAR[num].from == ROAD[roadID].to) {
					CAR[num].addRverse(1);
					//CAR[num].isRVER(1);
				}
			}
			else {
				newRoadID = CAR[num].route[i] - road0;
				if (CAR[num].reverse[i - 1] == 0) //上一条路的from-to就是车的行进方向
				{
					lastRoadID = CAR[num].route[i - 1] - road0;
					if (ROAD[lastRoadID].to == ROAD[newRoadID].from)
						CAR[num].addRverse(0);
					else
						CAR[num].addRverse(1);
				}
				if (CAR[num].reverse[i - 1] == 1) //上一条路的to-from就是车的行进方向
				{
					lastRoadID = CAR[num].route[i - 1] - road0;
					if (ROAD[lastRoadID].from == ROAD[newRoadID].from)
						CAR[num].addRverse(0);
					else
						CAR[num].addRverse(1);
				}
			}
			if (CAR[num].speed < ROAD[CAR[num].route[i] - road0].speed)
				CAR[num].addMaxSpeed(CAR[num].speed);
			else
				CAR[num].addMaxSpeed(ROAD[CAR[num].route[i] - road0].speed);
		}
	}
}


void Dispatch::getFreeBusyRoads(vector<Road> &ROAD) {

	freeRoads.clear();
	busyRoads.clear();

	//计算路上车流量的平均值，记得等下换成拥挤度的
	int ave_allCarNum = 0;
	for (int i = 0; i < (int)(ROAD.size()); i++) {
		ave_allCarNum += ROAD[i].allCarNum;
	}
	ave_allCarNum = ave_allCarNum / (int)(ROAD.size());

	//识别出车流量少的路
	//cout << "所有道路的车流量情况： " << endl;
	for (int i = 0; i < (int)(ROAD.size()); i++) {
		//cout << "道路id： " << ROAD[i].id << "车流量: " << ROAD[i].allCarNum << endl;
		if (ROAD[i].allCarNum < 0.2 * ave_allCarNum) {
			freeRoads.push_back(ROAD[i].id);
		}
		if (ROAD[i].allCarNum > 2.5 * ave_allCarNum) {
			busyRoads.push_back(ROAD[i].id);
		}
		else {
			//cout << "道路id： " << ROAD[i].id << "车流量: " << ROAD[i].allCarNum << endl;
			//cout << "道路id： " << ROAD[i].id << "该路权重为: " << ROAD[i].allCarNum << endl;
		}
	}
}

vector<int> Dispatch::setFlagDeadCar(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, vector<vector<int>> &CarDeadRoadId) {
	vector<int> carIDs;
	vector<int> canBeChangedDeadCarIDs;
	//canBeChangedDeadCarIDs.clear();
	for (int num = 0; num < crossSize; num++)
	{//按路口ID升序进行调度各个路口，路口内各道路按道路ID升序进行调度等待的车辆
		//cout << ", cross num is " << num;
		int roadIDS[4] = { CROSS[num].road1,CROSS[num].road2, CROSS[num].road3, CROSS[num].road4 };
		sort(roadIDS, roadIDS + 4); //从小到大排序

		//获取连接此路口的四个入入口方向道路的正反向
		int dir[4];
		for (int q = 0; q < 4; q++)
		{
			if (roadIDS[q] == -1) //没有路
				continue;
			if (ROAD[roadIDS[q] - road0].to == num + cross0)
				dir[q] = 0;
			else
				dir[q] = 1;
		}

		//按序遍历道路的第一优先级车辆
		for (int q = 0; q < 4; q++)
		{
			//当前道路上的车未被调度完
			while (!isRoadOver(roadIDS[q], dir[q], ROAD, CAR))
			{
				//获取第一优先级的车...
				carIDs.clear();
				carIDs = getCar3(roadIDS[q], dir[q], ROAD, CAR, 15);
				if (carIDs.size() == 0)
					break;
				for (int i = 0; i < (int)carIDs.size(); i++) {

					if (CAR[carIDs[i] - car0].preset == 1) {
						continue;
					}
					if (CAR[carIDs[i] - car0].nextCrossDistance < CAR[carIDs[i] - car0].maxSpeed) {//当前时刻要过路口的车，不要修改，情况太多，有bug
						continue;
					}
					if (CAR[carIDs[i] - car0].passRoadNumber == (int)(CAR[carIDs[i] - car0].route.size()) - 1) {//目前这条路是该车的最后一段路，也不要凑热闹了
						continue;
					}
					else if (CAR[carIDs[i] - car0].passRoadNumber ==(int)(CAR[carIDs[i] - car0].route.size()) - 2) {//该车的下一条路是要到终点，也不要凑热闹了
						continue;
					}
					else if (CAR[carIDs[i] - car0].passRoadNumber == (int)(CAR[carIDs[i] - car0].route.size()) - 3) {//该车的下下一条路是要到终点，也不要凑热闹了
						continue;
					}
					//CAR[carIDs[i] - car0].usedToBeDeadCar = true;//走下去有设置这个标志的，这里不需要
					CAR[carIDs[i] - car0].changeDeadFlag = true;//注意
					CAR[carIDs[i] - car0].deadInRoadId = CAR[carIDs[i] - car0].location[0];
					CarDeadRoadId[carIDs[i] - car0].push_back(CAR[carIDs[i] - car0].location[0]);
					CAR[carIDs[i] - car0].deadRoadId.push_back(CAR[carIDs[i] - car0].location[0]);
					CAR[carIDs[i] - car0].deadInRoadId_next = CAR[carIDs[i] - car0].nextRoad;
					canBeChangedDeadCarIDs.push_back(carIDs[i] - car0);
				}
				break;
			}
		}
	}
	return canBeChangedDeadCarIDs;
}

//从备份时刻开始改，先不管目前是否要过路口
vector<int> Dispatch::setFlagDeadCar2(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, vector<vector<int>> &CarDeadRoadId) {
	vector<int> carIDs;
	vector<int> canBeChangedDeadCarIDs;
	//canBeChangedDeadCarIDs.clear();
	for (int num = 0; num < crossSize; num++)
	{//按路口ID升序进行调度各个路口，路口内各道路按道路ID升序进行调度等待的车辆
		//cout << ", cross num is " << num;
		int roadIDS[4] = { CROSS[num].road1,CROSS[num].road2, CROSS[num].road3, CROSS[num].road4 };
		sort(roadIDS, roadIDS + 4); //从小到大排序

		//获取连接此路口的四个入入口方向道路的正反向
		int dir[4];
		for (int q = 0; q < 4; q++)
		{
			if (roadIDS[q] == -1) //没有路
				continue;
			if (ROAD[roadIDS[q] - road0].to == num + cross0)
				dir[q] = 0;
			else
				dir[q] = 1;
		}

		//按序遍历道路的第一优先级车辆
		for (int q = 0; q < 4; q++)
		{
			//当前道路上的车未被调度完
			while (!isRoadOver(roadIDS[q], dir[q], ROAD, CAR))
			{
				//获取第一优先级的车...
				carIDs.clear();
				carIDs = getCar3(roadIDS[q], dir[q], ROAD, CAR, 15);
				if (carIDs.size() == 0)
					break;
				for (int i = 0; i < (int)carIDs.size(); i++) {

					if (CAR[carIDs[i] - car0].preset == 1) {
						continue;
					}
					//if (CAR[carIDs[i] - car0].nextCrossDistance < CAR[carIDs[i] - car0].maxSpeed) {//当前时刻要过路口的车，不要修改，情况太多，有bug
					//	continue;
					//}
					//if (CAR[carIDs[i] - car0].passRoadNumber == CAR[carIDs[i] - car0].route.size() - 1) {//目前这条路是该车的最后一段路，也不要凑热闹了
					//	continue;
					//}
					//else if (CAR[carIDs[i] - car0].passRoadNumber == CAR[carIDs[i] - car0].route.size() - 2) {//该车的下一条路是要到终点，也不要凑热闹了
					//	continue;
					//}
					//else if (CAR[carIDs[i] - car0].passRoadNumber == CAR[carIDs[i] - car0].route.size() - 3) {//该车的下下一条路是要到终点，也不要凑热闹了
					//	continue;
					//}
					//CAR[carIDs[i] - car0].usedToBeDeadCar = true;//走下去有设置这个标志的，这里不需要
					CAR[carIDs[i] - car0].changeDeadFlag = true;//注意
					//CAR[carIDs[i] - car0].deadInRoadId = CAR[carIDs[i] - car0].location[0];
					CarDeadRoadId[carIDs[i] - car0].push_back(CAR[carIDs[i] - car0].location[0]);
					//CAR[carIDs[i] - car0].deadRoadId.push_back(CAR[carIDs[i] - car0].location[0]);
					//CAR[carIDs[i] - car0].deadInRoadId_next = CAR[carIDs[i] - car0].nextRoad;
					canBeChangedDeadCarIDs.push_back(carIDs[i] - car0);
				}
				break;
			}
		}
	}
	return canBeChangedDeadCarIDs;
}

void Dispatch::changeDeadCarRoute(Car &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, const Graph_DG &OriginalCarGraph) {

	if (CAR.preset != 1 && CAR.ATD!=-1 && CAR.nextCrossDistance >= CAR.maxSpeed && CAR.passRoadNumber < (int)(CAR.route.size()) - 2) {//过路口、预置车、最后两条路的，都不改
		Graph_DG deadCarGraph(OriginalCarGraph);
		deadCarGraph.initRoute_DealLock_back2(CAR, CROSS, ROAD);
		//这里要换成改该车的下一条路、重新计算四个vector
		//计算maxSP和reverse
		CAR.maxSP.clear();
		CAR.reverse.clear();
		int roadID = CAR.route[0] - road0;
		if (CAR.from == ROAD[roadID].from) //正向
		{
			CAR.addRverse(0);
		}
		if (CAR.from == ROAD[roadID].to) //反向
		{
			CAR.addRverse(1);
		}
		for (int i = 0; i < (int)(CAR.route.size()); i++)
		{
			int newRoadID = CAR.route[i] - road0;
			if (i > 0)
			{
				if (CAR.reverse[i - 1] == 0) //上一条路的from-to就是车的行进方向
				{
					int lastRoad = CAR.route[i - 1] - road0;
					if (ROAD[lastRoad].to == ROAD[newRoadID].from)
						CAR.addRverse(0);
					else
						CAR.addRverse(1);
				}
				if (CAR.reverse[i - 1] == 1) //上一条路的to-from就是车的行进方向
				{
					int lastRoad = CAR.route[i - 1] - road0;
					if (ROAD[lastRoad].from == ROAD[newRoadID].from)
						CAR.addRverse(0);
					else
						CAR.addRverse(1);
				}
			}

			if (CAR.speed < ROAD[CAR.route[i] - road0].speed)
				CAR.addMaxSpeed(CAR.speed);
			else
				CAR.addMaxSpeed(ROAD[CAR.route[i] - road0].speed);
		}
	}
}

void Dispatch::changeDeadCarRoute2(Car &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, const Graph_DG &OriginalCarGraph, vector<int> &CarDeadRoadId) {

	if (CAR.preset != 1 && CAR.ATD != -1 && CAR.nextCrossDistance >= CAR.maxSpeed && CAR.passRoadNumber < (int)(CAR.route.size()) - 2) {//过路口、预置车、最后两条路的，都不改
		Graph_DG deadCarGraph(OriginalCarGraph);
		deadCarGraph.initRoute_DealLock_back3(CAR, CROSS, ROAD, CarDeadRoadId);
		//这里要换成改该车的下一条路、重新计算四个vector
		//计算maxSP和reverse
		CAR.maxSP.clear();
		CAR.reverse.clear();
		int roadID = CAR.route[0] - road0;
		if (CAR.from == ROAD[roadID].from) //正向
		{
			CAR.addRverse(0);
		}
		if (CAR.from == ROAD[roadID].to) //反向
		{
			CAR.addRverse(1);
		}
		for (int i = 0; i < (int)(CAR.route.size()); i++)
		{
			int newRoadID = CAR.route[i] - road0;
			if (i > 0)
			{
				if (CAR.reverse[i - 1] == 0) //上一条路的from-to就是车的行进方向
				{
					int lastRoad = CAR.route[i - 1] - road0;
					if (ROAD[lastRoad].to == ROAD[newRoadID].from)
						CAR.addRverse(0);
					else
						CAR.addRverse(1);
				}
				if (CAR.reverse[i - 1] == 1) //上一条路的to-from就是车的行进方向
				{
					int lastRoad = CAR.route[i - 1] - road0;
					if (ROAD[lastRoad].from == ROAD[newRoadID].from)
						CAR.addRverse(0);
					else
						CAR.addRverse(1);
				}
			}

			if (CAR.speed < ROAD[CAR.route[i] - road0].speed)
				CAR.addMaxSpeed(CAR.speed);
			else
				CAR.addMaxSpeed(ROAD[CAR.route[i] - road0].speed);
		}
	}
}


void Dispatch::printOUT(vector<Car> &CAR)
{
	int i, j;
	cout << "The routes are:" << endl;
	for (i = 0; i < (int)(CAR.size()); i++)
	{
		cout << "(" << CAR[i].id << ", " << CAR[i].ATD << ", ";
		for (j = 0; j < (int)(CAR[i].route.size())-1; j++)
		{
			cout << CAR[i].route[j] << ", ";
		}
		cout << CAR[i].route[j] << ")" << endl;
	}
}
