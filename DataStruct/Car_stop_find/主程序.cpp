#include"��ͷ.h"

//ͣ������ʾ
void display_park(IsPoint p[])
{
	int j = 1;
	for (int i = 0; i < 23; i++)
	{
		if (p[i].i == false)
		{
			cout << i + 1 << "�ų�λ" << '[' << p[i].p.row << ',' << p[i].p.col << ']'<<'\t';
			if (j++ % 4 == 0)
			{
				cout << endl;
			}
		}
	}
	cout << endl;
}

//��ͼ���غ���
bool Load_Map(int map[][MAP_COL],IsPoint p[])
{
	//map[MAP_ROW][MAP_COL];
	fstream infile("����/map.txt");
	if (!infile.is_open())
	{
		return false;
	}
	for (int i = 0; i < MAP_ROW; ++i)
	{
		for (int j = 0; j < MAP_COL; ++j)
			map[i][j] = int(infile.get() - 48);  //�ַ�ת��Ϊint  ascii-48���ڶ�Ӧ����.
	}
	int i=0;
	while (i<23)
	{

		p[i].p.row = int(infile.get() - 48);
		p[i].p.col = int(infile.get() - 48);
		p[i].i = false;
		/*cout << '[' << p[i].p.row << ',' << p[i].p.col <<']'<< endl;*/  //�ж����������
		++i;
	}
	//cout << "�ļ���ȡ���" << endl;
	infile.close();
	return true;
}

//׼��һ�������������жϲ����������Ƿ����ͨ��
bool IsMove(PathNode p[][MAP_COL], int row, int col)
{
	if (row < 0 || row >= MAP_ROW || col < 0 || col >= MAP_COL)
		return false;//���Խ�磬����Ҫ����λ�õ��ж�
	if (p[row][col].val != 0 || p[row][col].isFind == true)
		return false;//��ʾ��ǰ���е�Ԫ��Ҫô���ϰ���Ҫô�Ѿ������ʹ�������ͨ��
	return true;
}

//�ж������Ƿ�����������������
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

