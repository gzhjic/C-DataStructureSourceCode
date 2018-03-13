/*--@程豪琪--*/
/*--2017/12/15--*/
/*--拓扑排序，数据结构：图，邻接表--*/

#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100

/*----------------------------------------------引入数据结构：图------------------------------------------------------*/

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

/*----------------------------------------------引入数据结构：图------------------------------------------------------*/

/*---------------------------------------------引入数据结构：队列-----------------------------------------------------*/

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

/*---------------------------------------------引入数据结构：队列-----------------------------------------------------*/


/*--kahn算法，利用广度优先bfs的思想，以入度为0优先的角度构造结果序列--*/
 
void kahn_TopoOrder(ALGraph *G)
{
	int in,topo; 
	int CountVertex = 0;			//记录输出顶点个数，以便判断有无环路 
	int indegree[MAXSIZE];		//定义一个辅助数组，入度域数组，存储各顶点的入度
	LinkQueue Q;
	InitQueue(&Q);
	EdgeNode *eg;
	
	/*--初始化入度域数组--*/
	for(in=0;in<G->numVertexes;in++)
	{
		printf("请输入顶点v%d的入度：",in);
		scanf("%d",&indegree[in]);
		if(indegree[in] == 0)
		{
			EnQueue(in,&Q);		//将入度为0的顶点进入队列 
		}
	}
	
	/*--队列非空时，进行主循环--*/
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
	
	/*--判断有向图中有无环路，判断输出结果是否正确--*/
	if(CountVertex < G->numVertexes)
	{
		printf("\n有向图中存在环路，输出结果错误！");
	} 
	
} 

int main()
{
	ALGraph G1;
	CreateALGraphX(&G1);
	kahn_TopoOrder(&G1);
	return 0;
} 
