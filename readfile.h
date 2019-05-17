#pragma once
#ifndef __READFILE_H__
#define __READFILE_H__

#include <vector>
#include "Car.h"
#include "Road.h"
#include "Cross.h"
#include "presetAnswer.h"
#include <string>
#include <algorithm>
#include "readfile_map.h"

using namespace std;

class Readfile
{
public:
	string carPath;
	string roadPath;
	string crossPath;
	string answerPath;
	string presetAnswerPath;

	map<int, Car> CAR_map;
	map<int, Cross> CROSS_map;
	map<int, Road> ROAD_map;
	map<int, PresetAnswer> PRESET_map;

	vector<int> CARid, CROSSid, ROADid, PRESETid;

	vector<Car> CAR;
	vector<Cross> CROSS;
	vector<Road> ROAD;

	vector<Car> getCar();
	vector<Cross> getCross();
	vector<Road> getRoad();
	map<int,PresetAnswer> getPreset();
	vector<vector<int>> getData(string fileName);
	void outPut(vector<Car> &CAR);
	void outPut2();

	void getMapData(string carP, string roadP, string crossP, string answerp,string presetAnswerP);
	void getVectorData();
	void Tranfer();
	void setPreset();
	void inTranfer(vector<Car> &CAR);

	Readfile(string carP, string roadP, string crossP, string answerp,string presetAnswerPath);

	//预备函数
	bool isRouteLegal(Car &car, vector<Cross> &CROSS, vector<Road> &ROAD, vector<int> &ROADID);  //判断路径合法——即是否可到达
};

#endif 


