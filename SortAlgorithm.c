/*--@程豪琪--*/
/*--2017/01/16--*/
/*--排序算法：冒泡排序（快速排序）、选择排序（堆排序）、直接插入排序（希尔排序）、归并排序、基数排序--*/


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAXSIZE 100
#define NULLKEY -32768
typedef int ElemType;
/*----------------------------------------------------------导入：队列数据结构--------------------------------------------------------------*/ 

/*定义结点*/
typedef struct QNode
{
	ElemType elem;
	struct QNode *next;
}QNode,*QueuePtr;

/*定义队列*/
typedef struct LinkQueue
{
	QueuePtr front;
	QueuePtr rear;	
}LinkQueue;

/*初始化*/
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

/*入队操作，队尾插入元素*/
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
 
/*出队操作，队首删除元素*/
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
 
/*取值操作，返回队首元素*/
ElemType Front(LinkQueue *Q)
{
	if(Q->front == Q->rear)
		return -1;
	else
		return Q->front->next->elem;	
}

/*----------------------------------------------------------导入：队列数据结构--------------------------------------------------------------*/ 

/*--记录：数据结构--*/
typedef struct Record
{
	ElemType *elem;
	int len;
}Record;

/*--初始化记录--*/
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
	printf("排序完成后的序列："); 
	for(i=1;i<=Array->len;i++)
	{
		printf("%d|",Array->elem[i]);
	}	
	printf("\n");
}

/*--基本操作：比较+移动--*/
void swap(Record *Array,int i,int j)
{
	ElemType temp = Array->elem[i];
	Array->elem[i] = Array->elem[j];
	Array->elem[j] = temp;
} 

/*--简单冒泡排序：通过两两比较，小者前移，大者后移--*/
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

