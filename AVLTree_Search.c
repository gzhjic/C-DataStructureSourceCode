/*--@�̺���--*/
/*--2018/01/02--*/
/*--���ң�ƽ������������AVL��-*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int ElemType;

typedef struct ATNode
{
	ElemType data;
	int bf;								/*--ƽ������--*/			 
	struct ATNode *lchild,*rchild;
}ATNode,*ATree;

/*--AVL�������Ҳ������ݹ�ʵ��--*/
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
		printf("����ʧ�ܣ�\n");
	}
}

/*--AVL��������������ݹ�ʵ�֣���������ɻ�ı�����������ƽ�⣡��--*/

/*--��ƽ���������������������������--*/ 
void L_Rotate(ATree *T)
{	//���� 
	ATNode *R;
	R = (*T)->rchild;
	(*T)->rchild = R->lchild;
	R->lchild = *T;
	*T = R;
}

void R_Rotate(ATree *T)
{	//���� 
	ATNode *L;
	L = (*T)->lchild;
	(*T)->lchild = L->rchild;
	L->rchild = *T;
	*T = L;
	/*--���ݽ��ָ���ָ�룬ʵ����ԭ��С��ƽ���������ڵ�*T�ĸ��ڵ㣬ָ���������ĸ��ڵ�L��(�ؽ���������)--*/
}

/*--��ƽ������������LL�͡�RR�͡�LR����RL��--*/
void L_Recover(ATree *T)
{	//LL����LR�� 
	ATNode *L,*Lr;
	L = (*T)->lchild;
	Lr = L->rchild;
	switch(L->bf)
	{
		case 1:					//LL�� 
			(*T)->bf = 0;
			L->bf = 0;
			R_Rotate(T);
			break;
		case -1:				//LR��
			switch(Lr->bf)
			{
				case 1:				//Lr���
					(*T)->bf = -1;
					L->bf = 0; 
					break;
				case 0:				//Lr�ȸ�
					(*T)->bf = 0;
					L->bf = 0;
					break;
				case -1:			//Lr�Ҹ� 
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
{	//RR����RL�� 
	ATNode *R,*Rl;
	R = (*T)->rchild;
	Rl = R->lchild;
	switch(R->bf)
	{
		case -1:				//RR�� 
			(*T)->bf = 0;
			R->bf = 0;
			L_Rotate(T);
			break;
		case 1:					//RL��
			switch(Rl->bf)
			{
				case 1:				//Rl���
					(*T)->bf = 0;
					R->bf = -1; 
					break;
				case 0:				//Rl�ȸ�
					(*T)->bf = 0;
					R->bf = 0;
					break;
				case -1:			//Rl�Ҹ� 
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
		*unbal = true;			//����Ϊ�����ݣ����Բ��룬���ܴ���ƽ�� 
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
		{	//��ƽ����ܱ�����ʱ
			switch((*T)->bf)
			{
				case 1:				//���*T�����Һ��Ӻ�(*T)->bf -1 = 0;
					(*T)->bf = 0; 
					*unbal = false; 
					break;
				case 0:				//���*T�����Һ��Ӻ�(*T)->bf -1 = -1;
					(*T)->bf = -1;
					*unbal = true;	//����ݹ����ԭ·���ز���·����·���ϵĸ��ڵ�ƽ�����Ӷ�����1��-1 
					break;
				case -1:			//���*T�����Һ��Ӻ�(*T)->bf -1 = -2(ʧȥƽ�⣬��ʱ���*TΪ��С��ƽ���������ڵ�);
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
		{	//��ƽ����ܱ�����ʱ
			switch((*T)->bf)
			{
				case 1:				//���*T�������Ӻ�(*T)->bf +1 = 2(ʧȥƽ�⣬��ʱ���*TΪ��С��ƽ���������ڵ�);
					L_Recover(T);
					*unbal = false; 
					break;
				case 0:				//���*T�������Ӻ�(*T)->bf +1 = 1
					(*T)->bf = 1;
					*unbal = true;	//����ݹ����ԭ·���ز���·����·���ϵĸ��ڵ�ƽ�����Ӷ�����1��-1
					break;
				case -1:			//���*T�������Ӻ�(*T)->bf +1 = 0
					(*T)->bf = 0;
					*unbal = false;
					break; 
			} 
			
		}
	}
	else
		*unbal = false;			//�����Ѵ��ڣ�������룬ƽ��δ������			
}


/*--AVL����ɾ���������ݹ�ʵ��--*/
/*--�������ϵĲ��ģ�����˼��һ��--*/ 


/*--�ݹ齨��AVL��--*/
ATNode *Create_ATree(ATree *T)
{
	 
	ElemType elem;
	bool unbalance = false;
	printf("���������ݣ�");
	scanf("%d",&elem);
	while(elem!=-1)
	{
		Insert_ATree(elem,T,&unbalance);
		printf("���������ݣ�");
		scanf("%d",&elem);
	}
	return *T;	
}

/*--�������������--*/
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
	printf("�������������У�"); 
	Traver_data(T);
	printf("\n");
	
	printf("�������������У�����Ӧƽ�����ӣ�"); 
	Traver_bf(T);
	printf("\n");	
}

int main()
{
	/*--��֤���У�{62,88,58,47,35,73,51,99,37,93}--*/	
	ATree T1 = NULL;
	T1 = Create_ATree(&T1);
	Print_ATree(&T1);
	return 0;
}

