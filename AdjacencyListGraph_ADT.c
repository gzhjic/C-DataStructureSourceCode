/*--@�̺���--*/
/*--2017/11/15--*/
/*--ͼ���洢�ṹ����ʽ�洢����ʾ���ڽӱ������ + �߱�--*/
 
#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100

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

/*--��������ͼ���������ڽӱ���ʽ--*/
void CreateALGraph(ALGraph *G)
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
		printf("��������ͼ�ߣ�vi,vj���ϵ��±�i,�±�j��Ȩw:");
		scanf("%d,%d,%d",&i,&j,&w);
		
		eg = (EdgeNode*)malloc(sizeof(EdgeNode));      //Ϊ�߱�������洢�ռ� 
		if(!eg)
			exit(-1);
		
		eg->next = G->adjlist[i].firstedge;            //����ͷ�巨�����ڽӽ�� 
		eg->weight = w;
		eg->adjvex = j;
		G->adjlist[i].firstedge = eg;
		
		eg = (EdgeNode*)malloc(sizeof(EdgeNode));
		if(!eg)
			exit(-1);
		
		eg->next = G->adjlist[j].firstedge;            //��Ϊ������ͼ�� 
		eg->weight = w;                                //������ѭ���У� 
		eg->adjvex = i;                                //һ�ξ����i��j�ֱ�����˲��� 
		G->adjlist[j].firstedge = eg;
				
	}
}

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
/*--������ȣ�����ͼ--*/
int visited[MAXSIZE];

void dfs(ALGraph *G,int i)
{
	EdgeNode *eg;
	visited[i] = 1;
	printf("%d",G->adjlist[i].value);
	eg = G->adjlist[i].firstedge;
	while(eg!=NULL)
	{
		if(visited[eg->adjvex]!=1)
			dfs(G,eg->adjvex);
		eg = eg->next;
	}
}

void dfsTraverse(ALGraph *G)
{
	int i;
	for(i=0;i<G->numVertexes;i++)
		visited[i] = 0;
	for(i=0;i<G->numVertexes;i++)
	{
		if(visited[i]!=1)
			dfs(G,i);
	}
} 

/*--������ȣ�����ͼ--*/
/*-------------------------------------------�ȵ��룺���в���-------------------------------------------------*/ 

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

/*-----------------------------------------------���в���-------------------------------------------------*/ 
void bfsTraverse(ALGraph *G)
{
	int i,k;
	EdgeNode *eg;
	LinkQueue Q;
	InitQueue(&Q);
	for(i=0;i<G->numVertexes;i++)
	{
		visited[i] = 0;
	}
	for(i=0;i<G->numVertexes;i++)
	{
		if(visited[i]!=1)
		{
			EnQueue(i,&Q);
			visited[i] = 1;
			printf("%d",G->adjlist[i].value);
			while(Q.front != Q.rear)
			{
				k = Front(&Q);
				eg = G->adjlist[k].firstedge;
				DeQueue(&Q);
				while(eg!=NULL)
				{
					if(visited[eg->adjvex]!=1)
					{
						EnQueue(eg->adjvex,&Q);
						visited[eg->adjvex] = 1;
						printf("%d",G->adjlist[eg->adjvex].value);
					}
					eg = eg->next;
				}
			}
		}
	}
}


int main()
{
	ALGraph G1;
	CreateALGraph(&G1);
	printf("%d,%d",G1.adjlist[0].firstedge->adjvex,G1.adjlist[0].firstedge->weight);
	printf("\n------------\n");
	dfsTraverse(&G1);
	printf("\n------------\n");
	bfsTraverse(&G1);
	printf("\n------------\n");
	
	ALGraph G2;
	CreateALGraphX(&G2);
	printf("%d,%d",G2.adjlist[0].firstedge->adjvex,G2.adjlist[0].firstedge->weight);
	printf("\n------------\n");
	dfsTraverse(&G2);
	printf("\n------------\n");
	bfsTraverse(&G2);
	printf("\n------------\n");
	return 0;
}
