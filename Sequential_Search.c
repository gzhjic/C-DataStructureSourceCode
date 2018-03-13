/*--@�̺���--*/
/*--2017/12/25--*/
/*--���ң�˳�����--*/


#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100 

typedef int KeyType;
typedef int FieldType;

/*--���Ա�--*/
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

/*--��ͨ��˳�����--*/
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

/*--�Ż���˳�����--*/
int Sequential_Search2(KeyType key,int last,Record *array)
{
	int i;
	array[0].key = key;			//�����ˡ��ڱ�����ʡȥ��Խ���жϣ���ÿ�εġ�i<=last�����жϣ������ݽϴ�ʱ��Ч����ߺܶ� 
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
	printf("˳����ҽ����%d,%d\n",ret1,ret2);
	return 0;
} 
