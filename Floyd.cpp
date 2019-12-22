#include"Floyd.h"
#include "readfile.h"
#define MAX_NUM 99999
#define Lower_Bound 0.2
#define Upper_Bound 0.8

//���캯��
Graph_DG::Graph_DG(int vexnum, vector<Road>& ROAD) {


	//��ʼ���������ͱ���
	this->vexnum = vexnum;
	this->edge = edge;
	//Ϊ�ڽӾ��󿪱ٿռ�͸���ֵ
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
			//�ڽӾ����ʼ��	//��ͼ�����ʼ��
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

	//������ͼ
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

//ר���ڴ������������Ĺ��캯��
Graph_DG::Graph_DG(const Graph_DG &OriginalCarGraph) {
	//��ʼ���������ͱ���
	this->vexnum = OriginalCarGraph.vexnum;
	this->edge = OriginalCarGraph.edge;
	//Ϊ�ڽӾ��󿪱ٿռ�͸���ֵ
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
			//����ԭ��ͼ������
			arc[i][k] = OriginalCarGraph.arc[i][k];
			//dis[i][k] = OriginalCarGraph.dis[i][k];
			//path[i][k] = OriginalCarGraph.path[i][k];
			map[i][k] = OriginalCarGraph.map[i][k];
		}
	}
}

//��������
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
	//cout << "������ÿ���ߵ������յ㣨�����Ŵ�1��ʼ���Լ���Ȩ��" << endl;
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

		//�����жϱߵ���Ϣ�Ƿ�Ϸ������ڿ�ɾ���Խ�ʡʱ��
		//while (!this->check_edge_value(start, end, weight)) {
		//	cout << "����ıߵ���Ϣ���Ϸ�������������" << endl;
		//	//exit(1);
		//	//cin >> start >> end >> weight;
		//}

		//���ڽӾ����Ӧ�ϵĵ㸳ֵ
		arc[start][end] = weight;
		map[start ][end] = ROAD[count].id;
		//����ͼ���������д���
		//if (kind == 2)
		//	arc[end - 1][start - 1] = weight;

		//˫�е�
		if (ROAD[count].isDuplex == 1) {
			arc[end][start] = weight;
			map[end][start] = ROAD[count].id;
		}
		++count;
	}
}

//����ɾ�����ò�����
void Graph_DG::print() {
	cout << "ͼ���ڽӾ���Ϊ��" << endl;
	int count_row = 0; //��ӡ�еı�ǩ
	int count_col = 0; //��ӡ�еı�ǩ
					   //��ʼ��ӡ
	while (count_row != this->vexnum) {
		count_col = 0;
		while (count_col != this->vexnum) {
			if (arc[count_row][count_col] == MAX_NUM)
				cout << "��" << " ";
			else
				cout << arc[count_row][count_col] << " ";
			++count_col;
		}
		cout << endl;
		++count_row;
	}
}

//�㷨�ĺ���
void Graph_DG::Floyd() {
	int row = 0;
	int col = 0;
	for (row = 0; row < this->vexnum; row++) {
		for (col = 0; col < this->vexnum; col++) {
			//�Ѿ���D��ʼ��Ϊ�ڽӾ����ֵ
			this->dis[row][col] = this->arc[row][col];
			//����P�ĳ�ֵ��Ϊ�����ߵ��յ㶥����±�
			this->path[row][col] = col;
		}
	}

	//����ѭ�������ڼ���ÿ����Ե����·��
	int temp = 0;
	int select = 0;
	for (temp = 0; temp < this->vexnum; temp++) {
		for (row = 0; row < this->vexnum; row++) {
			for (col = 0; col < this->vexnum; col++) {
				//Ϊ�˷�ֹ�����������Ҫ����һ��selectֵ
				select = (dis[row][temp] == MAX_NUM || dis[temp][col] == MAX_NUM) ? MAX_NUM : (dis[row][temp] + dis[temp][col]);
				if (this->dis[row][col] > select) {
					//�������ǵ�D����
					this->dis[row][col] = select;
					//�������ǵ�P����
					this->path[row][col] = this->path[row][temp];
				}
			}
		}
	}
}

