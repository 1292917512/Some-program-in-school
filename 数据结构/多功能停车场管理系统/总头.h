#pragma once
#include"CMystack.h"
#include"CMylist.h" 
#include"Vehicle.h"
#include<stdlib.h>
#include <time.h>
#include<math.h>
#include<fstream>
#include<string>
#define MONEY 10  //停车单价
#define MAP_ROW 10   //地图长
#define MAP_COL 10   //地图宽

typedef struct
{
	string VehLicense;
	string VehKind;
	struct tm StarTime;
	struct tm EndTime;
	MyPoint sp;
	MyPoint p;
}Veh;
//车子运行方向的枚举
enum Path_Dir { p_up, p_down, p_left, p_right };


//准备一个辅助数组（1、资源地图数组不能变；2、对资源地图要进数据标记）
struct PathNode
{
	int val;//保存原始资源的路径点信息
	Path_Dir dir; //当前路径点的方向标记
	bool isFind;//当前路径点是否被访问过
};
	

//记录提车位置是否可用
struct IsPoint  
{
	MyPoint p;
	bool i;
};

void mainmuen()
{
	cout << "\t\t\t\t\t系统可选操作\t\t" << endl;
	cout << "\t\t\t\t\t1、车辆进停车场\t\t" << endl;
	cout << "\t\t\t\t\t2、车辆出停车场\t\t" << endl;
	cout << "\t\t\t\t\t3、显示停车场剩余停车位\t\t" << endl;
	cout << "\t\t\t\t\t4、车辆信息显示\t\t" << endl;
	cout << "\t\t\t\t\t5、退出系统\t\t" << endl;
}
