#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define  max 10
typedef struct
{
	char name[10]; //姓名定义
	char xh[10];//学号定义
	char bj[10];//班级
	int age;//年龄
	int fs[10];//10次分数
	int   zf;//10次分数的总分
}elemtype;//结构体
typedef struct lnode
{
	elemtype data;
	struct lnode* next;
}linklist;//定义节点
void initlist(linklist*& l)
{
	l = (linklist*)malloc(sizeof(linklist));
	l->next = NULL;
}//初始化线性表

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
}//创建头结点
void displist(linklist* l)//学生信息输出
{
	linklist* p = l->next;
	printf("全部学生的信息统计如下\n");
	printf("学生的名字  学号  班级  年龄  该学生的十次成绩为（0代表没有成绩）");
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
	if (p == NULL)  //当链表为空的时候返回
	{
		return;
	}
	q = p->next;
	p->next = NULL;   //把原来的链表切成两个部分
	while (q != NULL)
	{
		postq = q->next;  //先保存第二个节点的
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
	elemtype a[3] = { { "马","123","1班",18,9,9,9,7,9,5,4,3,2 },
	{ "孙","223","2班",19,10,10,10,10,10,6,4,3,1,7 },
	{ "柳","113","1班",20,11,4,5,4,5,6,7,8,9,10 } };//初始化的
	createlist(l, a, 3);
	displist(l);
	//selsesort(l);
	insertsort(l);
	printf("修改过后");
	displist(l);
}
