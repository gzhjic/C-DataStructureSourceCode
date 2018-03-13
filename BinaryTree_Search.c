/*--@程豪琪--*/
/*--2018/01/02--*/
/*--查找：二叉查找树-*/

#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;


typedef struct BSTNode
{
	ElemType data;
	struct BSTNode	*lchild,*rchild;
}BSTNode,*BSTree;

/*--二叉查找树，查找操作，递归实现--*/
BSTNode	*Search_BSTree(ElemType key,BSTree *T)
{
	if(*T!=NULL)
	{
		if(key > (*T)->data)
			return Search_BSTree(key,&(*T)->rchild);
		else if(key < (*T)->data)
			return Search_BSTree(key,&(*T)->lchild);
		else
			return *T;
	}
	else
	{
		return NULL;
		printf("查找失败！\n");
	}
}

/*--二叉查找树，查找操作，非递归实现--*/
BSTNode *NRSearch_BSTree(ElemType key,BSTree *T)
{
	BSTNode *temp;
	temp = *T;
	while(temp!=NULL)
	{
		if(key > temp->data)
			temp = temp->rchild;
		else if(key < temp->data)
			temp = temp->lchild;
		else
			return temp;
	}
	
	return NULL;
	printf("查找失败！\n");
	
}

/*--二叉查找树，插入操作，递归实现--*/
void Insert_BSTree(ElemType key,BSTree *T)
{
	if(!*T)
	{
		*T = (BSTNode*)malloc(sizeof(BSTNode));
		if(!*T)
			exit(-1);
		(*T)->data = key;
		(*T)->lchild = (*T)->rchild = NULL;
	}	
	else
	{
		if(key > (*T)->data)
			Insert_BSTree(key,&(*T)->rchild);
		else if(key < (*T)->data)
			Insert_BSTree(key,&(*T)->lchild);
		else
			printf("数据已存在，无需插入！\n");
	
	}
}

/*--二叉查找树，插入操作，非递归实现--*/
void NRInsert_BSTree(ElemType key,BSTree *T)
{
	BSTNode *temp,*par;
	temp = *T;
	par = *T;
	
	while(temp!=NULL)
	{
		if(key > temp->data)
		{
			par = temp;
			temp = temp->rchild;			
		}	
		else if(key < temp->data)
		{
			par = temp;
			temp = temp->lchild;
		}
		else
			printf("数据已存在，无需插入！\n");
	}
	
	temp = (BSTNode*)malloc(sizeof(BSTNode));
	if(!temp)
		exit(-1);
	temp->data = key;
	temp->lchild = temp->rchild = NULL; 
	
	/*--由于是结点的指针申请动态空间，而非结点指针的指针，所以需要将新插入结点与原二叉树连接！--*/
	if(par!=NULL && par->data > temp->data)				 
		par->lchild = temp;								//新插入的结点是原二叉树叶节点par的左子树
	else if(par!=NULL && par->data < temp->data)		
		par->rchild = temp;								//新插入的结点是原二叉树叶节点par的右子树
} 

/*--二叉查找树，删除操作，递归实现--*/
void Delete(BSTree *T)
{
	BSTNode *p,*s,*par;
	p = *T;
	if(p->lchild == NULL)		//仅左子树为空或为叶节点 
	{
		*T = (*T)->rchild;
		free(p);
	}
	else if(p->rchild == NULL)	//仅右子树为空 
	{
		*T = (*T)->lchild;
		free(p);
	}
	else						//左右子树都存在 
	{
		par = *T;
		s = (*T)->lchild;
		while(s->rchild!=NULL)
		{
			par = s;
			s = s->rchild; 
		}
		(*T)->data = s->data;
		if(par!=(*T))
			par->rchild = s->lchild;
		else
			par->lchild = s->lchild;
		
		free(s);		 
	} 
}

void Delete_BSTree(ElemType key,BSTree *T)
{
	if(*T!=NULL)
	{
		if(key > (*T)->data)
			Delete_BSTree(key,&(*T)->rchild);
		else if(key < (*T)->data)
			Delete_BSTree(key,&(*T)->lchild);
		else
			Delete(T);
	}
	else
		printf("删除失败！\n"); 
} 

/*--二叉查找树，删除操作，非递归实现--*/
void NRDelete_BSTree(ElemType key,BSTree *T)
{
	BSTNode *p,*s,*par;
	p = *T;
	par = *T;
	while(p!=NULL)
	{
		if(key > p->data)
		{
			par = p;
			p = p->rchild;
		}	
		else if(key < p->data)
		{
			par = p;
			p = p->lchild;
		}
			
		else
			break; 
	}
	
	if(!p)
		printf("删除失败！\n");
	else
	{
		if(p->lchild == NULL)							//仅左子树为空或为叶节点
		{
			if(par!=NULL && par->data < p->data)			//p是par的右子树 
				par->rchild = p->rchild;
			else if(par!=NULL && par->data > p->data)		//p是par的左子树
				par->lchild = p->rchild;	
			free(p);
		}
		else if(p->rchild == NULL)						//仅右子树为空
		{
			if(par!=NULL && par->data < p->data)			//p是par的右子树 
				par->rchild = p->lchild;
			else if(par!=NULL && par->data > p->data)		//p是par的左子树
				par->lchild = p->lchild;
			free(p);
		}
		else											//左右子树都存在
		{
			par = p;
			s = p->lchild;
			while(s->rchild!=NULL)
			{
				par = s;
				s = s->rchild;
			}	
			p->data = s->data;
			if(par!=p)
				par->rchild = s->lchild;
			else
				par->lchild = s->lchild;
			
			free(s);
		} 
	}
}

/*--递归建立二叉查找树--*/
BSTNode *Create_BSTree(BSTree *T)
{
	//*T = NULL;					//建立树*T时，因为指针*T未初始化，所以指针*T值随机分配，是未知的！ 
	 
	ElemType elem;
	printf("输入结点数据：");
	scanf("%d",&elem);
	while(elem!=-1)
	{
		Insert_BSTree(elem,T);
		printf("输入结点数据：");
		scanf("%d",&elem);
	}
	return *T;	
}

/*--中序遍历二叉树--*/
void Traver_BSTree(BSTree *T)
{
	if(!(*T))
		return;
	Traver_BSTree(&(*T)->lchild);
	printf("%d|",(*T)->data);
	Traver_BSTree(&(*T)->rchild);
} 

void Print_BSTree(BSTree *T)
{
	printf("二叉排序树序列："); 
	Traver_BSTree(T);
	printf("\n");	
}

int main()
{
	/*--验证序列：{62,88,58,47,35,73,51,99,37,93}--*/
	BSTree T1;					//此时指针T1未知，是随机的,并不为空！
	T1 = NULL; 					//故应先初始化 
	BSTNode *ret1,*ret2;

	T1 = Create_BSTree(&T1);
	Print_BSTree(&T1);

	ret1 = Search_BSTree(51,&T1);
	printf("查找结果：%d\n",ret1->data); 
	ret2 = NRSearch_BSTree(93,&T1);
	printf("查找结果：%d\n",ret2->data);
	
	printf("----------非递归插入----------\n"); 
	NRInsert_BSTree(20,&T1);
	Print_BSTree(&T1);	
	
	printf("-----------递归删除-----------\n"); 
	Delete_BSTree(47,&T1);
	Print_BSTree(&T1);
	
	printf("----------非递归删除----------\n"); 
	NRDelete_BSTree(47,&T1);
	Print_BSTree(&T1);
	
	return 0;
}

