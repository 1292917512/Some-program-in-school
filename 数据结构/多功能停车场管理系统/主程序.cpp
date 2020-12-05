#include"总头.h"

//停车点显示
void display_park(IsPoint p[])
{
	int j = 1;
	for (int i = 0; i < 23; i++)
	{
		if (p[i].i == false)
		{
			cout << i + 1 << "号车位" << '[' << p[i].p.row << ',' << p[i].p.col << ']'<<'\t';
			if (j++ % 4 == 0)
			{
				cout << endl;
			}
		}
	}
	cout << endl;
}

//地图加载函数
bool Load_Map(int map[][MAP_COL],IsPoint p[])
{
	//map[MAP_ROW][MAP_COL];
	fstream infile("数据/map.txt");
	if (!infile.is_open())
	{
		return false;
	}
	for (int i = 0; i < MAP_ROW; ++i)
	{
		for (int j = 0; j < MAP_COL; ++j)
			map[i][j] = int(infile.get() - 48);  //字符转换为int  ascii-48等于对应数字.
	}
	int i=0;
	while (i<23)
	{

		p[i].p.row = int(infile.get() - 48);
		p[i].p.col = int(infile.get() - 48);
		p[i].i = false;
		/*cout << '[' << p[i].p.row << ',' << p[i].p.col <<']'<< endl;*/  //判断输入的坐标
		++i;
	}
	//cout << "文件读取完毕" << endl;
	infile.close();
	return true;
}

//准备一个函数，用来判断参数的坐标是否可以通行
bool IsMove(PathNode p[][MAP_COL], int row, int col)
{
	if (row < 0 || row >= MAP_ROW || col < 0 || col >= MAP_COL)
		return false;//如果越界，不需要进行位置的判断
	if (p[row][col].val != 0 || p[row][col].isFind == true)
		return false;//表示当前行列的元素要么是障碍，要么已经被访问过，不能通行
	return true;
}

