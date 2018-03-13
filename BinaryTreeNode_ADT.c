/*--@�̺���--*/
/*--2017/10/30--*/
/*--���������洢�ṹ����ʽ�洢����ʾ������������������--*/
/*--�����˳��洢�����Բ�ǿ�����⣬���Ǵ洢�ռ�û�б��ܺõ����ã�--*/
/*--�����˵ݹ�ķ������б���--*/

#include<stdio.h>
#include<stdlib.h>

typedef char ElemType;

typedef struct BTNode
{
	ElemType Elem;
	struct BTNode *lchild,*rchild;
}BTNode,*BTree;

/*-------------------------------------------------------------------------------- 

//����һ�ſյĶ�����
void Empty(BTree BT)
{
	BT = (BTree)malloc(sizeof(BTNode));  //malloc()���ط������ָ�룬���򷵻�NULL 
	if(!BT)
		exit(-1);
}

****��֪��Ϊʲô���������������е���Empty()���ǳ������Ǵ��ݵ�Ӧ����ָ�밡��****
****��������Ϊ- BTree BT -���ֶ��壬BT���βΣ�**** 
 
-----------------------------------------------------------------------------------*/ 

/*----------------------------------------------------------------------------------
//���������˳�򣬽���һ���µĶ�����
void CreateBTree(BTree BT)                //����������⣬- BTree BT -���ֶ��壬BT���βΣ� 
{
	//���õݹ�ķ�ʽ                     //��Ȼ���βΣ���ָ�����βΣ� 
	ElemType data;                       //����һ��ָ���������β���Ϊ���޸�ʵ�ε�ֵ����ָ��ָ���ֵ 
	scanf("%c",&data);
	fflush(stdin);      
	if(data == '#')
		BT = NULL;
	else
	{
		BT = (BTree)malloc(sizeof(BTNode));   //Ȼ��[��������Ĳ�����һ��ָ�룬��Ҫָ���ø�ָ��ȥ���붯̬�ڴ�]������ 
		if(!BT)                               //��Ȼ��һ�о��Ǵ�����������ο���http://blog.csdn.net/lpp1989/article/details/7767109 
			exit(-1);
		BT->Elem = data;
		printf("����%c�����ӽ��:",data);
		CreateBTree(BT->lchild);
		printf("����%c�����ӽ��:",data);
		CreateBTree(BT->rchild);
	}
} 
****����˵������������е�Empty()��CreateBTree()�������г�������⡣**** 
****ԭ��ָ��δ����ã�****
-----------------------------------------------------------------------------------*/
void CreateBTree(BTree *BT)                           
{
	//���õݹ�ķ�ʽ
	ElemType data;
	scanf("%c",&data);
	fflush(stdin);   //���������ɾ����һ�俴���ᷢ��ʲô�������ӣ�http://blog.csdn.net/hao5743/article/details/6939661  
	if(data == '#')
		*BT = NULL;
	else
	{
		*BT = (BTree)malloc(sizeof(BTNode));   //�����Ҫʹ�ú���ָ���������ڴ�ռ䣬��ô��Ҫʹ��ָ��ָ���ָ�룡 
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
void PreorderTraverse(BTree BT)
{
	if(BT == NULL)
		return;
	printf("%c",BT->Elem);
	PreorderTraverse(BT->lchild);
	PreorderTraverse(BT->rchild);
} 

//�������������
void InorderTraverse(BTree BT)
{
	if(BT == NULL)
		return;
	InorderTraverse(BT->lchild);
	printf("%c",BT->Elem);
	InorderTraverse(BT->rchild);
}

//�������������
void PostorderTraverse(BTree BT)
{
	if(BT == NULL)
		return;
	PostorderTraverse(BT->lchild);
	PostorderTraverse(BT->rchild);
	printf("%c",BT->Elem);
} 

//��ȡ�����������
int TreeDepth(BTree BT)
{
	int depth;
	int leftDepth,rightDepth;
	depth = 0;
	if(BT)
	{
		leftDepth = TreeDepth(BT->lchild);    //�������ĸ߶ȷ��ظ�leftDepth 
		rightDepth = TreeDepth(BT->rchild);   //�������ĸ߶ȷ��ظ�rightDepth
		depth = leftDepth>=rightDepth?leftDepth+1:rightDepth+1;  
	}
	return depth;         //�ݹ鷵�ص��ǵ�ǰ������depth 
} 

//��ȡҶ�ӽ��ĸ���
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
	printf("����������ȣ�%d\n",TreeDepth(BT1));
	printf("��������Ҷ�ӽ�������%d\n",LeafCount(BT1)); 
	return 0;
}
 

