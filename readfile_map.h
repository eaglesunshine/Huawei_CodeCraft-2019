#pragma once
#ifndef __READFILE_MAP_H__
#define __READFILE_MAP_H__

#include <vector>
#include "Car.h"
#include "Road.h"
#include "Cross.h"
#include "presetAnswer.h"
#include <string>
#include <map>

using namespace std;

class ReadfileMap
{
public:
	string carPath;
	string roadPath;
	string crossPath;
	string answerPath;
	string presetAnswerPath;

	vector<int> CARID;
	vector<int> CROSSID;
	vector<int> ROADID;
	vector<int> PRESETID;

	map<int, Car> getCar();
	map<int, Cross> getCross();
	map<int, Road> getRoad();
	map<int, PresetAnswer> getPreset();
	vector<vector<int>> getData(string fileName);
	void outPut(map<int, Car> &CAR);

	ReadfileMap(string carP, string roadP, string crossP, string answerP, string presetAnswerP);
};

#endif 


