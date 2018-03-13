/*--@�̺���--*/
/*--2017/12/13--*/
/*--��Ȩ����ͼ������ͼ�е�Դ���·�����⣬���ݽṹ��ͼ���ڽӾ���--*/
/*--��أ�Djikstra�Ͻ�˹�����㷨--*/


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

/*--��������ͼ���������ڽӾ�����ʽ--*/
void CreateAMGraphX(AMGraph *G)
{
	int i,j,k,w;
	printf("��������ͼ��������ͱߵĸ�����");
	scanf("%d,%d",&G->numVertexes,&G->numEdges); 
	/*--��ʼ����������ͱ�����--*/
	for(i=0;i<G->numVertexes;i++)
	{
		printf("��������ͼ��%d��������Ϣ��",i+1); 
		scanf("%d",&G->vertex[i]);   //���붥����Ϣ 
	}
	for(i=0;i<G->numVertexes;i++)
		for(j=0;j<G->numVertexes;j++)
		{
			G->edges[i][j] = INFINITY;  //������ȫ��ʼ��ΪInfinity 
		}
	/*--����numEdges���ߣ������ڽӾ���--*/
	for(k=0;k<G->numEdges;k++)
	{
		printf("��������ͼ��<vi,vj>�ϵ��±�i,�±�j��Ȩw:");
		scanf("%d,%d,%d",&i,&j,&w);
		G->edges[i][j] = w;               //��i�У����ȣ�vi->vj��ȨֵΪw 
	}
}
/*-------------------------------------------�������ݽṹ������ͼ���ڽӾ�����ʽ��-------------------------------------------------*/

/*--Djistra�Ͻ�˹�����㷨--*/

/*--Findmin��������Distance[n]�ҳ�·����С��ֵD[w]�������ض�Ӧ����w--*/
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
	int Distance[MAXSIZE];                //���ڴ洢Դ��v0����i�Ŷ�������·�� 
	int Final[MAXSIZE];                   //���ڴ洢Դ��v0����i�Ŷ���֮�䣬���·�����������һ������  
	int Selected[MAXSIZE];                //���ڱ�ʾ�������ϣ����ѱ�ѡ�ж��㼯��S����δ��ѡ�ж��㼯��V-S 
	
	/*--��ʼ����������--*/	
	for(i=0;i<G->numVertexes;i++)
	{
		Distance[i] = G->edges[0][i];      
		Final[i] = 0;                
		Selected[i] = 0;                  
	} 
	Distance[0] = 0;
	Selected[0] = 1;	    //��ʼ����ֻѡ��Դ��v0��������0��ʾ��δѡ�� 
	
	/*--��ѭ����ÿ�����Դ��v0��ĳ������v�����·��--*/ 
	for(i=0;i<G->numVertexes;i++)
	{
		w = FindMin(Distance,Selected,G->numVertexes);    
		Selected[w] = 1;
		/*--����w��Ϊ��β����Ӧ���г��ȣ��������ҳ�V-S�еĸ�����ͷv--*/
		/*--�Ƚϵ�ǰv0��v�����·��Distance[v]����Distance[w]+edges[w][v]�Ĵ�С�������µ�ǰ���·��������--*/
		
		for(v=0;v<G->numVertexes;v++)
		{
			if((Selected[v]!=1)&&(Distance[v]>Distance[w]+G->edges[w][v]))   //�����������v��·������������·���ĳ��Ȼ�Ҫ�̵Ļ� 
			{
				Distance[v] = Distance[w] + G->edges[w][v];                  //����Distance[v]��Final[v]
				Final[v] = w;
			} 
		} 
	} 
	
	printf("���·�����ȣ�");
	for(i=0;i<G->numVertexes;i++)
	{
		printf("|%d",Distance[i]);
	}
	
	printf("\n���·����");
	for(i=0;i<G->numVertexes;i++)
	{
		printf("|%d",Final[i]);
	}
}


/*--��������Կ�����������Ҫ���ÿһ�Զ���֮������·����������ͼ�е�ÿ��������ΪԴ�㣬n�θ���Dijikstra�㷨����--*/ 
/*--������ʹ�ã�Floyd���������㷨--*/

void ShortestPath_Floyd(AMGraph *G,int vi,int vj)
{	
	int i,j,k;
	int Distance[MAXSIZE][MAXSIZE];		//�þ�������㵽��������·��Ȩֵ�� 
	int	Final[MAXSIZE][MAXSIZE];		//�þ���(·������)�����Ӧ�������С·����ǰ�����󣬴洢���·�����������һ�������±�
	
	/*--��ʼ��������������--*/
	for(i=0;i<G->numVertexes;i++)
	{
		for(j=0;j<G->numVertexes;j++)
		{
			Distance[i][j] = G->edges[i][j];
			Final[i][j] = j;
		}
	} 
	
	/*--����ѡ���м��㣬����n����̽--*/
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
	
	/*--��ӡvi��vj�����·��--*/
	printf("v%d��v%d�����·������Ϊ��%d\n",vi,vj,Distance[vi][vj]);          
	printf("v%d��v%d�����·��Ϊ��v%d",vi,vj,vi);      //��ӡԴ�� 
	k = Final[vi][vj];				   			      //��õ�һ��ǰ��·��<vi,...,vk1>(<vi,...,vk1>+<vk1,...,vj>)�����±�k1 
	while(k!=vj)
	{
		printf("-> v%d",k);
		k = Final[k][vj];							  //�����һ��ǰ��·��<vi,...,vki>(<vi,...,vki>+<vki,...,vj>)�����±�ki					
	}
	printf("-> v%d\n",vj);      					  //��ӡ�յ� 
	
} 

int main()
{
	AMGraph G1;                 
	//CreateAMGraphX(&G1);
	CreateAMGraph(&G1);
	/*--Դ��v0���յ�v8�����·��--*/
	ShortestPath_Djikstra(&G1);
	ShortestPath_Floyd(&G1,0,8);    
	return 0;
} 














