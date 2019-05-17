#include"Floyd.h"
#include "readfile.h"
#define MAX_NUM 99999
#define Lower_Bound 0.2
#define Upper_Bound 0.8

//构造函数
Graph_DG::Graph_DG(int vexnum, vector<Road>& ROAD) {


	//初始化顶点数和边数
	this->vexnum = vexnum;
	this->edge = edge;
	//为邻接矩阵开辟空间和赋初值
	arc = new int*[this->vexnum];
	dis = new int*[this->vexnum];
	path = new int*[this->vexnum];
	map = new int*[this->vexnum];
	for (int i = 0; i < this->vexnum; i++) {
		arc[i] = new int[this->vexnum];
		dis[i] = new int[this->vexnum];
		path[i] = new int[this->vexnum];
		map[i] = new int[this->vexnum];
		for (int k = 0; k < this->vexnum; k++) {
			//邻接矩阵初始化	//地图矩阵初始化
			if (i == k) {
				arc[i][k] = 0;
				map[i][k] = 0;
			}
			else {
				arc[i][k] = MAX_NUM;
				map[i][k] = -1;
			}
		}
	}

	//建有向图
	edge = 0;
	for (int i = 0; i < (int)(ROAD.size()); i++)
	{
		if (ROAD[i].isDuplex == 0) {
			edge += 1;
		}
		else {
			edge += 2;
		}
	}
}

//专用于处理死锁车辆的构造函数
Graph_DG::Graph_DG(const Graph_DG &OriginalCarGraph) {
	//初始化顶点数和边数
	this->vexnum = OriginalCarGraph.vexnum;
	this->edge = OriginalCarGraph.edge;
	//为邻接矩阵开辟空间和赋初值
	arc = new int*[this->vexnum];
	dis = new int*[this->vexnum];
	path = new int*[this->vexnum];
	map = new int*[this->vexnum];
	for (int i = 0; i < this->vexnum; i++) {
		arc[i] = new int[this->vexnum];
		dis[i] = new int[this->vexnum];
		path[i] = new int[this->vexnum];
		map[i] = new int[this->vexnum];
		for (int k = 0; k < this->vexnum; k++) {
			//复制原地图的数据
			arc[i][k] = OriginalCarGraph.arc[i][k];
			//dis[i][k] = OriginalCarGraph.dis[i][k];
			//path[i][k] = OriginalCarGraph.path[i][k];
			map[i][k] = OriginalCarGraph.map[i][k];
		}
	}
}

//析构函数
Graph_DG::~Graph_DG() {

	for (int i = 0; i < this->vexnum; i++) {
		delete this->arc[i];
		delete this->dis[i];
		delete this->path[i];
		delete this->map[i];

	}
	delete dis;
	delete arc;
	delete path;
	delete map;
}

void Graph_DG::createGraph(int kind, vector<Road>& ROAD, int num_road) {
	//cout << "请输入每条边的起点和终点（顶点编号从1开始）以及其权重" << endl;
	int start;
	int end;
	int weight;
	int count = 0;
	//cout << ROAD.size << endl;
	int maxRoadSpeed = 0;
	for (int i = 0; i < (int)(ROAD.size()); i++)
	{
		if (maxRoadSpeed < ROAD[i].speed)
			maxRoadSpeed = ROAD[i].speed;
	}

	while (count < num_road) {
		//cin >> start >> end >> weight;
		start = ROAD[count].from;
		end = ROAD[count].to;
		weight = (ROAD[count].length / ROAD[count].channel) + maxRoadSpeed - ROAD[count].speed;
		//weight =ROAD[count].length - ROAD[count].channel;

		//首先判断边的信息是否合法，后期可删除以节省时间
		//while (!this->check_edge_value(start, end, weight)) {
		//	cout << "输入的边的信息不合法，请重新输入" << endl;
		//	//exit(1);
		//	//cin >> start >> end >> weight;
		//}

		//对邻接矩阵对应上的点赋值
		arc[start][end] = weight;
		map[start ][end] = ROAD[count].id;
		//无向图添加上这行代码
		//if (kind == 2)
		//	arc[end - 1][start - 1] = weight;

		//双行道
		if (ROAD[count].isDuplex == 1) {
			arc[end][start] = weight;
			map[end][start] = ROAD[count].id;
		}
		++count;
	}
}

//后期删除，用不到的
void Graph_DG::print() {
	cout << "图的邻接矩阵为：" << endl;
	int count_row = 0; //打印行的标签
	int count_col = 0; //打印列的标签
					   //开始打印
	while (count_row != this->vexnum) {
		count_col = 0;
		while (count_col != this->vexnum) {
			if (arc[count_row][count_col] == MAX_NUM)
				cout << "∞" << " ";
			else
				cout << arc[count_row][count_col] << " ";
			++count_col;
		}
		cout << endl;
		++count_row;
	}
}

//算法的核心
void Graph_DG::Floyd() {
	int row = 0;
	int col = 0;
	for (row = 0; row < this->vexnum; row++) {
		for (col = 0; col < this->vexnum; col++) {
			//把矩阵D初始化为邻接矩阵的值
			this->dis[row][col] = this->arc[row][col];
			//矩阵P的初值则为各个边的终点顶点的下标
			this->path[row][col] = col;
		}
	}

	//三重循环，用于计算每个点对的最短路径
	int temp = 0;
	int select = 0;
	for (temp = 0; temp < this->vexnum; temp++) {
		for (row = 0; row < this->vexnum; row++) {
			for (col = 0; col < this->vexnum; col++) {
				//为了防止溢出，所以需要引入一个select值
				select = (dis[row][temp] == MAX_NUM || dis[temp][col] == MAX_NUM) ? MAX_NUM : (dis[row][temp] + dis[temp][col]);
				if (this->dis[row][col] > select) {
					//更新我们的D矩阵
					this->dis[row][col] = select;
					//更新我们的P矩阵
					this->path[row][col] = this->path[row][temp];
				}
			}
		}
	}
}