//Ѱ�ҳ���λ��
void find_car(int mapArr[][MAP_COL],Veh v,IsPoint pk[])
{
	//����һ�ݸ����ĵ�ͼ
	PathNode pathArr[MAP_ROW][MAP_COL];
	for (int i = 0; i < MAP_ROW; ++i)
	{
		for (int j = 0; j < MAP_COL; ++j)
		{
			pathArr[i][j].val = mapArr[i][j];
			pathArr[i][j].isFind = false;//��ʾ��ͼ�е�ÿһ���ڵ㶼û�б����ʹ�
			pathArr[i][j].dir = p_up;//��ʾ����ͼ�е�ÿһ���ڵ㶼�趨һ����ʼ����
		}
	}
	for (int i = 0; i < 23; ++i)
	{
		pathArr[pk[i].p.row][pk[i].p.col].isFind = pk[i].i;
	}

	MyPoint beginPoint = v.sp; //���忪ʼλ��
	MyPoint endPoint = v.p;
	//׼��һ�����������������ͨ��·����
	CMyStack<MyPoint> ms;
	ms.push(beginPoint);//�����ѹ�뵽�����У��������Һ����Ľ��

	//׼��һ����������㣬�������ж���һ����ͨ��λ��
	MyPoint NearPoint = beginPoint;//��������Ϊ��㣬Ȼ��ͨ������趨�ķ��������ܱ�·����������

	//��ʼѰ·
	while (true)//�޷�ȷ��ѭ������
	{
		switch (pathArr[NearPoint.row][NearPoint.col].dir)//�жϵ�ǰ����ڸ����������趨�ķ���
		{
		case p_up:
			//if (pathArr[NearPoint.row - 1][NearPoint.col].val == 0 &&	//��ʾ��ǰ�����һ��λ���ǿ�ͨ�е�
			//	pathArr[NearPoint.row - 1][NearPoint.col].isFind == false)//��ʾ��ǰ�����һ��λ����û�з��ʵ�
			pathArr[NearPoint.row][NearPoint.col].dir = p_left;//��ǰ·�ڵ���һ�������ǳ���
			if (IsMove(pathArr, NearPoint.row - 1, NearPoint.col))
			{
				//��ʾ��ǰ������Ϸ�����ͨ��
				pathArr[NearPoint.row][NearPoint.col].isFind = true;//��ǰ���Ϊ�ѷ���
				MyPoint temp = { NearPoint.row - 1, NearPoint.col };
				ms.push(temp);//ѹ���������
				NearPoint = temp;//������Ϸ����ͨ�еĵ㸳ֵ�������㣬������һ�ε�����
			}
			break;
		case p_left:
			pathArr[NearPoint.row][NearPoint.col].dir = p_down;//��ǰ·�ڵ���һ�������ǳ���
			if (IsMove(pathArr, NearPoint.row, NearPoint.col - 1))
			{
				//��ʾ��ǰ������Ϸ�����ͨ��
				pathArr[NearPoint.row][NearPoint.col].isFind = true;//��ǰ���Ϊ�ѷ���
				MyPoint temp = { NearPoint.row, NearPoint.col - 1 };
				ms.push(temp);//ѹ���������
				NearPoint = temp;//������Ϸ����ͨ�еĵ㸳ֵ�������㣬������һ�ε�����
			}
			break;
		case p_down:
			pathArr[NearPoint.row][NearPoint.col].dir = p_right;//��ǰ·�ڵ���һ�������ǳ���
			if (IsMove(pathArr, NearPoint.row + 1, NearPoint.col))
			{
				//��ʾ��ǰ������Ϸ�����ͨ��
				pathArr[NearPoint.row][NearPoint.col].isFind = true;//��ǰ���Ϊ�ѷ���
				MyPoint temp = { NearPoint.row + 1, NearPoint.col };
				ms.push(temp);//ѹ���������
				NearPoint = temp;//������Ϸ����ͨ�еĵ㸳ֵ�������㣬������һ�ε�����
			}
			break;
		case p_right://���һ�����򣬱�ʾǰ�����������Ѿ��������
			if (IsMove(pathArr, NearPoint.row, NearPoint.col + 1))
			{
				//��ʾ��ǰ������Ϸ�����ͨ��
				pathArr[NearPoint.row][NearPoint.col].isFind = true;//��ǰ���Ϊ�ѷ���
				MyPoint temp = { NearPoint.row, NearPoint.col + 1 };
				ms.push(temp);//ѹ���������
				NearPoint = temp;//������Ϸ����ͨ�еĵ㸳ֵ�������㣬������һ�ε�����
			}
			else
			{
				//��ʾ��ǰ·�����з��򶼲�ͨ��Ҫ׼����ջ
				MyPoint tempPoint = ms.getTop();//�õ���ջ֮ǰ��ջ��Ԫ��
				pathArr[tempPoint.row][tempPoint.col].isFind = true;//Ҫ�˳�ջ�����Ԫ��Ҳ���Ѿ����ʹ���
				ms.pop();
				if (!ms.empty())//���ջ��Ϊ��
					NearPoint = ms.getTop();//�õ��µ�ջ��Ԫ��
			}
			break;
		}

		if (NearPoint.row == endPoint.row && NearPoint.col == endPoint.col)
			break;//�ҵ��յ�
		if (ms.empty())
			break;//û���յ�
	}
	if (ms.empty())
	{
		cout << "��ͣ��λ�ò�����" << endl;
	}
	cout << "��λ��·����" << '[' << v.p.row << ',' << v.p.col << ']' << "��Ϊԭ���Ϊ�յ㣬�������¡�" << endl;
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
		MyPoint tempPoint = ms.getTop();    //ȡջ������
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
		//printf("row = %d, col = %d\n", tempPoint.row, tempPoint.col);  ���ÿһ�������飩
		ms.pop();
	}
	m[v.p.row][v.p.col] = 2;
	m[v.sp.row][v.sp.col] = 7;
	//���ԭ��ֵ�����飩
	//for (int i = 0; i < MAP_ROW; i++)
	//{
	//	for (int j = 0; j < MAP_COL; j++)
	//	{
	//		cout << m[i][j] << "\t";
	//	}
	//	cout << endl << endl;
	//}
	//�������·��
	for (int i = 0; i < MAP_ROW; i++)
	{
		for (int j = 0; j < MAP_COL; j++)
		{
			if (m[i][j] == 2)
			{
				cout << "��" << "\t";
			}
			else if (m[i][j] == 3)
			{
				cout << "��" << "\t";
			}
			else if (m[i][j] == 4)
			{
				cout << "��" << "\t";
			}
			else if (m[i][j] == 5)
			{
				cout << "��" << "\t";
			}
			else if (m[i][j] == 6)
			{
				cout << "��" << "\t";
			}
			else if (m[i][j] == 7)
			{
				cout << "��" << "\t";
			}
			else
			{
				cout << m[i][j] << "\t";
			}
			
		}
		cout << endl<<endl;
	}

}

