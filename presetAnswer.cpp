#include "presetAnswer.h"

bool PresetAnswer::init(vector<int> carData)
{
	if (carData.size() == 0)
		return false;

	id = carData[0];
	ATD = carData[1];

	for (int i = 2; i < (int)(carData.size()); i++)
	{
		route.push_back(carData[i]);
	}
	return true;
}