#include<stdio.h>
#include<malloc.h>
#define MAX 20
typedef struct BTNode {       /*�ڵ�ṹ����*/
	char data;               /*�ڵ�����*/
	struct BTNode* lchild;
	struct BTNode* rchild;  /*ָ��*/
}*BiTree;

typedef struct
{
	BTNode* data[MAX];
	int front, rear;
}SqQueue;

bool InitSqueue(SqQueue *&q)  //���г�ʼ��
{
	q = (SqQueue*)malloc(sizeof(SqQueue));
	q->front = 0;
	q->rear = 0;
	return true;
}

bool enQueue(SqQueue* &q,BiTree &n)   //���Ӳ���
{
	if ((q->rear + 1) % MAX == q->front)
		return false;
	q->rear = (q->rear + 1) % MAX;
	q->data[q->rear] = n;
}

bool deQueue(SqQueue*& q, BiTree& n)   //���Ӳ���
{
	if (q->front == q->rear)
		return false;
	q->front = (q->front + 1) % MAX;
	n = q->data[q->front];
	return true;
}

bool QueueEmpty(SqQueue* q)  //�ж϶���Ϊ��
{
	if (q->front == q->rear)
		return true;
	return false;
}

void createBiTree(BiTree* t) { /* �����������������*/
	char s;
	BiTree q;
	printf("\nplease input data:(exit for #)");
	s = getchar();
	if (s == '#') { *t = NULL; return; }
	q = (BiTree)malloc(sizeof(struct BTNode));
	if (q == NULL) { printf("Memory alloc failure!"); return; }
	q->data = s;
	*t = q;
	createBiTree(&q->lchild); /*�ݹ齨��������*/
	createBiTree(&q->rchild); /*�ݹ齨��������*/
}

void PreOrder(BiTree p) {  /* �������������*/
	if (p != NULL) {
		printf("%c", p->data);
		PreOrder(p->lchild);
		PreOrder(p->rchild);
	}
}
void InOrder(BiTree p) {  /* �������������*/
	if (p != NULL) {
		InOrder(p->lchild);
		printf("%c", p->data);
		InOrder(p->rchild);
	}
}
void PostOrder(BiTree p) {  /* �������������*/
	if (p != NULL) {
		PostOrder(p->lchild);
		PostOrder(p->rchild);
		printf("%c", p->data);
	}
}

void LevelOrder(BiTree p)  //�ö��еĲ�α���
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



void Preorder_n(BiTree p) { /*��������ķǵݹ��㷨*/
	BiTree stack[MAX], q;
	int top = 0, i;
	for (i = 0; i < MAX; i++) stack[i] = NULL;/*��ʼ��ջ*/
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

int count(BiTree t) //�ܽڵ�����
{
	if (t == NULL)
		return 0;
	return count(t->lchild) + count(t->rchild) + 1;
}

int leaves(BiTree t) //Ҷ�ڵ�����
{
	if (t == NULL)
		return 0;
	if (t->lchild == NULL&&t->rchild==NULL)
		return 1;
	return leaves(t->lchild) + leaves(t->rchild);
}


void release(BiTree t) { /*�ͷŶ������ռ�*/
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
	printf("\n\n����������У��ǵݹ飩:");
	Preorder_n(t);
	printf("\n�ܽڵ������Ϊ%d\n",count(t));
	printf("Ҷ�ӽڵ������%d\n", leaves(t));

	release(t);
	return 0;
}