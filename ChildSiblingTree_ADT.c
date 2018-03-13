/*--@程豪琪--*/
/*--2017/11/06--*/
/*--树，存储结构：顺序存储+链式存储，表示：孩子兄弟表示法--*/

/*   ___________________________________  */
/*  |_data_|_firstchild_|_rightsibling_|  */

/*--该表示法最大的优点，就是将一棵复杂的树变成了一棵二叉树！--*/
/*--寻找结点的孩子及兄弟较为方便，但寻找双亲较为麻烦，可以在结点中添加parent指针域解决问题！--*/ 

#include<stdio.h>
#include<stdlib.h>

typedef char ElemType;


typedef struct CSNode
{
	ElemType Elem;
	struct CSNode *firstchild,*rightsib; 
}CSTNode,*CSTree;

//创建一棵树，先序遍历 
void CreateCSTree(CSTree *T)
{
	ElemType data;
	scanf("%c%*c",&data);
	if(data == '#')
		*T = NULL;
	else
	{
		*T = (CSTree)malloc(sizeof(CSTNode));
		if(!(*T))
			exit(-1);
		(*T)->Elem = data;
		printf("输入%c的第一个孩子:",data);
		CreateCSTree(&(*T)->firstchild);
		printf("输入%c的右兄弟:",data);
		CreateCSTree(&(*T)->rightsib);	
	}
} 

//返回树T结点node的双亲，若node是根，则返回空 
CSTNode *Parent(CSTNode *node,CSTree T)
{
	//递归方法，先序遍历 
	CSTNode *Temp;
	CSTNode *parent;
	if(node==T||node==NULL||T==NULL)
		return NULL;
	Temp = T->firstchild;
	while(Temp!=node&&Temp!=NULL)
	{
		parent = Parent(node,Temp);
		if(parent != NULL)
			return parent;
		Temp = Temp->rightsib;
	}
	if(Temp == node)
		return T;
	return NULL;
} 

//返回树T结点node的最左儿子。若node是叶节点，则返回空
CSTNode *LeftMostChild(CSTNode *node,CSTree T)
{
	if(node->firstchild==NULL||node==NULL||T==NULL)
		return NULL;
	return node->firstchild;
}

//返回树T结点node的右兄弟，否则返回空
CSTNode *RightSibling(CSTNode *node,CSTree T)
{
	if(node->rightsib==NULL||node==NULL||T==NULL)
		return NULL;
	return node->rightsib;	
} 

//先序遍历树
void PreorderTraverse(CSTree T)
{
	CSTNode *Temp;
	if(T == NULL)
		return;
	printf("%c",T->Elem);
	Temp = T->firstchild;
	while(Temp!=NULL)
	{
		PreorderTraverse(Temp);
		Temp = Temp->rightsib;
	}		 
} 

int main()
{
	CSTree CST;
	printf("输入根节点：");
	CreateCSTree(&CST);
	printf("%c所在结点的双亲的数据为%c！\n",CST->firstchild->rightsib->Elem,Parent(CST->firstchild->rightsib,CST)->Elem);
	printf("%c所在结点的最左儿子的数据为%c！\n",CST->firstchild->rightsib->Elem,LeftMostChild(CST->firstchild->rightsib,CST)->Elem);
	printf("%c所在结点的右兄弟的数据为%c！\n",CST->firstchild->Elem,RightSibling(CST->firstchild,CST)->Elem); 
	PreorderTraverse(CST);
	return 0;
}
