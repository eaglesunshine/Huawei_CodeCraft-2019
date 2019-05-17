#include "Backup_data.h"

bool Backup_data::init(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, int &GlobalTime)
{
	backupTime = GlobalTime;
	backup_CAR.clear();
	backup_CAR.insert(backup_CAR.begin(), CAR.begin(), CAR.end());
	backup_CROSS.clear();
	backup_CROSS.insert(backup_CROSS.begin(), CROSS.begin(), CROSS.end());
	backup_ROAD.clear();
	backup_ROAD.insert(backup_ROAD.begin(), ROAD.begin(), ROAD.end());
	return true;
}
