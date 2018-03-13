/*--@�̺���--*/
/*--2017/10/17--*/
/*--ջ��ָ��ʵ�֣���ʽ�洢--*/
/*-------------------------------------*
 *       _____________   ____________  * 
 * top->|_head_|_____|->|__a__|__^__|  * 
 *                    ^ջ��            *
 * ��ջ��                              *
 *       _____________                 *
 * top->|_head_|__^__|                 *
 *-------------------------------------*/

#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;

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

/*��������*/
void Traverse(StackNode *S)
{
	StackNode *Temp;
	Temp = S;
	if((Temp->next) == NULL)
		printf("Stack is empty!");
	else
	{
		while((Temp->next) != NULL)
		{
			printf("%d",Temp->next->elem);
			Temp = Temp->next;
		}
	}
}

int main()
{
	int i,n;
	ElemType data;
	StackNode *S;
	Init(S);
	printf("Input sum of elements:");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("Input an element:");
		scanf("%d",&data);
		Push(data,S);
	}
	printf("Stack top-element:%d\n",Top(S));
	Pop(S);
	printf("Stack top-element:%d\n",Top(S));
	Traverse(S);
	return 0;
}


