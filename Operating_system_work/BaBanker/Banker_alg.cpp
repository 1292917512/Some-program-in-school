#include<iostream>
#include<fstream>
using namespace std;

#define PR_NUM 5   //������
#define RE_NUM 4	//��Դ��

typedef struct Process   //�����̶���Ϊ�ṹ��
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

//������������
int Process_inti(PR(&P)[PR_NUM]);
void input(PR(&P)[PR_NUM], RE(&R)[RE_NUM]);
void DJSTR(PR(&P)[PR_NUM], RE(&R)[RE_NUM]);
void input_file(PR(&P)[PR_NUM], RE(&R)[RE_NUM]);
void is_ok(PR(&P)[PR_NUM]);

//������
int main()
{
	PR p[PR_NUM];
	RE r[RE_NUM];
	input(p, r);  //�ֶ���������
	//input_file(p, r);  //�ļ���������
	Process_inti(p);
	cout << "���� " << "����������	" << "�������   " << "    ������� " << "	���þ���" << endl;
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
		cout << "����Ŀ����ȫ" << endl;
		return;
	}
	cout << "����Ŀ��ȫ" << endl;
	return;
}


//�ֶ�����
void input(PR(&P)[PR_NUM],RE(&R)[RE_NUM])
{
	cout<<"���м��㷨����:\n��������̣�";
	for (size_t i = 0; i < PR_NUM; i++)
	{
		cin >> P[i].id;
	}
	cout<<"��������Դ����:";
	for (size_t i = 0; i < RE_NUM; i++)
	{
		cin>>R[i].id;
	}
	cout << "��������Դ����";
	for (size_t i = 0; i < RE_NUM; i++)
	{
		cout << R[i].id << " ";
	}
	cout << "����" << endl;
	for (size_t i = 0; i < RE_NUM; i++)
	{
		cin>>R[i].Available;
	}
	cout << "����������������Max" << endl;
	for (size_t i = 0; i <PR_NUM; i++)
	{
		for (size_t j = 0; j < RE_NUM; j++)
		{
			cin>>Max_Matrix[i][j];
		}
	}
	cout << "�����뵱ǰ�������Used" << endl;
	for (size_t i = 0; i < PR_NUM; i++)
	{
		for (size_t j = 0; j < RE_NUM; j++)
		{
			cin>>Use_Matrix[i][j];
		}
	}

}


//�ļ�����
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
	cout << "����" << endl;
	for (size_t i = 0; i < RE_NUM; i++)
	{
		outfile >> R[i].Available;
	}
	cout << "����������������Max" << endl;
	for (size_t i = 0; i < PR_NUM; i++)
	{
		for (size_t j = 0; j < RE_NUM; j++)
		{
			outfile >> Max_Matrix[i][j];
		}
	}
	cout << "�����뵱ǰ�������Used" << endl;
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
				//cout << "����" << P[j].id << "�Ѿ�����" << endl;
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
			P[i].Request[j] = Max_Matrix[i][j] - Use_Matrix[i][j];  //�������Ľ���

		}
	}
	return 0;
}