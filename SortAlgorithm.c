/*--@�̺���--*/
/*--2017/01/16--*/
/*--�����㷨��ð�����򣨿������򣩡�ѡ�����򣨶����򣩡�ֱ�Ӳ�������ϣ�����򣩡��鲢���򡢻�������--*/


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAXSIZE 100
#define NULLKEY -32768
typedef int ElemType;
/*----------------------------------------------------------���룺�������ݽṹ--------------------------------------------------------------*/ 

/*������*/
typedef struct QNode
{
	ElemType elem;
	struct QNode *next;
}QNode,*QueuePtr;

/*�������*/
typedef struct LinkQueue
{
	QueuePtr front;
	QueuePtr rear;	
}LinkQueue;

/*��ʼ��*/
void InitQueue(LinkQueue *Q)
{
	QNode *Temp;
	Temp = (QNode*)malloc(sizeof(QNode));
	if(!Temp)
		exit(-1);
	Q->front = Temp;
	Q->front->next = NULL;
	Q->rear = Q->front;
}

/*��Ӳ�������β����Ԫ��*/
void EnQueue(ElemType data,LinkQueue *Q)
{
	QNode *Temp;
	Temp = (QNode*)malloc(sizeof(QNode));
	if(!Temp)
		exit(-1);
	Temp->elem = data;
	Temp->next = NULL;
	Q->rear->next = Temp;
	Q->rear = Temp;	
}
 
/*���Ӳ���������ɾ��Ԫ��*/
void DeQueue(LinkQueue *Q)
{
	QNode *Temp;
	if(Q->front == Q->rear)
		printf("Queue is empty!");
	else
	{
		Temp = Q->front->next;
		Q->front->next = Temp->next;
		if(Temp == Q->rear)
			Q->rear = Q->front;
		free(Temp); 
	}	
}
 
/*ȡֵ���������ض���Ԫ��*/
ElemType Front(LinkQueue *Q)
{
	if(Q->front == Q->rear)
		return -1;
	else
		return Q->front->next->elem;	
}

/*----------------------------------------------------------���룺�������ݽṹ--------------------------------------------------------------*/ 

/*--��¼�����ݽṹ--*/
typedef struct Record
{
	ElemType *elem;
	int len;
}Record;

/*--��ʼ����¼--*/
void Init_Record(Record *Array,int n)
{
	Array->elem = (ElemType*)malloc(sizeof(ElemType)*MAXSIZE);
	if(!Array->elem)
		exit(-1);
	int i;
	for(i=0;i<n+1;i++)
	{
		Array->elem[i] = NULLKEY;
	}
	Array->len = n;
} 

void CreateRecord(Record *Array,int array[])
{
	int i;
	for(i=1;i<=Array->len;i++)
	{
		Array->elem[i] = array[i-1];
	}		
}

void PrintRecord(Record *Array)
{
	int i;
	printf("������ɺ�����У�"); 
	for(i=1;i<=Array->len;i++)
	{
		printf("%d|",Array->elem[i]);
	}	
	printf("\n");
}

/*--�����������Ƚ�+�ƶ�--*/
void swap(Record *Array,int i,int j)
{
	ElemType temp = Array->elem[i];
	Array->elem[i] = Array->elem[j];
	Array->elem[j] = temp;
} 

/*--��ð������ͨ�������Ƚϣ�С��ǰ�ƣ����ߺ���--*/
void BubbleSort(Record *Array)
{
	int i,j;
	for(i=1;i<=Array->len;i++)
	{
		for(j=Array->len;j>=i+1;j--)
		{
			if(Array->elem[j]<Array->elem[j-1])
				swap(Array,j,j-1);
		}
	}
}

/*--�Ż�ð������--*/
void BubbleSort_Modified(Record *Array)
{
	int i,j;
	bool sequential = false;						//������У��磺{2,1,3,4,5,6,7} 
	for(i=1;i<=Array->len&&sequential==false;i++)
	{
		sequential = true;							//δ���������������˳�ð������ 
		for(j=Array->len;j>=i+1;j--)
		{
			if(Array->elem[j]<Array->elem[j-1])
			{
				swap(Array,j,j-1);
				sequential = false;
			}
			
		}
	}
} 
 
/*--ѡ������ÿ��ѡ����ǰ��С�Ĺؼ���--*/ 
void SelectSort(Record *Array)
{
	int i,j,min;
	for(i=1;i<Array->len;i++)
	{
		min = i;
		for(j=Array->len;j>=i+1;j--)
		{
			if(Array->elem[min]>Array->elem[j])
				min = j;
		}
		if(i!=min)
		{
			swap(Array,i,min);
		}
	}
}

/*--ֱ�Ӳ�������:��A[x]�������ź��������{A[1],...A[i]}��--*/
void InsertSort(Record *Array)
{
	int i,j;
	for(i=1;i<=Array->len;i++)
	{
		j=i;
		while(Array->elem[j]<Array->elem[j-1])		//�ڱ�A[0]=-32768 
		{
			swap(Array,j,j-1);
			j = j-1;							
		} 
	}
}

