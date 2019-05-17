#include "readfile_map.h"
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

ReadfileMap::ReadfileMap(string carP, string roadP, string crossP, string answerP, string presetAnswerP)
{
	this->carPath = carP;
	this->roadPath = roadP;
	this->crossPath = crossP;
	this->answerPath = answerP;
	this->presetAnswerPath = presetAnswerP;
}

map<int, Car> ReadfileMap::getCar()
{
	int num;
	vector<vector<int>> carDataAll = getData(carPath);
	num = 0;
	map<int, Car> CAR;
	while (num < (int)(carDataAll.size()))
	{
		Car tempCar;
		tempCar.init(carDataAll[num]);
		CAR.insert(pair<int, Car>(carDataAll[num][0],tempCar));
		CARID.push_back(carDataAll[num][0]);
		++num;
	}
	sort(CARID.begin(),CARID.end());
	return CAR;
}

map<int, Cross> ReadfileMap::getCross()
{
	int num;
	vector<vector<int>> crossDataAll = getData(crossPath);
	num = 0;
	map<int, Cross> CROSS;
	while (num < (int)(crossDataAll.size()))
	{
		Cross tempCross;
		tempCross.init(crossDataAll[num]);
		CROSS.insert(pair<int, Cross>(crossDataAll[num][0], tempCross));
		CROSSID.push_back(crossDataAll[num][0]);
		++num;
	}
	sort(CROSSID.begin(), CROSSID.end());
	return CROSS;
}

map<int, Road> ReadfileMap::getRoad()
{
	int num;
	vector<vector<int>> roadDataAll = getData(roadPath);
	num = 0;
	map<int, Road> ROAD;
	while (num < (int)(roadDataAll.size()))
	{
		Road tempRoad;
		tempRoad.init(roadDataAll[num]);
		ROAD.insert(pair<int, Road>(roadDataAll[num][0], tempRoad));
		ROADID.push_back(roadDataAll[num][0]);
		++num;
	}
	sort(ROADID.begin(), ROADID.end());
	return ROAD;
}

map<int, PresetAnswer> ReadfileMap::getPreset()
{
	int num;
	vector<vector<int>> presetDataAll = getData(presetAnswerPath);
	num = 0;
	map<int, PresetAnswer> PRESET;
	while (num < (int)(presetDataAll.size()))
	{
		PresetAnswer tempPreset;
		tempPreset.init(presetDataAll[num]);
		PRESET.insert(pair<int, PresetAnswer>(presetDataAll[num][0], tempPreset));
		PRESETID.push_back(presetDataAll[num][0]);
		++num;
	}
	sort(PRESETID.begin(), PRESETID.end());
	return PRESET;
}

vector<vector<int>> ReadfileMap::getData(string fileName)
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

void ReadfileMap::outPut(map<int, Car> &CAR)
{
	ofstream out;
	out.open(answerPath);
	out << "#(carId, StartTime, RoadId[])"<<endl;
	map<int, Car>::iterator it;
	for (it = CAR.begin(); it != CAR.end(); it++)
	{
		int j;
		out << "("<<it->first<< ", " << it->second.ATD << ", ";
		for (j = 0; j < (int)(it->second.route.size())-1; j++)
		{
			out << it->second.route[j] << ", ";
		}
		out << it->second.route[j] << ")" << endl;
	}
	out.close();
}