//判断数据是否出现问题输出数据用
void display_map(int map[][MAP_COL])
{
	for (size_t i = 0; i < MAP_ROW; ++i)
	{
		for (size_t j = 0; j < MAP_COL; j++)
		{
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
}

//寻找车辆位置
void find_car(int mapArr[][MAP_COL],Veh v,IsPoint pk[])
{
	//构建一份辅助的地图
	PathNode pathArr[MAP_ROW][MAP_COL];
	for (int i = 0; i < MAP_ROW; ++i)
	{
		for (int j = 0; j < MAP_COL; ++j)
		{
			pathArr[i][j].val = mapArr[i][j];
			pathArr[i][j].isFind = false;//表示地图中的每一个节点都没有被访问过
			pathArr[i][j].dir = p_up;//表示给地图中的每一个节点都设定一个初始方向
		}
	}
	for (int i = 0; i < 23; ++i)
	{
		pathArr[pk[i].p.row][pk[i].p.col].isFind = pk[i].i;
	}

	MyPoint beginPoint = v.sp; //定义开始位子
	MyPoint endPoint = v.p;
	//准备一个容器，用来保存可通行路径点
	CMyStack<MyPoint> ms;
	ms.push(beginPoint);//把起点压入到容器中，用来查找后续的结点

	//准备一个辅助坐标点，帮助来判断下一个可通行位置
	MyPoint NearPoint = beginPoint;//辅助点先为起点，然后通过起点设定的方向来对周边路径进行搜索

	//开始寻路
	while (true)//无法确定循环次数
	{
		switch (pathArr[NearPoint.row][NearPoint.col].dir)//判断当前起点在辅助数组中设定的方向
		{
		case p_up:
			//if (pathArr[NearPoint.row - 1][NearPoint.col].val == 0 &&	//表示当前点的上一行位置是可通行的
			//	pathArr[NearPoint.row - 1][NearPoint.col].isFind == false)//表示当前点的上一行位置是没有访问的
			pathArr[NearPoint.row][NearPoint.col].dir = p_left;//当前路口的下一个方向标记出来
			if (IsMove(pathArr, NearPoint.row - 1, NearPoint.col))
			{
				//表示当前坐标的上方向能通行
				pathArr[NearPoint.row][NearPoint.col].isFind = true;//当前点改为已访问
				MyPoint temp = { NearPoint.row - 1, NearPoint.col };
				ms.push(temp);//压入这个坐标
				NearPoint = temp;//把这个上方向可通行的点赋值给辅助点，进行下一次的搜索
			}
			break;
		case p_left:
			pathArr[NearPoint.row][NearPoint.col].dir = p_down;//当前路口的下一个方向标记出来
			if (IsMove(pathArr, NearPoint.row, NearPoint.col - 1))
			{
				//表示当前坐标的上方向能通行
				pathArr[NearPoint.row][NearPoint.col].isFind = true;//当前点改为已访问
				MyPoint temp = { NearPoint.row, NearPoint.col - 1 };
				ms.push(temp);//压入这个坐标
				NearPoint = temp;//把这个上方向可通行的点赋值给辅助点，进行下一次的搜索
			}
			break;
		case p_down:
			pathArr[NearPoint.row][NearPoint.col].dir = p_right;//当前路口的下一个方向标记出来
			if (IsMove(pathArr, NearPoint.row + 1, NearPoint.col))
			{
				//表示当前坐标的上方向能通行
				pathArr[NearPoint.row][NearPoint.col].isFind = true;//当前点改为已访问
				MyPoint temp = { NearPoint.row + 1, NearPoint.col };
				ms.push(temp);//压入这个坐标
				NearPoint = temp;//把这个上方向可通行的点赋值给辅助点，进行下一次的搜索
			}
			break;
		case p_right://最后一个方向，表示前面三个方向已经搜索完成
			if (IsMove(pathArr, NearPoint.row, NearPoint.col + 1))
			{
				//表示当前坐标的上方向能通行
				pathArr[NearPoint.row][NearPoint.col].isFind = true;//当前点改为已访问
				MyPoint temp = { NearPoint.row, NearPoint.col + 1 };
				ms.push(temp);//压入这个坐标
				NearPoint = temp;//把这个上方向可通行的点赋值给辅助点，进行下一次的搜索
			}
			else
			{
				//表示当前路口所有方向都不通，要准备退栈
				MyPoint tempPoint = ms.getTop();//得到退栈之前的栈顶元素
				pathArr[tempPoint.row][tempPoint.col].isFind = true;//要退出栈的这个元素也是已经访问过了
				ms.pop();
				if (!ms.empty())//如果栈不为空
					NearPoint = ms.getTop();//得到新的栈顶元素
			}
			break;
		}

		if (NearPoint.row == endPoint.row && NearPoint.col == endPoint.col)
			break;//找到终点
		if (ms.empty())
			break;//没有终点
	}
	if (ms.empty())
	{
		cout << "此停车位置不存在" << endl;
	}
	cout << "车位的路径：" << '[' << v.p.row << ',' << v.p.col << ']' << "☆为原点★为终点，导航如下↓" << endl;
	int m[MAP_ROW][MAP_COL];
	for (int i = 0; i < MAP_ROW; i++)
	{
		for (int j = 0; j < MAP_COL; j++)
		{
			m[i][j] = mapArr[i][j];
		}
	}
	int  x1=2, y1=4;
	while (!ms.empty())
	{
		MyPoint tempPoint = ms.getTop();    //取栈顶坐标
		x1 = tempPoint.row - x1, y1 = tempPoint.col - y1;
		if (x1 == 0 && y1 == 0)
		{
			m[tempPoint.row][tempPoint.col] = 2;
		}
		if (x1 == 1)
		{
			m[tempPoint.row][tempPoint.col] = 3;
		}
		if (x1 == -1)
		{
			m[tempPoint.row][tempPoint.col] = 4;
		}
		if (y1 == 1)
		{
			m[tempPoint.row][tempPoint.col] = 5;
		}
		if (y1 == -1)
		{
			m[tempPoint.row][tempPoint.col] = 6;
		}
		x1 = tempPoint.row,y1 = tempPoint.col;
		//printf("row = %d, col = %d\n", tempPoint.row, tempPoint.col);  输出每一步（检验）
		ms.pop();
	}
	m[v.p.row][v.p.col] = 2;
	m[v.sp.row][v.sp.col] = 7;
	//输出原点值（检验）
	//for (int i = 0; i < MAP_ROW; i++)
	//{
	//	for (int j = 0; j < MAP_COL; j++)
	//	{
	//		cout << m[i][j] << "\t";
	//	}
	//	cout << endl << endl;
	//}
	//输出导航路径
	for (int i = 0; i < MAP_ROW; i++)
	{
		for (int j = 0; j < MAP_COL; j++)
		{
			if (m[i][j] == 2)
			{
				cout << "★" << "\t";
			}
			else if (m[i][j] == 3)
			{
				cout << "↑" << "\t";
			}
			else if (m[i][j] == 4)
			{
				cout << "↓" << "\t";
			}
			else if (m[i][j] == 5)
			{
				cout << "←" << "\t";
			}
			else if (m[i][j] == 6)
			{
				cout << "→" << "\t";
			}
			else if (m[i][j] == 7)
			{
				cout << "☆" << "\t";
			}
			else
			{
				cout << m[i][j] << "\t";
			}
			
		}
		cout << endl<<endl;
	}

}

//车子入停车场
void car_meloading(LinkNode<Veh>& mst, int map[][MAP_COL], LinkNode<Veh>& ms, IsPoint p[])
{
	int pt;  //保存要停车的停车点
	Veh v;
	while (true)
	{
		system("cls");
		cout << "请输入车牌" << endl;
		cin >> v.VehLicense;
		if (!mst.ListFind_only(v.VehLicense))
		{
			break;
		}
		cout << "输入的车牌重复，请重新输入";
		system("pause");
	}

	cout << "请输入车辆种类" << endl;
	cin >> v.VehKind;
	while (true)
	{
		cout << "停车场地图↓" << endl;
		display_map(map); //显示停车场地图
		cout << "请输入目前位置（行列用空格隔开）";
		cin >> v.sp.row >> v.sp.col;
		system("cls");
		if (0 < v.sp.col < 10 && 0 < v.sp.row < 10 && map[v.sp.row][v.sp.col] != 1)
		{
			break;
		}
		cout << "输入的位置不存在或者不能为存在点";
		system("pause");
	}
	int t[3] = {25,26,27}; //替换中介量
	int n=0;
	int flag;
	while (n!=3)
	{
		int min = 999;
		for (int i = 0; i < 23; i++)
		{
			flag = 1;
			for (int k = 0; k < 3; k++)
			{
				if (t[k] == i)
				flag = 0;
			}
			if (flag==1)
			{
				if (min > sqrt((v.sp.col - p[i].p.col) * (v.sp.col - p[i].p.col) + (v.sp.row - p[i].p.row) * (v.sp.row - p[i].p.row)))
				{
					min = sqrt((v.sp.col - p[i].p.col) * (v.sp.col - p[i].p.col) + (v.sp.row - p[i].p.row) * (v.sp.row - p[i].p.row));
					t[n] = i;
				}
			}
		}
		n++;
	}

	while (true)
	{
		system("cls");
		cout << "可放车的停车位" << endl;
		display_park(p);//显示没有被用的车位
		cout << "推荐停车位:"<<t[0]+1<<','<<t[1]+1<<','<<t[2]+1<<"号停车位置"<<endl;
		cout << "请输入你想要的停的车位:" << endl;
		cin >> pt;
		if (!((pt < 1 && pt>23) || p[pt - 1].i == true))
		{
			break;
		}
		cout << "输入的停车位不存在或已经被使用,请重新录入系统" << endl;
		system("pause");
	}
	system("cls");
	v.p = p[pt-1].p;
	time_t now;  //声明time_t类型变量
	time(&now);      //获取系统日期和时间
	localtime_s(&v.StarTime, &now);   //获取当地日期和时间
	find_car(map, v, p);
	p[pt - 1].i = true;
	cout <<"车子入库时间：" << v.StarTime.tm_year + 1900 << "年" << v.StarTime.tm_mon + 1 << "月" << v.StarTime.tm_mday << "日" << v.StarTime.tm_hour << "时" << v.StarTime.tm_min << "分" << endl;
	ms.inset(v);
} 

int main()
{
	IsPoint park[23];
	int n=1;
	int mapArr[MAP_ROW][MAP_COL];
	string s;
	Veh  v;
	time_t now;  //声明time_t类型变量
	time(&now);      //获取系统日期和时间
	Load_Map(mapArr,park);  //通过文件载入地图信息
	LinkNode<Veh>ms1;
	Vehicle<Veh>ms2;
	while (n)
	{
		mainmuen();
		cin >> n;
		switch (n)
		{
		case 1:
			car_meloading(ms1,mapArr,ms1,park);     //将车放入停车场（压入链表）
			break;
		case 2:
			cout << "车库内已经有的车子:" << endl;
			ms1.displist();
			cout << "请输入出库的车子车牌:" ;
			cin >> s;
			cout << endl;
			if (ms1.ListFind(s, v))   //取出并清车位
			{
				for (int i = 0; i < 23; i++)
				{
					if (v.p.row == park[i].p.row&& v.p.col == park[i].p.col)
					{
						park[i].i = false;   //出停车场的车子让停车位空出来。
					}
				}
				localtime_s(&v.EndTime, &now);
				cout << "花费" << ms2.Time_spent(v) << "元" << endl; 
			}
			else
			{
				cout << "没有找到这个车子" << endl;
			}
			ms1.displist();
			break;
		case 3:display_park(park); break;
		case 4:ms1.displist(); break;
		case 5:exit(0);
		case 6: return 0;
		default:
			cout << "输入有误，请重新输入"<<endl;
			break;
		}
		system("pause");
		system("cls");
	}
	return 0;
}