//后期删除，用不到的
void Graph_DG::print_path() {
	cout << "各个顶点对的最短路径：" << endl;
	int row = 0;
	int col = 0;
	int temp = 0;
	for (row = 0; row < this->vexnum; row++) {
		for (col = 0; col < this->vexnum; col++) {
			cout << "v" << to_string(row + 1) << "---" << "v" << to_string(col + 1) << " weight: "
				<< this->dis[row][col] << " path: " << " v" << to_string(row + 1);
			temp = path[row][col];
			//循环输出途径的每条路径。
			while (temp != col) {
				cout << "-->" << "v" << to_string(temp + 1);
				temp = path[temp][col];
			}
			cout << "-->" << "v" << to_string(col + 1) << endl;
		}
		cout << endl;
	}

	//cout << "DIS矩阵为：" << endl;
	//int count_row = 0; //打印行的标签
	//int count_col = 0; //打印列的标签
	//				   //开始打印
	//while (count_row != this->vexnum) {
	//	count_col = 0;
	//	while (count_col != this->vexnum) {
	//		if (dis[count_row][count_col] == INT_MAX)
	//			cout << "∞" << " ";
	//		else
	//			cout << dis[count_row][count_col] << " ";
	//		++count_col;
	//	}
	//	cout << endl;
	//	++count_row;
	//}
}

//将Floyd算出的路径存入
void Graph_DG::set_path(vector<Car>& CAR, vector<Cross>& CROSS, vector<Road> &ROAD, int num_car) {
	int row = 0;
	int col = 0;
	int temp = 0;
	int temp_road_id = 0;
	int temp_next = 0;
	int road_id[4] = { -1,-1,-1,-1 };
	int k, now_road_direction, next_road_direction, err;
	//int road1_id, road2_id, road3_id, road4_id;
	int last_position=0, next_position;
	int last_road_id, next_road_id;

	for (int i = 0; i < num_car; i++) {
		//if (i == 61442)
		//	int HHH = 1;
		if (CAR[i].preset == 1) {//如果是预置车辆
			//CAR[i].direction.clear();//不需要，因为全程下来，预置车辆只会设置一次direction			
			
			for (int j = 0; j < (int)(CAR[i].route.size()); ++j) {
				//last_position = 0;
				if (j == 0) {//第一个转向，肯定是直行
					CAR[i].direction.push_back(0);
					last_position = CAR[i].from;
					temp_road_id = CAR[i].route[j];
					if (ROAD[temp_road_id].from == last_position) {
						next_position = ROAD[temp_road_id].to;
					}
					else if (ROAD[temp_road_id].to == last_position) {
						next_position = ROAD[temp_road_id].from;
					}
					last_position = next_position;//注意
					continue;
				}
				last_road_id = CAR[i].route[j - 1];
				next_road_id = CAR[i].route[j];//j从1开始才会进入这里，也就是第二条路径开始才考虑转向
				if (ROAD[next_road_id].from == last_position) {
					next_position = ROAD[next_road_id].to;
				}
				if (ROAD[next_road_id].to == last_position) {
					next_position = ROAD[next_road_id].from;
				}
				//这里开始考虑第二个起的转向
				road_id[0] = CROSS[last_position].road1;
				road_id[1] = CROSS[last_position].road2;
				road_id[2] = CROSS[last_position].road3;
				road_id[3] = CROSS[last_position].road4;

				//设置转向
				for (k = 0; k < 4; k++) {
					if (last_road_id == road_id[k]) {
						now_road_direction = k;
						break;
					}
				}
				if (k == 4) {
					cout << "出错啦，这个路口找不到目前所在的路！一般不会出现" << endl;
					//system("pause");
					exit(1);
				}

				for (k = 0; k < 4; k++) {
					if (next_road_id == road_id[k]) {
						next_road_direction = k;
						break;
					}
				}
				if (k == 4) {
					cout << "出错啦，这个路口找不到下一条路！一般不会出现" << endl;
					//system("pause");
					exit(1);
				}
				err = next_road_direction - now_road_direction;
				//设置转向信息，如果顺时针1，就是左转；如果逆时针-1，就是右转；如果相差2就是直行
				switch (err)
				{
				case 1:		//左转
					CAR[i].direction.push_back(1);
					break;
				case -3:	//左转
					CAR[i].direction.push_back(1);
					break;
				case -1:	//右转
					CAR[i].direction.push_back(2);
					break;
				case 3:		//右转
					CAR[i].direction.push_back(2);
					break;
				case 2:		//直行
					CAR[i].direction.push_back(0);
					break;
				case -2:	//直行
					CAR[i].direction.push_back(0);
					break;
				default:
					cout << "出现了掉头，不允许！" << endl;
					exit(1);
					//system("pause");
					break;
				}
				last_position = next_position;
			}
		}
		else {
			CAR[i].route.clear();
			row = CAR[i].from;
			col = CAR[i].to;
			temp = path[row][col];
			temp_road_id = map[row][temp];
			CAR[i].route.push_back(temp_road_id);
			CAR[i].direction.push_back(0);

			while (temp != col) {
				road_id[0] = CROSS[temp].road1;
				road_id[1] = CROSS[temp].road2;
				road_id[2] = CROSS[temp].road3;
				road_id[3] = CROSS[temp].road4;

				for (k = 0; k < 4; k++) {
					if (temp_road_id == road_id[k]) {
						now_road_direction = k;
						break;
					}
				}
				if (k == 4) {
					cout << "出错啦，这个路口找不到目前所在的路！一般不会出现" << endl;
					//system("pause");
					exit(1);
				}

				//设置路径
				temp_next = path[temp][col];
				temp_road_id = map[temp][temp_next];
				CAR[i].route.push_back(temp_road_id);
				temp = temp_next;

				//设置转向
				for (k = 0; k < 4; k++) {
					if (temp_road_id == road_id[k]) {
						next_road_direction = k;
						break;
					}
				}
				if (k == 4) {
					cout << "出错啦，这个路口找不到下一条路！一般不会出现" << endl;
					//system("pause");
					exit(1);
				}
				err = next_road_direction - now_road_direction;



				//设置转向信息，如果顺时针1，就是左转；如果逆时针-1，就是右转；如果相差2就是直行
				switch (err)
				{
				case 1:		//左转
					CAR[i].direction.push_back(1);
					break;
				case -3:	//左转
					CAR[i].direction.push_back(1);
					break;
				case -1:	//右转
					CAR[i].direction.push_back(2);
					break;
				case 3:		//右转
					CAR[i].direction.push_back(2);
					break;
				case 2:		//直行
					CAR[i].direction.push_back(0);
					break;
				case -2:	//直行
					CAR[i].direction.push_back(0);
					break;
				default:
					cout << "出现了掉头，不允许！" << endl;
					exit(1);
					//system("pause");
					break;
				}
			}
		}
	}
}

