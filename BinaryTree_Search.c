/*--@�̺���--*/
/*--2018/01/02--*/
/*--���ң����������-*/

#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;


typedef struct BSTNode
{
	ElemType data;
	struct BSTNode	*lchild,*rchild;
}BSTNode,*BSTree;

/*--��������������Ҳ������ݹ�ʵ��--*/
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
		printf("����ʧ�ܣ�\n");
	}
}

/*--��������������Ҳ������ǵݹ�ʵ��--*/
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
	printf("����ʧ�ܣ�\n");
	
}

/*--���������������������ݹ�ʵ��--*/
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
			printf("�����Ѵ��ڣ�������룡\n");
	
	}
}

/*--���������������������ǵݹ�ʵ��--*/
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
			printf("�����Ѵ��ڣ�������룡\n");
	}
	
	temp = (BSTNode*)malloc(sizeof(BSTNode));
	if(!temp)
		exit(-1);
	temp->data = key;
	temp->lchild = temp->rchild = NULL; 
	
	/*--�����ǽ���ָ�����붯̬�ռ䣬���ǽ��ָ���ָ�룬������Ҫ���²�������ԭ���������ӣ�--*/
	if(par!=NULL && par->data > temp->data)				 
		par->lchild = temp;								//�²���Ľ����ԭ������Ҷ�ڵ�par��������
	else if(par!=NULL && par->data < temp->data)		
		par->rchild = temp;								//�²���Ľ����ԭ������Ҷ�ڵ�par��������
} 

/*--�����������ɾ���������ݹ�ʵ��--*/
void Delete(BSTree *T)
{
	BSTNode *p,*s,*par;
	p = *T;
	if(p->lchild == NULL)		//��������Ϊ�ջ�ΪҶ�ڵ� 
	{
		*T = (*T)->rchild;
		free(p);
	}
	else if(p->rchild == NULL)	//��������Ϊ�� 
	{
		*T = (*T)->lchild;
		free(p);
	}
	else						//�������������� 
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
		printf("ɾ��ʧ�ܣ�\n"); 
} 

/*--�����������ɾ���������ǵݹ�ʵ��--*/
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
		printf("ɾ��ʧ�ܣ�\n");
	else
	{
		if(p->lchild == NULL)							//��������Ϊ�ջ�ΪҶ�ڵ�
		{
			if(par!=NULL && par->data < p->data)			//p��par�������� 
				par->rchild = p->rchild;
			else if(par!=NULL && par->data > p->data)		//p��par��������
				par->lchild = p->rchild;	
			free(p);
		}
		else if(p->rchild == NULL)						//��������Ϊ��
		{
			if(par!=NULL && par->data < p->data)			//p��par�������� 
				par->rchild = p->lchild;
			else if(par!=NULL && par->data > p->data)		//p��par��������
				par->lchild = p->lchild;
			free(p);
		}
		else											//��������������
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

/*--�ݹ齨�����������--*/
BSTNode *Create_BSTree(BSTree *T)
{
	//*T = NULL;					//������*Tʱ����Ϊָ��*Tδ��ʼ��������ָ��*Tֵ������䣬��δ֪�ģ� 
	 
	ElemType elem;
	printf("���������ݣ�");
	scanf("%d",&elem);
	while(elem!=-1)
	{
		Insert_BSTree(elem,T);
		printf("���������ݣ�");
		scanf("%d",&elem);
	}
	return *T;	
}

/*--�������������--*/
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
	printf("�������������У�"); 
	Traver_BSTree(T);
	printf("\n");	
}

int main()
{
	/*--��֤���У�{62,88,58,47,35,73,51,99,37,93}--*/
	BSTree T1;					//��ʱָ��T1δ֪���������,����Ϊ�գ�
	T1 = NULL; 					//��Ӧ�ȳ�ʼ�� 
	BSTNode *ret1,*ret2;

	T1 = Create_BSTree(&T1);
	Print_BSTree(&T1);

	ret1 = Search_BSTree(51,&T1);
	printf("���ҽ����%d\n",ret1->data); 
	ret2 = NRSearch_BSTree(93,&T1);
	printf("���ҽ����%d\n",ret2->data);
	
	printf("----------�ǵݹ����----------\n"); 
	NRInsert_BSTree(20,&T1);
	Print_BSTree(&T1);	
	
	printf("-----------�ݹ�ɾ��-----------\n"); 
	Delete_BSTree(47,&T1);
	Print_BSTree(&T1);
	
	printf("----------�ǵݹ�ɾ��----------\n"); 
	NRDelete_BSTree(47,&T1);
	Print_BSTree(&T1);
	
	return 0;
}

