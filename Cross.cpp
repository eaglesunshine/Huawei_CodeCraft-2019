#include "Cross.h"
#include <cstdio>
#include <cstring>

bool Cross::init(vector<int> crossData)
{
	if ((int)(crossData.size()) == 0)
		return false;

	id = crossData[0];
	road1 = crossData[1];
	road2 = crossData[2];
	road3 = crossData[3];
	road4 = crossData[4];
	return true;
}

void Cross::addStartCar(int carId)
{
	StartCar.push_back(carId);
}

void Cross::subStartCar(vector<int> carCut)
{
	vector<int>::iterator it0, it1;
	for (it0 = carCut.begin(); it0 != carCut.end(); it0++)
		for (it1 = StartCar.begin(); it1 != StartCar.end();)
		{
			if (*it1 == *it0)
				it1 = StartCar.erase(it1);	//删除元素，返回值指向已删除元素的下一个位置
			else
				++it1;
		}
}

void Cross::renew()
{
	if ((int)(StartCar.size() )> 0)
		StartCar.clear();
}
