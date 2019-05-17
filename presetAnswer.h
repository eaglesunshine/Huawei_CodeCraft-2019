#pragma once
#ifndef __PRESETANSWER_H__
#define __PRESETANSWER_H__

#include <vector>
using namespace std;

class PresetAnswer
{
public:
	int id;
	int ATD;
	vector<int> route;

	bool init(vector<int> carData);
};


#endif 