/*--@程豪琪--*/
/*--2017/11/02--*/
/*--线索二叉树，存储结构：链式存储，表示：二叉链表，| lc | ltag |data | rtag | rc |--*/
/*--ltag = 0，左孩子；ltag = 1，前驱--*/ 
/*--rtag = 0，右孩子；rtag = 1，后继--*/
/*--解决了普通二叉树的二叉链表形式浪费空间资源的问题--*/

#include<stdio.h>
#include<stdlib.h>

typedef char ElemType;

typedef struct BThrNode
{
	ElemType Elem;
	struct BThrNode *lchild,*rchild; 
	int ltag,rtag;     //线索ltag,rtag的类型可以是bool型、int型... 
}BThrNode,*BThrTree;

/*--线索化：对二叉树以某种次序遍历使其变为线索二叉树的过程--*/
/*--实质就是将二叉链表中的控指针改为指向前驱或后继的线索--*/ 

BThrTree pre;   //定义一个全局变量，始终指向刚刚访问过的结点 

/*先序创建二叉树*/
void CreateBThrTree(BThrTree *BT)
{
	ElemType data;
	scanf("%c",&data);
	fflush(stdin);
	if(data == '#')
		*BT = NULL;
	else
	{
		*BT = (BThrTree)malloc(sizeof(BThrNode));
		if(!*BT)
			exit(-1);
		(*BT)->Elem = data;
		(*BT)->ltag = 0;
		(*BT)->rtag = 0;
		printf("输入%c的左子结点:",data);
		CreateBThrTree(&(*BT)->lchild);
		printf("输入%c的右子结点:",data);
		CreateBThrTree(&(*BT)->rchild);
	}
}

/*以结点p为根节点的子树中序线索化*/
void InThreading(BThrTree p)
{
	if(p)
	{
		InThreading(p->lchild);
		if(!p->lchild)           //----线索化操作---- 
		{
			p->ltag = 1;
			p->lchild = pre;
		}
		if(!pre->rchild)
		{
			pre->rtag = 1;   
			pre->rchild = p;
		}                        //----线索化操作---- 
		pre = p;
		InThreading(p->rchild);
	}
}

/*带头节点的中序线索化*/
/*中序，对称遍历序列，相比前序和后序，适用性更强！*/
void InorderThreading(BThrTree *head,BThrTree p)
{
	*head = (BThrTree)malloc(sizeof(BThrNode));  //创建一个头节点，使二叉链形成一个闭环链 
	if(!*head)
		exit(-1);
	(*head)->ltag = 0;                           //头节点， root<--\--\ 0 \   \ 1 \ --\-->head(最后指向最右结点)。 
	(*head)->rtag = 1;
	(*head)->rchild = (*head);
	if(!p)
		(*head)->lchild = (*head);
	else
	{
		(*head)->lchild = p;
		pre = *head;
		InThreading(p);
		pre->rchild = (*head);      //最右结点的后继线索指向头节点     
		pre->rtag = 1;
		(*head)->rchild = pre;     //头节点后继线索指向最右结点 
	}
} 

/*求任意结点p的中序前驱和后继*/
/*----------------------------------------------------------------
求前驱：
1.若结点p的左子树不为空（ltag=0）,则所求结点即为其左子树的最右结点；
2.若结点p的左子树为空（ltag=1）,则所求结点即为左线索所指结点；
求后继：
1.若结点p的右子树不为空（rtag=0）,则所求结点即为其右子树最左结点；
2.若结点p的右子树为空（rtag=1）,则所求结点即为右线索所指结点；； 
-----------------------------------------------------------------*/ 
BThrNode *InorderPre(BThrNode *p)
{
	BThrNode *Q;
	Q = p->lchild;
	if(p->ltag == 0)
	{
		while(Q->rtag == 0)
			Q = Q->rchild;
	}
	return Q;
}

BThrNode *InorderNext(BThrNode *p)
{
	BThrNode *Q;
	Q = p->rchild;
	if(p->rtag == 0)
	{
		while(Q->ltag == 0)
			Q = Q->lchild;
	}
	return Q;
}

/*中序遍历二叉树，利用InorderNext()函数*/
void InorderBThrTree(BThrNode *head)
{
	BThrNode *Temp;
	Temp = head->lchild;
	while(Temp->ltag == 0)
	{
		Temp = Temp->lchild;   //先找到中序遍历的第一个结点 
	}
	do
	{
		if(Temp != head)
			printf("%c",Temp->Elem);
		Temp = InorderNext(Temp);     //接着循环，寻找后继结点，直至回到头节点 
	}while(Temp != head);
}

/*向线索二叉树插入给定结点的右儿子*/
void RInsert(BThrNode *S,BThrNode *R)
{
	//中序遍历 
	BThrNode *Temp;
	R->rchild = S->rchild;    //右儿子R指向，原结点S指向后继结点或右子树
	R->rtag = S->rtag;       
	S->rchild = R;            //结点S的右儿子即为结点R 
	S->rtag = 0;           
	R->lchild = S;            //结点R的前驱即为结点S
	R->ltag = 1;            
	if(R->rtag == 0)          //若原结点S存在右子树，现为R的右子树 
	{
		Temp = InorderNext(R);    //找到结点R的后继结点 
		Temp->lchild = R;         //该后继结点的前驱即为结点R 
	} 
}

/*向线索二叉树插入给定结点的左儿子*/
void LInsert(BThrNode *S,BThrNode *R)
{
	//中序遍历 
	BThrNode *Temp;
	R->lchild = S->lchild;      //左儿子指向，原结点S指向前驱结点或左子树    
	R->ltag = S->ltag;
	S->lchild = R;              //结点S的左儿子即为结点R
	S->ltag = 0;
	R->rchild = S;              //结点R的后继即为结点S 
	R->rtag = 1;
	if(R->ltag == 0)            //若原结点S存在左子树，现为R的左子树
	{
		Temp = InorderPre(R);   //找到结点R的前驱结点
		Temp->rchild = R;       //该前驱结点的后继即为结点R
	} 
}
 

int main()
{
	BThrTree BT1;
	BThrTree Head;

	BThrNode *Rp,*Lp;                          //初始化两个需要插入的结点Rp,Lp 
	Rp = (BThrNode *)malloc(sizeof(BThrNode));
	if(!Rp)
		exit(-1);
	Rp->Elem = 'R';
	Lp = (BThrNode *)malloc(sizeof(BThrNode));
	if(!Lp)
		exit(-1);
	Lp->Elem = 'L';
	
	printf("输入根节点：");
	CreateBThrTree(&BT1);
	InorderThreading(&Head,BT1);
	printf("%c所在结点的前驱，其数据项为：%c\n",BT1->Elem,InorderPre(BT1)->Elem);
	printf("%c所在结点的后继，其数据项为：%c\n",BT1->Elem,InorderNext(BT1)->Elem);
	printf("中序遍历结果：");
	InorderBThrTree(Head);
	printf("\n");
	RInsert(BT1,Rp);
	printf("中序遍历结果：");
	InorderBThrTree(Head);
	printf("\n");
	LInsert(BT1,Lp);
	printf("中序遍历结果：");
	InorderBThrTree(Head);
	printf("\n");
	printf("%c所在结点的前驱，其数据项为：%c\n",BT1->Elem,InorderPre(BT1)->Elem);
	printf("%c所在结点的后继，其数据项为：%c\n",BT1->Elem,InorderNext(BT1)->Elem);
	return 0;
}
