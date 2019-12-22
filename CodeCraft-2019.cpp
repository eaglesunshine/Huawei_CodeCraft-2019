#include <iostream>
#include <vector>
#include<fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "Car.h"
#include "Cross.h"
#include "Road.h"
#include "presetAnswer.h"
#include "readfile_map.h"
#include "readfile.h"
#include "Floyd.h"
#include "Dispatch.h"
#include "time.h"
#include <ctime>
#define BADTIME 100000
using namespace::std;

int main(int argc, char *argv[])
{
	clock_t startTime, endTime;
	startTime = clock();//��ʱ��ʼ
	srand((unsigned)time(NULL));

	/*if(argc < 6){
		std::cout << "please input args: carPath, roadPath, crossPath, answerPath" << std::endl;
		exit(1);
	}
	
	std::string carPath(argv[1]);
	std::string roadPath(argv[2]);
	std::string crossPath(argv[3]);
	std::string presetAnswerPath(argv[4]);
	std::string answerPath(argv[5]);
	
	std::cout << "carPath is " << carPath << std::endl;
	std::cout << "roadPath is " << roadPath << std::endl;
	std::cout << "crossPath is " << crossPath << std::endl;
	std::cout << "presetAnswerPath is " << presetAnswerPath << std::endl;
	std::cout << "answerPath is " << answerPath << std::endl;*/

	string carPath = "config/car.txt";
	string roadPath = "config/road.txt";
	string crossPath = "config/cross.txt";
	string answerPath = "config/answer.txt";
	string presetAnswerPath = "config/presetAnswer.txt";

	// TODO:read input filebuf
	Readfile myReadfile(carPath, roadPath, crossPath, answerPath, presetAnswerPath);
	vector<Car> CAR= myReadfile.getCar();
	vector<Cross> CROSS = myReadfile.getCross();
	vector<Road> ROAD = myReadfile.getRoad();
	map<int, PresetAnswer> PRESET = myReadfile.getPreset();
	Graph_DG graph((int)(CROSS.size()), ROAD);
	graph.initRoute(CAR, CROSS, ROAD);

	//��24������
	//myReadfile.outPut2();

	// TODO:process
	Dispatch Dispatcher;
	static int GlobalTime = 1;
	int batchNum=20, t=2, limitNum=5000;;
	if (CAR[0].from == 139)
	{
		batchNum = 353;		//353*3(singal)
		t = 3;	
		limitNum = 6800;
	}
	if (CAR[0].from == 146)
	{
		batchNum = 324;		//353*3(singal)
		t = 3;
		limitNum = 7500;	 
	}

	//search batchsize
	//batchNum = Dispatcher.searchBestBatchNum(CAR, CROSS, ROAD, batchNum, limitNum);
	
	//search limitnumber
	//limitNum= Dispatcher.searchBestLimitNum(CAR, CROSS, ROAD, batchNum, limitNum);

	Dispatcher.Batch2(CAR, batchNum, t);
	Dispatcher.setLimitNum(limitNum);
	Dispatcher.givePT(CAR);
	//int bestTime = Dispatcher.dispathMAIN(CAR, CROSS, ROAD, GlobalTime, 0, BADTIME);

	vector<Car> tempCAR; 
	vector<Cross> tempCROSS; 
	vector<Road> tempROAD;
	tempCAR.insert(tempCAR.begin(), CAR.begin(), CAR.end());
	int bestTime = BADTIME;
	int temp_time;
	GlobalTime = 1;
	int TT = 2;
	int loop_num = 0;
	while (loop_num < 50) {
		GlobalTime = 1;
		loop_num++;
		//if (loop_num == 4)
		//	int check = 1;
		temp_time = Dispatcher.dispathMAIN_withDeal3(tempCAR, CROSS, ROAD, GlobalTime, TT, BADTIME, graph, myReadfile.CROSSid);
		//temp_time = Dispatcher.dispathMAIN(tempCAR, CROSS, ROAD, GlobalTime, 1, BADTIME);
		//if(temp_time== BADTIME)
		//	Dispatcher.deadLockProcess1(tempCAR, CROSS, ROAD);
		++TT;
		cout << "**************************************"<<temp_time << endl;
		cout << "dispatch time is " << Dispatcher.computeTE(tempCAR) << endl;
		if (temp_time < bestTime) {
			bestTime = temp_time;
			break;
		}
	}

	//int bestTime = Dispatcher.searchBestTime2(CAR, CROSS, ROAD);

	// TODO:write output file
	//myReadfile.inTranfer(tempCAR);
	//myReadfile.outPut(tempCAR);

	endTime = clock();//��ʱ����
	cout << "the globalTime is " << bestTime << endl;
	cout << "dispatch time is " << Dispatcher.computeTE(tempCAR) << endl;
	cout << "All dispatch time is " << Dispatcher.computeTEsum(tempCAR) << endl;
	cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	//system("pause");
	GlobalTime = 1;
	for (int k = 0; k < int(tempCAR.size()); k++)
	{
		if (tempCAR[k].preset == 0)
		{
			tempCAR[k].PT = tempCAR[k].ATD;
		}
	}
	temp_time = Dispatcher.dispathMAIN(tempCAR, CROSS, ROAD, GlobalTime, 1, BADTIME);
	cout << "the globalTime is " << temp_time << endl;
	cout << "dispatch time is " << Dispatcher.computeTE(tempCAR) << endl;
	cout << "All dispatch time is " << Dispatcher.computeTEsum(tempCAR) << endl;
	//system("pause");
	return 0;
}
