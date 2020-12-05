#include<iostream>
#include<vector>
#include<stdlib.h>
#include<fstream>
#define BLOCK_NUM 3
using namespace std;


typedef struct black
{
	int B[BLOCK_NUM];
	int point;
}B;


void init_file(vector<int>& q, B& b);
void OPT(vector<int>& q, B& b);
int main()
{
	int bznum;
	vector<int> q;   //序列数组
	B b; //内存块
	cout<<"请输入访问序列：";
	init_file(q,b);
	OPT(q, b);
	cin.get();
	return 0;
}


void init_file(vector<int> &q,B &b)
{
	char a[5];
	ifstream outfile;
	try
	{
		outfile.open("input.txt", ios::out | ios::in); 
	}
	catch (exception)
	{
		cout << "fail to open file" << endl;
		exit(0);
	}
	while((outfile>>a))
	{
		//cout<<a<<endl;
		q.push_back(atoi(a));
	}
	b.point=0;
	for(int i=0;i<BLOCK_NUM;++i)
	{
		b.B[i]=-1;
	}
	cout << "<<导入成功" << endl;
}

void OPT(vector<int>& q, B& b)
{
	cout << "已进入OPT\n";
	int flag;
	for (int i = 0; i < q.size(); ++i)
	{
		flag = 0;
		int isfar_point;
		cout << q[i] << "  ";
		if (b.B[b.point] == -1)
		{
			b.B[b.point] = q[i];
			b.point = (b.point + 1) % BLOCK_NUM;
		}
		else
		{
			for (int k = 0; k < BLOCK_NUM; ++k)
			{
				if (q[i] == b.B[k])
				{
					flag = 1;
				}
			}
			if (flag == 0)
			{
				isfar_point = 0;
				for (size_t k = 0; k < BLOCK_NUM; ++k)
				{
					for (int j = i + 1; j < q.size(); ++j)
					{
						if (b.B[k] == q[j])
						{
							if (j > isfar_point)
							{
								isfar_point = j;
								b.point = k;
								break;
							}
							break;
						}
						if (j == q.size() - 1)
						{
							b.point = k;
							break;
						}
					}
				}
				b.B[b.point] = q[i];
			}
		}
		for (size_t i = 0; i < BLOCK_NUM; i++)
		{
			if (b.B[i] == -1)
				cout << "   ";
			else
			{
				cout << b.B[i] << "  ";
			}

		}
		cout << endl;
	}


}