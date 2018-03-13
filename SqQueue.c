/*--@�̺���--*/
/*--2017/10/18--*/
/*--���е�����ʵ�֣�˳��洢--*/
/*---------------------------------------------* 
 *                                             *
 *  ѭ�����У�                                 *
 *		������(rear+1)%QueueSize == front      *
 *      �ӿգ�rear = front                     * 
 *		�ӳ���(rear-front+QueueSize)%QueueSize *
 *	                                           *
 *---------------------------------------------*/
 
/*--------------------------------------------------------------------* 
 *	�ڳ��Ӳ���ʱ��ֻ��front���ƣ�                                     * 
 * 	��Ϊ������ѭ���ģ���ԭ����Ԫ��δɾ������ռ�ݿռ�                  * 
 *	����������Ӳ������ǻ���Ӱ���𣿣���������ӣ���ʵ�ʶӻ������ģ���* 
 * 	���������ʹ�����ó��Ӳ���ʹ�����б�գ���ʵ���϶�����Ȼ�����ģ�  * 
 * 	Ϊʲô����ν����                                                *    
 *--------------------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100

typedef int ElemType;

typedef struct SqQueue
{
	ElemType *elem;
	int front;
	int rear;
}SqQueue;

/*��ʼ��*/
void InitQueue(SqQueue *Q)
{
	Q->elem = (ElemType*)malloc(MAXSIZE*sizeof(ElemType)); 
	if(!Q->elem)                                             
		exit(-1);
	Q->front = 0;
	Q->rear = 0;
}

/*��Ӳ���*/
void EnQueue(ElemType x,SqQueue *Q)
{
	if((Q->rear+1)%MAXSIZE == Q->front)
		printf("Queue is full!\n");
	else
	{
		Q->elem[Q->rear] = x;
		Q->rear = (Q->rear+1)%MAXSIZE;
	}
} 
/*���Ӳ���*/
void DeQueue(SqQueue *Q)
{
	if(Q->front == Q->rear)
		printf("Queue is empty!");
	else
		Q->front = (Q->front+1)%MAXSIZE;
} 

/*ȡֵ���������ض���Ԫ��*/
ElemType Front(SqQueue *Q)
{
	if(Q->front == Q->rear)
		return -1;
	else
		return Q->elem[Q->front];
} 

int main()
{
	int i,n;
	ElemType data;
	SqQueue *Q;
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
