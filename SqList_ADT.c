/*--@�̺���--*/
/*--2017/10/11--*/
/*--˳��������ʵ�֣�˳��洢--*/ 
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100 

typedef int ElemType;
typedef int position;

typedef struct SqList
{
	ElemType *elem;    
	int last;
}SqList;

/*��ʼ�����Ա�*/ 
void InitList(SqList *L)
{
	L->elem = (ElemType*)malloc(MAXSIZE*sizeof(ElemType)); //����洢�ռ��СΪ�� 
	if(!L->elem)                                           //����*ÿ��Ԫ����ռ�ռ� 
		exit(-1);                                          //ElemType *�Ƕ���ָ���������͵�ָ��,
	L->last = 0;                                           //��ַ�������ָ��ElemType��ָ��elem
	                                                       //ָ��elem��Ϊ����������׵�ַ  
}

/*�ձ�˳��������*/ 
void CreateList_Array(ElemType x,SqList *L)
{
	if(L->last == MAXSIZE)
		printf("List is Full!");
	else 
	{
		L->elem[L->last+1] = x;   //��L->last+1��elem�����±�Ϊ0�Ŀ��� 
		L->last += 1;             // ���Ա��1��ʼ
	}
} 

/*������������Ա�Ϊ�ձ�*/ 
void Insert(ElemType x,position p,SqList *L)
{
	position q;
	if(L->last >= MAXSIZE - 1)
		printf("List is Full!"); 
	else if((p > L->last)||(p < 1))
		printf("Wrong position!");
	else
	{
		for(q = L->last;q >= p;q--)
		{
			L->elem[q+1] = L->elem[q];		
		}
		L->elem[p] = x;
		L->last += 1;
	}
}

/*�������������Ա��1��ʼ*/
void Traverse(SqList *L)
{
	int i;
	for(i=1;i<=L->last;i++)
	{
		printf("%d",L->elem[i]);
	}
	printf("\n");
} 

/*ȡֵ����*/
ElemType Get(position p,SqList *L)
{
	if((p < 1)||(p > L->last))
		printf("Wrong position!");
	else
		return L->elem[p];
} 

/*���Ҳ���*/
position Locate(ElemType x,SqList *L)
{
	int i;
	for(i=1;i<=L->last;i++)
	{
		if(L->elem[i] == x)
			return i;
	}
	 
	return 0;
}

/*ɾ������*/
void Delete(position p,SqList *L)
{
	position q;
	if((p < 1)||(p > L->last))
		printf("Wrong position");
	else
	{
		for(q=p;q<L->last;q++)
		{
			L->elem[q] = L->elem[q+1];
		}
		L->last -= 1;
	}
}

/*�õ���*/
int GetLength(SqList *L)
{
	return L->last;
}

int main()
{
	int a[10] = {11,22,33,44,55,66};
	int i;
	SqList L;
	InitList(&L);
	printf("%d\n",L.last);
	printf("%d\n",GetLength(&L));
	for(i=0;i<=9;i++)
	{
		CreateList_Array(a[i],&L);
	} 
	printf("%d\n",L.last);
    Traverse(&L);
	Insert(77,7,&L);
	printf("\n");
	Traverse(&L);
	printf("%d\n",L.last);
	printf("%d\n",Get(7,&L));
	printf("%d\n",Locate(77,&L));
	Delete(7,&L);
	Traverse(&L);
	printf("%d\n",L.last);
	printf("%d\n",GetLength(&L));
	return 0;	
}





