/*--@程豪琪--*/
/*--2017/10/18--*/
/*--队列的指针实现，链式存储--*/

#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;

/*定义结点*/
typedef struct QNode
{
	ElemType elem;
	struct QNode *next;
}QNode,*QueuePtr;

/*定义队列*/
typedef struct LinkQueue
{
	QueuePtr front;
	QueuePtr rear;	
}LinkQueue;

/*初始化*/
void InitQueue(LinkQueue *Q)
{
	QNode *Temp;
	Temp = (QNode*)malloc(sizeof(QNode));
	if(!Temp)
		exit(-1);
	Q->front = Temp;
	Q->front->next = NULL;
	Q->rear = Q->front;
	printf("Queue being built Succesfully!");
}

/*入队操作，队尾插入元素*/
void EnQueue(ElemType data,LinkQueue *Q)
{
	QNode *Temp;
	Temp = (QNode*)malloc(sizeof(QNode));
	if(!Temp)
		exit(-1);
	Temp->elem = data;
	Temp->next = NULL;
	Q->rear->next = Temp;
	Q->rear = Temp;	
}
 
/*出队操作，队首删除元素*/
void DeQueue(LinkQueue *Q)
{
	QNode *Temp;
	if(Q->front == Q->rear)
		printf("Queue is empty!");
	else
	{
		Temp = Q->front->next;
		Q->front->next = Temp->next;
		if(Temp == Q->rear)
			Q->rear = Q->front;
		free(Temp); 
	}	
}
 
/*取值操作，返回队首元素*/
ElemType Front(LinkQueue *Q)
{
	if(Q->front == Q->rear)
		return -1;
	else
		return Q->front->next->elem;	
}
int main()
{
	int i,n;
	ElemType data;
	LinkQueue *Q;
	InitQueue(Q);
	printf("Input sum of elements:");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("Input an element:");
		scanf("%d",&data);
		EnQueue(data,Q);
	}
	printf("front-element of Queue:%d\n",Front(Q));
	DeQueue(Q);
	printf("front-element of Queue:%d\n",Front(Q));
	return 0;
} 
 
