/*--@�̺���--*/
/*--2017/11/01--*/
/*--���������洢�ṹ����ʽ�洢����ʾ������������������--*/
/*--�����˷ǵݹ�ķ������б���--*/
/*--�ǵݹ�����������ķ����м��֣�������ݽ̿��飬����ջ�������ǵݹ鷽��--*/

/*------------------------------------˼�����⣨δ�����---------------------------------------
	1.�ǵݹ鷽�����������ƶ�������
	2.�ǵݹ鷽��������������ȣ�
	3.�ݹ鷽�����ƶ�������
	4.�ǵݹ鷽��/�ݹ鷽�������������Ԫ�أ� 
------------------------------------˼�����⣨δ�����---------------------------------------*/  

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAXSIZE 100

typedef char ElemType;

/*----------------------------------------���������-------------------------------------------*/ 
typedef struct BTNode
{
	ElemType Elem;
	struct BTNode *lchild,*rchild;	
}BTNode,*BTree;
/*----------------------------------------���������-------------------------------------------*/ 


/*------------------------------------------ջ����----------------------------------------------*/
typedef struct SqStack
{
	//ElemType *top;
	//ElemType *base;
	BTree *top;             //����Ӧ��ע�⣬ջ�д洢������Ϊ����������ָ�룡���� 
	BTree *base;            //��������--root = s.top;--���Ͳ���Ӧ������ͽ���ˣ� 
	int stacksize;
}SqStack;

/*��ʼ��*/
void InitStack(SqStack *S)
{
	S->base = (BTree *)malloc(MAXSIZE*sizeof(BTree));  
	if(!S->base)
		exit(-1);
	S->top = S->base;
    S->stacksize = MAXSIZE;
    //printf("Succesfully Init Stack!\n");
}

bool Empty(SqStack *S)
{
	if(S->top == S->base)
		return true;
	else
		return false;
}

/*��ջ����*/
void Push(BTree x,SqStack *S)
{
	if((S->top-S->base)>=S->stacksize)
		printf("Stack is full!\n");
	else
	{
		*S->top = x;    
		S->top += 1;  
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
BTree Top(SqStack *S)
{
	if((S->top-S->base)>=S->stacksize)
		return NULL;
	else
	{
		return *(S->top-1);  
	}	
} 
/*------------------------------------------ջ����----------------------------------------------*/


void CreateBTree(BTree *BT)                           
{
	//���õݹ�ķ�ʽ
	ElemType data;
	scanf("%c",&data);
	fflush(stdin);     
	if(data == '#')
		*BT = NULL;
	else
	{
		*BT = (BTree)malloc(sizeof(BTNode));   
		if(!BT)
			exit(-1);
		(*BT)->Elem = data;
		printf("����%c�����ӽ��:",data);
		CreateBTree(&(*BT)->lchild);
		printf("����%c�����ӽ��:",data);
		CreateBTree(&(*BT)->rchild);
	}
}

//�������������
void PreorderTraverse(BTree root)
{
	//���÷ǵݹ�ķ���
	SqStack s;
	InitStack(&s);
	while((root!=NULL)||(!Empty(&s)))
	{
		while(root!=NULL)
		{
			printf("%c",root->Elem);
			Push(root,&s);
			root = root->lchild;			
		}
		if(!Empty(&s))
		{
			
			//root = s.top;   
			//������������Ϊ�������Ͳ���Ӧ����һ�����ˣ�Ӧ�ý�ǰһ������ָ�븳��root��������ջ�У���ô����
			//�ο����������ע�ͽ�� 
			root = *(s.top-1);   //ע����ָ����top-1Ӵ���ο��ļ�SqStack_ADT.c��Push()���� 
			Pop(&s);
			root = root->rchild;
		}
	} 
} 

//�������������
void InorderTraverse(BTree root)
{
	//���÷ǵݹ�ķ���
	SqStack s;
	InitStack(&s);
	while((root!=NULL)||(!Empty(&s)))
	{
		while(root!=NULL)
		{
			Push(root,&s);
			root = root->lchild;			
		}
		if(!Empty(&s))
		{
			root = *(s.top-1);
			printf("%c",root->Elem);  
			Pop(&s);
			root = root->rchild;
		}
	} 
} 

//�������������
void PostorderTraverse(BTree root)
{
	//���÷ǵݹ�ķ���
	BTree pr;
	SqStack s;
	InitStack(&s);
	while((root!=NULL)||(!Empty(&s)))
	{
		while(root!=NULL)
		{
			Push(root,&s);
			pr = root->rchild;
			root = root->lchild;
			if(root==NULL)
				root = pr;
		}
		root = Top(&s);
		Pop(&s);
		printf("%c",root->Elem);
		if((!Empty(&s))&&(Top(&s)->lchild)==root)
			root = Top(&s)->rchild;
		else
			root = NULL;
	}
} 

//�������Ҷ�ӽ��ĸ���
int LeafCount(BTree root)
{
	//���÷ǵݹ�ķ���
	int num; 
	SqStack s;
	InitStack(&s);
	if(root == NULL)
		return 0;
	while((root!=NULL)||(!Empty(&s)))
	{
		while(root!=NULL)
		{
			Push(root,&s);
			if((root->lchild==NULL)&&(root->rchild==NULL))
				num += 1;
			root = root->lchild;
		}
		if((!Empty(&s)))
		{
			root = *(s.top-1);
			Pop(&s);
			root = root->rchild;
		}
	}
	return num;
} 
 
int main()
{
	BTree BT1;
	printf("������ڵ㣺"); 
	CreateBTree(&BT1);
	printf("������������������");
	PreorderTraverse(BT1);
	printf("\n");
	printf("������������������");
	InorderTraverse(BT1);
	printf("\n");
	printf("������������������");
	PostorderTraverse(BT1);
	printf("\n");
	printf("������Ҷ�ӽ�������%d\n",LeafCount(BT1));
	return 0;
}
 
 
