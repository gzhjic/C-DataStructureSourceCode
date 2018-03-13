/*--@程豪琪--*/
/*--2017/12/25--*/
/*--查找：分块查找（块索引，块间有序，块内无序）-*/


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
	
	array[0].key = 0; 		//主表第0号单元不用
	for(i=1;i<=15;i++)
	{
		printf("请输入主表中的数据：");		
		scanf("%d",&array[i].key);
	}	
	
	return array;
}

KeyType Block[MAXSIZE];
/*-----------------------------------
也可以定义一个数据结构：分块索引表
	typedef struct Block
	{
		KeyType *maxkey;
		int L_block;
		int blast;
	}Block;
-----------------------------------*/

/*--分块查找:查找->索引表(->块)->主表，当L_block = sqrt(last)时，平均查找长度最小，为ASL = sqrt(last)+1--*/
int Block_Search(KeyType key,int L_block,int last,Record *array,int blast,KeyType *block)
{
	/*--块长L_block，主表长last，块索引表长blast--*/ 
	int i,j,next;
	i = 1;
	/*--先查找块索引表--*/
	while((block[i]<key)&&(i<=blast))
		i++;
	/*--若找到相应块（块号）--*/
	if(i<=blast)
	{
		/*--然后在主表对应块中查找--*/
		j = (i-1)*L_block+1;			//找到对应快起始元素序号
		next = i*L_block+1;
		while((array[j].key!=key)&&(j<=next)&&(j<=last))	//主表不一定均匀划分，有可能最后一个块长度不够块长L_block 
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
		printf("请输入块索引表中的数据：");		//块索引表中存入主表中每块的最大键值,第0号单元不用 
		scanf("%d",&Block[i]);
	}
	int ret;
	ret = Block_Search(38,5,15,mainArray,3,Block);
	printf("分块查找结果：%d\n",ret);
	return 0;
} 




