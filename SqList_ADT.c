/*--@程豪琪--*/
/*--2017/10/11--*/
/*--顺序表的数组实现，顺序存储--*/ 
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

/*初始化线性表*/ 
void InitList(SqList *L)
{
	L->elem = (ElemType*)malloc(MAXSIZE*sizeof(ElemType)); //分配存储空间大小为： 
	if(!L->elem)                                           //最大表长*每个元素所占空间 
		exit(-1);                                          //ElemType *是定义指向这种类型的指针,
	L->last = 0;                                           //地址分配给了指向ElemType的指针elem
	                                                       //指针elem即为定义数组的首地址  
}

/*空表顺序插入操作*/ 
void CreateList_Array(ElemType x,SqList *L)
{
	if(L->last == MAXSIZE)
		printf("List is Full!");
	else 
	{
		L->elem[L->last+1] = x;   //？L->last+1把elem数组下标为0的空着 
		L->last += 1;             // 线性表从1开始
	}
} 

/*插入操作，线性表不为空表*/ 
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

/*遍历操作，线性表从1开始*/
void Traverse(SqList *L)
{
	int i;
	for(i=1;i<=L->last;i++)
	{
		printf("%d",L->elem[i]);
	}
	printf("\n");
} 

/*取值操作*/
ElemType Get(position p,SqList *L)
{
	if((p < 1)||(p > L->last))
		printf("Wrong position!");
	else
		return L->elem[p];
} 

/*查找操作*/
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

/*删除操作*/
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

/*得到表长*/
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





