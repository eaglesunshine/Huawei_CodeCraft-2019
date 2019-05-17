#include "Car.h"
#include "time.h"
#include <cstdio>
#include <cstring>
#include "stdlib.h"
#define N  9999


bool Car::init(vector<int> carData)
{
	if (carData.size() == 0)
		return false;

	id = carData[0];
	from = carData[1];
	to = carData[2];
	speed = carData[3];
	planTime = carData[4];
	PT = planTime;
	priority = carData[5];
	preset = carData[6];
	return true;
}

vector<int> Car::setRoute(vector<int> routeData)
{
	return routeData;
}

void Car::setEndTime(int Time)
{
	EndTime = Time;
}

void Car::setNowSpeed(int speed)
{
	nowSpeed = speed;
}

void Car::updateRoute(int num, int roadId)
{
	int oldSize = (int)(route.size());
	if (num <= oldSize + 1)
		route[num - 1] = roadId;
	else
		route.push_back(roadId);
}

void Car::updateLocation(int road, int channel, int position)
{
	location[0] = road;
	location[1] = channel;
	location[2] = position;
}

void Car::setATD(int time)
{
	ATD = time;
}

void Car::setState(int STD)
{
	state = STD;
}

void Car::setBlockDistance(int distance)
{
	blockDistance = distance;
}

bool Car::computeNEXT(vector<Road> &ROAD, vector<Cross> &CROSS)
{
	////计算nextRoad,nextRoadSpeed,nextCrossDirection,nextCrossDistance
	//int nowRoad = location[0];
	//vector<int>::iterator it;
	//int num = 0;
	//for (it = route.begin(); it != route.end(); it++)
	//{
	//	if (*it == nowRoad)
	//		break;
	//	++num;
	//}

	int num = passRoadNumber;
	int nowRoad = route[num];

	if (num == (int)(route.size()) - 1) //最后一条路
	{
		maxSpeed = maxSP[num];
		isReverse = reverse[num];
		nextRoad = LastRoad;  //new

		if (isReverse == 0)
			nextCross = ROAD[nowRoad - ROAD[0].id].to;
		else
			nextCross = ROAD[nowRoad - ROAD[0].id].from;

		if (LastRoad == -1)
			nextReverse = 0;

		if (LastRoad != -1)  //new
		{
			if (nextCross == ROAD[nextRoad - ROAD[0].id].from)
				nextReverse = 0;
			if (nextCross == ROAD[nextRoad - ROAD[0].id].to)
				nextReverse = 1;
		}

		nextRoadSpeed = -1;

		nextCrossDirection = 0;  //new

		nextCrossDistance = ROAD[nowRoad - ROAD[0].id].length - location[2];

		return false;
	}

	maxSpeed = maxSP[num];
	isReverse = reverse[num];

	nextReverse = reverse[num + 1];
	nextRoad = route[num + 1];

	if (isReverse == 0)
		nextCross = ROAD[nowRoad - ROAD[0].id].to;
	else
		nextCross = ROAD[nowRoad - ROAD[0].id].from;

	nextRoadSpeed = maxSP[num + 1];

	nextCrossDirection = direction[num + 1];

	nextCrossDistance = ROAD[nowRoad - ROAD[0].id].length - location[2];
	return true;
}

void Car::setReverse(int Is)
{
	isReverse = Is;
}

void Car::setToNextRoad(int Is)
{
	toNextRoad = Is;
}

void Car::setIsTerminate(int Is)
{
	isTerminate = Is;
}

void Car::addRverse(int ISR)
{
	reverse.push_back(ISR);
}

void Car::addMaxSpeed(int SP)
{
	maxSP.push_back(SP);
}

void Car::isRVER(int ISR)
{
	isReverse = ISR;
}

//void Car::addDieCount(int roadID)
//{
//	++dieCount[roadID];
//}

void Car::addPlanTime()
{
	//int RandomNumber;
	//RandomNumber = rand() % 10 + 1;//生成1~100随机数
	//float randI = rand() % (N + 1) / (float)(N + 1);
	//if(randI>0.5)
	PT = PT + 1;
}

void Car::addPlanTime1()
{
	if (preset == 0)
		PT = PT + 1;
	if (preset == 1)
		PT = PT;
}

void Car::addPT(int T)
{
	if (preset == 0)
		PT = PT + T;
	if (preset == 1)
		PT = PT;
}

void Car::renew()
{
	ATD = -1;
	EndTime = 0;
	nowSpeed = 0;
	maxSpeed = 0;
	for (int i = 0; i < 3; i++)
		location[i] = 0;
	nextRoad = 0;
	nextCross = 0;
	nextRoadSpeed = 0;
	nextCrossDistance = 0;
	nextCrossDirection = 0;
	state = -1;
	blockDistance = 0;
	isReverse = 0;
	toNextRoad = 0;
	isTerminate = 0;
	nextReverse = 0;
	isReset = 0;
	passRoadNumber = 0;
	//memset(dieCount, 0, sizeof(dieCount));
	maxSPClear();
	reverseClear();
}

void Car::maxSPClear()
{
	if(maxSP.size()>0)
		maxSP.clear();
}


void Car::reverseClear()
{
	if(reverse.size()>0)
		reverse.clear();
}

//void Car::dieToZero()
//{
//	memset(dieCount, 0, sizeof(dieCount));
//}

void Car::setReset(int IS)
{
	isReset = IS;
}

void Car::subPT(int T)
{
	if (preset == 1)
		PT = PT;
	if (preset == 0)
	{
		if ((PT - T) > planTime)
			PT = PT - T;
	}
	//int RandomNumber = rand() % rate + 1;//生成1~5随机数
	//if (PT - RandomNumber > planTime)
	//{
	//	PT = PT - RandomNumber;
	//	//float randI = rand() % (N + 1) / (float)(N + 1);
	//	//if(randI>0.4)
	//	//	PT = PT - RandomNumber;
	//	//else
	//	//	PT = PT + RandomNumber;
	//}
}

void Car::setPT(int T)
{
	PT = T;
}