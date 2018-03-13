/*--@程豪琪--*/
/*--2017/11/15--*/
/*--图，存储结构：链式存储，表示：邻接表（顶点表 + 边表）--*/
 
#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100

typedef int VertexType;
typedef int EdgeType;

typedef struct EdgeNode
{
	int adjvex;                //邻接点域，用于存储顶点对应的下标 
	EdgeType weight;           //用于存储权值 
	struct EdgeNode *next;
}EdgeNode;

typedef struct VerTexNode
{
	VertexType value;          //顶点域，用于存储顶点信息
	struct EdgeNode *firstedge; 
}VerTexNode,*AdjList;

typedef struct ALGraph
{
	AdjList adjlist;
	int numVertexes,numEdges;
}ALGraph;

/*--构建无向图（网），邻接表形式--*/
void CreateALGraph(ALGraph *G)
{
	EdgeNode *eg;
	int i,j,k;
	EdgeType w;
	printf("输入无向图顶点个数和边的个数：");
	scanf("%d,%d",&G->numVertexes,&G->numEdges); 
	
	/*--初始化顶点表--*/
	G->adjlist = (AdjList)malloc(MAXSIZE*sizeof(VerTexNode));   //给顶点表申请一块连续的存储空间，返回给表头指针 
	if(!G->adjlist)
		exit(-1);
		
	for(i=0;i<G->numVertexes;i++)
	{
		printf("读入无向图第%d个顶点信息：",i+1); 
		scanf("%d",&G->adjlist[i].value);            //输入顶点信息
		G->adjlist[i].firstedge = NULL;          
	}
	
	/*--读入numEdges条边，建立邻接表--*/
	for(k=0;k<G->numEdges;k++)
	{
		printf("输入无向图边（vi,vj）上的下标i,下标j和权w:");
		scanf("%d,%d,%d",&i,&j,&w);
		
		eg = (EdgeNode*)malloc(sizeof(EdgeNode));      //为边表结点申请存储空间 
		if(!eg)
			exit(-1);
		
		eg->next = G->adjlist[i].firstedge;            //利用头插法插入邻接结点 
		eg->weight = w;
		eg->adjvex = j;
		G->adjlist[i].firstedge = eg;
		
		eg = (EdgeNode*)malloc(sizeof(EdgeNode));
		if(!eg)
			exit(-1);
		
		eg->next = G->adjlist[j].firstedge;            //因为是无向图， 
		eg->weight = w;                                //所以在循环中， 
		eg->adjvex = i;                                //一次就针对i和j分别进行了插入 
		G->adjlist[j].firstedge = eg;
				
	}
}

/*--构建有向图（网），正邻接表形式--*/
void CreateALGraphX(ALGraph *G)
{
	EdgeNode *eg;
	int i,j,k;
	EdgeType w;
	printf("输入有向图顶点个数和边的个数：");
	scanf("%d,%d",&G->numVertexes,&G->numEdges); 
	
	/*--初始化顶点表--*/
	G->adjlist = (AdjList)malloc(MAXSIZE*sizeof(VerTexNode));   //给顶点表申请一块连续的存储空间，返回给表头指针 
	if(!G->adjlist)
		exit(-1);
		
	for(i=0;i<G->numVertexes;i++)
	{
		printf("读入有向图第%d个顶点信息：",i+1); 
		scanf("%d",&G->adjlist[i].value);            //输入顶点信息
		G->adjlist[i].firstedge = NULL;          
	}
	
	/*--读入numEdges条边，建立邻接表--*/
	for(k=0;k<G->numEdges;k++)
	{
		printf("输入有向图边<vi,vj>上的下标i,下标j和权w:");
		scanf("%d,%d,%d",&i,&j,&w);
		
		eg = (EdgeNode*)malloc(sizeof(EdgeNode));      //为边表结点申请存储空间 
		if(!eg)
			exit(-1);
		
		eg->next = G->adjlist[i].firstedge;            //利用头插法插入邻接结点 
		eg->weight = w;
		eg->adjvex = j;
		G->adjlist[i].firstedge = eg;
	}
}
/*--深度优先，遍历图--*/
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

/*--广度优先，遍历图--*/
/*-------------------------------------------先导入：队列操作-------------------------------------------------*/ 

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
	printf("Queue being built Succesfully!\n");
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

/*-----------------------------------------------队列操作-------------------------------------------------*/ 
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
