#pragma once
#include"CMystack.h"
#include"CMylist.h" 
#include"Vehicle.h"
#include<stdlib.h>
#include <time.h>
#include<math.h>
#include<fstream>
#include<string>
#define MONEY 10  //ͣ������
#define MAP_ROW 10   //��ͼ��
#define MAP_COL 10   //��ͼ��

typedef struct
{
	string VehLicense;
	string VehKind;
	struct tm StarTime;
	struct tm EndTime;
	MyPoint sp;
	MyPoint p;
}Veh;
//�������з����ö��
enum Path_Dir { p_up, p_down, p_left, p_right };


//׼��һ���������飨1����Դ��ͼ���鲻�ܱ䣻2������Դ��ͼҪ�����ݱ�ǣ�
struct PathNode
{
	int val;//����ԭʼ��Դ��·������Ϣ
	Path_Dir dir; //��ǰ·����ķ�����
	bool isFind;//��ǰ·�����Ƿ񱻷��ʹ�
};
	

//��¼�ᳵλ���Ƿ����
struct IsPoint  
{
	MyPoint p;
	bool i;
};

void mainmuen()
{
	cout << "\t\t\t\t\tϵͳ��ѡ����\t\t" << endl;
	cout << "\t\t\t\t\t1��������ͣ����\t\t" << endl;
	cout << "\t\t\t\t\t2��������ͣ����\t\t" << endl;
	cout << "\t\t\t\t\t3����ʾͣ����ʣ��ͣ��λ\t\t" << endl;
	cout << "\t\t\t\t\t4��������Ϣ��ʾ\t\t" << endl;
	cout << "\t\t\t\t\t5���˳�ϵͳ\t\t" << endl;
}
