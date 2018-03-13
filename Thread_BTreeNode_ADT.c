/*--@�̺���--*/
/*--2017/11/02--*/
/*--�������������洢�ṹ����ʽ�洢����ʾ����������| lc | ltag |data | rtag | rc |--*/
/*--ltag = 0�����ӣ�ltag = 1��ǰ��--*/ 
/*--rtag = 0���Һ��ӣ�rtag = 1�����--*/
/*--�������ͨ�������Ķ���������ʽ�˷ѿռ���Դ������--*/

#include<stdio.h>
#include<stdlib.h>

typedef char ElemType;

typedef struct BThrNode
{
	ElemType Elem;
	struct BThrNode *lchild,*rchild; 
	int ltag,rtag;     //����ltag,rtag�����Ϳ�����bool�͡�int��... 
}BThrNode,*BThrTree;

/*--���������Զ�������ĳ�ִ������ʹ���Ϊ�����������Ĺ���--*/
/*--ʵ�ʾ��ǽ����������еĿ�ָ���Ϊָ��ǰ�����̵�����--*/ 

BThrTree pre;   //����һ��ȫ�ֱ�����ʼ��ָ��ոշ��ʹ��Ľ�� 

/*���򴴽�������*/
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
		printf("����%c�����ӽ��:",data);
		CreateBThrTree(&(*BT)->lchild);
		printf("����%c�����ӽ��:",data);
		CreateBThrTree(&(*BT)->rchild);
	}
}

/*�Խ��pΪ���ڵ����������������*/
void InThreading(BThrTree p)
{
	if(p)
	{
		InThreading(p->lchild);
		if(!p->lchild)           //----����������---- 
		{
			p->ltag = 1;
			p->lchild = pre;
		}
		if(!pre->rchild)
		{
			pre->rtag = 1;   
			pre->rchild = p;
		}                        //----����������---- 
		pre = p;
		InThreading(p->rchild);
	}
}

/*��ͷ�ڵ������������*/
/*���򣬶ԳƱ������У����ǰ��ͺ��������Ը�ǿ��*/
void InorderThreading(BThrTree *head,BThrTree p)
{
	*head = (BThrTree)malloc(sizeof(BThrNode));  //����һ��ͷ�ڵ㣬ʹ�������γ�һ���ջ��� 
	if(!*head)
		exit(-1);
	(*head)->ltag = 0;                           //ͷ�ڵ㣬 root<--\--\ 0 \   \ 1 \ --\-->head(���ָ�����ҽ��)�� 
	(*head)->rtag = 1;
	(*head)->rchild = (*head);
	if(!p)
		(*head)->lchild = (*head);
	else
	{
		(*head)->lchild = p;
		pre = *head;
		InThreading(p);
		pre->rchild = (*head);      //���ҽ��ĺ������ָ��ͷ�ڵ�     
		pre->rtag = 1;
		(*head)->rchild = pre;     //ͷ�ڵ�������ָ�����ҽ�� 
	}
} 

/*��������p������ǰ���ͺ��*/
/*----------------------------------------------------------------
��ǰ����
1.�����p����������Ϊ�գ�ltag=0��,�������㼴Ϊ�������������ҽ�㣻
2.�����p��������Ϊ�գ�ltag=1��,�������㼴Ϊ��������ָ��㣻
���̣�
1.�����p����������Ϊ�գ�rtag=0��,�������㼴Ϊ�������������㣻
2.�����p��������Ϊ�գ�rtag=1��,�������㼴Ϊ��������ָ��㣻�� 
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

/*�������������������InorderNext()����*/
void InorderBThrTree(BThrNode *head)
{
	BThrNode *Temp;
	Temp = head->lchild;
	while(Temp->ltag == 0)
	{
		Temp = Temp->lchild;   //���ҵ���������ĵ�һ����� 
	}
	do
	{
		if(Temp != head)
			printf("%c",Temp->Elem);
		Temp = InorderNext(Temp);     //����ѭ����Ѱ�Һ�̽�㣬ֱ���ص�ͷ�ڵ� 
	}while(Temp != head);
}

/*������������������������Ҷ���*/
void RInsert(BThrNode *S,BThrNode *R)
{
	//������� 
	BThrNode *Temp;
	R->rchild = S->rchild;    //�Ҷ���Rָ��ԭ���Sָ���̽���������
	R->rtag = S->rtag;       
	S->rchild = R;            //���S���Ҷ��Ӽ�Ϊ���R 
	S->rtag = 0;           
	R->lchild = S;            //���R��ǰ����Ϊ���S
	R->ltag = 1;            
	if(R->rtag == 0)          //��ԭ���S��������������ΪR�������� 
	{
		Temp = InorderNext(R);    //�ҵ����R�ĺ�̽�� 
		Temp->lchild = R;         //�ú�̽���ǰ����Ϊ���R 
	} 
}

/*����������������������������*/
void LInsert(BThrNode *S,BThrNode *R)
{
	//������� 
	BThrNode *Temp;
	R->lchild = S->lchild;      //�����ָ��ԭ���Sָ��ǰ������������    
	R->ltag = S->ltag;
	S->lchild = R;              //���S������Ӽ�Ϊ���R
	S->ltag = 0;
	R->rchild = S;              //���R�ĺ�̼�Ϊ���S 
	R->rtag = 1;
	if(R->ltag == 0)            //��ԭ���S��������������ΪR��������
	{
		Temp = InorderPre(R);   //�ҵ����R��ǰ�����
		Temp->rchild = R;       //��ǰ�����ĺ�̼�Ϊ���R
	} 
}
 

int main()
{
	BThrTree BT1;
	BThrTree Head;

	BThrNode *Rp,*Lp;                          //��ʼ��������Ҫ����Ľ��Rp,Lp 
	Rp = (BThrNode *)malloc(sizeof(BThrNode));
	if(!Rp)
		exit(-1);
	Rp->Elem = 'R';
	Lp = (BThrNode *)malloc(sizeof(BThrNode));
	if(!Lp)
		exit(-1);
	Lp->Elem = 'L';
	
	printf("������ڵ㣺");
	CreateBThrTree(&BT1);
	InorderThreading(&Head,BT1);
	printf("%c���ڽ���ǰ������������Ϊ��%c\n",BT1->Elem,InorderPre(BT1)->Elem);
	printf("%c���ڽ��ĺ�̣���������Ϊ��%c\n",BT1->Elem,InorderNext(BT1)->Elem);
	printf("������������");
	InorderBThrTree(Head);
	printf("\n");
	RInsert(BT1,Rp);
	printf("������������");
	InorderBThrTree(Head);
	printf("\n");
	LInsert(BT1,Lp);
	printf("������������");
	InorderBThrTree(Head);
	printf("\n");
	printf("%c���ڽ���ǰ������������Ϊ��%c\n",BT1->Elem,InorderPre(BT1)->Elem);
	printf("%c���ڽ��ĺ�̣���������Ϊ��%c\n",BT1->Elem,InorderNext(BT1)->Elem);
	return 0;
}
