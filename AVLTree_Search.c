/*--@程豪琪--*/
/*--2018/01/02--*/
/*--查找：平衡二叉查找树，AVL树-*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int ElemType;

typedef struct ATNode
{
	ElemType data;
	int bf;								/*--平衡因子--*/			 
	struct ATNode *lchild,*rchild;
}ATNode,*ATree;

/*--AVL树，查找操作，递归实现--*/
ATNode	*Search_ATree(ElemType key,ATree *T)
{
	if(*T!=NULL)
	{
		if(key > (*T)->data)
			return Search_ATree(key,&(*T)->rchild);
		else if(key < (*T)->data)
			return Search_ATree(key,&(*T)->lchild);
		else
			return *T;
	}
	else
	{
		return NULL;
		printf("查找失败！\n");
	}
}

/*--AVL树，插入操作，递归实现（插入操作可会改变二叉查找树的平衡！）--*/

/*--再平衡的两个基本操作：左旋和右旋--*/ 
void L_Rotate(ATree *T)
{	//左旋 
	ATNode *R;
	R = (*T)->rchild;
	(*T)->rchild = R->lchild;
	R->lchild = *T;
	*T = R;
}

void R_Rotate(ATree *T)
{	//右旋 
	ATNode *L;
	L = (*T)->lchild;
	(*T)->lchild = L->rchild;
	L->rchild = *T;
	*T = L;
	/*--传递结点指针的指针，实现了原最小不平衡子树根节点*T的父节点，指向新子树的根节点L。(重接子树操作)--*/
}

/*--再平衡的四种情况：LL型、RR型、LR型与RL型--*/
void L_Recover(ATree *T)
{	//LL型与LR型 
	ATNode *L,*Lr;
	L = (*T)->lchild;
	Lr = L->rchild;
	switch(L->bf)
	{
		case 1:					//LL型 
			(*T)->bf = 0;
			L->bf = 0;
			R_Rotate(T);
			break;
		case -1:				//LR型
			switch(Lr->bf)
			{
				case 1:				//Lr左高
					(*T)->bf = -1;
					L->bf = 0; 
					break;
				case 0:				//Lr等高
					(*T)->bf = 0;
					L->bf = 0;
					break;
				case -1:			//Lr右高 
					(*T)->bf = 0;
					L->bf = 1; 
					break;
			}
			Lr->bf = 0;
			L_Rotate(&(*T)->lchild);
			R_Rotate(T); 
			break;
	} 
} 

void R_Recover(ATree *T)
{	//RR型与RL型 
	ATNode *R,*Rl;
	R = (*T)->rchild;
	Rl = R->lchild;
	switch(R->bf)
	{
		case -1:				//RR型 
			(*T)->bf = 0;
			R->bf = 0;
			L_Rotate(T);
			break;
		case 1:					//RL型
			switch(Rl->bf)
			{
				case 1:				//Rl左高
					(*T)->bf = 0;
					R->bf = -1; 
					break;
				case 0:				//Rl等高
					(*T)->bf = 0;
					R->bf = 0;
					break;
				case -1:			//Rl右高 
					(*T)->bf = 1;
					R->bf = 0; 
					break;
			}
			Rl->bf = 0;
			R_Rotate(&(*T)->rchild);
			L_Rotate(T); 
			break;
	} 
} 

void Insert_ATree(ElemType key,ATree *T,bool *unbal)
{
	if(!*T)
	{
		*unbal = true;			//数据为新数据，可以插入，可能打破平衡 
		*T = (ATNode*)malloc(sizeof(ATNode));
		if(!*T)
			exit(-1);
		(*T)->bf = 0;
		(*T)->data = key;
		(*T)->lchild = (*T)->rchild = NULL;
	}
	else if(key > (*T)->data)
	{
		Insert_ATree(key,&(*T)->rchild,unbal);
		if(*unbal)
		{	//当平衡可能被打破时
			switch((*T)->bf)
			{
				case 1:				//结点*T插入右孩子后，(*T)->bf -1 = 0;
					(*T)->bf = 0; 
					*unbal = false; 
					break;
				case 0:				//结点*T插入右孩子后，(*T)->bf -1 = -1;
					(*T)->bf = -1;
					*unbal = true;	//跟随递归过程原路返回查找路径，路径上的父节点平衡因子都会变成1或-1 
					break;
				case -1:			//结点*T插入右孩子后，(*T)->bf -1 = -2(失去平衡，此时结点*T为最小不平衡子树根节点);
					R_Recover(T);
					*unbal = false; 
					break; 
			} 
		}	
	}
	else if(key < (*T)->data)
	{
		Insert_ATree(key,&(*T)->lchild,unbal);
		if(*unbal)
		{	//当平衡可能被打破时
			switch((*T)->bf)
			{
				case 1:				//结点*T插入左孩子后，(*T)->bf +1 = 2(失去平衡，此时结点*T为最小不平衡子树根节点);
					L_Recover(T);
					*unbal = false; 
					break;
				case 0:				//结点*T插入左孩子后，(*T)->bf +1 = 1
					(*T)->bf = 1;
					*unbal = true;	//跟随递归过程原路返回查找路径，路径上的父节点平衡因子都会变成1或-1
					break;
				case -1:			//结点*T插入左孩子后，(*T)->bf +1 = 0
					(*T)->bf = 0;
					*unbal = false;
					break; 
			} 
			
		}
	}
	else
		*unbal = false;			//数据已存在，无需插入，平衡未被打破			
}


/*--AVL树，删除操作，递归实现--*/
/*--看了网上的博文，可以思考一下--*/ 


/*--递归建立AVL树--*/
ATNode *Create_ATree(ATree *T)
{
	 
	ElemType elem;
	bool unbalance = false;
	printf("输入结点数据：");
	scanf("%d",&elem);
	while(elem!=-1)
	{
		Insert_ATree(elem,T,&unbalance);
		printf("输入结点数据：");
		scanf("%d",&elem);
	}
	return *T;	
}

/*--中序遍历二叉树--*/
void Traver_data(ATree *T)
{
	if(!(*T))
		return;
	Traver_data(&(*T)->lchild);
	printf("%d|",(*T)->data);
	Traver_data(&(*T)->rchild);
} 

void Traver_bf(ATree *T)
{
	if(!(*T))
		return;
	Traver_bf(&(*T)->lchild);
	printf("%d|",(*T)->bf);
	Traver_bf(&(*T)->rchild);
} 

void Print_ATree(ATree *T)
{
	printf("二叉排序树序列："); 
	Traver_data(T);
	printf("\n");
	
	printf("二叉排序树序列，结点对应平衡因子："); 
	Traver_bf(T);
	printf("\n");	
}

int main()
{
	/*--验证序列：{62,88,58,47,35,73,51,99,37,93}--*/	
	ATree T1 = NULL;
	T1 = Create_ATree(&T1);
	Print_ATree(&T1);
	return 0;
}

