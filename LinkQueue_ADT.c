/*--@�̺���--*/
/*--2017/10/18--*/
/*--���е�ָ��ʵ�֣���ʽ�洢--*/

#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;

/*������*/
typedef struct QNode
{
	ElemType elem;
	struct QNode *next;
}QNode,*QueuePtr;

/*�������*/
typedef struct LinkQueue
{
	QueuePtr front;
	QueuePtr rear;	
}LinkQueue;

/*��ʼ��*/
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

/*��Ӳ�������β����Ԫ��*/
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
 
/*���Ӳ���������ɾ��Ԫ��*/
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
 
/*ȡֵ���������ض���Ԫ��*/
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
 
