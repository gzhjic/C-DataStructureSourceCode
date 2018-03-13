/*--@程豪琪--*/
/*--2017/11/14--*/
/*--图，存储结构：连续存储，表示：邻接矩阵（一维数组 + 二维数组）--*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h> 

#define INFINITY 32767
#define MAXSIZE 100

typedef int VertexType; //我这里本打算用char型，但是输入时"回车"老是出问题,用了%*c和fflush(stdin)都解决不了 
typedef int EdgeType;
typedef int ElemType;   //栈和队列元素类型 

typedef struct AMGraph
{
	VertexType vertex[MAXSIZE];
	EdgeType edges[MAXSIZE][MAXSIZE];
	int numVertexes,numEdges;
}AMGraph;

/*--构建无向图（网），邻接矩阵形式--*/
void CreateAMGraph(AMGraph *G)
{
	int i,j,k,w;
	printf("输入无向图顶点个数和边的个数：");
	scanf("%d,%d",&G->numVertexes,&G->numEdges); 
	/*--初始化顶点数组和边数组--*/
	for(i=0;i<G->numVertexes;i++)
	{
		printf("读入无向图第%d个顶点信息：",i+1); 
		scanf("%d",&G->vertex[i]);   //输入顶点信息 
	}
	for(i=0;i<G->numVertexes;i++)
		for(j=0;j<G->numVertexes;j++)
		{
			G->edges[i][j] = INFINITY;  //边数组全初始化为Infinity 
		}
	/*--读入numEdges条边，建立邻接矩阵--*/
	for(k=0;k<G->numEdges;k++)
	{
		printf("输入无向图边（vi,vj）上的下标i,下标j和权w:");
		scanf("%d,%d,%d",&i,&j,&w);
		G->edges[i][j] = w;               //最终构建了一个无向网 
		G->edges[j][i] = G->edges[i][j];  //无向图的邻接矩阵为对称矩阵 
	}
}

/*--构建有向图（网），邻接矩阵形式--*/
void CreateAMGraphX(AMGraph *G)
{
	int i,j,k,w;
	printf("输入有向图顶点个数和边的个数：");
	scanf("%d,%d",&G->numVertexes,&G->numEdges); 
	/*--初始化顶点数组和边数组--*/
	for(i=0;i<G->numVertexes;i++)
	{
		printf("读入有向图第%d个顶点信息：",i+1); 
		scanf("%d",&G->vertex[i]);   //输入顶点信息 
	}
	for(i=0;i<G->numVertexes;i++)
		for(j=0;j<G->numVertexes;j++)
		{
			G->edges[i][j] = INFINITY;  //边数组全初始化为Infinity 
		}
	/*--读入numEdges条边，建立邻接矩阵--*/
	for(k=0;k<G->numEdges;k++)
	{
		printf("输入有向图边<vi,vj>上的下标i,下标j和权w:");
		scanf("%d,%d,%d",&i,&j,&w);
		G->edges[i][j] = w;               //第i行，出度，vi->vj，权值为w 
	}
}

/*--打印邻接矩阵--*/
void PrintAMGraph(AMGraph *G)
{
	int i,j;
	for(i=0;i<G->numVertexes;i++)
	{		
		for(j=0;j<G->numVertexes;j++)
		{
			printf("%d|",G->edges[i][j]);
		}
		printf("\n");
	}	
	printf("\n-------------\n");
	for(i=0;i<G->numVertexes;i++)
		printf("%d",G->vertex[i]);
}

/*--深度优先，遍历图--*/
/*--问题1：按深度遍历，可能会回到原顶点，如何避免多次访问?
  --将访问过的结点作标志，建立一个数组visited[n]={0,未访问；1,访问过。}存储这些标志--*/
/*--问题2：因为图可能是非连通的，如何选取顶点?
  --先任选取vertex[n]中的一个顶点，visited[i]置1，开始遍历
  --第一次结束后，当visited[n]中仍有未访问过的结点，任取一个作顶点，重复，继续遍历，直至visited[n]中全被访问！--*/ 
/*--问题3：递归，非递归?
  --深度优先遍历就是一个递归的过程，采用非递归算法需要用到栈！--*/
  
/*--dfs:递归思想--*/
int visited[MAXSIZE];

void dfs(AMGraph *G,int i)
{
	int j;
	/*先将当前访问结点置visited*/
	visited[i] = 1;      
	printf("%d",G->vertex[i]);                   //访问当前结点
	for(j=0;j<G->numVertexes;j++)     //按行访问邻接矩阵，第i行所有关系
	{
		if((G->edges[i][j]!=INFINITY)&&(visited[j]!=1))
			dfs(G,j);
	} 
}

void dfsTraverse(AMGraph *G)
{
	int i;
	/*--初始化visited[n]，全置0，未访问过！--*/
	for(i=0;i<G->numVertexes;i++)
	{
		visited[i] = 0;
	}
	/*--选取visited[n]中未被访问过的结点作遍历顶点--*/
	for(i=0;i<G->numVertexes;i++)
	{
		//默认第一次遍历的顶点为vertex[0] 
		if(visited[i] != 1)
			dfs(G,i);
	}
}

