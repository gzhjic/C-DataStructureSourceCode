/*--@程豪琪--*/
/*--2018/01/03--*/
/*--查找：简单哈希表查找（散列表查找）-*/

#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100
#define NULLKEY -32768

typedef int ElemType;

int size = 0; 

/*--哈希表数据结构--*/
typedef struct HashTable 
{
	ElemType *record;
	int numElem;
}HashTable;  

/*--哈希表初始化--*/
void Init_HashTB(HashTable *H,int hashSize)
{
	int i;
	H->record = (ElemType*)malloc(MAXSIZE*sizeof(ElemType));
	if(!H->record)
		exit(-1);
	size = hashSize;
	H->numElem = size;
	for(i=0;i<size;i++)
	{
		H->record[i] = NULLKEY;
	} 
} 

/*--散列函数--*/
int Hash(ElemType key) 
{
	return key % size;		//除留余数法 
}

/*--冲突处理：开放定址法的线性探测--*/
void Inser_HashTB(ElemType key,HashTable *H)
{ 
	int addr = Hash(key);
	if(H->record[addr] != NULLKEY)
		addr = (addr + 1) % size;
	H->record[addr] = key;		
} 

/*--哈希表查找操作--*/
int Hash_Search(ElemType key,HashTable *H)
{
	int addr;
	addr = Hash(key);
	while(H->record[addr] != key)
	{
		addr = (addr + 1) % size;
		if(H->record[addr] == NULLKEY || addr == Hash(key))
			return -1;		/*  查找失败  */					
	}
	
	return addr;
}  

int main()
{
	/*--只是哈希表查找的简单实现，熟悉基本流程！--*/
	HashTable H1;
	Init_HashTB(&H1,12);
	
	int i,test[12] = {12,67,56,16,25,37,22,29,15,47,48,34};
	for(i=0;i<12;i++)
	{
		Inser_HashTB(test[i],&H1);
	}
	for(i=0;i<12;i++)
	{
		printf("%d|",H1.record[i]);
	}
	printf("\n---------------------\n");
	
	int ret;
	ret = Hash_Search(16,&H1);
	printf("%d\n",H1.record[ret]);	
	return 0;
}
