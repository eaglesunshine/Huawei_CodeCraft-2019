#pragma once
#ifndef __BACK_DATA_H__
#define __BACK_DATA_H__

#include <vector>
#include "Car.h"
#include "Cross.h"
#include "Road.h"

using namespace std;

class Backup_data
{
public:
	int backupTime = 0;
	vector<Car> backup_CAR;
	vector<Cross> backup_CROSS;
	vector<Road> backup_ROAD;

	bool init(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime);
};

#endif 
