/*--@程豪琪--*/
/*--2017/12/13--*/
/*--带权有向图或无向图中单源最短路径问题，数据结构：图（邻接矩阵）--*/
/*--相关：Djikstra迪杰斯特拉算法--*/


#include<stdio.h>
#include<stdlib.h>

#define INFINITY 32767
#define MAXSIZE 100

typedef int VertexType;
typedef int EdgeType;


/*-------------------------------------------导入数据结构，无向图（邻接矩阵形式）-------------------------------------------------*/

/*--定义数据结构，图--*/ 
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
		scanf("%d",&G->vertex[i]);  
	}
	for(i=0;i<G->numVertexes;i++)
		for(j=0;j<G->numVertexes;j++)
		{
			G->edges[i][j] = INFINITY;
		}
	/*--读入numEdges条边，建立邻接矩阵--*/
	for(k=0;k<G->numEdges;k++)
	{
		printf("输入无向图边（vi,vj）上的下标i,下标j和权w:");
		scanf("%d,%d,%d",&i,&j,&w);
		G->edges[i][j] = w;               
		G->edges[j][i] = G->edges[i][j];  
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
/*-------------------------------------------导入数据结构，无向图（邻接矩阵形式）-------------------------------------------------*/

/*--Djistra迪杰斯特拉算法--*/

/*--Findmin函数，在Distance[n]找出路径最小的值D[w]，并返回对应顶点w--*/
int FindMin(int *Dis,int *Sel,int n) 
{
	int min = INFINITY;
	int i,w = 1;                     
	for(i=0;i<n;i++)
	{
		if((Sel[i]!=1)&&(Dis[i]<min))
		{
			min = Dis[i];
			w = i;
		}
	}
	return w;
}

void ShortestPath_Djikstra(AMGraph *G)
{
	int i,v,w;
	int Distance[MAXSIZE];                //用于存储源点v0到第i号顶点的最短路径 
	int Final[MAXSIZE];                   //用于存储源点v0到第i号顶点之间，最短路径经过的最后一个顶点  
	int Selected[MAXSIZE];                //用于表示两个集合，即已被选中顶点集合S，与未被选中顶点集合V-S 
	
	/*--初始化辅助数组--*/	
	for(i=0;i<G->numVertexes;i++)
	{
		Distance[i] = G->edges[0][i];      
		Final[i] = 0;                
		Selected[i] = 0;                  
	} 
	Distance[0] = 0;
	Selected[0] = 1;	    //初始化，只选中源点v0，其余置0表示均未选中 
	
	/*--主循环，每次求得源点v0到某个顶点v的最短路径--*/ 
	for(i=0;i<G->numVertexes;i++)
	{
		w = FindMin(Distance,Selected,G->numVertexes);    
		Selected[w] = 1;
		/*--顶点w作为弧尾，它应该有出度，接下来找出V-S中的各个弧头v--*/
		/*--比较当前v0到v的最短路径Distance[v]，与Distance[w]+edges[w][v]的大小，来更新当前最短路径及距离--*/
		
		for(v=0;v<G->numVertexes;v++)
		{
			if((Selected[v]!=1)&&(Distance[v]>Distance[w]+G->edges[w][v]))   //如果经过顶点v的路径比现在这条路径的长度还要短的话 
			{
				Distance[v] = Distance[w] + G->edges[w][v];                  //更新Distance[v]与Final[v]
				Final[v] = w;
			} 
		} 
	} 
	
	printf("最短路径长度：");
	for(i=0;i<G->numVertexes;i++)
	{
		printf("|%d",Distance[i]);
	}
	
	printf("\n最短路径：");
	for(i=0;i<G->numVertexes;i++)
	{
		printf("|%d",Final[i]);
	}
}


/*--从上面可以看出，当我需要求出每一对顶点之间的最短路径，可以令图中的每个顶点作为源点，n次复用Dijikstra算法即可--*/ 
/*--还可以使用，Floyd弗洛伊德算法--*/

void ShortestPath_Floyd(AMGraph *G,int vi,int vj)
{	
	int i,j,k;
	int Distance[MAXSIZE][MAXSIZE];		//该矩阵代表顶点到顶点的最短路径权值和 
	int	Final[MAXSIZE][MAXSIZE];		//该矩阵(路径矩阵)代表对应顶点的最小路径的前驱矩阵，存储最短路径经过的最后一个顶点下标
	
	/*--初始化两个辅助矩阵--*/
	for(i=0;i<G->numVertexes;i++)
	{
		for(j=0;j<G->numVertexes;j++)
		{
			Distance[i][j] = G->edges[i][j];
			Final[i][j] = j;
		}
	} 
	
	/*--依次选择中间结点，进行n次试探--*/
	for(k=0;k<G->numVertexes;k++)
	{
		for(i=0;i<G->numVertexes;i++)
		{
			for(j=0;j<G->numVertexes;j++)
			{
				if(Distance[i][j] > Distance[i][k]+Distance[k][j])
				{
					Distance[i][j] = Distance[i][k]+Distance[k][j];
					Final[i][j] = Final[i][k];
				}
			}
		} 
	}
	
	/*--打印vi到vj的最短路径--*/
	printf("v%d到v%d的最短路径长度为：%d\n",vi,vj,Distance[vi][vj]);          
	printf("v%d到v%d的最短路径为：v%d",vi,vj,vi);      //打印源点 
	k = Final[vi][vj];				   			      //获得第一个前驱路径<vi,...,vk1>(<vi,...,vk1>+<vk1,...,vj>)顶点下标k1 
	while(k!=vj)
	{
		printf("-> v%d",k);
		k = Final[k][vj];							  //获得下一个前驱路径<vi,...,vki>(<vi,...,vki>+<vki,...,vj>)顶点下标ki					
	}
	printf("-> v%d\n",vj);      					  //打印终点 
	
} 

int main()
{
	AMGraph G1;                 
	//CreateAMGraphX(&G1);
	CreateAMGraph(&G1);
	/*--源点v0，终点v8的最短路径--*/
	ShortestPath_Djikstra(&G1);
	ShortestPath_Floyd(&G1,0,8);    
	return 0;
} 