/*--�򵥿�������--*/
ElemType FindPivotKey(Record *Array,int first)		//ѡȡ��һ����¼KeyֵΪ����ֵ 
{
	ElemType pivotkey = Array->elem[first];
	return pivotkey;
}

int Partion(Record *Array,int first,int end)		//���������ȡ���β��� 
{
	ElemType pivotkey = FindPivotKey(Array,first);
	int low = first,high = end;
	while(low<high)
	{
		while(low<high&&Array->elem[high]>=pivotkey)
			high--;
		swap(Array,low,high);
		while(low<high&&Array->elem[low]<=pivotkey)
			low++;
		swap(Array,low,high);
	}
	return low; 
}

void Qsort(Record *Array,int first,int end)
{
	int pivot;
	if(first<end)
	{
		pivot = Partion(Array,first,end);
		Qsort(Array,first,pivot-1);
		Qsort(Array,pivot+1,end);
	}
}

void QuickSort(Record *Array)
{
	Qsort(Array,1,Array->len);
} 

/*--�Ż���������--*/
ElemType FindPivotKey_Modified(Record *Array,int first,int end)		 
{
	//ʹѡȡ������ֵ���ӽ��м�ֵ��һ��������ȡ�з�
	int mid = first + (end-first);
	if(Array->elem[first]>Array->elem[end])
		swap(Array,first,end); 
	if(Array->elem[mid]>Array->elem[end])
		swap(Array,mid,end);
	if(Array->elem[mid]>Array->elem[end])
		swap(Array,first,mid);
	ElemType pivotkey = Array->elem[first];					//��ʱfirst��keyֵΪ�м�ֵ 
	return pivotkey;
}

int Partion_Modified(Record *Array,int first,int end)	
{
	ElemType pivotkey = FindPivotKey_Modified(Array,first,end);		//pivotkey������first=low�� 
	int low = first,high = end;
	//�Ľ���Ϊ�滻,���ٽ��� 
	while(low<high)
	{
		while(low<high&&Array->elem[high]>=pivotkey)
			high--;
		Array->elem[low] = Array->elem[high]; 
		while(low<high&&Array->elem[low]<=pivotkey)
			low++;
		Array->elem[high] = Array->elem[low];
	}
	Array->elem[low] = pivotkey;							//low=high����������ֵ 
	return low; 
}

void Qsort_Modified(Record *Array,int first,int end)
{
	 
	int pivot;
	//���ٵݹ����
	while(first<end)
	{
		pivot = Partion(Array,first,end);
		Qsort_Modified(Array,first,pivot-1);
		
		first = pivot+1; 
	}
}

void QuickSort_Modified(Record *Array)
{
	Qsort_Modified(Array,1,Array->len);
} 

/*--�����򣺴����ѣ����ѣ���ȡ�Ѷ�keyֵ�����ѵ����һ��ֵ����Ѷ���������--*/
void HeapAdjust(Record *Array,int root,int len)
{
	/*--�ҵ�ĳһ�����ս���i��Ϊ��ǰ�����root--*/ 
	int i = root;
	/*--����ȫ�����������ʣ���2*iֵ�������ѵ�--*/		
	while(i<=len/2)
	{
		/*--��ǰ�����ֻ��һ�������,�ø��ڵ�ֻ����iֵ���ķ��ս���--*/
		if((i==len/2)&&(len%2==0))
		{
			if(Array->elem[i]<Array->elem[2*i])
				swap(Array,i,2*i); 
			break;
		}
		/*--��ǰ���ڵ��������ӣ������Ҷ���--*/
		else if(Array->elem[i]<Array->elem[2*i])
		{
			if(Array->elem[2*i]>=Array->elem[2*i+1])		//����Ӵ�
			{
				swap(Array,i,2*i);
				i = 2*i;
			}
			else											//�Ҷ��Ӵ�
			{
				swap(Array,i,2*i+1);
				i = 2*i+1;
			}		
		}
		else
			break;
	}							
} 

void HeapSort(Record *Array)
{
	int i;
	/*--��ʼ���ѣ�ֻ�������ս���--*/
	for(i=Array->len/2;i>=1;i--)
	{
		HeapAdjust(Array,i,Array->len); 
	}
	for(i=Array->len;i>=2;i--)
	{
		/*--ȡ�Ѷ�keyֵ�����ѵ����һ��ֵ����Ѷ���������--*/
		swap(Array,1,i);
		HeapAdjust(Array,1,i-1);
	}
}

