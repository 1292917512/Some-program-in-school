#include<stdio.h>
#include<malloc.h>
#define MAX 20
typedef struct BTNode {       /*节点结构声明*/
	char data;               /*节点数据*/
	struct BTNode* lchild;
	struct BTNode* rchild;  /*指针*/
}*BiTree;

typedef struct
{
	BTNode* data[MAX];
	int front, rear;
}SqQueue;

bool InitSqueue(SqQueue *&q)  //队列初始化
{
	q = (SqQueue*)malloc(sizeof(SqQueue));
	q->front = 0;
	q->rear = 0;
	return true;
}

bool enQueue(SqQueue* &q,BiTree &n)   //进队操作
{
	if ((q->rear + 1) % MAX == q->front)
		return false;
	q->rear = (q->rear + 1) % MAX;
	q->data[q->rear] = n;
}

bool deQueue(SqQueue*& q, BiTree& n)   //出队操作
{
	if (q->front == q->rear)
		return false;
	q->front = (q->front + 1) % MAX;
	n = q->data[q->front];
	return true;
}

bool QueueEmpty(SqQueue* q)  //判断队列为空
{
	if (q->front == q->rear)
		return true;
	return false;
}

void createBiTree(BiTree* t) { /* 先序遍历创建二叉树*/
	char s;
	BiTree q;
	printf("\nplease input data:(exit for #)");
	s = getchar();
	if (s == '#') { *t = NULL; return; }
	q = (BiTree)malloc(sizeof(struct BTNode));
	if (q == NULL) { printf("Memory alloc failure!"); return; }
	q->data = s;
	*t = q;
	createBiTree(&q->lchild); /*递归建立左子树*/
	createBiTree(&q->rchild); /*递归建立右子树*/
}

void PreOrder(BiTree p) {  /* 先序遍历二叉树*/
	if (p != NULL) {
		printf("%c", p->data);
		PreOrder(p->lchild);
		PreOrder(p->rchild);
	}
}
void InOrder(BiTree p) {  /* 中序遍历二叉树*/
	if (p != NULL) {
		InOrder(p->lchild);
		printf("%c", p->data);
		InOrder(p->rchild);
	}
}
void PostOrder(BiTree p) {  /* 后序遍历二叉树*/
	if (p != NULL) {
		PostOrder(p->lchild);
		PostOrder(p->rchild);
		printf("%c", p->data);
	}
}

void LevelOrder(BiTree p)  //用队列的层次遍历
{
	BiTree b;
	SqQueue* qu;
	InitSqueue(qu);
	enQueue(qu, p);
	while (!QueueEmpty)
	{
		deQueue(qu, b);
		printf("%c", b->data);
		if (b->lchild != NULL)
		{
			deQueue(qu, b->lchild);
		}
		if (b->rchild != NULL)
		{
			deQueue(qu, b->rchild);
		}
	}
	printf("\n");
}



void Preorder_n(BiTree p) { /*先序遍历的非递归算法*/
	BiTree stack[MAX], q;
	int top = 0, i;
	for (i = 0; i < MAX; i++) stack[i] = NULL;/*初始化栈*/
	q = p;
	while (q != NULL) {
		printf("%c", q->data);
		if (q->rchild != NULL) stack[top++] = q->rchild;
		if (q->lchild != NULL) q = q->lchild;
		else
			if (top > 0) q = stack[--top];
			else q = NULL;
	}
}

int count(BiTree t) //总节点数量
{
	if (t == NULL)
		return 0;
	return count(t->lchild) + count(t->rchild) + 1;
}

int leaves(BiTree t) //叶节点数量
{
	if (t == NULL)
		return 0;
	if (t->lchild == NULL&&t->rchild==NULL)
		return 1;
	return leaves(t->lchild) + leaves(t->rchild);
}


void release(BiTree t) { /*释放二叉树空间*/
	if (t != NULL) {
		release(t->lchild);
		release(t->rchild);
		free(t);
	}
}

int main() {
	BiTree t = NULL;
	createBiTree(&t);
	printf("\n\nPreOrder the tree is:");
	PreOrder(t);
	printf("\n\nInOrder the tree is:");
	InOrder(t);
	printf("\n\nPostOrder the tree is:");
	PostOrder(t);
	printf("\n\n先序遍历序列（非递归）:");
	Preorder_n(t);
	printf("\n总节点的数量为%d\n",count(t));
	printf("叶子节点的数量%d\n", leaves(t));

	release(t);
	return 0;
}