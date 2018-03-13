/*--@程豪琪--*/
/*--2017/11/27--*/
/*--最小生成树，数据结构：图（邻接矩阵）--*/
/*--相关：Prim普里姆算法和Kruscal克鲁斯卡尔算法--*/ 


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

/*-------------------------------------------导入数据结构，无向图（邻接矩阵形式）-------------------------------------------------*/

/*--普利姆算法，基本思想：贪心法--*/ 
void MiniSpanTree_Prim(AMGraph *G)
{
	int i,j,k;
	int min;
	int UAdjvex[MAXSIZE];    //数组UAdjvex[n]用于存放集合U中的顶点下标值，集合U即已落在生成树上的顶点集 
	int LowCost[MAXSIZE];    //数组LowCost[n]用于存放集合V-U与集合U顶点之间最短边的权值 
	
	/*--初始化数组UAdjvex[n]与LowCost[n]--*/ 
	UAdjvex[0] = 0;          //任取一个顶点加入集合U中，例如默认选择顶点v0
	LowCost[0] = 0;          //默认v0到自身的距离为0，LowCost[i] = 0表示该顶点已放入集合U中 
	
	for(i=1;i<G->numVertexes;i++)   
	{
		UAdjvex[i] = 0;
		LowCost[i] = G->edges[UAdjvex[0]][i];    //遍历顶点邻接矩阵中顶点v0所在行的所有权值，存入LowCost[i]中以初始化 
	}
	
	
	/*--循环(n-1)次--*/ 
	for(j=0;j<G->numVertexes-1;j++)
	{
		min = INFINITY;
		k = 0;
		
		for(i=0;i<G->numVertexes;i++)
		{
			if((LowCost[i]!=0)&&(LowCost[i]<min))  //找出LowCost[n]中权值最小且不为0的权值，以及对应顶点序号并赋值给k 
			{
				min = LowCost[i];
				k = i;
			}
		}
		
		printf("最小生成树中一条边为：(v%d,v%d)\n",UAdjvex[k],k);
		LowCost[k] = 0;                           //将新找到的顶点加入集合U中 
		
		for(i=0;i<G->numVertexes;i++)             //更新数组UAdjvex[n]与LowCost[n]，即更新剩余顶点到当前生成树的最短举例 
		{
			if((LowCost[i]!=0)&&(LowCost[i]>G->edges[k][i]))   //比较边(vt,vj)与边(vt-1,vj)的权值大小，vt为当前时刻刚加入集合U的顶点 
			{
				LowCost[i] = G->edges[k][i];                   //若边(vt,vj)权值更小，则更新LowCost[j]=边(vt,vj)权值与UAdjvex[i]= 顶点vt下标值 
				UAdjvex[i] = k;                                //否则不更新 
			}	
		}		
	}

}



 /*--定义边集数组，用于表示图结构 --*/
typedef struct Edge  
{
	int begin;
	int end;
	int weight;
}Edge;

/*--查询函数，返回某一个集合的根结点--*/
int Union_Find(int *parent,int root)
{
	while(parent[root] > 0)
		root = parent[root];
	return root;
}

/*--克鲁斯卡尔算法，基本思想：并查集(Union-Find)--*/
void MiniSpanTree_Kruscal(AMGraph *G)
{
	int i,j,k,n,m;
	int begintemp,endtemp,weitemp;
	int parent[MAXSIZE];
	Edge *Uedges;
	Uedges = (Edge*)malloc(MAXSIZE*sizeof(Edge));
	if(!Uedges)
		exit(-1);
	
	/*--将邻接矩阵的边"按权值由小到大的顺序"存储到边集数组中(并查集思想)--*/
	k = 0;
	for(i=0;i<G->numVertexes;i++)                //先将邻接矩阵中所有边存储到边集数组中 
	{
		for(j=i+1;j<G->numVertexes;j++)
		{
			if(G->edges[i][j]!=INFINITY)
			{
				Uedges[k].begin = i;
				Uedges[k].end = j;
				Uedges[k].weight = G->edges[i][j];
				k++;
			}
		}
	}

	for(i=0;i<G->numEdges;i++)                   //使用冒泡排序将边集数组由小到大排序 
	{	
		for(j=i+1;j<G->numEdges;j++) 
		{
			if(Uedges[j].weight < Uedges[i].weight)
			{
				begintemp = Uedges[j].begin;
				endtemp = Uedges[j].end;
				weitemp = Uedges[j].weight; 
				
				Uedges[j].begin = Uedges[i].begin;
				Uedges[j].end = Uedges[i].end;
				Uedges[j].weight = Uedges[i].weight;
				
				Uedges[i].begin = begintemp;
				Uedges[i].end = endtemp;
				Uedges[i].weight = weitemp;
			}	
		} 
	}
	
	/*--初始化，将每一个顶点看作一个单独的连通分量(并查集思想)--*/
	for(i=0;i<G->numVertexes;i++)
	{
		parent[i] = -1;             //-1代表i此时为根节点 
	}
	
	/*--按次序搜索连接两个不同连通分量的边，并合并--*/
	for(i=0;i<G->numEdges;i++)
	{
		n = Union_Find(parent,Uedges[i].begin);
		m = Union_Find(parent,Uedges[i].end);
		if(n!=m)                                   //判断是否在一个连通分量中(防止形成环路) 
		{
			parent[n] = m;
			printf("最小生成树中一条边为：(v%d,v%d)\n",Uedges[i].begin,Uedges[i].end);
		}
	}
	
}

int main()
{
	AMGraph G1;       
	CreateAMGraph(&G1); 
	MiniSpanTree_Prim(&G1);
	MiniSpanTree_Kruscal(&G1);
	return 0;
}
