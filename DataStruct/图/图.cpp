#include<stdio.h>
#include<stdlib.h>
//邻接矩阵结构
#define INF 999999   //无穷大
#define MVNum 100                       	//最大顶点数 
typedef char VerTexType;              	//假设顶点的数据类型为字符型 

typedef struct {
	VerTexType vexs[MVNum];            		//顶点表 
	int arcs[MVNum][MVNum];      	            //邻接矩阵 
	int vexnum, arcnum;
                		//图的当前点数和边数 
}AMGraph;

//构造无向图
void Create(AMGraph* G)
{
	int i, j, k;
	printf("请输入顶点数和边数:\n");
	scanf_s("%d%d", &G->vexnum, &G->arcnum);
	fflush(stdin);
	for (i = 0; i < G->vexnum; i++)     //建立顶点表
	{
		printf("\n第%d个顶点：", i);
		scanf_s("%c", &G->vexs[i]);
		getchar();
	}
	for (i = 0; i < G->vexnum; i++)   //矩阵初始化 
		for (j = 0; j < G->vexnum; j++)
			G->arcs[i][j] = 0;

	for (k = 0; k < G->arcnum; k++)
	{
		printf("输入边（Vi,Vj）的下标i和j(空格隔开)：");
		scanf_s("%d%d", &i, &j);
		G->arcs[i][j] = 1;
		G->arcs[j][i] = G->arcs[i][j];
	}
}
//输出邻接矩阵
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
/*记当前生成树的顶点集合为S  */
/*未使用的顶点集合为V        */
/* 起始点为下标为0的顶点    */

void Prim(AMGraph* G)
{
	//记当前生成树的节点集合为S
	//未使用的节点结合为V
	//起始点下标为0
	int flag[MVNum];    //标记某个点是否在S中
	int nearest[MVNum];  //记录V中每个点到S中邻接点的最短边权值
	int adj[MVNum];      //记录与V中每个点最邻接近顶点的下标值
	int i, j, min;

	for (i = 0; i < G->vexnum; ++i) //初始化集合
		flag[i] = 0;

	flag[0] = 1;  //初始点放入S中

	for (i = 1; i < G->vexnum; ++i)
	{
		nearest[i] = G->arcs[0][i];
		adj[i] = 0;
	}
	int count = G->vexnum;
	printf("此图的最小生成树是:\n");
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

		printf("(%c,%c)权值是：%d\n", G->vexs[adj[j]], G->vexs[j], G->arcs[j][adj[j]]);
		flag[j] = 1;   //新顶点放入S中

		for (i = 0; i < G->vexnum; ++i)
		{
			if (!flag[i] && G->arcs[i][j] < nearest[i])
			{
				nearest[i] = G->arcs[i][j];   //调整距离
				adj[i] = j;   //调整最近顶点下标
			}
		}
	}
}
int main()
{
	AMGraph G;
	Create(&G);
	printf("邻接矩阵数据如下：\n");
	Output(&G);
	//Prim(&G);
	return 0;
}