//����ɾ�����ò�����
void Graph_DG::print_path() {
	cout << "��������Ե����·����" << endl;
	int row = 0;
	int col = 0;
	int temp = 0;
	for (row = 0; row < this->vexnum; row++) {
		for (col = 0; col < this->vexnum; col++) {
			cout << "v" << to_string(row + 1) << "---" << "v" << to_string(col + 1) << " weight: "
				<< this->dis[row][col] << " path: " << " v" << to_string(row + 1);
			temp = path[row][col];
			//ѭ�����;����ÿ��·����
			while (temp != col) {
				cout << "-->" << "v" << to_string(temp + 1);
				temp = path[temp][col];
			}
			cout << "-->" << "v" << to_string(col + 1) << endl;
		}
		cout << endl;
	}

	//cout << "DIS����Ϊ��" << endl;
	//int count_row = 0; //��ӡ�еı�ǩ
	//int count_col = 0; //��ӡ�еı�ǩ
	//				   //��ʼ��ӡ
	//while (count_row != this->vexnum) {
	//	count_col = 0;
	//	while (count_col != this->vexnum) {
	//		if (dis[count_row][count_col] == INT_MAX)
	//			cout << "��" << " ";
	//		else
	//			cout << dis[count_row][count_col] << " ";
	//		++count_col;
	//	}
	//	cout << endl;
	//	++count_row;
	//}
}

//��Floyd�����·������
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
		if (CAR[i].preset == 1) {//�����Ԥ�ó���
			//CAR[i].direction.clear();//����Ҫ����Ϊȫ��������Ԥ�ó���ֻ������һ��direction			
			
			for (int j = 0; j < (int)(CAR[i].route.size()); ++j) {
				last_position = 0;
				if (j == 0) {//��һ��ת�򣬿϶���ֱ��
					CAR[i].direction.push_back(0);
					last_position = CAR[i].from;
					temp_road_id = CAR[i].route[j];
					if (ROAD[temp_road_id].from == last_position) {
						next_position = ROAD[temp_road_id].to;
					}
					else if (ROAD[temp_road_id].to == last_position) {
						next_position = ROAD[temp_road_id].from;
					}
					last_position = next_position;//ע��
					continue;
				}
				last_road_id = CAR[i].route[j - 1];
				next_road_id = CAR[i].route[j];//j��1��ʼ�Ż�������Ҳ���ǵڶ���·����ʼ�ſ���ת��
				if (ROAD[next_road_id].from == last_position) {
					next_position = ROAD[next_road_id].to;
				}
				if (ROAD[next_road_id].to == last_position) {
					next_position = ROAD[next_road_id].from;
				}
				//���￪ʼ���ǵڶ������ת��
				road_id[0] = CROSS[last_position].road1;
				road_id[1] = CROSS[last_position].road2;
				road_id[2] = CROSS[last_position].road3;
				road_id[3] = CROSS[last_position].road4;

				//����ת��
				for (k = 0; k < 4; k++) {
					if (last_road_id == road_id[k]) {
						now_road_direction = k;
						break;
					}
				}
				if (k == 4) {
					cout << "�����������·���Ҳ���Ŀǰ���ڵ�·��һ�㲻�����" << endl;
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
					cout << "�����������·���Ҳ�����һ��·��һ�㲻�����" << endl;
					//system("pause");
					exit(1);
				}
				err = next_road_direction - now_road_direction;
				//����ת����Ϣ�����˳ʱ��1��������ת�������ʱ��-1��������ת��������2����ֱ��
				switch (err)
				{
				case 1:		//��ת
					CAR[i].direction.push_back(1);
					break;
				case -3:	//��ת
					CAR[i].direction.push_back(1);
					break;
				case -1:	//��ת
					CAR[i].direction.push_back(2);
					break;
				case 3:		//��ת
					CAR[i].direction.push_back(2);
					break;
				case 2:		//ֱ��
					CAR[i].direction.push_back(0);
					break;
				case -2:	//ֱ��
					CAR[i].direction.push_back(0);
					break;
				default:
					cout << "�����˵�ͷ����������" << endl;
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
					cout << "�����������·���Ҳ���Ŀǰ���ڵ�·��һ�㲻�����" << endl;
					//system("pause");
					exit(1);
				}

				//����·��
				temp_next = path[temp][col];
				temp_road_id = map[temp][temp_next];
				CAR[i].route.push_back(temp_road_id);
				temp = temp_next;

				//����ת��
				for (k = 0; k < 4; k++) {
					if (temp_road_id == road_id[k]) {
						next_road_direction = k;
						break;
					}
				}
				if (k == 4) {
					cout << "�����������·���Ҳ�����һ��·��һ�㲻�����" << endl;
					//system("pause");
					exit(1);
				}
				err = next_road_direction - now_road_direction;



				//����ת����Ϣ�����˳ʱ��1��������ת�������ʱ��-1��������ת��������2����ֱ��
				switch (err)
				{
				case 1:		//��ת
					CAR[i].direction.push_back(1);
					break;
				case -3:	//��ת
					CAR[i].direction.push_back(1);
					break;
				case -1:	//��ת
					CAR[i].direction.push_back(2);
					break;
				case 3:		//��ת
					CAR[i].direction.push_back(2);
					break;
				case 2:		//ֱ��
					CAR[i].direction.push_back(0);
					break;
				case -2:	//ֱ��
					CAR[i].direction.push_back(0);
					break;
				default:
					cout << "�����˵�ͷ����������" << endl;
					exit(1);
					//system("pause");
					break;
				}
			}
		}
	}
}

