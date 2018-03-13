/*--@程豪琪--*/
/*--2017/10/16--*/
/*--栈的数组实现，顺序存储--*/
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
	ElemType *top;          //这里要注意，栈中需要存入什么类型的数据！ 
	ElemType *base;         //参考文件NonRecursion_BTreeNode_ADT.c 
	int stacksize;
}SqStack;

/*初始化*/
void InitStack(SqStack *S)
{
	S->base = (ElemType *)malloc(MAXSIZE*sizeof(ElemType));  
	if(!S->base)
		exit(-1);
	S->top = S->base;
    S->stacksize = MAXSIZE;
    printf("Succesfully Init Stack!\n");
}

/*入栈操作*/
void Push(ElemType x,SqStack *S)
{
	if((S->top-S->base)>=S->stacksize)
		printf("Stack is full!\n");
	else
	{
		*S->top = x;   //*S->top即*（S->top），向指针S->top指向的块送值x 
		S->top += 1;   //栈顶元素，*(S->top-1) 
	}
}

/*出栈操作*/
void Pop(SqStack *S)
{
	if(S->top == S->base)
		printf("Stack is empty!\n");
	else
	{
		S->top -= 1;
	}
}

/*取值操作，返回栈顶元素*/
ElemType Top(SqStack *S)
{
	if((S->top-S->base)>=S->stacksize)
		return -1;
	else
	{
		return *(S->top-1);   //注意优先级：->或. >  *或+或- 
	}	
} 

/*遍历操作*/
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
