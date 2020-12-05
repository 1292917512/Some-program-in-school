#include<iostream>
#include<fstream>
using namespace std;

#define PR_NUM 5   //进程数
#define RE_NUM 4	//资源数

typedef struct Process   //将进程定义为结构体
{
	char id[10];
	bool flag;
	int Request[RE_NUM];
}PR;

typedef struct Resoure
{
	char id[10];
	int Available;
}RE;

static int Max_Matrix[PR_NUM][RE_NUM];
//=
//{
//	4,6,3,8,
//	3,3,5,2,
//	6,6,0,9,
//	3,4,8,7,
//	4,3,2,5
//};
static int Use_Matrix[PR_NUM][RE_NUM];
//=
//{
//	1,1,0,1,
//	2,2,4,1,
//	0,5,0,1,
//	1,1,1,5,
//	2,0,2,2,
//
//};

//函数声明部分
int Process_inti(PR(&P)[PR_NUM]);
void input(PR(&P)[PR_NUM], RE(&R)[RE_NUM]);
void DJSTR(PR(&P)[PR_NUM], RE(&R)[RE_NUM]);
void input_file(PR(&P)[PR_NUM], RE(&R)[RE_NUM]);
void is_ok(PR(&P)[PR_NUM]);

//主函数
int main()
{
	PR p[PR_NUM];
	RE r[RE_NUM];
	input(p, r);  //手动输入数据
	//input_file(p, r);  //文件读入数据
	Process_inti(p);
	cout << "进程 " << "最大需求矩阵	" << "分配矩阵   " << "    需求矩阵 " << "	可用矩阵" << endl;
	DJSTR(p, r);
	is_ok(p);
	int c = getchar();
	return 0;
}

void is_ok(PR(&P)[PR_NUM])
{
	bool flag = true;
	for (size_t i = 0; i < PR_NUM; i++)
	{
		if (P[i].flag == false)
			flag = false;
	}
	if (flag == false)
	{
		cout << "此项目不安全" << endl;
		return;
	}
	cout << "此项目安全" << endl;
	return;
}


//手动输入
void input(PR(&P)[PR_NUM],RE(&R)[RE_NUM])
{
	cout<<"银行家算法输入:\n请输入进程：";
	for (size_t i = 0; i < PR_NUM; i++)
	{
		cin >> P[i].id;
	}
	cout<<"请输入资源种类:";
	for (size_t i = 0; i < RE_NUM; i++)
	{
		cin>>R[i].id;
	}
	cout << "请输入资源数量";
	for (size_t i = 0; i < RE_NUM; i++)
	{
		cout << R[i].id << " ";
	}
	cout << "数量" << endl;
	for (size_t i = 0; i < RE_NUM; i++)
	{
		cin>>R[i].Available;
	}
	cout << "请输入最大需求矩阵Max" << endl;
	for (size_t i = 0; i <PR_NUM; i++)
	{
		for (size_t j = 0; j < RE_NUM; j++)
		{
			cin>>Max_Matrix[i][j];
		}
	}
	cout << "请输入当前分配矩阵Used" << endl;
	for (size_t i = 0; i < PR_NUM; i++)
	{
		for (size_t j = 0; j < RE_NUM; j++)
		{
			cin>>Use_Matrix[i][j];
		}
	}

}


//文件读入
void input_file(PR(&P)[PR_NUM], RE(&R)[RE_NUM])
{

	ifstream outfile;
	char a[10];
	try
	{
		outfile.open("input.txt", ios::out | ios::in);
	}
	catch (exception)
	{
		cout << "fail to open file" << endl;
		exit(0);
	}
	for (size_t i = 0; i < PR_NUM; i++)
	{
		outfile>> P[i].id;
	}
	for (size_t i = 0; i < RE_NUM; i++)
	{
		outfile >> R[i].id;
	}
	for (size_t i = 0; i < RE_NUM; i++)
	{
		cout << R[i].id << " ";
	}
	cout << "数量" << endl;
	for (size_t i = 0; i < RE_NUM; i++)
	{
		outfile >> R[i].Available;
	}
	cout << "请输入最大需求矩阵Max" << endl;
	for (size_t i = 0; i < PR_NUM; i++)
	{
		for (size_t j = 0; j < RE_NUM; j++)
		{
			outfile >> Max_Matrix[i][j];
		}
	}
	cout << "请输入当前分配矩阵Used" << endl;
	for (size_t i = 0; i < PR_NUM; i++)
	{
		for (size_t j = 0; j < RE_NUM; j++)
		{
			outfile >> Use_Matrix[i][j];
		}
	}
	outfile.close();
}



void DJSTR(PR(&P)[PR_NUM], RE(&R)[RE_NUM])
{
	int i, j, k;
	int count;
	for (i = 0; i < PR_NUM; ++i)
	{
		for (j = 0; j < PR_NUM; ++j)
		{
			count = 0;
			for (k = 0; k < RE_NUM; ++k)
			{
				if (P[j].flag == false && P[j].Request[k] <= R[k].Available)
					count++;
			}
			if (count == RE_NUM)
			{
				for (k = 0; k < RE_NUM; ++k)
				{
					R[k].Available += Use_Matrix[j][k];
				}
				P[j].flag = true;
				//cout << "进程" << P[j].id << "已经结束" << endl;
				cout << P[j].id;
				cout << "	";
				for (size_t i = 0; i < RE_NUM; i++)
				{
					cout << Max_Matrix[j][i] << " ";
				}
				cout << "	";
				for (size_t i = 0; i < RE_NUM; i++)
				{
					cout << Use_Matrix[j][i] << " ";
				}
				cout << "	";
				for (size_t i = 0; i < RE_NUM; i++)
				{
					cout << P[j].Request[i] << " ";
				}
				cout << "	";
				for (size_t i = 0; i < RE_NUM; i++)
				{
					cout << R[i].Available << " ";
				}
				cout << endl;
				break;
			}
		}
	}
}

int Process_inti(PR(&P)[PR_NUM])
{
	int i, j;
	for (i = 0; i < PR_NUM; ++i)
	{
		P[i].flag = false;
		for (j = 0; j < RE_NUM; ++j)
		{
			P[i].Request[j] = Max_Matrix[i][j] - Use_Matrix[i][j];  //需求矩阵的建立

		}
	}
	return 0;
}