/*--@程豪琪--*/
/*--2017/10/18--*/
/*--队列的数组实现，顺序存储--*/
/*---------------------------------------------* 
 *                                             *
 *  循环队列：                                 *
 *		队满：(rear+1)%QueueSize == front      *
 *      队空：rear = front                     * 
 *		队长：(rear-front+QueueSize)%QueueSize *
 *	                                           *
 *---------------------------------------------*/
 
/*--------------------------------------------------------------------* 
 *	在出队操作时，只是front后移，                                     * 
 * 	因为队列是循环的，而原队首元素未删除，仍占据空间                  * 
 *	这样对于入队操作不是会有影响吗？（例如虽出队，但实际队还是满的！）* 
 * 	另外如果即使我利用出队操作使满队列变空，但实际上队列仍然是满的！  * 
 * 	为什么？如何解决？                                                *    
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

/*初始化*/
void InitQueue(SqQueue *Q)
{
	Q->elem = (ElemType*)malloc(MAXSIZE*sizeof(ElemType)); 
	if(!Q->elem)                                             
		exit(-1);
	Q->front = 0;
	Q->rear = 0;
}

/*入队操作*/
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
/*出队操作*/
void DeQueue(SqQueue *Q)
{
	if(Q->front == Q->rear)
		printf("Queue is empty!");
	else
		Q->front = (Q->front+1)%MAXSIZE;
} 

/*取值操作，返回队首元素*/
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
