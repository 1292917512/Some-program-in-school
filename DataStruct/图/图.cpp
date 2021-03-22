#include<stdio.h>
#include<stdlib.h>
//�ڽӾ���ṹ
#define INF 999999   //�����
#define MVNum 100                       	//��󶥵��� 
typedef char VerTexType;              	//���趥�����������Ϊ�ַ��� 

typedef struct {
	VerTexType vexs[MVNum];            		//����� 
	int arcs[MVNum][MVNum];      	            //�ڽӾ��� 
	int vexnum, arcnum;
                		//ͼ�ĵ�ǰ�����ͱ��� 
}AMGraph;

//��������ͼ
void Create(AMGraph* G)
{
	int i, j, k;
	printf("�����붥�����ͱ���:\n");
	scanf_s("%d%d", &G->vexnum, &G->arcnum);
	fflush(stdin);
	for (i = 0; i < G->vexnum; i++)     //���������
	{
		printf("\n��%d�����㣺", i);
		scanf_s("%c", &G->vexs[i]);
		getchar();
	}
	for (i = 0; i < G->vexnum; i++)   //�����ʼ�� 
		for (j = 0; j < G->vexnum; j++)
			G->arcs[i][j] = 0;

	for (k = 0; k < G->arcnum; k++)
	{
		printf("����ߣ�Vi,Vj�����±�i��j(�ո����)��");
		scanf_s("%d%d", &i, &j);
		G->arcs[i][j] = 1;
		G->arcs[j][i] = G->arcs[i][j];
	}
}
//����ڽӾ���
void Output(AMGraph* G)
{
	int i, j, count = 0;
	for (i = 0; i < G->vexnum; i++)
		printf("\t%c", G->vexs[i]);
	printf("\n");
	for (i = 0; i < G->vexnum; i++)
	{
		printf("%4c", G->vexs[i]);
		for (j = 0; j < G->vexnum; j++)
		{
			printf("\t%d", G->arcs[i][j]);
			count++;
			if (count % G->vexnum == 0)
				printf("\n");
		}
	}
}
/*�ǵ�ǰ�������Ķ��㼯��ΪS  */
/*δʹ�õĶ��㼯��ΪV        */
/* ��ʼ��Ϊ�±�Ϊ0�Ķ���    */

void Prim(AMGraph* G)
{
	//�ǵ�ǰ�������Ľڵ㼯��ΪS
	//δʹ�õĽڵ���ΪV
	//��ʼ���±�Ϊ0
	int flag[MVNum];    //���ĳ�����Ƿ���S��
	int nearest[MVNum];  //��¼V��ÿ���㵽S���ڽӵ����̱�Ȩֵ
	int adj[MVNum];      //��¼��V��ÿ�������ڽӽ�������±�ֵ
	int i, j, min;

	for (i = 0; i < G->vexnum; ++i) //��ʼ������
		flag[i] = 0;

	flag[0] = 1;  //��ʼ�����S��

	for (i = 1; i < G->vexnum; ++i)
	{
		nearest[i] = G->arcs[0][i];
		adj[i] = 0;
	}
	int count = G->vexnum;
	printf("��ͼ����С��������:\n");
	while (--count)
	{
		min = INF;
		j = 0;
		for (i = 0; i < G->vexnum; ++i)
		{
			if (!flag[i] && nearest[i] < min)
			{
				min = nearest[i];
				j = i;
			}
		}

		printf("(%c,%c)Ȩֵ�ǣ�%d\n", G->vexs[adj[j]], G->vexs[j], G->arcs[j][adj[j]]);
		flag[j] = 1;   //�¶������S��

		for (i = 0; i < G->vexnum; ++i)
		{
			if (!flag[i] && G->arcs[i][j] < nearest[i])
			{
				nearest[i] = G->arcs[i][j];   //��������
				adj[i] = j;   //������������±�
			}
		}
	}
}
int main()
{
	AMGraph G;
	Create(&G);
	printf("�ڽӾ����������£�\n");
	Output(&G);
	//Prim(&G);
	return 0;
}