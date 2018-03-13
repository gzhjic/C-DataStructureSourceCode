/*--@�̺���--*/
/*--2017/10/16--*/
/*--ջ������ʵ�֣�˳��洢--*/
/*--------------------------------*
 *  | a  | b  | c  |   |   |   |  *
 *   ^base          ^top          *   
 *   0    1    2    3             *
 *--------------------------------*/ 

#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100

typedef int ElemType;

typedef struct SqStack
{
	ElemType *top;          //����Ҫע�⣬ջ����Ҫ����ʲô���͵����ݣ� 
	ElemType *base;         //�ο��ļ�NonRecursion_BTreeNode_ADT.c 
	int stacksize;
}SqStack;

/*��ʼ��*/
void InitStack(SqStack *S)
{
	S->base = (ElemType *)malloc(MAXSIZE*sizeof(ElemType));  
	if(!S->base)
		exit(-1);
	S->top = S->base;
    S->stacksize = MAXSIZE;
    printf("Succesfully Init Stack!\n");
}

/*��ջ����*/
void Push(ElemType x,SqStack *S)
{
	if((S->top-S->base)>=S->stacksize)
		printf("Stack is full!\n");
	else
	{
		*S->top = x;   //*S->top��*��S->top������ָ��S->topָ��Ŀ���ֵx 
		S->top += 1;   //ջ��Ԫ�أ�*(S->top-1) 
	}
}

/*��ջ����*/
void Pop(SqStack *S)
{
	if(S->top == S->base)
		printf("Stack is empty!\n");
	else
	{
		S->top -= 1;
	}
}

/*ȡֵ����������ջ��Ԫ��*/
ElemType Top(SqStack *S)
{
	if((S->top-S->base)>=S->stacksize)
		return -1;
	else
	{
		return *(S->top-1);   //ע�����ȼ���->��. >  *��+��- 
	}	
} 

/*��������*/
void Traverse(SqStack *S)
{
	if(S->top == NULL)
		printf("No Stack being built!\n");
	else if(S->base == S->top)
		printf("Stack is Empty!\n");
	else
	{
		while(S->top != S->base)
		{
			printf("%d",*(S->top-1));
			S->top -= 1;
		}	
	}
}

int main()
{
	int i,n;
	ElemType elem;
	SqStack *s;
	InitStack(s);
	printf("Input Sum of Elements:");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("Input an element:");
		scanf("%d",&elem);
		Push(elem,s);
	}
	printf("Stack top-element is:%d\n",*(s->top-1));
	printf("Stack top-element is:%d\n",*(s->base));
	Pop(s);
	printf("Stack top-element is:%d\n",*(s->top-1));
	printf("Stack top-element is:%d\n",*(s->top));
	printf("Stack top-element is:%d\n",Top(s));
	Traverse(s);
	return 0;
}