//带死锁处理的setPath
//这里要注意，如果是预置车辆，不能这么处理！！！！！！以后再写！！！！！！！！！
void Graph_DG::set_path_DealLock(Car &CAR, vector<Cross>& CROSS) {
	int row = 0;
	int col = 0;
	int temp = 0;
	int temp_road_id = 0;
	int temp_next = 0;
	int road_id[4] = { -1,-1,-1,-1 };
	int k, now_road_direction, next_road_direction, err;
	//int road1_id, road2_id, road3_id, road4_id;

	//for (int i = 0; i < num_car; i++) {
	if (CAR.preset != 1) {
		CAR.route.clear();
		CAR.direction.clear();
		row = CAR.from;
		col = CAR.to;
		temp = path[row][col];
		temp_road_id = map[row][temp];
		CAR.route.push_back(temp_road_id);
		CAR.direction.push_back(0);

		while (temp != col) {
			road_id[0] = CROSS[temp].road1;
			road_id[1] = CROSS[temp].road2;
			road_id[2] = CROSS[temp].road3;
			road_id[3] = CROSS[temp].road4;

			for (k = 0; k < 4; k++) {
				if (temp_road_id == road_id[k]) {
					now_road_direction = k;
					break;
				}
			}
			if (k == 4) {
				cout << "出错啦，这个路口找不到目前所在的路！一般不会出现" << endl;
				//system("pause");
				exit(1);
			}

			//设置路径
			temp_next = path[temp][col];
			temp_road_id = map[temp][temp_next];
			CAR.route.push_back(temp_road_id);
			temp = temp_next;

			//设置转向
			for (k = 0; k < 4; k++) {
				if (temp_road_id == road_id[k]) {
					next_road_direction = k;
					break;
				}
			}
			if (k == 4) {
				cout << "出错啦，这个路口找不到下一条路！一般不会出现" << endl;
				//system("pause");
				exit(1);
			}
			err = next_road_direction - now_road_direction;



			//设置转向信息，如果顺时针1，就是左转；如果逆时针-1，就是右转；如果相差2就是直行
			switch (err)
			{
			case 1:		//左转
				CAR.direction.push_back(1);
				break;
			case -3:	//左转
				CAR.direction.push_back(1);
				break;
			case -1:	//右转
				CAR.direction.push_back(2);
				break;
			case 3:		//右转
				CAR.direction.push_back(2);
				break;
			case 2:		//直行
				CAR.direction.push_back(0);
				break;
			case -2:	//直行
				CAR.direction.push_back(0);
				break;
			default:
				cout << "出现了掉头，不允许！" << endl;
				exit(1);
				//system("pause");
				break;
			}

		}
	}
}

void Graph_DG::set_path_DealLock_back(Car &CAR, vector<Cross>& CROSS, vector<Road> &ROAD) {
	int row = 0;
	int col = 0;
	int temp = 0;
	int temp_road_id = 0;
	int temp_next = 0;
	int road_id[4] = { -1,-1,-1,-1 };
	int dir_now_road_id, dir_next_road_id, temp_direction, dir_temp;
	int now_road_id;

	int pass_cross_id=0;//继续走过的路口，不要掉头
	vector<int> link_cross;
	//bool back_flag[4] = { false,false,false,false };//这个变量好像也没啥用，等下删了
	int road_weight[4] = { MAX_NUM ,MAX_NUM ,MAX_NUM ,MAX_NUM };
	int min_road_weight = MAX_NUM;
	int min_link_cross = -1;
	int next_road = -1;
	int temp_num = 0;
	int first_temp_road_id = 0;
	bool flag5 = true;
	/*bool IS = false;*/

		now_road_id = CAR.location[0];
		//vector<int>::iterator iter = find(CAR[i].route.begin(), CAR[i].route.end(), now_road_id); //查找3
		if (CAR.route[CAR.passRoadNumber] != now_road_id) {
			cout << "该车路径里没找到目前这条路，一般不会出现，出现了说明程序没写对" << endl;
			//system("pause");
			exit(1);
		}
		//if (iter == CAR[i].route.end()) {
		//	cout << "没找到，一般不会出现，出现了说明程序没写对" << endl;
		//	system("pause");
		//	exit(1);
		//}
		//if ((iter + 1) == CAR[i].route.end()) {//目前这条路是该车的最后一段路，也不要凑热闹了
		//	continue;
		//}


		/************这里开始是计算是否回头，是否要换路****************/
		min_link_cross = -1;
		if (CAR.isReverse == 0) {
			CAR.nextCross = ROAD[now_road_id].to;
			pass_cross_id = ROAD[now_road_id].from;//刚刚已经走过的路口
		}
		if (CAR.isReverse == 1) {
			CAR.nextCross = ROAD[now_road_id].from;
			pass_cross_id = ROAD[now_road_id].to;//刚刚已经走过的路口
		}
		link_cross = getLinkCross(CROSS[CAR.nextCross], ROAD);
		//是否回头的标志置位
		min_road_weight = MAX_NUM;
		for (int j = 0; j < 4; j++) {
			//back_flag[j] = false;
			road_weight[j] = MAX_NUM;
			if (link_cross[j] == -1 || link_cross[j] == pass_cross_id) {
				//back_flag[j] = true;
				continue;
			}
			if (path[link_cross[j]][CAR.to] == CAR.nextCross) {
				//back_flag[j] = true;
				continue;
			}
			road_weight[j] = arc[CAR.nextCross][link_cross[j]] + dis[link_cross[j]][CAR.to];//这一小段+后面的路

			//识别出代价最低的路：
			if (road_weight[j] < min_road_weight) {
				min_road_weight = road_weight[j];
				min_link_cross = link_cross[j];//这个min_link_cross要么= -1,要么就肯定是可以走，而且是要走的
			}
		}

		//如果得出的下个结点本来就是所规划的路径，那就不要修改任何路径信息了，换下一辆车
		next_road = -1;
		next_road = CAR.route[CAR.passRoadNumber + 1];
		flag5 = true;
		if (min_link_cross == -1 || min_link_cross == ROAD[next_road].from || min_link_cross == ROAD[next_road].to) {
			flag5 = false;//找到的所有路都权重太高，或者本来就是这条路，换下一辆车
		}
		/************这里结束是计算是否回头，是否要换路****************/

		if (flag5 == true) {
			//至此，得出了下一步要走的结点是min_link_cross，存的是CROSS的直接用的下标，确定要换路了
		//for (iter += 1; iter != CAR[i].route.end(); ) {//删除还没走的rounte
		//	iter = CAR[i].route.erase(iter);
		//}
			CAR.route.erase(CAR.route.begin() + CAR.passRoadNumber + 1, CAR.route.end());

			//删对应的direction
			/*for (iter = CAR[i].direction.begin() + (int)CAR[i].route.size(); iter != CAR[i].direction.end();) {
				iter = CAR[i].direction.erase(iter);
			}*/
			CAR.direction.erase(CAR.direction.begin() + CAR.passRoadNumber + 1, CAR.direction.end());

			//继续规划剩下的路了,这里还没写完！！！！！！！！！
			//插目前这一段路，不要用Floyd的图了，直接插，防止又开始绕
			//row = CAR[i].nextCross;
			//col = min_link_cross;
			road_id[0] = CROSS[CAR.nextCross].road1;
			road_id[1] = CROSS[CAR.nextCross].road2;
			road_id[2] = CROSS[CAR.nextCross].road3;
			road_id[3] = CROSS[CAR.nextCross].road4;
			for (temp_num = 0; temp_num < 4; temp_num++) {
				if (road_id[temp_num] == -1) {
					continue;
				}
				if (ROAD[road_id[temp_num]].from == min_link_cross || ROAD[road_id[temp_num]].to == min_link_cross) {
					temp_road_id = ROAD[road_id[temp_num]].id;
					CAR.route.push_back(temp_road_id);
					break;
				}
			}
			if (temp_num == 4) {
				cout << "出错啦，找不到要走的这一段小路！一般不会出现" << endl;
				//system("pause");
				exit(1);
			}

			temp_direction = this->findDirection(CROSS[CAR.nextCross], CAR.location[0], temp_road_id);
			CAR.direction.push_back(temp_direction);
			first_temp_road_id = temp_road_id;

			//插剩下的路
			row = min_link_cross;
			col = CAR.to;
			if (row != col) {
				temp = path[row][col];
				temp_road_id = map[row][temp];
				CAR.route.push_back(temp_road_id);
				temp_direction = this->findDirection(CROSS[min_link_cross], first_temp_road_id, temp_road_id);
				CAR.direction.push_back(temp_direction);

				while (temp != col) {
					dir_temp = temp;

					//设置转向
					dir_now_road_id = temp_road_id;

					//设置路径
					temp_next = path[temp][col];
					temp_road_id = map[temp][temp_next];
					CAR.route.push_back(temp_road_id);
					temp = temp_next;

					//设置转向
					dir_next_road_id = temp_road_id;
					temp_direction = this->findDirection(CROSS[dir_temp], dir_now_road_id, dir_next_road_id);
					CAR.direction.push_back(temp_direction);
				}
			}
			/*IS = true;*/
			
		}
		//if(IS==true)
		//	cout << "car route is modified!! "<< endl;
}