/*--ϣ�����򣺽�A[x]�������ź���������ӱ�,ʵ����Ծʽ�ƶ�--*/
void ShellSort(Record *Array)
{
	int i,j,incerment;
	for(incerment=Array->len/2;incerment>=1;incerment=incerment/2)		//����������incerment=1 
	{
		for(i=incerment+1;i<=Array->len;i++)
		{
			if(Array->elem[i]<Array->elem[i-incerment])
			{
				Array->elem[0] = Array->elem[i];						//A[x]�ݴ���A[0]�� 
				for(j=i-incerment;j>0&&Array->elem[0]<Array->elem[j];j=j-incerment)
					Array->elem[j+incerment] = Array->elem[j];			//��ǰkeyֵ����A[x],����һ������ 
				Array->elem[j+incerment] = Array->elem[0];				//�ҵ�����λ�ú󣬽�A[x]���뵽��λ�� 
			}
		}
	}
	Array->elem[0] = NULLKEY; 
} 

/*--�鲢����--*/
void Merge(Record *Array,int left,int mid,int right,Record *Sorted)		//��Array�������й鲢��Sorted 
{
	int i=left,j=mid+1,k=i;
	while(j<=right&&i<=mid)
		Sorted->elem[k++] = (Array->elem[i]<Array->elem[j])?Array->elem[i++]:Array->elem[j++];
	while(i<=mid)
		Sorted->elem[k++] = Array->elem[i++];		//����������ʣ�࣬��ʣ�ಿ�ָ��Ƶ��鲢�����е�β�� 
	while(j<=right)
		Sorted->elem[k++] = Array->elem[j++];		//����������ʣ�࣬��ʣ�ಿ�ָ��Ƶ��鲢�����е�β��
}
void Msort(Record *Array,int left,int right,Record *Sorted)				//��Array�鲢�����Ƶ�Sorted
{
	int mid;
	Record tempSorted;								//tempSortedΪ�ֲ����� 
	Init_Record(&tempSorted,Array->len); 
	if(left == right)
		Sorted->elem[right] = Array->elem[right];
	else
	{
		mid = (left+right)/2;						//ƽ��Array���� 
		Msort(Array,left,mid,&tempSorted);
		Msort(Array,mid+1,right,&tempSorted);
		Merge(&tempSorted,left,mid,right,Sorted);
	}
}
void MergeSort(Record *Array)
{
	Msort(Array,1,Array->len,Array);
}

/*--�����������������Ƚϵ�����--*/ 
int FindRadix(ElemType key,int pass)
{
	int i,power = 1;
	for(i=1;i<=pass-1;i++)
	{
		power = power*10; 
	} 
	return (key%(power*10))/power;					//��ӦͰ��Ϊbucket = (key%10^p)/10^p-1 
} 

void Rsort(LinkQueue *Array,int figure)
{
	int i,pass,radix;
	ElemType data;
	LinkQueue Bucket[10];
	for(pass = 1;pass<=figure;pass++)
	{
		for(i=0;i<=9;i++)
		{
			InitQueue(&Bucket[i]);	
		}
		while(Array->front!=Array->rear)
		{
			data = Front(Array);
			DeQueue(Array);
			radix = FindRadix(data,pass);
			EnQueue(data,&Bucket[radix]);
		} 
		for(i=0;i<=9;i++)
		{
			while(Bucket[i].front!=Bucket[i].rear)
			{
				data = Front(&Bucket[i]);
				DeQueue(&Bucket[i]);
				EnQueue(data,Array);
			}
		}
	}
}
void RaixSort(Record *Array,int figure)
{
	int i;
	LinkQueue Q;
	InitQueue(&Q);
	for(i=1;i<=Array->len;i++)
		EnQueue(Array->elem[i],&Q);
	Rsort(&Q,figure);
	for(i=1;i<=Array->len;i++)
	{
		Array->elem[i] = Front(&Q);
		DeQueue(&Q);
	}	
}

int main()
{
	ElemType a[10] = {5,1,9,3,7,4,8,6,2,0};
	ElemType b[10] = {2,4,7,9,6,5,3,3,8,9};
	ElemType c[10] = {9,1,5,8,3,7,3,4,6,2};	
	Record A1,A2,A3;
	Init_Record(&A1,10);
	Init_Record(&A2,10);
	Init_Record(&A3,10);
	CreateRecord(&A1,a);
	CreateRecord(&A2,b);
	CreateRecord(&A3,c);
	/*--------------------------------------
	BubbleSort(&A1);
	BubbleSort_Modified(&A1);
	
	SelectSort(&A1);
	
	InsertSort(&A1);
	
	QuickSort(&A1);
	PrintRecord(&A1);
;
	QuickSort_Modified(&A1);
	PrintRecord(&A1);

	
	HeapSort(&A2);
	PrintRecord(&A2);
	
	ShellSort(&A3);
	PrintRecord(&A3);
	
	MergeSort(&A2);
	PrintRecord(&A2);
	--------------------------------------*/
	ElemType d[16] = {321,986,123,432,543,18,765,678,987,789,98,890,109,901,210,12};	
	Record A4;
	Init_Record(&A4,16);	
	CreateRecord(&A4,d);
	
	RaixSort(&A4,3);
	PrintRecord(&A4);
	return 0;
}
