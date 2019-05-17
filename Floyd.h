/************************************************************/
/*                程序作者：Willam                          */
/*                程序完成时间：2017/3/11                   */
/*                有任何问题请联系：2930526477@qq.com       */
/************************************************************/
//@尽量写出完美的程序

#pragma once
//#pragma once是一个比较常用的C/C++杂注，
//只要在头文件的最开始加入这条杂注，
//就能够保证头文件只被编译一次。

/*
本博客开始对Floyd算法的使用邻接矩阵实现的
*/

#include<iostream>
#include<string>
#include "Road.h"
#include "Car.h"
#include "Cross.h"
using namespace std;

class Graph_DG {
private:
	int vexnum;   //图的顶点个数
	int edge;     //图的边数
	int **arc;   //邻接矩阵
	int ** dis;   //记录各个顶点最短路径的信息
	int ** path;  //记录各个最短路径的信息
	int ** map;   //记录原始地图，即每两个路口之间是哪条路
public:
	//构造函数
	Graph_DG(int vexnum, vector<Road>& ROAD);
	Graph_DG(const Graph_DG &DeadCarGraph);
	//析构函数
	~Graph_DG();
	// 判断我们每次输入的的边的信息是否合法
	//顶点从1开始编号
	//bool check_edge_value(int start, int end, int weight);
	//创建图
	void createGraph(int, vector<Road>& ROAD, int num_road);
	//打印邻接矩阵
	void print();
	//求最短路径
	void Floyd();
	//打印最短路径
	void print_path();
	//设路径
	void set_path(vector<Car>& CAR, vector<Cross>& CROSS, vector<Road> &ROAD, int num_car);
	void set_path_DealLock(Car &CAR, vector<Cross>& CROSS);
	void set_path_Dynamic(vector<Car>& CAR, vector<Cross>& CROSS, vector<Road> &ROAD);
	void set_out_road(vector<Car>& CAR, vector<Cross>& CROSS);
	void set_out_road_DealLock(Car &CAR, vector<Cross>& CROSS);
	void set_path_DealLock_back(Car &CAR, vector<Cross>& CROSS, vector<Road> &ROAD);
	int findDirection(Cross &CROSS, int now_road_id, int next_road_id);

	void initRoute(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD);
	void initRoute_DealLock(Car &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, vector<int> &freeRoads, vector<int> &busyRoads,vector<int> &CROSSID);
	void initRoute_DealLock_back(Car &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, vector<int> &freeRoads, vector<int> &busyRoads, vector<int> &CROSSID);
	void initRoute_DealLock_back2(Car &CAR, vector<Cross> &CROSS, vector<Road> &ROAD);
	void initRoute_DealLock_back3(Car &CAR, vector<Cross> &CROSS, vector<Road> &ROAD, vector<int> &CarDeadRoadId);
	void initRoute_Dynamic(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD);
	vector<int> getLinkCross(Cross &CROSS, vector<Road> &ROAD);
};
