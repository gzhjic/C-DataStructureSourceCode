/*--@程豪琪--*/
/*--2017/11/01--*/
/*--二叉树，存储结构：链式存储，表示：二叉链表（左右链）--*/
/*--采用了非递归的方法进行遍历--*/
/*--非递归遍历二叉树的方法有几种，这里根据教科书，利用栈，创建非递归方法--*/

/*------------------------------------思考问题（未解决）---------------------------------------
	1.非递归方法创建，复制二叉树？
	2.非递归方法求解二叉树的深度？
	3.递归方法复制二叉树？
	4.非递归方法/递归方法向二叉树插入元素？ 
------------------------------------思考问题（未解决）---------------------------------------*/  

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAXSIZE 100

typedef char ElemType;

/*----------------------------------------定义二叉链-------------------------------------------*/ 
typedef struct BTNode
{
	ElemType Elem;
	struct BTNode *lchild,*rchild;	
}BTNode,*BTree;
/*----------------------------------------定义二叉链-------------------------------------------*/ 


/*------------------------------------------栈操作----------------------------------------------*/
typedef struct SqStack
{
	//ElemType *top;
	//ElemType *base;
	BTree *top;             //这里应该注意，栈中存储的类型为二叉树根的指针！！！ 
	BTree *base;            //所以下面--root = s.top;--类型不对应的问题就解决了！ 
	int stacksize;
}SqStack;

/*初始化*/
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

/*入栈操作*/
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
BTree Top(SqStack *S)
{
	if((S->top-S->base)>=S->stacksize)
		return NULL;
	else
	{
		return *(S->top-1);  
	}	
} 
/*------------------------------------------栈操作----------------------------------------------*/


void CreateBTree(BTree *BT)                           
{
	//利用递归的方式
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
		printf("输入%c的左子结点:",data);
		CreateBTree(&(*BT)->lchild);
		printf("输入%c的右子结点:",data);
		CreateBTree(&(*BT)->rchild);
	}
}

//先序遍历二叉树
void PreorderTraverse(BTree root)
{
	//采用非递归的方法
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
			//这里编译错误，因为两边类型不对应！这一步卡了，应该将前一个结点的指针赋给root，但它在栈中，怎么处理？
			//参考代码上面的注释解答！ 
			root = *(s.top-1);   //注意是指针是top-1哟，参考文件SqStack_ADT.c的Push()函数 
			Pop(&s);
			root = root->rchild;
		}
	} 
} 

//中序遍历二叉树
void InorderTraverse(BTree root)
{
	//采用非递归的方法
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

//后序遍历二叉树
void PostorderTraverse(BTree root)
{
	//采用非递归的方法
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

//求二叉树叶子结点的个数
int LeafCount(BTree root)
{
	//采用非递归的方法
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
	printf("输入根节点："); 
	CreateBTree(&BT1);
	printf("先序遍历二叉树结果：");
	PreorderTraverse(BT1);
	printf("\n");
	printf("中序遍历二叉树结果：");
	InorderTraverse(BT1);
	printf("\n");
	printf("后序遍历二叉树结果：");
	PostorderTraverse(BT1);
	printf("\n");
	printf("二叉树叶子结点个数：%d\n",LeafCount(BT1));
	return 0;
}
 
 