void Graph_DG::set_path_Dynamic(vector<Car>& CAR, vector<Cross>& CROSS, vector<Road> &ROAD) {
	int row = 0;
	int col = 0;
	int temp = 0;
	int temp_road_id = 0;
	int temp_next = 0;
	int road_id[4] = { -1,-1,-1,-1 };
	int dir_now_road_id, dir_next_road_id, temp_direction, dir_temp;
	int now_road_id;

	int pass_cross_id;//继续走过的路口，不要掉头
	vector<int> link_cross;
	//bool back_flag[4] = { false,false,false,false };//这个变量好像也没啥用，等下删了
	int road_weight[4] = { MAX_NUM ,MAX_NUM ,MAX_NUM ,MAX_NUM };
	int min_road_weight = MAX_NUM;
	int min_link_cross = -1;
	int next_road = -1;
	int temp_num = 0;
	int first_temp_road_id = 0;
	//bool is = false;
	for (int i = 0; i < (int)CAR.size(); i++) {

		if (CAR[i].usedToBeDeadCar == true) {//曾经是死锁车辆，不要参与实时规划
			continue;
		}
		if (CAR[i].preset == 1) {//预置车辆也不要参与实时规划
			continue;
		}
		if (CAR[i].ATD == -1) {//没出发的车就不要凑热闹了
			continue;
		}
		if (CAR[i].isTerminate == 1) {//到达终点的车也不要参与
			continue;
		}
		if (CAR[i].nextCrossDistance < CAR[i].maxSpeed) {//只改那些当前时刻不过路口的车
			continue;
		}
		if (CAR[i].passRoadNumber == (int)(CAR[i].route.size()) - 1) {//目前这条路是该车的最后一段路，也不要凑热闹了
			continue;
		}
		else if (CAR[i].passRoadNumber == (int)(CAR[i].route.size()) - 2) {//该车的下一条路是要到终点，也不要凑热闹了
			continue;
		}
		else if (CAR[i].passRoadNumber == (int)(CAR[i].route.size()) - 3) {//该车的下下一条路是要到终点，也不要凑热闹了
			continue;
		}

		now_road_id = CAR[i].location[0];
		//vector<int>::iterator iter = find(CAR[i].route.begin(), CAR[i].route.end(), now_road_id); //查找3
		if (CAR[i].route[CAR[i].passRoadNumber] != now_road_id) {
			cout << "该车路径里没找到目前这条路，一般不会出现，出现了说明程序没写对" << endl;
			//system("pause");
			exit(1);
		}
		//if (iter == CAR[i].route.end()) {
		//	cout << "没找到，一般不会出现，出现了说明程序没写对" << endl;
		//	system("pause");
		//	exit(1);
		//}
		//if ((iter + 1) == CAR[i].route.end()) {//目前这条路是该车的最后一段路，也不要凑热闹了
		//	continue;
		//}


		/************这里开始是计算是否回头，是否要换路****************/
		pass_cross_id = 0;
		min_link_cross = -1;
		if (CAR[i].isReverse == 0) {
			CAR[i].nextCross = ROAD[now_road_id].to;
			pass_cross_id = ROAD[now_road_id].from;//刚刚已经走过的路口
		}
		if (CAR[i].isReverse == 1) {
			CAR[i].nextCross = ROAD[now_road_id].from;
			pass_cross_id = ROAD[now_road_id].to;//刚刚已经走过的路口
		}
		link_cross = getLinkCross(CROSS[CAR[i].nextCross], ROAD);
		//是否回头的标志置位
		min_road_weight = MAX_NUM;
		for (int j = 0; j < 4; j++) {
			//back_flag[j] = false;
			road_weight[j] = MAX_NUM;
			if (link_cross[j] == -1 || link_cross[j] == pass_cross_id) {
				//back_flag[j] = true;
				continue;
			}
			if (path[link_cross[j]][CAR[i].to] == CAR[i].nextCross) {
				//back_flag[j] = true;
				continue;
			}
			road_weight[j] = arc[CAR[i].nextCross][link_cross[j]] + dis[link_cross[j]][CAR[i].to];//这一小段+后面的路

			//识别出代价最低的路：
			if (road_weight[j] < min_road_weight) {
				min_road_weight = road_weight[j];
				min_link_cross = link_cross[j];//这个min_link_cross要么= -1,要么就肯定是可以走，而且是要走的
			}
		}

		//如果得出的下个结点本来就是所规划的路径，那就不要修改任何路径信息了，换下一辆车
		next_road = -1;
		next_road = CAR[i].route[CAR[i].passRoadNumber + 1];
		if (min_link_cross == -1 || min_link_cross == ROAD[next_road].from || min_link_cross == ROAD[next_road].to) {
			continue;//找到的所有路都权重太高，或者本来就是这条路，换下一辆车
		}
		/************这里结束是计算是否回头，是否要换路****************/


		//至此，得出了下一步要走的结点是min_link_cross，存的是CROSS的直接用的下标，确定要换路了
		//for (iter += 1; iter != CAR[i].route.end(); ) {//删除还没走的rounte
		//	iter = CAR[i].route.erase(iter);
		//}
		CAR[i].route.erase(CAR[i].route.begin() + CAR[i].passRoadNumber + 1, CAR[i].route.end());

		//删对应的direction
		/*for (iter = CAR[i].direction.begin() + (int)CAR[i].route.size(); iter != CAR[i].direction.end();) {
			iter = CAR[i].direction.erase(iter);
		}*/
		CAR[i].direction.erase(CAR[i].direction.begin() + CAR[i].passRoadNumber + 1, CAR[i].direction.end());

		//继续规划剩下的路了,这里还没写完！！！！！！！！！
		//插目前这一段路，不要用Floyd的图了，直接插，防止又开始绕
		//row = CAR[i].nextCross;
		//col = min_link_cross;
		road_id[0] = CROSS[CAR[i].nextCross].road1;
		road_id[1] = CROSS[CAR[i].nextCross].road2;
		road_id[2] = CROSS[CAR[i].nextCross].road3;
		road_id[3] = CROSS[CAR[i].nextCross].road4;
		for (temp_num = 0; temp_num < 4; temp_num++) {
			if (road_id[temp_num] == -1) {
				continue;
			}
			if (ROAD[road_id[temp_num]].from == min_link_cross || ROAD[road_id[temp_num]].to == min_link_cross) {
				temp_road_id = ROAD[road_id[temp_num]].id;
				CAR[i].route.push_back(temp_road_id);
				break;
			}
		}
		if (temp_num == 4) {
			cout << "出错啦，找不到要走的这一段小路！一般不会出现" << endl;
			//system("pause");
			exit(1);
		}

		temp_direction = this->findDirection(CROSS[CAR[i].nextCross], CAR[i].location[0], temp_road_id);
		CAR[i].direction.push_back(temp_direction);
		first_temp_road_id = temp_road_id;

		//插剩下的路
		row = min_link_cross;
		col = CAR[i].to;
		if (row == col) {//已经到了啊，而且已经插完最后一条路了，下面不需要继续了，换下一辆车
			//cout << "一般不会出现123123123" << endl;
			//system("pause");
			//exit(1);
			continue;
		}
		temp = path[row][col];
		temp_road_id = map[row][temp];
		CAR[i].route.push_back(temp_road_id);
		temp_direction = this->findDirection(CROSS[min_link_cross], first_temp_road_id, temp_road_id);
		CAR[i].direction.push_back(temp_direction);

		while (temp != col) {
			dir_temp = temp;

			//设置转向
			dir_now_road_id = temp_road_id;

			//设置路径
			temp_next = path[temp][col];
			temp_road_id = map[temp][temp_next];
			CAR[i].route.push_back(temp_road_id);
			temp = temp_next;

			//设置转向
			dir_next_road_id = temp_road_id;
			temp_direction = this->findDirection(CROSS[dir_temp], dir_now_road_id, dir_next_road_id);
			CAR[i].direction.push_back(temp_direction);
		}

		//is = true;
	}
	//if (is == true)
	//	cout << "haha" << endl;
}

