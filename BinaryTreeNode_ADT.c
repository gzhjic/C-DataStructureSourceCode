/*--@程豪琪--*/
/*--2017/10/30--*/
/*--二叉树，存储结构：链式存储，表示：二叉链表（左右链）--*/
/*--解决了顺序存储适用性不强的问题，但是存储空间没有被很好的利用！--*/
/*--采用了递归的方法进行遍历--*/

#include<stdio.h>
#include<stdlib.h>

typedef char ElemType;

typedef struct BTNode
{
	ElemType Elem;
	struct BTNode *lchild,*rchild;
}BTNode,*BTree;

/*-------------------------------------------------------------------------------- 

//建立一颗空的二叉树
void Empty(BTree BT)
{
	BT = (BTree)malloc(sizeof(BTNode));  //malloc()返回分配域的指针，否则返回NULL 
	if(!BT)
		exit(-1);
}

****不知道为什么？我在其他函数中调用Empty()老是出错，但是传递的应该是指针啊！****
****或许是因为- BTree BT -这种定义，BT是形参？**** 
 
-----------------------------------------------------------------------------------*/ 

/*----------------------------------------------------------------------------------
//先序遍历的顺序，建立一颗新的二叉树
void CreateBTree(BTree BT)                //接上面的问题，- BTree BT -这种定义，BT是形参？ 
{
	//利用递归的方式                     //当然是形参，即指针作形参！ 
	ElemType data;                       //而且一般指针作函数形参是为了修改实参的值，即指针指向的值 
	scanf("%c",&data);
	fflush(stdin);      
	if(data == '#')
		BT = NULL;
	else
	{
		BT = (BTree)malloc(sizeof(BTNode));   //然而[如果函数的参数是一个指针，不要指望用该指针去申请动态内存]！！！ 
		if(!BT)                               //显然这一行就是错误的做法。参考：http://blog.csdn.net/lpp1989/article/details/7767109 
			exit(-1);
		BT->Elem = data;
		printf("输入%c的左子结点:",data);
		CreateBTree(BT->lchild);
		printf("输入%c的右子结点:",data);
		CreateBTree(BT->rchild);
	}
} 
****解决了调用上述引用中的Empty()，CreateBTree()老是运行出错的问题。**** 
****原因：指针未处理好！****
-----------------------------------------------------------------------------------*/
void CreateBTree(BTree *BT)                           
{
	//利用递归的方式
	ElemType data;
	scanf("%c",&data);
	fflush(stdin);   //你可以试着删除这一句看看会发生什么现象！链接：http://blog.csdn.net/hao5743/article/details/6939661  
	if(data == '#')
		*BT = NULL;
	else
	{
		*BT = (BTree)malloc(sizeof(BTNode));   //如果非要使用函数指针来申请内存空间，那么需要使用指向指针的指针！ 
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
void PreorderTraverse(BTree BT)
{
	if(BT == NULL)
		return;
	printf("%c",BT->Elem);
	PreorderTraverse(BT->lchild);
	PreorderTraverse(BT->rchild);
} 

//中序遍历二叉树
void InorderTraverse(BTree BT)
{
	if(BT == NULL)
		return;
	InorderTraverse(BT->lchild);
	printf("%c",BT->Elem);
	InorderTraverse(BT->rchild);
}

//后序遍历二叉树
void PostorderTraverse(BTree BT)
{
	if(BT == NULL)
		return;
	PostorderTraverse(BT->lchild);
	PostorderTraverse(BT->rchild);
	printf("%c",BT->Elem);
} 

//求取二叉树的深度
int TreeDepth(BTree BT)
{
	int depth;
	int leftDepth,rightDepth;
	depth = 0;
	if(BT)
	{
		leftDepth = TreeDepth(BT->lchild);    //左子树的高度返回给leftDepth 
		rightDepth = TreeDepth(BT->rchild);   //右子树的高度返回给rightDepth
		depth = leftDepth>=rightDepth?leftDepth+1:rightDepth+1;  
	}
	return depth;         //递归返回的是当前子树的depth 
} 

//求取叶子结点的个数
int LeafCount(BTree BT)
{
	int leftNum,rightNum;
	if(!BT)
		return 0; 
	if((!BT->rchild)&&(!BT->lchild))
		return 1;
	else
	{
		leftNum = LeafCount(BT->lchild);
		rightNum = LeafCount(BT->rchild);
		return leftNum + rightNum;
	}
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
	printf("二叉树的深度：%d\n",TreeDepth(BT1));
	printf("二叉树的叶子结点个数：%d\n",LeafCount(BT1)); 
	return 0;
}
 