/*--dfs:非递归思想，利用栈--*/

/*-------------------------------------------先导入：栈操作-------------------------------------------------*/

/*定义栈*/
typedef struct StackNode
{
	ElemType elem;
	struct StackNode *next;
}StackNode;

/*初始化*/
void Init(StackNode *S)
{
	S = (StackNode*)malloc(sizeof(StackNode));
	if(!S)
		exit(-1);
	S->next = NULL;
	printf("StackNode being built Succesfully!\n");
}

/*入栈操作*/
void Push(ElemType x,StackNode *S)
{
	StackNode *Temp;
	Temp = (StackNode*)malloc(sizeof(StackNode));
	if(!Temp)
		exit(-1);
	Temp->elem = x;
	Temp->next = S->next;
	S->next = Temp; 
}

/*出栈操作*/
void Pop(StackNode *S)
{
	StackNode *Temp;
	if(S->next == NULL)
		printf("Stack is empty!");
	else
	{
		Temp = S->next;
		S->next = Temp->next;
		free(Temp);
	}
}

/*取值操作，返回栈顶元素*/
ElemType Top(StackNode *S)
{
	if(S->next == NULL)
		return -1;
	else
		return S->next->elem;
}

/*判断栈是否为空*/
bool Empty(StackNode *S)
{
	if(S->next == NULL && S == NULL)
		return true;
	else
		return false;
}

/*-----------------------------------------------栈操作---------------------------------------------------*/
void NonRecur_dfs(AMGraph *G)
{
	int i,j,k;
	int needPop; 
	StackNode S;
	Init(&S);
	for(i=0;i<G->numVertexes;i++)
		visited[i] = 0;
	for(i=0;i<G->numVertexes;i++)
	{
		if(visited[i]!=1)
		{
			Push(i,&S);
			visited[i] = 1;
			printf("%d",G->vertex[i]);
			while(!Empty(&S))          //当栈不为空时 
			{
				k = Top(&S);            //下面for循环，是遍历栈顶下标所在的行，寻找与之相邻且未访问过的顶点 
				needPop = 1;
				for(j=0;j<G->numVertexes;j++)
				{
					if((G->edges[k][j]!=INFINITY)&&(visited[j]!=1))
					{
						needPop = 0;
						Push(j,&S);
						visited[j] = 1;
						printf("%d",G->vertex[j]);
						break;
					}
				}
				/*需判断后再出栈！*/
				//if(j == G->numVertexes)  //若for循环后没有与之相邻且未访问过的顶点,此时j++后，最终j等于图的顶点总数numVertexes 
				if(needPop == 1)
					Pop(&S); 
			}
		}
	}
} 


/*--广度优先，遍历图--*/
/*--类似于树的层序遍历，需要用到队列，同样需要visited[n]标志已访问过的顶点--*/

/*-------------------------------------------先导入：队列操作-------------------------------------------------*/ 

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
void bfsTraverse(AMGraph *G)
{
	int i,j,k;
	LinkQueue Q;
	InitQueue(&Q);
	/*--初始化visited[n]数组，全置0，未访问过！--*/
	for(i=0;i<G->numVertexes;i++)
		visited[i] = 0;
	/*--选取visited[n]中未被访问过的结点作遍历顶点--*/
	for(i=0;i<G->numVertexes;i++)
	{
		if(visited[i]!=1)
		{
			EnQueue(i,&Q);
			visited[i] = 1;
			printf("%d",G->vertex[i]);
			while(Q.front!=Q.rear)     //当队列不为空时
			{
				k = Front(&Q);         //取出队列中当前遍历开始时，顶点的下标 
				DeQueue(&Q);
				for(j=0;j<G->numVertexes;j++)
				{
					if((G->edges[k][j]!=INFINITY)&&(visited[j]!=1))
					{
						visited[j] = 1;     //k下一层的顶点马上入队，即将访问过，先置1 
						printf("%d",G->vertex[j]); 
						EnQueue(j,&Q);
					}
				}
			} 
		}
	}
} 

int main()
{
	AMGraph G1;          //这里我使用--{AMGraph *G1;CreateAMGraph(G1);}指针出错了，为什么呢？ 
	CreateAMGraph(&G1); 
	dfsTraverse(&G1);
	printf("\n-------------\n");
	bfsTraverse(&G1);
	//printf("\n-------------\n");
	//NonRecur_dfs(&G1);              //不知道为啥，DEV c++运行到这儿，输出正确结果后就出错停止运行了！ 
	printf("\n-------------\n");
	PrintAMGraph(&G1);

	printf("\n-------------\n");
	
	AMGraph G2;
	CreateAMGraphX(&G2);
	dfsTraverse(&G2);
	printf("\n-------------\n");
	bfsTraverse(&G2);
	//printf("\n-------------\n");
	//NonRecur_dfs(&G2);
	printf("\n-------------\n");
	PrintAMGraph(&G2);
	
	return 0;
}