int Graph_DG::findDirection(Cross &CROSS, int now_road_id, int next_road_id) {
	int road_id[4] = { -1,-1,-1,-1 };
	road_id[0] = CROSS.road1;
	road_id[1] = CROSS.road2;
	road_id[2] = CROSS.road3;
	road_id[3] = CROSS.road4;
	int k, now_road_direction, next_road_direction, err;

	for (k = 0; k < 4; k++) {
		if (now_road_id == road_id[k]) {
			now_road_direction = k;
			break;
		}
	}
	if (k == 4) {
		cout << "出错啦，这个路口找不到目前所在的路！一般不会出现" << endl;
		//system("pause");
		exit(1);
	}
	for (k = 0; k < 4; k++) {
		if (next_road_id == road_id[k]) {
			next_road_direction = k;
			break;
		}
	}
	if (k == 4) {
		cout << "出错啦，这个路口找不到下一条路！一般不会出现" << endl;
		//system("pause");
		exit(1);
	}
	err = next_road_direction - now_road_direction;

	//设置转向信息，如果顺时针1，就是左转；如果逆时针-1，就是右转；如果相差2就是直行
	switch (err)
	{
	case 1:		//左转
		return(1);
		break;
	case -3:	//左转
		return(1);
		break;
	case -1:	//右转
		return(2);
		break;
	case 3:		//右转
		return(2);
		break;
	case 2:		//直行
		return(0);
		break;
	case -2:	//直行
		return(0);
		break;
	default:
		cout << "出现了掉头的现象，不允许出现！" << endl;
		//system("pause");
		break;
	}
	return 0;
}

