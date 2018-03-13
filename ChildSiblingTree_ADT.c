/*--@�̺���--*/
/*--2017/11/06--*/
/*--�����洢�ṹ��˳��洢+��ʽ�洢����ʾ�������ֵܱ�ʾ��--*/

/*   ___________________________________  */
/*  |_data_|_firstchild_|_rightsibling_|  */

/*--�ñ�ʾ�������ŵ㣬���ǽ�һ�ø��ӵ��������һ�ö�������--*/
/*--Ѱ�ҽ��ĺ��Ӽ��ֵܽ�Ϊ���㣬��Ѱ��˫�׽�Ϊ�鷳�������ڽ�������parentָ���������⣡--*/ 

#include<stdio.h>
#include<stdlib.h>

typedef char ElemType;


typedef struct CSNode
{
	ElemType Elem;
	struct CSNode *firstchild,*rightsib; 
}CSTNode,*CSTree;

//����һ������������� 
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
		printf("����%c�ĵ�һ������:",data);
		CreateCSTree(&(*T)->firstchild);
		printf("����%c�����ֵ�:",data);
		CreateCSTree(&(*T)->rightsib);	
	}
} 

//������T���node��˫�ף���node�Ǹ����򷵻ؿ� 
CSTNode *Parent(CSTNode *node,CSTree T)
{
	//�ݹ鷽����������� 
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

//������T���node��������ӡ���node��Ҷ�ڵ㣬�򷵻ؿ�
CSTNode *LeftMostChild(CSTNode *node,CSTree T)
{
	if(node->firstchild==NULL||node==NULL||T==NULL)
		return NULL;
	return node->firstchild;
}

//������T���node�����ֵܣ����򷵻ؿ�
CSTNode *RightSibling(CSTNode *node,CSTree T)
{
	if(node->rightsib==NULL||node==NULL||T==NULL)
		return NULL;
	return node->rightsib;	
} 

//���������
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
	printf("������ڵ㣺");
	CreateCSTree(&CST);
	printf("%c���ڽ���˫�׵�����Ϊ%c��\n",CST->firstchild->rightsib->Elem,Parent(CST->firstchild->rightsib,CST)->Elem);
	printf("%c���ڽ���������ӵ�����Ϊ%c��\n",CST->firstchild->rightsib->Elem,LeftMostChild(CST->firstchild->rightsib,CST)->Elem);
	printf("%c���ڽ������ֵܵ�����Ϊ%c��\n",CST->firstchild->Elem,RightSibling(CST->firstchild,CST)->Elem); 
	PreorderTraverse(CST);
	return 0;
}
