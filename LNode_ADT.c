/*--@程豪琪--*/
/*--2017/10/12--*/
/*--顺序表的指针实现，链式存储--*/
#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;
typedef int position;

typedef struct LNode
{
	ElemType elem;       //数据域 
	struct LNode *next;  //指针域，定义一个指针，指向结点类型 
}LNode,*LinkList;       //这里 Linklist 也就代替了 LNode* 

void InitList(LNode *L)           //LNode*定义任意结点的指针变量 
{
	L = (LNode*)malloc(sizeof(LNode));    //生成新节点 
	if(!L)                                
		exit(-1);
	L->next = NULL;
}

/*头插法，建立单链表*/            //Linklist定义单链表，表示其头指针 
LinkList CreateList_Head(LNode *head,int n)
{
	int i;
	ElemType data; 
	LNode *Temp;
	head = (LinkList)malloc(sizeof(LNode));  //建立一个头节点
	if(!head)
		exit(-1); 
	head->next = NULL;
	printf("请输入线性表数据：\n");	
	for(i=1;i<=n;i++)
	{
		scanf("%d\n",&data);      //结束scanf循环输入，即EOF的输入方法：Windows是Ctrl+Z，Linux是Ctrl+D。
		Temp = (LNode*)malloc(sizeof(LNode));
		if(!Temp)
			exit(-1);
		Temp->elem = data;
		Temp->next = head->next;
		head->next = Temp;
	}
	
	return head;        //这里返回单链表的头指针，方便调用 
}

/*尾插法，建立单链表*/
LinkList CreateList_Last(LNode *last,int n)
{
	int i;
	ElemType data;
	LNode *Temp;
	LNode *head;
	
	last = (LinkList)malloc(sizeof(LNode));  //建立一个尾节点
	if(!last)
		exit(-1);
	last->next = NULL;
	head = last;                             //last始终指向尾节点 
	printf("请输入线性表数据：\n");
	for(i=1;i<=n;i++)
	{
		scanf("%d",&data);
		Temp = (LNode*)malloc(sizeof(LNode));
		if(!Temp)
			exit(-1);
		Temp->elem = data;
		Temp->next = NULL;
		last->next = Temp;
		last = Temp;
	} 
	return head; 
}

/*遍历操作*/ 
void Traverse(LNode *L)
{
	LNode *p;
	p = L->next;
	while(p!=NULL)
	{
		printf("%d",p->elem);
		p = p->next;
	}
	printf("\n");
}

/*得到指定位置处结点指针*/ 
LNode* GetPointer_Position(position p,LNode *L)
{
	int i;
	LNode *Temp;
	Temp = L;
	i = 0;
	while((i<p)&&(Temp!=NULL))
	{
		Temp = Temp->next;
		i=i+1;
	}
	if((Temp == NULL)||(i!=p))
		Temp = NULL;	
	return Temp;              //p=0返回头结点指针 
}

/*插入操作，指定位置*/ 
void Insert(ElemType data,position p,LNode *L)
{
	LNode *Temp;
	LNode *Pointer_pj1;
	if(p!=0)
	{
		Pointer_pj1 = GetPointer_Position(p-1,L);				
		if((Pointer_pj1!=NULL)&&(Pointer_pj1->next!=NULL))       //注意超出后，前一结点是尾结点->next为空，
		{                                                        //但前一结点指针Pointer_pj1不为空  
			Temp = (LNode*)malloc(sizeof(LNode));
			if(!Temp)
				exit(-1);
			Temp->elem = data;
			Temp->next = Pointer_pj1->next;
			Pointer_pj1->next = Temp;	
		}	
		else
		{
			printf("Wrong Position!\n");
		}
	}
	else
	{
		printf("Wrong Position!\n");
	}
}

/*删除操作*/
void Delete(position p,LNode *L)
{
	LNode *Temp;
	LNode *Pointer_pj1;
	if(p!=0)
	{
		Pointer_pj1 = GetPointer_Position(p-1,L);
		if((Pointer_pj1!=NULL)&&(Pointer_pj1->next!=NULL))     //注意超出后，前一结点是尾结点->next为空，
		{                                                      //但前一结点指针Pointer_pj1不为空 
			Temp = Pointer_pj1->next;                          //临时保存被删除结点指针以备释放 
			Pointer_pj1->next = Pointer_pj1->next->next;
			free(Temp);                                        //释放被删除结点的空间 			
		}
		else
		{
			printf("Wrong Position!\n");
		}
	}
	else
	{
		printf("Wrong Position!\n");	
	} 
}

/*按值查找操作*/
LNode* LocateElem(ElemType x,LNode *L)
{
	LNode *Temp;
	Temp = L->next;
	while(Temp->elem != x)
	{
		Temp = Temp->next;
		if(Temp == NULL)
			return NULL;
	}
	return Temp;
} 

/*取值操作*/
ElemType GetElem(position p,LNode *L)
{
	LNode *Pointer_p;
	Pointer_p = GetPointer_Position(p,L);
	if((Pointer_p!=NULL)&&(p!=0))
	{
		return Pointer_p->elem;
	}
	else
	{
		return -1;
	}
} 

int main()
{
	LNode *L;
	//L = CreateList_Head(L,5);
	L = CreateList_Last(L,5);
	Traverse(L);
	printf("%d\n",GetPointer_Position(11,L));
	Insert(99,5,L);
	Traverse(L);
	Delete(3,L);
	Traverse(L);
	printf("%d\n",LocateElem(3333,L));
	printf("%d\n",GetElem(22,L));
	return 0;
} 