vector<int> Graph_DG::getLinkCross(Cross &CROSS, vector<Road> &ROAD) {
	int road_id[4] = { -1,-1,-1,-1 };
	vector<int> link_cross;
	road_id[0] = CROSS.road1;
	road_id[1] = CROSS.road2;
	road_id[2] = CROSS.road3;
	road_id[3] = CROSS.road4;
	for (int j = 0; j < 4; j++) {
		if (road_id[j] == -1) {
			link_cross.push_back(-1);
			continue;
		}
		if (ROAD[road_id[j]].from == CROSS.id) {
			link_cross.push_back(ROAD[road_id[j]].to);
		}
		else if (ROAD[road_id[j]].to == CROSS.id && ROAD[road_id[j]].isDuplex == 1) {
			link_cross.push_back(ROAD[road_id[j]].from);
		}
		else {//有连接的，但是是单向道，走不过去的，所以还是-1
			link_cross.push_back(-1);
		}
	}
	return link_cross;
}


void Graph_DG::set_out_road(vector<Car>& CAR, vector<Cross>& CROSS) {
	int road_id[4] = { -1,-1,-1,-1 };
	int last_roadId;
	int nextRoadPosition = -1;
	for (int i = 0; i < (int)(CAR.size()); i++) {
		road_id[0] = CROSS[CAR[i].to ].road1;
		road_id[1] = CROSS[CAR[i].to ].road2;
		road_id[2] = CROSS[CAR[i].to ].road3;
		road_id[3] = CROSS[CAR[i].to ].road4;
		last_roadId = CAR[i].route[(int)(CAR[i].route.size()) - 1];
		for (int j = 0; j < 4; j++) {
			if (road_id[j] == last_roadId) {//j=0123
				nextRoadPosition = (j + 2) % 4;
				break;
			}
		}
		//CAR[i].route.push_back(road_id[nextRoadPosition]);
		CAR[i].LastRoad = road_id[nextRoadPosition];
		//CAR[i].direction.push_back(0);
	}
}

//带死锁处理时，只更新对应的车，不需要全部更新
void Graph_DG::set_out_road_DealLock(Car &CAR, vector<Cross>& CROSS) {
	int road_id[4] = { -1,-1,-1,-1 };
	int last_roadId;
	int nextRoadPosition = -1;
	//for (int i = 0; i < (int)(CAR.size()); i++) {
	road_id[0] = CROSS[CAR.to].road1;
	road_id[1] = CROSS[CAR.to ].road2;
	road_id[2] = CROSS[CAR.to ].road3;
	road_id[3] = CROSS[CAR.to ].road4;
	last_roadId = CAR.route[(int)(CAR.route.size()) - 1];
	for (int j = 0; j < 4; j++) {
		if (road_id[j] == last_roadId) {//j=0123
			nextRoadPosition = (j + 2) % 4;
			break;
		}
	}
	//CAR[i].route.push_back(road_id[nextRoadPosition]);
	CAR.LastRoad = road_id[nextRoadPosition];
	//CAR[i].direction.push_back(0);
//}
}

void Graph_DG::initRoute(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD)
{
	//Graph_DG graph(CROSS.size(), edge);//未考虑车道数，后期要加上，另外，会不会两个路口之间有两条路的特殊情况？
	this->createGraph(1, ROAD, (int)(ROAD.size()));//1代表有向图，2代表无向图
	this->Floyd();
	this->set_path(CAR, CROSS, ROAD, (int)(CAR.size()));
	this->set_out_road(CAR, CROSS);
}


void Graph_DG::initRoute_DealLock(Car &DeadCar, vector<Cross> &CROSS, vector<Road> &ROAD, vector<int> &freeRoads, vector<int> &busyRoads, vector<int> &CROSSID)
{
	int err_road_id, temp_from, temp_to;
	int change_flag;
	vector<int>::iterator it;
	if (DeadCar.nextRoad != -1) {	//考虑下一条路是不会走的情况（即过了终点之后的路）

		//动态规划时用到，如果是死锁车辆，则不要参与实时调度，这个版本没用到
		DeadCar.usedToBeDeadCar = true;

		err_road_id = DeadCar.location[0] - ROAD[0].id;//所在路的id
		temp_from = ROAD[err_road_id].from+1;
		temp_to = ROAD[err_road_id].to+1;

		change_flag = 0;
		for (int k = 0; k < (int)(freeRoads.size()); k++) {
			if (DeadCar.location[0] == freeRoads[k]) {//死锁车目前所在的路也是车流量少的路！
				//cout << "目前死锁的路也是车流量少的路！" << endl;
				//system("pause");
				if (DeadCar.PT -= err_road_id + 2 * DeadCar.location[2] > DeadCar.planTime) {
					DeadCar.PT -= err_road_id + 2 * DeadCar.location[2];
					change_flag = 1;
				}
				else {
					DeadCar.PT += err_road_id + 2 * DeadCar.location[2];
					change_flag = 1;
				}

				break;
			}
		}

		if (change_flag == 0) {//死锁车目前所在的路不是车流量少的路，删了这条路
			if (ROAD[err_road_id].to == DeadCar.nextCross) {
				arc[temp_from - 1][temp_to - 1] = 999;
				//map[temp_from - 1][temp_to - 1] = -1;
			}
			else if (ROAD[err_road_id].from == DeadCar.nextCross) {
				arc[temp_to - 1][temp_from - 1] = 999;
				//map[temp_to - 1][temp_from - 1] = -1;
			}

			//顺便把其他车流量少的路降低权重
			//cout << "车流量少的道路：" << endl;
			for (int i = 0; i < (int)(freeRoads.size()); i++) {
				err_road_id = freeRoads[i] - ROAD[0].id;

				temp_from = ROAD[err_road_id].from+1;
				//it = find(CROSSID.begin(), CROSSID.end(), temp_from);
				//temp_from = &*(it)-&CROSSID[0] + 1;

				temp_to = ROAD[err_road_id].to+1;
				//it = find(CROSSID.begin(), CROSSID.end(), temp_to);
				//temp_to = &*(it)-&CROSSID[0] + 1;

				arc[temp_from - 1][temp_to - 1] = 5;
				if (ROAD[err_road_id].isDuplex == 1) {
					arc[temp_to - 1][temp_from - 1] = 5;
				}
			}
			//顺便把其他车流量多的路设高权重
			//cout << "车流量高的道路：" << endl;
			for (int i = 0; i < (int)(busyRoads.size()); i++) {
				err_road_id = busyRoads[i] - ROAD[0].id;
				temp_from = ROAD[err_road_id].from+1;
				temp_to = ROAD[err_road_id].to+1;
				arc[temp_from - 1][temp_to - 1] = 100;
				if (ROAD[err_road_id].isDuplex == 1) {
					arc[temp_to - 1][temp_from - 1] = 100;
				}
			}

		}
		this->Floyd();
		this->set_path_DealLock(DeadCar, CROSS);
		this->set_out_road_DealLock(DeadCar, CROSS);
	}
}