/*--优化冒泡排序--*/
void BubbleSort_Modified(Record *Array)
{
	int i,j;
	bool sequential = false;						//针对序列，如：{2,1,3,4,5,6,7} 
	for(i=1;i<=Array->len&&sequential==false;i++)
	{
		sequential = true;							//未发生过交换，则退出冒泡排序 
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
 
/*--选择排序：每次选出当前最小的关键字--*/ 
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

/*--直接插入排序:将A[x]插入已排好序的序列{A[1],...A[i]}中--*/
void InsertSort(Record *Array)
{
	int i,j;
	for(i=1;i<=Array->len;i++)
	{
		j=i;
		while(Array->elem[j]<Array->elem[j-1])		//哨兵A[0]=-32768 
		{
			swap(Array,j,j-1);
			j = j-1;							
		} 
	}
}

/*--简单快速排序--*/
ElemType FindPivotKey(Record *Array,int first)		//选取第一个记录Key值为枢轴值 
{
	ElemType pivotkey = Array->elem[first];
	return pivotkey;
}

int Partion(Record *Array,int first,int end)		//快速排序采取分治策略 
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

/*--优化快速排序--*/
ElemType FindPivotKey_Modified(Record *Array,int first,int end)		 
{
	//使选取的枢轴值更接近中间值，一般用三数取中法
	int mid = first + (end-first);
	if(Array->elem[first]>Array->elem[end])
		swap(Array,first,end); 
	if(Array->elem[mid]>Array->elem[end])
		swap(Array,mid,end);
	if(Array->elem[mid]>Array->elem[end])
		swap(Array,first,mid);
	ElemType pivotkey = Array->elem[first];					//此时first处key值为中间值 
	return pivotkey;
}

int Partion_Modified(Record *Array,int first,int end)	
{
	ElemType pivotkey = FindPivotKey_Modified(Array,first,end);		//pivotkey在序列first=low处 
	int low = first,high = end;
	//改交换为替换,减少交换 
	while(low<high)
	{
		while(low<high&&Array->elem[high]>=pivotkey)
			high--;
		Array->elem[low] = Array->elem[high]; 
		while(low<high&&Array->elem[low]<=pivotkey)
			low++;
		Array->elem[high] = Array->elem[low];
	}
	Array->elem[low] = pivotkey;							//low=high处填入枢轴值 
	return low; 
}

void Qsort_Modified(Record *Array,int first,int end)
{
	 
	int pivot;
	//减少递归深度
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

/*--堆排序：创建堆（最大堆），取堆顶key值，将堆底最后一个值放入堆顶，调整堆--*/
void HeapAdjust(Record *Array,int root,int len)
{
	/*--找到某一个非终结结点i，为当前根结点root--*/ 
	int i = root;
	/*--由完全二叉树的性质，以2*i值递增到堆底--*/		
	while(i<=len/2)
	{
		/*--当前根结点只有一个左儿子,该根节点只能是i值最大的非终结结点--*/
		if((i==len/2)&&(len%2==0))
		{
			if(Array->elem[i]<Array->elem[2*i])
				swap(Array,i,2*i); 
			break;
		}
		/*--当前根节点既有左儿子，又有右儿子--*/
		else if(Array->elem[i]<Array->elem[2*i])
		{
			if(Array->elem[2*i]>=Array->elem[2*i+1])		//左儿子大
			{
				swap(Array,i,2*i);
				i = 2*i;
			}
			else											//右儿子大
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
	/*--初始建堆，只调整非终结结点--*/
	for(i=Array->len/2;i>=1;i--)
	{
		HeapAdjust(Array,i,Array->len); 
	}
	for(i=Array->len;i>=2;i--)
	{
		/*--取堆顶key值，将堆底最后一个值放入堆顶，调整堆--*/
		swap(Array,1,i);
		HeapAdjust(Array,1,i-1);
	}
}

/*--希尔排序：将A[x]插入已排好序的增量子表,实现跳跃式移动--*/
void ShellSort(Record *Array)
{
	int i,j,incerment;
	for(incerment=Array->len/2;incerment>=1;incerment=incerment/2)		//增量最后必须incerment=1 
	{
		for(i=incerment+1;i<=Array->len;i++)
		{
			if(Array->elem[i]<Array->elem[i-incerment])
			{
				Array->elem[0] = Array->elem[i];						//A[x]暂存如A[0]中 
				for(j=i-incerment;j>0&&Array->elem[0]<Array->elem[j];j=j-incerment)
					Array->elem[j+incerment] = Array->elem[j];			//当前key值大于A[x],后移一个增量 
				Array->elem[j+incerment] = Array->elem[0];				//找到插入位置后，将A[x]插入到该位置 
			}
		}
	}
	Array->elem[0] = NULLKEY; 
} 

/*--归并排序--*/
void Merge(Record *Array,int left,int mid,int right,Record *Sorted)		//将Array两子序列归并到Sorted 
{
	int i=left,j=mid+1,k=i;
	while(j<=right&&i<=mid)
		Sorted->elem[k++] = (Array->elem[i]<Array->elem[j])?Array->elem[i++]:Array->elem[j++];
	while(i<=mid)
		Sorted->elem[k++] = Array->elem[i++];		//若左序列有剩余，将剩余部分复制到归并后序列的尾部 
	while(j<=right)
		Sorted->elem[k++] = Array->elem[j++];		//若右序列有剩余，将剩余部分复制到归并后序列的尾部
}
void Msort(Record *Array,int left,int right,Record *Sorted)				//将Array归并并复制到Sorted
{
	int mid;
	Record tempSorted;								//tempSorted为局部向量 
	Init_Record(&tempSorted,Array->len); 
	if(left == right)
		Sorted->elem[right] = Array->elem[right];
	else
	{
		mid = (left+right)/2;						//平分Array序列 
		Msort(Array,left,mid,&tempSorted);
		Msort(Array,mid+1,right,&tempSorted);
		Merge(&tempSorted,left,mid,right,Sorted);
	}
}
void MergeSort(Record *Array)
{
	Msort(Array,1,Array->len,Array);
}

/*--基数排序：无需两两比较的排序--*/ 
int FindRadix(ElemType key,int pass)
{
	int i,power = 1;
	for(i=1;i<=pass-1;i++)
	{
		power = power*10; 
	} 
	return (key%(power*10))/power;					//对应桶号为bucket = (key%10^p)/10^p-1 
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
