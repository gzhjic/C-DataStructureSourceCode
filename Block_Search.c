/*--@�̺���--*/
/*--2017/12/25--*/
/*--���ң��ֿ���ң���������������򣬿�������-*/


#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100 

typedef int KeyType;
typedef int FieldType;

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
	
	array[0].key = 0; 		//�����0�ŵ�Ԫ����
	for(i=1;i<=15;i++)
	{
		printf("�����������е����ݣ�");		
		scanf("%d",&array[i].key);
	}	
	
	return array;
}

KeyType Block[MAXSIZE];
/*-----------------------------------
Ҳ���Զ���һ�����ݽṹ���ֿ�������
	typedef struct Block
	{
		KeyType *maxkey;
		int L_block;
		int blast;
	}Block;
-----------------------------------*/

/*--�ֿ����:����->������(->��)->������L_block = sqrt(last)ʱ��ƽ�����ҳ�����С��ΪASL = sqrt(last)+1--*/
int Block_Search(KeyType key,int L_block,int last,Record *array,int blast,KeyType *block)
{
	/*--�鳤L_block������last����������blast--*/ 
	int i,j,next;
	i = 1;
	/*--�Ȳ��ҿ�������--*/
	while((block[i]<key)&&(i<=blast))
		i++;
	/*--���ҵ���Ӧ�飨��ţ�--*/
	if(i<=blast)
	{
		/*--Ȼ���������Ӧ���в���--*/
		j = (i-1)*L_block+1;			//�ҵ���Ӧ����ʼԪ�����
		next = i*L_block+1;
		while((array[j].key!=key)&&(j<=next)&&(j<=last))	//����һ�����Ȼ��֣��п������һ���鳤�Ȳ����鳤L_block 
			j++;
		if(key == array[j].key)
			return j;
	}
	
	return 0;
} 

int main()
{
	Record *mainArray;
	mainArray = Create_Array(mainArray);
	int i;
	for(i=1;i<=3;i++)
	{
		printf("��������������е����ݣ�");		//���������д���������ÿ�������ֵ,��0�ŵ�Ԫ���� 
		scanf("%d",&Block[i]);
	}
	int ret;
	ret = Block_Search(38,5,15,mainArray,3,Block);
	printf("�ֿ���ҽ����%d\n",ret);
	return 0;
} 