void Graph_DG::initRoute_DealLock_back(Car &DeadCar, vector<Cross> &CROSS, vector<Road> &ROAD, vector<int> &freeRoads, vector<int> &busyRoads, vector<int> &CROSSID)
{
	int err_road_id, temp_from, temp_to;
	//回滚时，死锁车辆也不要参与实时调度了，怕又走回去了
	DeadCar.usedToBeDeadCar = true;

	err_road_id = DeadCar.nextRoad - ROAD[0].id;//下一条路的id
	temp_from = ROAD[err_road_id].from + 1;
	temp_to = ROAD[err_road_id].to + 1;

	if (ROAD[err_road_id].to == DeadCar.nextCross) {
		arc[temp_to - 1][temp_from - 1] = 999;
		//map[temp_from - 1][temp_to - 1] = -1;
	}
	else if (ROAD[err_road_id].from == DeadCar.nextCross) {
		arc[temp_from - 1][temp_to - 1] = 999;
		//map[temp_to - 1][temp_from - 1] = -1;
	}

	//对不同拥挤度的路做不同的权重加减，这里的权重参数需要进一步验证合理性
	for (int i = 0; i < (int)(ROAD.size()); i++) {
		temp_from = ROAD[i].from + 1;
		temp_to = ROAD[i].to + 1;
		for (int m = 0; m < ROAD[i].isDuplex + 1; m++) {
			if (m == 0) {//正向
				if (ROAD[i].crowding[m] < Lower_Bound) {
					if (arc[temp_from - 1][temp_to - 1] > 10) {
						arc[temp_from - 1][temp_to - 1] -= 10;
					}
					//else if (arc[temp_from - 1][temp_to - 1] > 10) {
					//	arc[temp_from - 1][temp_to - 1] -= 10;
					//}
				}
				else if (ROAD[i].crowding[m] > Upper_Bound) {
					arc[temp_from - 1][temp_to - 1] += 50;
				}
			}
			else if (m == 1) {//反向
				if (ROAD[i].crowding[m] < Lower_Bound) {
					if (arc[temp_to - 1][temp_from - 1] > 10) {
						arc[temp_to - 1][temp_from - 1] -= 10;
					}
					//else if (arc[temp_to - 1][temp_from - 1] > 10) {
					//	arc[temp_to - 1][temp_from - 1] -= 10;
					//}
				}
				else if (ROAD[i].crowding[m] > Upper_Bound) {
					arc[temp_to - 1][temp_from - 1] += 50;
				}
			}
		}
	}

	this->Floyd();
	this->set_path_DealLock_back(DeadCar, CROSS, ROAD);
	this->set_out_road_DealLock(DeadCar, CROSS);
}

void Graph_DG::initRoute_DealLock_back2(Car &DeadCar, vector<Cross> &CROSS, vector<Road> &ROAD)
{
	int err_road_id, temp_from, temp_to;
	//回滚时，死锁车辆也不要参与实时调度了，怕又走回去了
	DeadCar.usedToBeDeadCar = true;

	for (int i = 0; i < (int)(DeadCar.deadRoadId.size()); i++) {
		err_road_id = DeadCar.deadRoadId[i];//死锁时的路不走
		temp_from = ROAD[err_road_id].from + 1;
		temp_to = ROAD[err_road_id].to + 1;
		arc[temp_from - 1][temp_to - 1] += 30;
		if (ROAD[err_road_id].isDuplex == 1) {//这里懒得去计算正反向了，反正就是不走了
			arc[temp_to - 1][temp_from - 1] += 30;
		}
	}

	//err_road_id = DeadCar.deadInRoadId;//死锁时的路
	//temp_from = ROAD[err_road_id].from + 1;
	//temp_to = ROAD[err_road_id].to + 1;
	//arc[temp_from - 1][temp_to - 1] = 999;
	//if (ROAD[err_road_id].isDuplex == 1) {//这里懒得去计算正反向了，反正就是不走了
	//	arc[temp_to - 1][temp_from - 1] = 999;
	//}

	//err_road_id = DeadCar.deadInRoadId_next;//死锁时的下一条路
	//temp_from = ROAD[err_road_id].from + 1;
	//temp_to = ROAD[err_road_id].to + 1;
	//arc[temp_from - 1][temp_to - 1] = 999;
	//if (ROAD[err_road_id].isDuplex == 1) {//这里懒得去计算正反向了，反正就是不走了
	//	arc[temp_to - 1][temp_from - 1] = 999;
	//}

	err_road_id = DeadCar.nextRoad;//下一条路
	temp_from = ROAD[err_road_id].from + 1;
	temp_to = ROAD[err_road_id].to + 1;
	arc[temp_from - 1][temp_to - 1] += 10;
	if (ROAD[err_road_id].isDuplex == 1) {//这里懒得去计算正反向了，反正就是加高权重了
		arc[temp_to - 1][temp_from - 1] += 10;
	}


	//对不同拥挤度的路做不同的权重加减，这里的权重参数需要进一步验证合理性
	for (int i = 0; i < (int)(ROAD.size()); i++) {
		temp_from = ROAD[i].from + 1;
		temp_to = ROAD[i].to + 1;
		for (int m = 0; m < ROAD[i].isDuplex + 1; m++) {
			if (m == 0) {//正向
				if (ROAD[i].crowding[m] < Lower_Bound) {
					if (arc[temp_from - 1][temp_to - 1] > 10) {
						arc[temp_from - 1][temp_to - 1] -= 10;
					}
					//else if (arc[temp_from - 1][temp_to - 1] > 10) {
					//	arc[temp_from - 1][temp_to - 1] -= 10;
					//}
				}
				else if (ROAD[i].crowding[m] > Upper_Bound) {
					arc[temp_from - 1][temp_to - 1] += 50;
				}
			}
			else if (m == 1) {//反向
				if (ROAD[i].crowding[m] < Lower_Bound) {
					if (arc[temp_to - 1][temp_from - 1] > 10) {
						arc[temp_to - 1][temp_from - 1] -= 10;
					}
					//else if (arc[temp_to - 1][temp_from - 1] > 10) {
					//	arc[temp_to - 1][temp_from - 1] -= 10;
					//}
				}
				else if (ROAD[i].crowding[m] > Upper_Bound) {
					arc[temp_to - 1][temp_from - 1] += 50;
				}
			}
		}
	}

	this->Floyd();
	this->set_path_DealLock_back(DeadCar, CROSS, ROAD);
	this->set_out_road_DealLock(DeadCar, CROSS);
}