//������ͣ����
void car_meloading(LinkNode<Veh>& mst, int map[][MAP_COL], LinkNode<Veh>& ms, IsPoint p[])
{
	int pt;  //����Ҫͣ����ͣ����
	Veh v;
	while (true)
	{
		system("cls");
		cout << "�����복��" << endl;
		cin >> v.VehLicense;
		if (!mst.ListFind_only(v.VehLicense))
		{
			break;
		}
		cout << "����ĳ����ظ�������������";
		system("pause");
	}

	cout << "�����복������" << endl;
	cin >> v.VehKind;
	while (true)
	{
		cout << "ͣ������ͼ��" << endl;
		display_map(map); //��ʾͣ������ͼ
		cout << "������Ŀǰλ�ã������ÿո������";
		cin >> v.sp.row >> v.sp.col;
		system("cls");
		if (0 < v.sp.col < 10 && 0 < v.sp.row < 10 && map[v.sp.row][v.sp.col] != 1)
		{
			break;
		}
		cout << "�����λ�ò����ڻ��߲���Ϊ���ڵ�";
		system("pause");
	}
	int t[3] = {25,26,27}; //�滻�н���
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
		cout << "�ɷų���ͣ��λ" << endl;
		display_park(p);//��ʾû�б��õĳ�λ
		cout << "�Ƽ�ͣ��λ:"<<t[0]+1<<','<<t[1]+1<<','<<t[2]+1<<"��ͣ��λ��"<<endl;
		cout << "����������Ҫ��ͣ�ĳ�λ:" << endl;
		cin >> pt;
		if (!((pt < 1 && pt>23) || p[pt - 1].i == true))
		{
			break;
		}
		cout << "�����ͣ��λ�����ڻ��Ѿ���ʹ��,������¼��ϵͳ" << endl;
		system("pause");
	}
	system("cls");
	v.p = p[pt-1].p;
	time_t now;  //����time_t���ͱ���
	time(&now);      //��ȡϵͳ���ں�ʱ��
	localtime_s(&v.StarTime, &now);   //��ȡ�������ں�ʱ��
	find_car(map, v, p);
	p[pt - 1].i = true;
	cout <<"�������ʱ�䣺" << v.StarTime.tm_year + 1900 << "��" << v.StarTime.tm_mon + 1 << "��" << v.StarTime.tm_mday << "��" << v.StarTime.tm_hour << "ʱ" << v.StarTime.tm_min << "��" << endl;
	ms.inset(v);
} 

int main()
{
	IsPoint park[23];
	int n=1;
	int mapArr[MAP_ROW][MAP_COL];
	string s;
	Veh  v;
	time_t now;  //����time_t���ͱ���
	time(&now);      //��ȡϵͳ���ں�ʱ��
	Load_Map(mapArr,park);  //ͨ���ļ������ͼ��Ϣ
	LinkNode<Veh>ms1;
	Vehicle<Veh>ms2;
	while (n)
	{
		mainmuen();
		cin >> n;
		switch (n)
		{
		case 1:
			car_meloading(ms1,mapArr,ms1,park);     //��������ͣ������ѹ������
			break;
		case 2:
			cout << "�������Ѿ��еĳ���:" << endl;
			ms1.displist();
			cout << "���������ĳ��ӳ���:" ;
			cin >> s;
			cout << endl;
			if (ms1.ListFind(s, v))   //ȡ�����峵λ
			{
				for (int i = 0; i < 23; i++)
				{
					if (v.p.row == park[i].p.row&& v.p.col == park[i].p.col)
					{
						park[i].i = false;   //��ͣ�����ĳ�����ͣ��λ�ճ�����
					}
				}
				localtime_s(&v.EndTime, &now);
				cout << "����" << ms2.Time_spent(v) << "Ԫ" << endl; 
			}
			else
			{
				cout << "û���ҵ��������" << endl;
			}
			ms1.displist();
			break;
		case 3:display_park(park); break;
		case 4:ms1.displist(); break;
		case 5:exit(0);
		case 6: return 0;
		default:
			cout << "������������������"<<endl;
			break;
		}
		system("pause");
		system("cls");
	}
	return 0;
}
