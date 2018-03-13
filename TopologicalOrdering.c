/*--@�̺���--*/
/*--2017/12/15--*/
/*--�����������ݽṹ��ͼ���ڽӱ�--*/

#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100

/*----------------------------------------------�������ݽṹ��ͼ------------------------------------------------------*/

typedef int VertexType;
typedef int EdgeType;

typedef struct EdgeNode
{
	int adjvex;                //�ڽӵ������ڴ洢�����Ӧ���±� 
	EdgeType weight;           //���ڴ洢Ȩֵ 
	struct EdgeNode *next;
}EdgeNode;

typedef struct VerTexNode
{
	VertexType value;          //���������ڴ洢������Ϣ
	struct EdgeNode *firstedge; 
}VerTexNode,*AdjList;

typedef struct ALGraph
{
	AdjList adjlist;
	int numVertexes,numEdges;
}ALGraph;

/*--��������ͼ�����������ڽӱ���ʽ--*/
void CreateALGraphX(ALGraph *G)
{
	EdgeNode *eg;
	int i,j,k;
	EdgeType w;
	printf("��������ͼ��������ͱߵĸ�����");
	scanf("%d,%d",&G->numVertexes,&G->numEdges); 
	
	/*--��ʼ�������--*/
	G->adjlist = (AdjList)malloc(MAXSIZE*sizeof(VerTexNode));   //�����������һ�������Ĵ洢�ռ䣬���ظ���ͷָ�� 
	if(!G->adjlist)
		exit(-1);
		
	for(i=0;i<G->numVertexes;i++)
	{
		printf("��������ͼ��%d��������Ϣ��",i+1); 
		scanf("%d",&G->adjlist[i].value);            //���붥����Ϣ
		G->adjlist[i].firstedge = NULL;          
	}
	
	/*--����numEdges���ߣ������ڽӱ�--*/
	for(k=0;k<G->numEdges;k++)
	{
		printf("��������ͼ��<vi,vj>�ϵ��±�i,�±�j��Ȩw:");
		scanf("%d,%d,%d",&i,&j,&w);
		
		eg = (EdgeNode*)malloc(sizeof(EdgeNode));      //Ϊ�߱�������洢�ռ� 
		if(!eg)
			exit(-1);
		
		eg->next = G->adjlist[i].firstedge;            //����ͷ�巨�����ڽӽ�� 
		eg->weight = w;
		eg->adjvex = j;
		G->adjlist[i].firstedge = eg;
	}
}

/*----------------------------------------------�������ݽṹ��ͼ------------------------------------------------------*/

/*---------------------------------------------�������ݽṹ������-----------------------------------------------------*/

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
	printf("Queue being built Succesfully!\n");
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

/*---------------------------------------------�������ݽṹ������-----------------------------------------------------*/


/*--kahn�㷨�����ù������bfs��˼�룬�����Ϊ0���ȵĽǶȹ���������--*/
 
void kahn_TopoOrder(ALGraph *G)
{
	int in,topo; 
	int CountVertex = 0;			//��¼�������������Ա��ж����޻�· 
	int indegree[MAXSIZE];		//����һ���������飬��������飬�洢����������
	LinkQueue Q;
	InitQueue(&Q);
	EdgeNode *eg;
	
	/*--��ʼ�����������--*/
	for(in=0;in<G->numVertexes;in++)
	{
		printf("�����붥��v%d����ȣ�",in);
		scanf("%d",&indegree[in]);
		if(indegree[in] == 0)
		{
			EnQueue(in,&Q);		//�����Ϊ0�Ķ��������� 
		}
	}
	
	/*--���зǿ�ʱ��������ѭ��--*/
	while(Q.front!=Q.rear)		 
	{
		topo = Front(&Q);
		DeQueue(&Q);
		printf("-> v%d",topo);
		CountVertex += 1; 
		if(G->adjlist[topo].firstedge != NULL)
		{
			eg = G->adjlist[topo].firstedge;
			while( eg != NULL)
			{
				in = eg->adjvex;
				indegree[in] = indegree[in] - 1; 
				if(indegree[in]==0)
				{
					EnQueue(in,&Q);
				}
				eg = eg->next;
			}
		}
	}
	
	/*--�ж�����ͼ�����޻�·���ж��������Ƿ���ȷ--*/
	if(CountVertex < G->numVertexes)
	{
		printf("\n����ͼ�д��ڻ�·������������");
	} 
	
} 

int main()
{
	ALGraph G1;
	CreateALGraphX(&G1);
	kahn_TopoOrder(&G1);
	return 0;
} 
