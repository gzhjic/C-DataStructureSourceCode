/*--@�̺���--*/
/*--2018/01/03--*/
/*--���ң��򵥹�ϣ����ң�ɢ�б���ң�-*/

#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100
#define NULLKEY -32768

typedef int ElemType;

int size = 0; 

/*--��ϣ�����ݽṹ--*/
typedef struct HashTable 
{
	ElemType *record;
	int numElem;
}HashTable;  

/*--��ϣ���ʼ��--*/
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

/*--ɢ�к���--*/
int Hash(ElemType key) 
{
	return key % size;		//���������� 
}

/*--��ͻ�������Ŷ�ַ��������̽��--*/
void Inser_HashTB(ElemType key,HashTable *H)
{ 
	int addr = Hash(key);
	if(H->record[addr] != NULLKEY)
		addr = (addr + 1) % size;
	H->record[addr] = key;		
} 

/*--��ϣ����Ҳ���--*/
int Hash_Search(ElemType key,HashTable *H)
{
	int addr;
	addr = Hash(key);
	while(H->record[addr] != key)
	{
		addr = (addr + 1) % size;
		if(H->record[addr] == NULLKEY || addr == Hash(key))
			return -1;		/*  ����ʧ��  */					
	}
	
	return addr;
}  

int main()
{
	/*--ֻ�ǹ�ϣ����ҵļ�ʵ�֣���Ϥ�������̣�--*/
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
