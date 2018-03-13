/*--@�̺���--*/
/*--2017/12/25--*/
/*--���ң��۰����--*/

#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100 

typedef int KeyType;
typedef int FieldType;

/*--���ź�������Ա�--*/ 
typedef struct Record
{
	KeyType key;
	FieldType others;
}Record;

Record* Create_Array(Record *array)
{
	int i;
	array = (Record*)malloc(MAXSIZE*sizeof(Record));
	if(!array)
		exit(-1);
	
	for(i=0;i<=10;i++)
	{
		array[i].key = i*2;
	}	
	
	return array;
}

/*--�۰����--*/
int Binary_Search(KeyType key,int last,Record *array)
{
	int mid,low,high;
	high = last;
	low = 1;
	while(low<=high)
	{
		mid = (low+high)/2;
		if(key>array[mid].key)
			low = mid + 1;
		else if(key<array[mid].key)
			high = mid - 1;
		else
			return mid; 
	}

	return 0;
}

int main()
{
	int ret;
	Record *Array1;
	Array1 = Create_Array(Array1);
	ret = Binary_Search(14,10,Array1);
	printf("�۰���ҽ����%d\n",ret);
			
	return 0;
} 
