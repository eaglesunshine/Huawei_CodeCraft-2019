#include "readfile.h"
#include <fstream>
#include <string>
#include <sstream>

Readfile::Readfile(string carP, string roadP, string crossP, string answerP, string presetAnswerP)
{
	this->carPath = carP;
	this->roadPath = roadP;
	this->crossPath = crossP;
	this->answerPath = answerP;
	this->presetAnswerPath = presetAnswerP;

	this->getMapData(carP, roadP, crossP, answerP, presetAnswerP);
	this->getVectorData();
	this->setPreset();
	this->Tranfer();	
}

//判断路径合法：先拿preset_map先去做路径的id映射，再调此函数做路径可达判断
bool Readfile::isRouteLegal(Car &car, vector<Cross> &CROSS, vector<Road> &ROAD, vector<int> &ROADID)
{
	int i;
	vector<int>::iterator pos;

	//判断路径是否可达
	car.reverse.clear();
	for (i = 0; i < (int)(car.route.size()); i++)
	{
		int newRoadID = car.route[i];
		if (i == 0)
		{
			if (car.from == ROAD[newRoadID].from) //正向
			{
				car.addRverse(0);
			}
			if (car.from == ROAD[newRoadID].to) //反向
			{
				car.addRverse(1);
			}
			else   //路口对接不上
				return false;
		}
		if (i > 0)
		{
			if (car.reverse[i - 1] == 0) //上一条路的from-to就是车的行进方向
			{
				int lastRoad = car.route[i - 1];
				if (ROAD[lastRoad].to == ROAD[newRoadID].from)
					car.addRverse(0);
				if (ROAD[lastRoad].to == ROAD[newRoadID].to)
					car.addRverse(1);
				else
					return false;
			}
			if (car.reverse[i - 1] == 1) //上一条路的to-from就是车的行进方向
			{
				int lastRoad = car.route[i - 1];
				if (ROAD[lastRoad].from == ROAD[newRoadID].from)
					car.addRverse(0);
				if (ROAD[lastRoad].from == ROAD[newRoadID].to)
					car.addRverse(1);
				else
					return false;
			}
		}
	}
	//判断终点
	if (car.reverse[i] == 0)
	{
		if (ROAD[car.route[i]].to != car.to)
			return false;
	}
	if (car.reverse[i] == 1)
	{
		if (ROAD[car.route[i]].from != car.to)
			return false;
	}
	car.reverse.clear();

	return true;
}

vector<Car> Readfile::getCar()
{
	return CAR;
}

vector<Cross> Readfile::getCross()
{
	return CROSS;
}

vector<Road> Readfile::getRoad()
{
	return ROAD;
}

map<int,PresetAnswer> Readfile::getPreset()
{
	return PRESET_map;
}

vector<vector<int>> Readfile::getData(string fileName)
{
	ifstream inFile(fileName, ios::in);		// 读文件
	string lineStr;
	int count = 0;
	vector<vector<int>> ResultData;

	while (getline(inFile, lineStr))
	{
		stringstream ss(lineStr);
		string str;
		int pos1, pos2;
		vector<int> lineArray;

		while (getline(ss, str, ','))	// 按照逗号分隔,读取一行
		{
			pos1 = str.find("(");
			pos2 = str.find(")");
			if (pos1 != -1)
				str = str.substr(1, str.length() - 1);
			if (pos2 != -1)
				str = str.substr(0, str.length() - 1);

			lineArray.push_back(atoi(str.c_str()));
		}

		++count;
		if (count == 1)
			continue;

		ResultData.push_back(lineArray);
	}

	return ResultData;
}

void Readfile::getMapData(string carP, string roadP, string crossP, string answerp, string presetAnswerP)
{
	ReadfileMap myReadfile_map(carPath, roadPath, crossPath, answerPath, presetAnswerP);
	this->CAR_map = myReadfile_map.getCar();
	this->CROSS_map = myReadfile_map.getCross();
	this->ROAD_map = myReadfile_map.getRoad();
	this->PRESET_map = myReadfile_map.getPreset();

	CARid.insert(CARid.begin(), myReadfile_map.CARID.begin(), myReadfile_map.CARID.end());
	CROSSid.insert(CROSSid.begin(), myReadfile_map.CROSSID.begin(), myReadfile_map.CROSSID.end());
	ROADid.insert(ROADid.begin(), myReadfile_map.ROADID.begin(), myReadfile_map.ROADID.end());
	PRESETid.insert(PRESETid.begin(), myReadfile_map.PRESETID.begin(), myReadfile_map.PRESETID.end());
}

void Readfile::getVectorData()
{
	//map->vector
	map<int, Car>::iterator car_it;
	map<int, Cross>::iterator cross_it;
	map<int, Road>::iterator road_it;

	for (car_it = CAR_map.begin(); car_it != CAR_map.end(); car_it++)
	{
		this->CAR.push_back(car_it->second);
	}
	for (cross_it = CROSS_map.begin(); cross_it != CROSS_map.end(); cross_it++)
	{
		this->CROSS.push_back(cross_it->second);
	}
	for (road_it = ROAD_map.begin(); road_it != ROAD_map.end(); road_it++)
	{
		this->ROAD.push_back(road_it->second);
	}
}

