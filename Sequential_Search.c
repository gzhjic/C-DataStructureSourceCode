/*--@程豪琪--*/
/*--2017/12/25--*/
/*--查找：顺序查找--*/


#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100 

typedef int KeyType;
typedef int FieldType;

/*--线性表--*/
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

/*--普通的顺序查找--*/
int Sequential_Search1(KeyType key,int last,Record *array)
{
	int i;
	for(i=1;i<=last;i++)
	{
		if(array[i].key==key)
			return i;
	}
	
	return 0;				
}

/*--优化的顺序查找--*/
int Sequential_Search2(KeyType key,int last,Record *array)
{
	int i;
	array[0].key = key;			//设置了“哨兵”，省去了越界判断，即每次的“i<=last”的判断，当数据较大时，效率提高很多 
	i = last;
	while(array[i].key!=key)
	{
		i--;
	}
	
	return i;
}




int main()
{
	int ret1,ret2;
	Record *Array1;
	Array1 = Create_Array(Array1);
	int i;
	for(i=0;i<=10;i++)
	{
		printf("%d|",Array1[i].key);
	}
	printf("\n-----------------\n");
	ret1 = Sequential_Search1(14,10,Array1);
	ret2 = Sequential_Search2(14,10,Array1);
	printf("顺序查找结果：%d,%d\n",ret1,ret2);
	return 0;
} 
