#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define  max 10
typedef struct
{
	char name[10]; //��������
	char xh[10];//ѧ�Ŷ���
	char bj[10];//�༶
	int age;//����
	int fs[10];//10�η���
	int   zf;//10�η������ܷ�
}elemtype;//�ṹ��
typedef struct lnode
{
	elemtype data;
	struct lnode* next;
}linklist;//����ڵ�
void initlist(linklist*& l)
{
	l = (linklist*)malloc(sizeof(linklist));
	l->next = NULL;
}//��ʼ�����Ա�

void createlist(linklist*& l, elemtype a[], int n)
{
	linklist* s, * r;
	int i;
	l = (linklist*)malloc(sizeof(linklist));
	r = l;
	for (i = 0; i < n; i++)
	{
		s = (linklist*)malloc(sizeof(linklist));
		s->data = a[i];
		for (int j = 0; j < 10; ++j)
		{
			s->data.zf += a[i].fs[j];
		}
		r->next = s;
		r = s;
	}
	r->next = NULL;
}//����ͷ���
void displist(linklist* l)//ѧ����Ϣ���
{
	linklist* p = l->next;
	printf("ȫ��ѧ������Ϣͳ������\n");
	printf("ѧ��������  ѧ��  �༶  ����  ��ѧ����ʮ�γɼ�Ϊ��0����û�гɼ���");
	printf("\n");
	while (p != NULL)
	{
		printf("%-10s", p->data.name);
		printf("%-10s", p->data.xh);
		printf("%-10s", p->data.bj);
		printf("%-5d", p->data.age);
		printf("%3d", p->data.zf);
		for (int i = 0; i < 10; i++)
		{
			printf("%3d", p->data.fs[i]);
			//	printf("   ");
		}
		printf("\n");
		p = p->next;
	}
	printf("\n");

}

void selsesort(linklist*& l)
{
	linklist* p = l->next, * q, * min;
	elemtype t;
	min = p;
	while (p != NULL)
	{
		q = p->next;
		while (q != NULL)
		{
			if (strcmp(min->data.xh, q->data.xh) > 0)
			{
				min = q;
			}
			q = q->next;
		}
		if (p != min)
		{
			t = p->data;
			p->data = min->data;
			min->data = t;
		}
		p = p->next;
	}
}
void insertsort(linklist*& l)
{
	linklist* p = l->next, * q, * postq, * pre;		
	if (p == NULL)  //������Ϊ�յ�ʱ�򷵻�
	{
		return;
	}
	q = p->next;
	p->next = NULL;   //��ԭ���������г���������
	while (q != NULL)
	{
		postq = q->next;  //�ȱ���ڶ����ڵ��
		pre = l;
		p = l->next;
		while (p != NULL)
		{
			if (strcmp(p->data.xh, q->data.xh) > 0)
				break;
			pre = p;
			p = p->next;
		}
		q->next = pre->next;
		pre->next = q;
		q = postq;
	}
}
void main()
{
	int select = 0, i = 1;
	linklist* l;
	elemtype a[3] = { { "��","123","1��",18,9,9,9,7,9,5,4,3,2 },
	{ "��","223","2��",19,10,10,10,10,10,6,4,3,1,7 },
	{ "��","113","1��",20,11,4,5,4,5,6,7,8,9,10 } };//��ʼ����
	createlist(l, a, 3);
	displist(l);
	//selsesort(l);
	insertsort(l);
	printf("�޸Ĺ���");
	displist(l);
}
