/*--@�̺���--*/
/*--2017/10/12--*/
/*--˳����ָ��ʵ�֣���ʽ�洢--*/
#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;
typedef int position;

typedef struct LNode
{
	ElemType elem;       //������ 
	struct LNode *next;  //ָ���򣬶���һ��ָ�룬ָ�������� 
}LNode,*LinkList;       //���� Linklist Ҳ�ʹ����� LNode* 

void InitList(LNode *L)           //LNode*�����������ָ����� 
{
	L = (LNode*)malloc(sizeof(LNode));    //�����½ڵ� 
	if(!L)                                
		exit(-1);
	L->next = NULL;
}

/*ͷ�巨������������*/            //Linklist���嵥������ʾ��ͷָ�� 
LinkList CreateList_Head(LNode *head,int n)
{
	int i;
	ElemType data; 
	LNode *Temp;
	head = (LinkList)malloc(sizeof(LNode));  //����һ��ͷ�ڵ�
	if(!head)
		exit(-1); 
	head->next = NULL;
	printf("���������Ա����ݣ�\n");	
	for(i=1;i<=n;i++)
	{
		scanf("%d\n",&data);      //����scanfѭ�����룬��EOF�����뷽����Windows��Ctrl+Z��Linux��Ctrl+D��
		Temp = (LNode*)malloc(sizeof(LNode));
		if(!Temp)
			exit(-1);
		Temp->elem = data;
		Temp->next = head->next;
		head->next = Temp;
	}
	
	return head;        //���ﷵ�ص������ͷָ�룬������� 
}

/*β�巨������������*/
LinkList CreateList_Last(LNode *last,int n)
{
	int i;
	ElemType data;
	LNode *Temp;
	LNode *head;
	
	last = (LinkList)malloc(sizeof(LNode));  //����һ��β�ڵ�
	if(!last)
		exit(-1);
	last->next = NULL;
	head = last;                             //lastʼ��ָ��β�ڵ� 
	printf("���������Ա����ݣ�\n");
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

/*��������*/ 
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

/*�õ�ָ��λ�ô����ָ��*/ 
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
	return Temp;              //p=0����ͷ���ָ�� 
}

/*���������ָ��λ��*/ 
void Insert(ElemType data,position p,LNode *L)
{
	LNode *Temp;
	LNode *Pointer_pj1;
	if(p!=0)
	{
		Pointer_pj1 = GetPointer_Position(p-1,L);				
		if((Pointer_pj1!=NULL)&&(Pointer_pj1->next!=NULL))       //ע�ⳬ����ǰһ�����β���->nextΪ�գ�
		{                                                        //��ǰһ���ָ��Pointer_pj1��Ϊ��  
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

/*ɾ������*/
void Delete(position p,LNode *L)
{
	LNode *Temp;
	LNode *Pointer_pj1;
	if(p!=0)
	{
		Pointer_pj1 = GetPointer_Position(p-1,L);
		if((Pointer_pj1!=NULL)&&(Pointer_pj1->next!=NULL))     //ע�ⳬ����ǰһ�����β���->nextΪ�գ�
		{                                                      //��ǰһ���ָ��Pointer_pj1��Ϊ�� 
			Temp = Pointer_pj1->next;                          //��ʱ���汻ɾ�����ָ���Ա��ͷ� 
			Pointer_pj1->next = Pointer_pj1->next->next;
			free(Temp);                                        //�ͷű�ɾ�����Ŀռ� 			
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

/*��ֵ���Ҳ���*/
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

/*ȡֵ����*/
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

