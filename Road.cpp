#include "Road.h"
#include <cstdio>
#include <cstring>

bool Road::init(vector<int> roadData)
{
	if (roadData.size() == 0)
		return false;

	id = roadData[0];
	length = roadData[1];
	speed = roadData[2];
	channel = roadData[3];
	from = roadData[4];
	to = roadData[5];
	isDuplex = roadData[6];
	memset(roadCar, 0xff, sizeof(roadCar));
	vector<int> T1;
	vector<vector<int>> T2;
	T2.push_back(T1);
	T2.push_back(T1);
	T2.push_back(T1);
	WaitCar.push_back(T2);
	WaitCar.push_back(T2);
	return true;
}

void Road::addWaitCar(int way, int direction, int carId)
{
	WaitCar[way][direction].push_back(carId);
}

void Road::subWaitCar(int way, int direction, vector<int> carCut)
{
	vector<int>::iterator it0, it1;
	for (it0 = carCut.begin(); it0 != carCut.end(); it0++)
		for (it1 = WaitCar[way][direction].begin(); it1 != WaitCar[way][direction].end();)
		{
			if (*it1 == *it0)
				it1 = WaitCar[way][direction].erase(it1);	//删除元素，返回值指向已删除元素的下一个位置   
			else
				++it1;
		}
}

void Road::addRoadCar(int direction, int lane, int position, int carId)
{
	roadCar[direction][lane][position] = carId;
}

void Road::subRoadCar(int direction, int lane, int position)
{
	roadCar[direction][lane][position] = -1;
}

void Road::clearWaitCar(int way)
{
	if ((int)(WaitCar[way][0].size()) > 0)
		WaitCar[way][0].clear();
	if ((int)(WaitCar[way][1].size()) > 0)
		WaitCar[way][1].clear();
	if ((int)(WaitCar[way][2].size()) > 0)
		WaitCar[way][2].clear();
}

void Road::renew()
{
	clearWaitCar(0);
	clearWaitCar(1);

	nowCarNum = 0;		
	allCarNum = 0;
	
	memset(roadCar, 0xff, sizeof(nowNum));
	memset(roadCar, 0xff, sizeof(allNum));
	memset(roadCar, 0xff, sizeof(crowding));

	//roadCar[2][6][21]
	memset(roadCar, 0xff, sizeof(roadCar));
}

int Road::getNowCarNum()
{
	int m, k, j;
	nowCarNum = 0;
	for (m = 0; m < 2; m++)
	{
		if (m == 1 && isDuplex == 0)
			continue;
		for (k = 0; k < channel; k++)
			for (j = 0; j < length; j++)
			{
				if (roadCar[m][k][j] != -1)
					++nowCarNum;
			}
	}
	return nowCarNum;
}