void Readfile::setPreset()
{
	for (int i = 0; i < (int)(CAR.size()); i++)
	{
		if (CAR[i].preset == 1)
		{
			int carID = CAR[i].id;
			CAR[i].PT = PRESET_map[carID].ATD;
			CAR[i].route.insert(CAR[i].route.begin(), PRESET_map[carID].route.begin(), PRESET_map[carID].route.end());
		}
	}
}

void Readfile::Tranfer()
{
	//tsanfer id
	vector<int>::iterator it_cross, it_road;
	for (int i = 0; i < (int)(CAR.size()); i++)
	{
		CAR[i].idReal = CAR[i].id;
		CAR[i].id = i;
		it_cross = find(CROSSid.begin(), CROSSid.end(), CAR[i].from);
		CAR[i].from = &*(it_cross)-&CROSSid[0];
		it_cross = find(CROSSid.begin(), CROSSid.end(), CAR[i].to);
		CAR[i].to = &*(it_cross)-&CROSSid[0];
		if (CAR[i].preset == 1)
		{
			for (int j = 0; j < (int)(CAR[i].route.size()); j++)
			{
				it_road = find(ROADid.begin(), ROADid.end(), CAR[i].route[j]);
				CAR[i].route[j]= &*(it_road)-&ROADid[0];
			}
		}
	}

	for (int i = 0; i < (int)(CROSS.size()); i++)
	{
		CROSS[i].idReal = CROSS[i].id;
		CROSS[i].id = i;
		if (CROSS[i].road1 != -1)
		{
			it_road = find(ROADid.begin(), ROADid.end(), CROSS[i].road1);
			CROSS[i].road1 = &*(it_road)-&ROADid[0];
		}
		if (CROSS[i].road2 != -1)
		{
			it_road = find(ROADid.begin(), ROADid.end(), CROSS[i].road2);
			CROSS[i].road2 = &*(it_road)-&ROADid[0];
		}
		if (CROSS[i].road3 != -1)
		{
			it_road = find(ROADid.begin(), ROADid.end(), CROSS[i].road3);
			CROSS[i].road3 = &*(it_road)-&ROADid[0];
		}
		if (CROSS[i].road4 != -1)
		{
			it_road = find(ROADid.begin(), ROADid.end(), CROSS[i].road4);
			CROSS[i].road4 = &*(it_road)-&ROADid[0];
		}
	}

	for (int i = 0; i < (int)(ROAD.size()); i++)
	{
		ROAD[i].idReal = ROAD[i].id;
		ROAD[i].id = i;
		it_cross = find(CROSSid.begin(), CROSSid.end(), ROAD[i].from);
		ROAD[i].from = &*(it_cross)-&CROSSid[0];
		it_cross = find(CROSSid.begin(), CROSSid.end(), ROAD[i].to);
		ROAD[i].to = &*(it_cross)-&CROSSid[0];
	}
}

void Readfile::inTranfer(vector<Car> &CAR)
{
	//inTransfer id
	for (int i = 0; i < (int)(CAR.size()); i++)
	{
		CAR[i].id = CARid[i];
		for (int j = 0; j < (int)(CAR[i].route.size()); j++)
		{
			CAR[i].route[j] = ROADid[CAR[i].route[j]];
		}
	}
}

void Readfile::outPut(vector<Car> &CAR)
{
	ofstream out;
	out.open(answerPath);
	out << "#(carId, StartTime, RoadId[])" << endl;
	int i, j;
	for (i = 0; i < (int)(CAR.size()); i++)
	{
		if (CAR[i].preset == 1)
			continue;
		out << "(" << CAR[i].id << ", " << CAR[i].ATD << ", ";
		for (j = 0; j < (int)(CAR[i].route.size()) - 1; j++)
		{
			out << CAR[i].route[j] << ", ";
		}
		out << CAR[i].route[j] << ")" << endl;
	}
	out.close();
}

void Readfile::outPut2()
{
	ofstream out;
	out.open("config/newcar.txt");
	out << "#(carId, StartTime, RoadId[])" << endl;
	int  n, count = 0;
	map<int, Car>::iterator car_it;
	for (n = 0; n < 4; n++)
	{
		int addNum = n * 200000;
		int zero = 0;
		for (car_it=CAR_map.begin(); car_it!= CAR_map.end(); car_it++)
		{
			if (count > 200000)
				break;
			out << "(" << (car_it->second.id+addNum) << ", " 
				<< car_it->second.from << ", "
				<< car_it->second.to<<", "
				<<car_it->second.speed<< ", "
				<< car_it->second.planTime<<", "
				<< car_it->second.priority<<", "
				<< zero << ")" << endl;
			++count;
		}
	}	
	out.close();
}