//������������setPath
//����Ҫע�⣬�����Ԥ�ó�����������ô�����������������Ժ���д������������������
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
				cout << "�����������·���Ҳ���Ŀǰ���ڵ�·��һ�㲻�����" << endl;
				//system("pause");
				exit(1);
			}

			//����·��
			temp_next = path[temp][col];
			temp_road_id = map[temp][temp_next];
			CAR.route.push_back(temp_road_id);
			temp = temp_next;

			//����ת��
			for (k = 0; k < 4; k++) {
				if (temp_road_id == road_id[k]) {
					next_road_direction = k;
					break;
				}
			}
			if (k == 4) {
				cout << "�����������·���Ҳ�����һ��·��һ�㲻�����" << endl;
				//system("pause");
				exit(1);
			}
			err = next_road_direction - now_road_direction;



			//����ת����Ϣ�����˳ʱ��1��������ת�������ʱ��-1��������ת��������2����ֱ��
			switch (err)
			{
			case 1:		//��ת
				CAR.direction.push_back(1);
				break;
			case -3:	//��ת
				CAR.direction.push_back(1);
				break;
			case -1:	//��ת
				CAR.direction.push_back(2);
				break;
			case 3:		//��ת
				CAR.direction.push_back(2);
				break;
			case 2:		//ֱ��
				CAR.direction.push_back(0);
				break;
			case -2:	//ֱ��
				CAR.direction.push_back(0);
				break;
			default:
				cout << "�����˵�ͷ����������" << endl;
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

	int pass_cross_id=0;//�����߹���·�ڣ���Ҫ��ͷ
	vector<int> link_cross;
	//bool back_flag[4] = { false,false,false,false };//�����������Ҳûɶ�ã�����ɾ��
	int road_weight[4] = { MAX_NUM ,MAX_NUM ,MAX_NUM ,MAX_NUM };
	int min_road_weight = MAX_NUM;
	int min_link_cross = -1;
	int next_road = -1;
	int temp_num = 0;
	int first_temp_road_id = 0;
	bool flag5 = true;
	/*bool IS = false;*/

		now_road_id = CAR.location[0];
		//vector<int>::iterator iter = find(CAR[i].route.begin(), CAR[i].route.end(), now_road_id); //����3
		if (CAR.route[CAR.passRoadNumber] != now_road_id) {
			cout << "�ó�·����û�ҵ�Ŀǰ����·��һ�㲻����֣�������˵������ûд��" << endl;
			//system("pause");
			exit(1);
		}
		//if (iter == CAR[i].route.end()) {
		//	cout << "û�ҵ���һ�㲻����֣�������˵������ûд��" << endl;
		//	system("pause");
		//	exit(1);
		//}
		//if ((iter + 1) == CAR[i].route.end()) {//Ŀǰ����·�Ǹó������һ��·��Ҳ��Ҫ��������
		//	continue;
		//}


		/************���￪ʼ�Ǽ����Ƿ��ͷ���Ƿ�Ҫ��·****************/
		min_link_cross = -1;
		if (CAR.isReverse == 0) {
			CAR.nextCross = ROAD[now_road_id].to;
			pass_cross_id = ROAD[now_road_id].from;//�ո��Ѿ��߹���·��
		}
		if (CAR.isReverse == 1) {
			CAR.nextCross = ROAD[now_road_id].from;
			pass_cross_id = ROAD[now_road_id].to;//�ո��Ѿ��߹���·��
		}
		link_cross = getLinkCross(CROSS[CAR.nextCross], ROAD);
		//�Ƿ��ͷ�ı�־��λ
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
			road_weight[j] = arc[CAR.nextCross][link_cross[j]] + dis[link_cross[j]][CAR.to];//��һС��+�����·

			//ʶ���������͵�·��
			if (road_weight[j] < min_road_weight) {
				min_road_weight = road_weight[j];
				min_link_cross = link_cross[j];//���min_link_crossҪô= -1,Ҫô�Ϳ϶��ǿ����ߣ�������Ҫ�ߵ�
			}
		}

		//����ó����¸���㱾���������滮��·�����ǾͲ�Ҫ�޸��κ�·����Ϣ�ˣ�����һ����
		next_road = -1;
		next_road = CAR.route[CAR.passRoadNumber + 1];
		flag5 = true;
		if (min_link_cross == -1 || min_link_cross == ROAD[next_road].from || min_link_cross == ROAD[next_road].to) {
			flag5 = false;//�ҵ�������·��Ȩ��̫�ߣ����߱�����������·������һ����
		}
		/************��������Ǽ����Ƿ��ͷ���Ƿ�Ҫ��·****************/

		if (flag5 == true) {
			//���ˣ��ó�����һ��Ҫ�ߵĽ����min_link_cross�������CROSS��ֱ���õ��±꣬ȷ��Ҫ��·��
		//for (iter += 1; iter != CAR[i].route.end(); ) {//ɾ����û�ߵ�rounte
		//	iter = CAR[i].route.erase(iter);
		//}
			CAR.route.erase(CAR.route.begin() + CAR.passRoadNumber + 1, CAR.route.end());

			//ɾ��Ӧ��direction
			/*for (iter = CAR[i].direction.begin() + (int)CAR[i].route.size(); iter != CAR[i].direction.end();) {
				iter = CAR[i].direction.erase(iter);
			}*/
			CAR.direction.erase(CAR.direction.begin() + CAR.passRoadNumber + 1, CAR.direction.end());

			//�����滮ʣ�µ�·��,���ﻹûд�꣡����������������
			//��Ŀǰ��һ��·����Ҫ��Floyd��ͼ�ˣ�ֱ�Ӳ壬��ֹ�ֿ�ʼ��
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
				cout << "���������Ҳ���Ҫ�ߵ���һ��С·��һ�㲻�����" << endl;
				//system("pause");
				exit(1);
			}

			temp_direction = this->findDirection(CROSS[CAR.nextCross], CAR.location[0], temp_road_id);
			CAR.direction.push_back(temp_direction);
			first_temp_road_id = temp_road_id;

			//��ʣ�µ�·
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

					//����ת��
					dir_now_road_id = temp_road_id;

					//����·��
					temp_next = path[temp][col];
					temp_road_id = map[temp][temp_next];
					CAR.route.push_back(temp_road_id);
					temp = temp_next;

					//����ת��
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

	int pass_cross_id;//�����߹���·�ڣ���Ҫ��ͷ
	vector<int> link_cross;
	//bool back_flag[4] = { false,false,false,false };//�����������Ҳûɶ�ã�����ɾ��
	int road_weight[4] = { MAX_NUM ,MAX_NUM ,MAX_NUM ,MAX_NUM };
	int min_road_weight = MAX_NUM;
	int min_link_cross = -1;
	int next_road = -1;
	int temp_num = 0;
	int first_temp_road_id = 0;
	//bool is = false;
	for (int i = 0; i < (int)CAR.size(); i++) {

		if (CAR[i].usedToBeDeadCar == true) {//������������������Ҫ����ʵʱ�滮
			continue;
		}
		if (CAR[i].preset == 1) {//Ԥ�ó���Ҳ��Ҫ����ʵʱ�滮
			continue;
		}
		if (CAR[i].ATD == -1) {//û�����ĳ��Ͳ�Ҫ��������
			continue;
		}
		if (CAR[i].isTerminate == 1) {//�����յ�ĳ�Ҳ��Ҫ����
			continue;
		}
		if (CAR[i].nextCrossDistance < CAR[i].maxSpeed) {//ֻ����Щ��ǰʱ�̲���·�ڵĳ�
			continue;
		}
		if (CAR[i].passRoadNumber == (int)(CAR[i].route.size()) - 1) {//Ŀǰ����·�Ǹó������һ��·��Ҳ��Ҫ��������
			continue;
		}
		else if (CAR[i].passRoadNumber == (int)(CAR[i].route.size()) - 2) {//�ó�����һ��·��Ҫ���յ㣬Ҳ��Ҫ��������
			continue;
		}
		else if (CAR[i].passRoadNumber == (int)(CAR[i].route.size()) - 3) {//�ó�������һ��·��Ҫ���յ㣬Ҳ��Ҫ��������
			continue;
		}

		now_road_id = CAR[i].location[0];
		//vector<int>::iterator iter = find(CAR[i].route.begin(), CAR[i].route.end(), now_road_id); //����3
		if (CAR[i].route[CAR[i].passRoadNumber] != now_road_id) {
			cout << "�ó�·����û�ҵ�Ŀǰ����·��һ�㲻����֣�������˵������ûд��" << endl;
			//system("pause");
			exit(1);
		}
		//if (iter == CAR[i].route.end()) {
		//	cout << "û�ҵ���һ�㲻����֣�������˵������ûд��" << endl;
		//	system("pause");
		//	exit(1);
		//}
		//if ((iter + 1) == CAR[i].route.end()) {//Ŀǰ����·�Ǹó������һ��·��Ҳ��Ҫ��������
		//	continue;
		//}


		/************���￪ʼ�Ǽ����Ƿ��ͷ���Ƿ�Ҫ��·****************/
		pass_cross_id = 0;
		min_link_cross = -1;
		if (CAR[i].isReverse == 0) {
			CAR[i].nextCross = ROAD[now_road_id].to;
			pass_cross_id = ROAD[now_road_id].from;//�ո��Ѿ��߹���·��
		}
		if (CAR[i].isReverse == 1) {
			CAR[i].nextCross = ROAD[now_road_id].from;
			pass_cross_id = ROAD[now_road_id].to;//�ո��Ѿ��߹���·��
		}
		link_cross = getLinkCross(CROSS[CAR[i].nextCross], ROAD);
		//�Ƿ��ͷ�ı�־��λ
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
			road_weight[j] = arc[CAR[i].nextCross][link_cross[j]] + dis[link_cross[j]][CAR[i].to];//��һС��+�����·

			//ʶ���������͵�·��
			if (road_weight[j] < min_road_weight) {
				min_road_weight = road_weight[j];
				min_link_cross = link_cross[j];//���min_link_crossҪô= -1,Ҫô�Ϳ϶��ǿ����ߣ�������Ҫ�ߵ�
			}
		}

		//����ó����¸���㱾���������滮��·�����ǾͲ�Ҫ�޸��κ�·����Ϣ�ˣ�����һ����
		next_road = -1;
		next_road = CAR[i].route[CAR[i].passRoadNumber + 1];
		if (min_link_cross == -1 || min_link_cross == ROAD[next_road].from || min_link_cross == ROAD[next_road].to) {
			continue;//�ҵ�������·��Ȩ��̫�ߣ����߱�����������·������һ����
		}
		/************��������Ǽ����Ƿ��ͷ���Ƿ�Ҫ��·****************/


		//���ˣ��ó�����һ��Ҫ�ߵĽ����min_link_cross�������CROSS��ֱ���õ��±꣬ȷ��Ҫ��·��
		//for (iter += 1; iter != CAR[i].route.end(); ) {//ɾ����û�ߵ�rounte
		//	iter = CAR[i].route.erase(iter);
		//}
		CAR[i].route.erase(CAR[i].route.begin() + CAR[i].passRoadNumber + 1, CAR[i].route.end());

		//ɾ��Ӧ��direction
		/*for (iter = CAR[i].direction.begin() + (int)CAR[i].route.size(); iter != CAR[i].direction.end();) {
			iter = CAR[i].direction.erase(iter);
		}*/
		CAR[i].direction.erase(CAR[i].direction.begin() + CAR[i].passRoadNumber + 1, CAR[i].direction.end());

		//�����滮ʣ�µ�·��,���ﻹûд�꣡����������������
		//��Ŀǰ��һ��·����Ҫ��Floyd��ͼ�ˣ�ֱ�Ӳ壬��ֹ�ֿ�ʼ��
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
			cout << "���������Ҳ���Ҫ�ߵ���һ��С·��һ�㲻�����" << endl;
			//system("pause");
			exit(1);
		}

		temp_direction = this->findDirection(CROSS[CAR[i].nextCross], CAR[i].location[0], temp_road_id);
		CAR[i].direction.push_back(temp_direction);
		first_temp_road_id = temp_road_id;

		//��ʣ�µ�·
		row = min_link_cross;
		col = CAR[i].to;
		if (row == col) {//�Ѿ����˰��������Ѿ��������һ��·�ˣ����治��Ҫ�����ˣ�����һ����
			//cout << "һ�㲻�����123123123" << endl;
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

			//����ת��
			dir_now_road_id = temp_road_id;

			//����·��
			temp_next = path[temp][col];
			temp_road_id = map[temp][temp_next];
			CAR[i].route.push_back(temp_road_id);
			temp = temp_next;

			//����ת��
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
		cout << "�����������·���Ҳ���Ŀǰ���ڵ�·��һ�㲻�����" << endl;
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
		cout << "�����������·���Ҳ�����һ��·��һ�㲻�����" << endl;
		//system("pause");
		exit(1);
	}
	err = next_road_direction - now_road_direction;

	//����ת����Ϣ�����˳ʱ��1��������ת�������ʱ��-1��������ת��������2����ֱ��
	switch (err)
	{
	case 1:		//��ת
		return(1);
		break;
	case -3:	//��ת
		return(1);
		break;
	case -1:	//��ת
		return(2);
		break;
	case 3:		//��ת
		return(2);
		break;
	case 2:		//ֱ��
		return(0);
		break;
	case -2:	//ֱ��
		return(0);
		break;
	default:
		cout << "�����˵�ͷ�����󣬲��������֣�" << endl;
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
		else {//�����ӵģ������ǵ�������߲���ȥ�ģ����Ի���-1
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

//����������ʱ��ֻ���¶�Ӧ�ĳ�������Ҫȫ������
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
	//Graph_DG graph(CROSS.size(), edge);//δ���ǳ�����������Ҫ���ϣ����⣬�᲻������·��֮��������·�����������
	this->createGraph(1, ROAD, (int)(ROAD.size()));//1��������ͼ��2��������ͼ
	this->Floyd();
	this->set_path(CAR, CROSS, ROAD, (int)(CAR.size()));
	this->set_out_road(CAR, CROSS);
}


void Graph_DG::initRoute_DealLock(Car &DeadCar, vector<Cross> &CROSS, vector<Road> &ROAD, vector<int> &freeRoads, vector<int> &busyRoads, vector<int> &CROSSID)
{
	int err_road_id, temp_from, temp_to;
	int change_flag;
	vector<int>::iterator it;
	if (DeadCar.nextRoad != -1) {	//������һ��·�ǲ����ߵ�������������յ�֮���·��

		//��̬�滮ʱ�õ��������������������Ҫ����ʵʱ���ȣ�����汾û�õ�
		DeadCar.usedToBeDeadCar = true;

		err_road_id = DeadCar.location[0] - ROAD[0].id;//����·��id
		temp_from = ROAD[err_road_id].from+1;
		temp_to = ROAD[err_road_id].to+1;

		change_flag = 0;
		for (int k = 0; k < (int)(freeRoads.size()); k++) {
			if (DeadCar.location[0] == freeRoads[k]) {//������Ŀǰ���ڵ�·Ҳ�ǳ������ٵ�·��
				//cout << "Ŀǰ������·Ҳ�ǳ������ٵ�·��" << endl;
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

		if (change_flag == 0) {//������Ŀǰ���ڵ�·���ǳ������ٵ�·��ɾ������·
			if (ROAD[err_road_id].to == DeadCar.nextCross) {
				arc[temp_from - 1][temp_to - 1] = 999;
				//map[temp_from - 1][temp_to - 1] = -1;
			}
			else if (ROAD[err_road_id].from == DeadCar.nextCross) {
				arc[temp_to - 1][temp_from - 1] = 999;
				//map[temp_to - 1][temp_from - 1] = -1;
			}

			//˳��������������ٵ�·����Ȩ��
			//cout << "�������ٵĵ�·��" << endl;
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
			//˳����������������·���Ȩ��
			//cout << "�������ߵĵ�·��" << endl;
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
	//�ع�ʱ����������Ҳ��Ҫ����ʵʱ�����ˣ������߻�ȥ��
	DeadCar.usedToBeDeadCar = true;

	err_road_id = DeadCar.nextRoad - ROAD[0].id;//��һ��·��id
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

	//�Բ�ͬӵ���ȵ�·����ͬ��Ȩ�ؼӼ��������Ȩ�ز�����Ҫ��һ����֤������
	for (int i = 0; i < (int)(ROAD.size()); i++) {
		temp_from = ROAD[i].from + 1;
		temp_to = ROAD[i].to + 1;
		for (int m = 0; m < ROAD[i].isDuplex + 1; m++) {
			if (m == 0) {//����
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
			else if (m == 1) {//����
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
	//�ع�ʱ����������Ҳ��Ҫ����ʵʱ�����ˣ������߻�ȥ��
	DeadCar.usedToBeDeadCar = true;

	for (int i = 0; i < (int)(DeadCar.deadRoadId.size()); i++) {
		err_road_id = DeadCar.deadRoadId[i];//����ʱ��·����
		temp_from = ROAD[err_road_id].from + 1;
		temp_to = ROAD[err_road_id].to + 1;
		arc[temp_from - 1][temp_to - 1] += 30;
		if (ROAD[err_road_id].isDuplex == 1) {//��������ȥ�����������ˣ��������ǲ�����
			arc[temp_to - 1][temp_from - 1] += 30;
		}
	}

	//err_road_id = DeadCar.deadInRoadId;//����ʱ��·
	//temp_from = ROAD[err_road_id].from + 1;
	//temp_to = ROAD[err_road_id].to + 1;
	//arc[temp_from - 1][temp_to - 1] = 999;
	//if (ROAD[err_road_id].isDuplex == 1) {//��������ȥ�����������ˣ��������ǲ�����
	//	arc[temp_to - 1][temp_from - 1] = 999;
	//}

	//err_road_id = DeadCar.deadInRoadId_next;//����ʱ����һ��·
	//temp_from = ROAD[err_road_id].from + 1;
	//temp_to = ROAD[err_road_id].to + 1;
	//arc[temp_from - 1][temp_to - 1] = 999;
	//if (ROAD[err_road_id].isDuplex == 1) {//��������ȥ�����������ˣ��������ǲ�����
	//	arc[temp_to - 1][temp_from - 1] = 999;
	//}

	err_road_id = DeadCar.nextRoad;//��һ��·
	temp_from = ROAD[err_road_id].from + 1;
	temp_to = ROAD[err_road_id].to + 1;
	arc[temp_from - 1][temp_to - 1] += 10;
	if (ROAD[err_road_id].isDuplex == 1) {//��������ȥ�����������ˣ��������ǼӸ�Ȩ����
		arc[temp_to - 1][temp_from - 1] += 10;
	}


	//�Բ�ͬӵ���ȵ�·����ͬ��Ȩ�ؼӼ��������Ȩ�ز�����Ҫ��һ����֤������
	for (int i = 0; i < (int)(ROAD.size()); i++) {
		temp_from = ROAD[i].from + 1;
		temp_to = ROAD[i].to + 1;
		for (int m = 0; m < ROAD[i].isDuplex + 1; m++) {
			if (m == 0) {//����
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
			else if (m == 1) {//����
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

//ȫ�ֽ���
void Graph_DG::initRoute_DealLock_back3(Car &DeadCar, vector<Cross> &CROSS, vector<Road> &ROAD, vector<int> &CarDeadRoadId)
{
	int err_road_id, temp_from, temp_to;
	//�ع�ʱ����������Ҳ��Ҫ����ʵʱ�����ˣ������߻�ȥ��//�ȵ�
	DeadCar.usedToBeDeadCar = true;

	//if (CarDeadRoadId.size() > 3) {
	//	cout << "��������3�Σ��ڲ�ͬ·��ͬ·" << endl;
	//}
	for (int i = 0; i < (int)(CarDeadRoadId.size()); i++) {
		err_road_id = CarDeadRoadId[i];//����ʱ��·����
		temp_from = ROAD[err_road_id].from + 1;
		temp_to = ROAD[err_road_id].to + 1;
		arc[temp_from - 1][temp_to - 1] += 30;
		if (ROAD[err_road_id].isDuplex == 1) {//��������ȥ�����������ˣ��������ǲ�����
			arc[temp_to - 1][temp_from - 1] += 30;
		}
	}

	//err_road_id = DeadCar.deadInRoadId;//����ʱ��·
	//temp_from = ROAD[err_road_id].from + 1;
	//temp_to = ROAD[err_road_id].to + 1;
	//arc[temp_from - 1][temp_to - 1] = 999;
	//if (ROAD[err_road_id].isDuplex == 1) {//��������ȥ�����������ˣ��������ǲ�����
	//	arc[temp_to - 1][temp_from - 1] = 999;
	//}

	//err_road_id = DeadCar.deadInRoadId_next;//����ʱ����һ��·
	//temp_from = ROAD[err_road_id].from + 1;
	//temp_to = ROAD[err_road_id].to + 1;
	//arc[temp_from - 1][temp_to - 1] = 999;
	//if (ROAD[err_road_id].isDuplex == 1) {//��������ȥ�����������ˣ��������ǲ�����
	//	arc[temp_to - 1][temp_from - 1] = 999;
	//}

	//err_road_id = DeadCar.nextRoad;//��һ��·
	//temp_from = ROAD[err_road_id].from + 1;
	//temp_to = ROAD[err_road_id].to + 1;
	//arc[temp_from - 1][temp_to - 1] += 10;
	//if (ROAD[err_road_id].isDuplex == 1) {//��������ȥ�����������ˣ��������ǼӸ�Ȩ����
	//	arc[temp_to - 1][temp_from - 1] += 10;
	//}


	//�Բ�ͬӵ���ȵ�·����ͬ��Ȩ�ؼӼ��������Ȩ�ز�����Ҫ��һ����֤������
	for (int i = 0; i < (int)(ROAD.size()); i++) {
		temp_from = ROAD[i].from + 1;
		temp_to = ROAD[i].to + 1;
		for (int m = 0; m < ROAD[i].isDuplex + 1; m++) {
			if (m == 0) {//����
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
			else if (m == 1) {//����
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

	//�Բ�ͬӵ���ȵ�·����ͬ��Ȩ�ؼӼ��������Ȩ�ز�����Ҫ��һ����֤������
	for (int i = 0; i < (int)(ROAD.size()); i++) {
		temp_from = ROAD[i].from + 1;
		temp_to = ROAD[i].to + 1;
		//cout << arc[temp_from - 1][temp_to - 1] << ", " << arc[temp_to - 1][temp_from - 1] << endl;
		//arc[temp_from - 1][temp_to - 1] += 10 * ROAD[i].crowding[0];
		//arc[temp_to - 1][temp_from - 1] += 10 * ROAD[i].crowding[1];
		for (int m = 0; m < ROAD[i].isDuplex + 1; m++) {
			if (m == 0) {//����
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
			else if (m == 1) {//����
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
	this->set_path_Dynamic(CAR, CROSS, ROAD);//����ֻset�����·��ǰ���Ѿ��߹���·�������������ӵ����ֱ�Ӳ���set
	this->set_out_road(CAR, CROSS);//���ﲻ��Ҫÿ�ζ����м��㣬ֻ�����һ�μ���Ϳ����ˣ����¸�
}