//全局禁忌
void Graph_DG::initRoute_DealLock_back3(Car &DeadCar, vector<Cross> &CROSS, vector<Road> &ROAD, vector<int> &CarDeadRoadId)
{
	int err_road_id, temp_from, temp_to;
	//回滚时，死锁车辆也不要参与实时调度了，怕又走回去了//等等
	DeadCar.usedToBeDeadCar = true;

	//if (CarDeadRoadId.size() > 3) {
	//	cout << "死锁超过3次，在不同路或同路" << endl;
	//}
	for (int i = 0; i < (int)(CarDeadRoadId.size()); i++) {
		err_road_id = CarDeadRoadId[i];//死锁时的路不走
		temp_from = ROAD[err_road_id].from + 1;
		temp_to = ROAD[err_road_id].to + 1;
		arc[temp_from - 1][temp_to - 1] += 30;
		if (ROAD[err_road_id].isDuplex == 1) {//这里懒得去计算正反向了，反正就是不走了
			arc[temp_to - 1][temp_from - 1] += 30;
		}
	}

	//err_road_id = DeadCar.deadInRoadId;//死锁时的路
	//temp_from = ROAD[err_road_id].from + 1;
	//temp_to = ROAD[err_road_id].to + 1;
	//arc[temp_from - 1][temp_to - 1] = 999;
	//if (ROAD[err_road_id].isDuplex == 1) {//这里懒得去计算正反向了，反正就是不走了
	//	arc[temp_to - 1][temp_from - 1] = 999;
	//}

	//err_road_id = DeadCar.deadInRoadId_next;//死锁时的下一条路
	//temp_from = ROAD[err_road_id].from + 1;
	//temp_to = ROAD[err_road_id].to + 1;
	//arc[temp_from - 1][temp_to - 1] = 999;
	//if (ROAD[err_road_id].isDuplex == 1) {//这里懒得去计算正反向了，反正就是不走了
	//	arc[temp_to - 1][temp_from - 1] = 999;
	//}

	//err_road_id = DeadCar.nextRoad;//下一条路
	//temp_from = ROAD[err_road_id].from + 1;
	//temp_to = ROAD[err_road_id].to + 1;
	//arc[temp_from - 1][temp_to - 1] += 10;
	//if (ROAD[err_road_id].isDuplex == 1) {//这里懒得去计算正反向了，反正就是加高权重了
	//	arc[temp_to - 1][temp_from - 1] += 10;
	//}


	//对不同拥挤度的路做不同的权重加减，这里的权重参数需要进一步验证合理性
	for (int i = 0; i < (int)(ROAD.size()); i++) {
		temp_from = ROAD[i].from + 1;
		temp_to = ROAD[i].to + 1;
		for (int m = 0; m < ROAD[i].isDuplex + 1; m++) {
			if (m == 0) {//正向
				if (ROAD[i].crowding[m] < Lower_Bound) {
					if (arc[temp_from - 1][temp_to - 1] > 10) {
						arc[temp_from - 1][temp_to - 1] -= 10;
					}
					//else if (arc[temp_from - 1][temp_to - 1] > 10) {
					//	arc[temp_from - 1][temp_to - 1] -= 10;
					//}
				}
				else if (ROAD[i].crowding[m] > Upper_Bound) {
					arc[temp_from - 1][temp_to - 1] += 50;
				}
			}
			else if (m == 1) {//反向
				if (ROAD[i].crowding[m] < Lower_Bound) {
					if (arc[temp_to - 1][temp_from - 1] > 10) {
						arc[temp_to - 1][temp_from - 1] -= 10;
					}
					//else if (arc[temp_to - 1][temp_from - 1] > 10) {
					//	arc[temp_to - 1][temp_from - 1] -= 10;
					//}
				}
				else if (ROAD[i].crowding[m] > Upper_Bound) {
					arc[temp_to - 1][temp_from - 1] += 50;
				}
			}
		}
	}

	this->Floyd();
	this->set_path_DealLock_back(DeadCar, CROSS, ROAD);
	this->set_out_road_DealLock(DeadCar, CROSS);
}

void Graph_DG::initRoute_Dynamic(vector<Car> &CAR, vector<Cross> &CROSS, vector<Road> &ROAD) {

	int temp_from, temp_to;

	//对不同拥挤度的路做不同的权重加减，这里的权重参数需要进一步验证合理性
	for (int i = 0; i < (int)(ROAD.size()); i++) {
		temp_from = ROAD[i].from + 1;
		temp_to = ROAD[i].to + 1;
		//cout << arc[temp_from - 1][temp_to - 1] << ", " << arc[temp_to - 1][temp_from - 1] << endl;
		//arc[temp_from - 1][temp_to - 1] += 10 * ROAD[i].crowding[0];
		//arc[temp_to - 1][temp_from - 1] += 10 * ROAD[i].crowding[1];
		for (int m = 0; m < ROAD[i].isDuplex + 1; m++) {
			if (m == 0) {//正向
				if (ROAD[i].crowding[m] < Lower_Bound) {
					if (arc[temp_from - 1][temp_to - 1] > 20) {
						arc[temp_from - 1][temp_to - 1] -= 20;
					}
					else if (arc[temp_from - 1][temp_to - 1] > 10) {
						arc[temp_from - 1][temp_to - 1] -= 10;
					}
				}
				else if (ROAD[i].crowding[m] > Upper_Bound) {
					arc[temp_from - 1][temp_to - 1] += 50;
				}
			}
			else if (m == 1) {//反向
				if (ROAD[i].crowding[m] < Lower_Bound) {
					if (arc[temp_to - 1][temp_from - 1] > 20) {
						arc[temp_to - 1][temp_from - 1] -= 20;
					}
					else if (arc[temp_to - 1][temp_from - 1] > 10) {
						arc[temp_to - 1][temp_from - 1] -= 10;
					}
				}
				else if (ROAD[i].crowding[m] > Upper_Bound) {
					arc[temp_to - 1][temp_from - 1] += 50;
				}
			}
		}
	}

	this->Floyd();
	this->set_path_Dynamic(CAR, CROSS, ROAD);//这里只set后面的路，前面已经走过的路不能碰，如果不拥挤，直接不用set
	this->set_out_road(CAR, CROSS);//这里不需要每次都进行计算，只在最后一次计算就可以了，等下改
}

