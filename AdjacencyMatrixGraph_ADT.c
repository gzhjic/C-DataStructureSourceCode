/*--@�̺���--*/
/*--2017/11/14--*/
/*--ͼ���洢�ṹ�������洢����ʾ���ڽӾ���һά���� + ��ά���飩--*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h> 

#define INFINITY 32767
#define MAXSIZE 100

typedef int VertexType; //�����ﱾ������char�ͣ���������ʱ"�س�"���ǳ�����,����%*c��fflush(stdin)��������� 
typedef int EdgeType;
typedef int ElemType;   //ջ�Ͷ���Ԫ������ 

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
		printf("��������ͼ�ߣ�vi,vj���ϵ��±�i,�±�j��Ȩw:");
		scanf("%d,%d,%d",&i,&j,&w);
		G->edges[i][j] = w;               //���չ�����һ�������� 
		G->edges[j][i] = G->edges[i][j];  //����ͼ���ڽӾ���Ϊ�Գƾ��� 
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

/*--��ӡ�ڽӾ���--*/
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

/*--������ȣ�����ͼ--*/
/*--����1������ȱ��������ܻ�ص�ԭ���㣬��α����η���?
  --�����ʹ��Ľ������־������һ������visited[n]={0,δ���ʣ�1,���ʹ���}�洢��Щ��־--*/
/*--����2����Ϊͼ�����Ƿ���ͨ�ģ����ѡȡ����?
  --����ѡȡvertex[n]�е�һ�����㣬visited[i]��1����ʼ����
  --��һ�ν����󣬵�visited[n]������δ���ʹ��Ľ�㣬��ȡһ�������㣬�ظ�������������ֱ��visited[n]��ȫ�����ʣ�--*/ 
/*--����3���ݹ飬�ǵݹ�?
  --������ȱ�������һ���ݹ�Ĺ��̣����÷ǵݹ��㷨��Ҫ�õ�ջ��--*/
  
/*--dfs:�ݹ�˼��--*/
int visited[MAXSIZE];

void dfs(AMGraph *G,int i)
{
	int j;
	/*�Ƚ���ǰ���ʽ����visited*/
	visited[i] = 1;      
	printf("%d",G->vertex[i]);                   //���ʵ�ǰ���
	for(j=0;j<G->numVertexes;j++)     //���з����ڽӾ��󣬵�i�����й�ϵ
	{
		if((G->edges[i][j]!=INFINITY)&&(visited[j]!=1))
			dfs(G,j);
	} 
}

void dfsTraverse(AMGraph *G)
{
	int i;
	/*--��ʼ��visited[n]��ȫ��0��δ���ʹ���--*/
	for(i=0;i<G->numVertexes;i++)
	{
		visited[i] = 0;
	}
	/*--ѡȡvisited[n]��δ�����ʹ��Ľ������������--*/
	for(i=0;i<G->numVertexes;i++)
	{
		//Ĭ�ϵ�һ�α����Ķ���Ϊvertex[0] 
		if(visited[i] != 1)
			dfs(G,i);
	}
}

/*--dfs:�ǵݹ�˼�룬����ջ--*/

/*-------------------------------------------�ȵ��룺ջ����-------------------------------------------------*/

/*����ջ*/
typedef struct StackNode
{
	ElemType elem;
	struct StackNode *next;
}StackNode;

/*��ʼ��*/
void Init(StackNode *S)
{
	S = (StackNode*)malloc(sizeof(StackNode));
	if(!S)
		exit(-1);
	S->next = NULL;
	printf("StackNode being built Succesfully!\n");
}

/*��ջ����*/
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

/*��ջ����*/
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

/*ȡֵ����������ջ��Ԫ��*/
ElemType Top(StackNode *S)
{
	if(S->next == NULL)
		return -1;
	else
		return S->next->elem;
}

/*�ж�ջ�Ƿ�Ϊ��*/
bool Empty(StackNode *S)
{
	if(S->next == NULL && S == NULL)
		return true;
	else
		return false;
}

/*-----------------------------------------------ջ����---------------------------------------------------*/
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
			while(!Empty(&S))          //��ջ��Ϊ��ʱ 
			{
				k = Top(&S);            //����forѭ�����Ǳ���ջ���±����ڵ��У�Ѱ����֮������δ���ʹ��Ķ��� 
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
				/*���жϺ��ٳ�ջ��*/
				//if(j == G->numVertexes)  //��forѭ����û����֮������δ���ʹ��Ķ���,��ʱj++������j����ͼ�Ķ�������numVertexes 
				if(needPop == 1)
					Pop(&S); 
			}
		}
	}
} 


/*--������ȣ�����ͼ--*/
/*--���������Ĳ����������Ҫ�õ����У�ͬ����Ҫvisited[n]��־�ѷ��ʹ��Ķ���--*/

/*-------------------------------------------�ȵ��룺���в���-------------------------------------------------*/ 

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
void bfsTraverse(AMGraph *G)
{
	int i,j,k;
	LinkQueue Q;
	InitQueue(&Q);
	/*--��ʼ��visited[n]���飬ȫ��0��δ���ʹ���--*/
	for(i=0;i<G->numVertexes;i++)
		visited[i] = 0;
	/*--ѡȡvisited[n]��δ�����ʹ��Ľ������������--*/
	for(i=0;i<G->numVertexes;i++)
	{
		if(visited[i]!=1)
		{
			EnQueue(i,&Q);
			visited[i] = 1;
			printf("%d",G->vertex[i]);
			while(Q.front!=Q.rear)     //�����в�Ϊ��ʱ
			{
				k = Front(&Q);         //ȡ�������е�ǰ������ʼʱ��������±� 
				DeQueue(&Q);
				for(j=0;j<G->numVertexes;j++)
				{
					if((G->edges[k][j]!=INFINITY)&&(visited[j]!=1))
					{
						visited[j] = 1;     //k��һ��Ķ���������ӣ��������ʹ�������1 
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
	AMGraph G1;          //������ʹ��--{AMGraph *G1;CreateAMGraph(G1);}ָ������ˣ�Ϊʲô�أ� 
	CreateAMGraph(&G1); 
	dfsTraverse(&G1);
	printf("\n-------------\n");
	bfsTraverse(&G1);
	//printf("\n-------------\n");
	//NonRecur_dfs(&G1);              //��֪��Ϊɶ��DEV c++���е�����������ȷ�����ͳ���ֹͣ�����ˣ� 
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
