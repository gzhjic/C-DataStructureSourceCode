/*--@�̺���--*/
/*--2017/11/27--*/
/*--��С�����������ݽṹ��ͼ���ڽӾ���--*/
/*--��أ�Prim����ķ�㷨��Kruscal��³˹�����㷨--*/ 


#include<stdio.h>
#include<stdlib.h>

#define INFINITY 32767
#define MAXSIZE 100

typedef int VertexType;
typedef int EdgeType;


/*-------------------------------------------�������ݽṹ������ͼ���ڽӾ�����ʽ��-------------------------------------------------*/

/*--�������ݽṹ��ͼ--*/ 
typedef struct AMGraph
{
	VertexType vertex[MAXSIZE];
	EdgeType edges[MAXSIZE][MAXSIZE];
	int numVertexes,numEdges;
}AMGraph;

/*--��������ͼ���������ڽӾ�����ʽ--*/
void CreateAMGraph(AMGraph *G)
{
	int i,j,k,w;
	printf("��������ͼ��������ͱߵĸ�����");
	scanf("%d,%d",&G->numVertexes,&G->numEdges); 
	/*--��ʼ����������ͱ�����--*/
	for(i=0;i<G->numVertexes;i++)
	{
		printf("��������ͼ��%d��������Ϣ��",i+1); 
		scanf("%d",&G->vertex[i]);  
	}
	for(i=0;i<G->numVertexes;i++)
		for(j=0;j<G->numVertexes;j++)
		{
			G->edges[i][j] = INFINITY;
		}
	/*--����numEdges���ߣ������ڽӾ���--*/
	for(k=0;k<G->numEdges;k++)
	{
		printf("��������ͼ�ߣ�vi,vj���ϵ��±�i,�±�j��Ȩw:");
		scanf("%d,%d,%d",&i,&j,&w);
		G->edges[i][j] = w;               
		G->edges[j][i] = G->edges[i][j];  
	}
}

/*-------------------------------------------�������ݽṹ������ͼ���ڽӾ�����ʽ��-------------------------------------------------*/

/*--����ķ�㷨������˼�룺̰�ķ�--*/ 
void MiniSpanTree_Prim(AMGraph *G)
{
	int i,j,k;
	int min;
	int UAdjvex[MAXSIZE];    //����UAdjvex[n]���ڴ�ż���U�еĶ����±�ֵ������U���������������ϵĶ��㼯 
	int LowCost[MAXSIZE];    //����LowCost[n]���ڴ�ż���V-U�뼯��U����֮����̱ߵ�Ȩֵ 
	
	/*--��ʼ������UAdjvex[n]��LowCost[n]--*/ 
	UAdjvex[0] = 0;          //��ȡһ��������뼯��U�У�����Ĭ��ѡ�񶥵�v0
	LowCost[0] = 0;          //Ĭ��v0������ľ���Ϊ0��LowCost[i] = 0��ʾ�ö����ѷ��뼯��U�� 
	
	for(i=1;i<G->numVertexes;i++)   
	{
		UAdjvex[i] = 0;
		LowCost[i] = G->edges[UAdjvex[0]][i];    //���������ڽӾ����ж���v0�����е�����Ȩֵ������LowCost[i]���Գ�ʼ�� 
	}
	
	
	/*--ѭ��(n-1)��--*/ 
	for(j=0;j<G->numVertexes-1;j++)
	{
		min = INFINITY;
		k = 0;
		
		for(i=0;i<G->numVertexes;i++)
		{
			if((LowCost[i]!=0)&&(LowCost[i]<min))  //�ҳ�LowCost[n]��Ȩֵ��С�Ҳ�Ϊ0��Ȩֵ���Լ���Ӧ������Ų���ֵ��k 
			{
				min = LowCost[i];
				k = i;
			}
		}
		
		printf("��С��������һ����Ϊ��(v%d,v%d)\n",UAdjvex[k],k);
		LowCost[k] = 0;                           //�����ҵ��Ķ�����뼯��U�� 
		
		for(i=0;i<G->numVertexes;i++)             //��������UAdjvex[n]��LowCost[n]��������ʣ�ඥ�㵽��ǰ����������̾��� 
		{
			if((LowCost[i]!=0)&&(LowCost[i]>G->edges[k][i]))   //�Ƚϱ�(vt,vj)���(vt-1,vj)��Ȩֵ��С��vtΪ��ǰʱ�̸ռ��뼯��U�Ķ��� 
			{
				LowCost[i] = G->edges[k][i];                   //����(vt,vj)Ȩֵ��С�������LowCost[j]=��(vt,vj)Ȩֵ��UAdjvex[i]= ����vt�±�ֵ 
				UAdjvex[i] = k;                                //���򲻸��� 
			}	
		}		
	}

}



 /*--����߼����飬���ڱ�ʾͼ�ṹ --*/
typedef struct Edge  
{
	int begin;
	int end;
	int weight;
}Edge;

/*--��ѯ����������ĳһ�����ϵĸ����--*/
int Union_Find(int *parent,int root)
{
	while(parent[root] > 0)
		root = parent[root];
	return root;
}

/*--��³˹�����㷨������˼�룺���鼯(Union-Find)--*/
void MiniSpanTree_Kruscal(AMGraph *G)
{
	int i,j,k,n,m;
	int begintemp,endtemp,weitemp;
	int parent[MAXSIZE];
	Edge *Uedges;
	Uedges = (Edge*)malloc(MAXSIZE*sizeof(Edge));
	if(!Uedges)
		exit(-1);
	
	/*--���ڽӾ���ı�"��Ȩֵ��С�����˳��"�洢���߼�������(���鼯˼��)--*/
	k = 0;
	for(i=0;i<G->numVertexes;i++)                //�Ƚ��ڽӾ��������бߴ洢���߼������� 
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

	for(i=0;i<G->numEdges;i++)                   //ʹ��ð�����򽫱߼�������С�������� 
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
	
	/*--��ʼ������ÿһ�����㿴��һ����������ͨ����(���鼯˼��)--*/
	for(i=0;i<G->numVertexes;i++)
	{
		parent[i] = -1;             //-1����i��ʱΪ���ڵ� 
	}
	
	/*--��������������������ͬ��ͨ�����ıߣ����ϲ�--*/
	for(i=0;i<G->numEdges;i++)
	{
		n = Union_Find(parent,Uedges[i].begin);
		m = Union_Find(parent,Uedges[i].end);
		if(n!=m)                                   //�ж��Ƿ���һ����ͨ������(��ֹ�γɻ�·) 
		{
			parent[n] = m;
			printf("��С��������һ����Ϊ��(v%d,v%d)\n",Uedges[i].begin,Uedges[i].end);
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
