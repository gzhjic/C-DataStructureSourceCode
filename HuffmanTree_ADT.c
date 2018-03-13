/*--@程豪琪--*/
/*--2017/11/07--*/
/*--哈夫曼树，存储结构：顺序存储（数组）--*/

/*哈夫曼树结点：   ____________________________________________  */
/*                |_weight_|_parent_|_lchild_|_rchild_|_value_|  */

/*--哈夫曼树：假设有m个权值{w1,w2,...,wm},可以构造一棵含n个叶子结点的二叉树--*/
/*--每个叶子结点的权为wi,则其中带权路径长度WPL=w1*l1+w2*l2+...wm*lm最小的二叉树即为哈夫曼树！--*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
typedef char ElemType;
typedef char* *HuffmanCode;    //这里用来存储每个叶子结点的哈夫曼编码；
/*----------------------------------typedef char **HuffmanCode;----------------------------------------*/
                                                  
/*--char*  代表字符指针类型，其指向一个字符串的第一个元素，代表这个字符串,如char* str = "shcool"；   --*/
/*--char** 可以理解为字符串数组，如char* *a = new char* [10];                                        --*/
/*--                                   for(i=0;i<10;i++)                                             --*/
/*--								   { a[i]=new char[6]; }                                         --*/
/*--								   =>a[0] = "school"，a[0][2] = 'h' ;                            --*/

/*----------------------------------typedef char **HuffmanCode;----------------------------------------*/

typedef struct HTNode
{
	int weight;                //结点的权值，一般为int,float或double型
	int parent,lchild,rchild;
	ElemType value;                 //实际值 
}HTNode,*HuffmanTree;           //哈夫曼树各结点存储在由HuffmanTree定义的动态分配的数组中


/*一组树中选取权值最小的树*/
int MinNode(HuffmanTree HT,int n)
{
	int i,min;
	int min_weight;
	i = 1;
	while(HT[i].parent != 0)           //寻找到第一个没有双亲（未被选取过）的结点 
		i++;                       
	min_weight = HT[i].weight;
	min = i;                          
	for(;i<n;i++)                     //选取权值最小且parent = 0的树 
	{
		if((HT[i+1].weight<min_weight)&&(HT[i+1].parent==0))
		{
			min_weight = HT[i+1].weight;
			min = i+1;                        
		}
	}
	HT[min].parent = 1;                       //并将该棵树的双亲结点赋给序号1的结点，方便下次选取 
	return min;                               //返回权值最小且parent = 0的树的序号 
}

/*--构造哈夫曼树--*/
HTNode *CreateHTree(int n)
{
	HuffmanTree HT;
	int i;
	ElemType data;
	int wei;
	int s1,s2;
	if(n<=1)
		return;
	int total = 2*n-1;         //一棵有n个叶子结点的哈夫曼树总共有(2*n-1)个结点 
	HT = (HuffmanTree)malloc(total*sizeof(HTNode));
	if(!HT)
		exit(-1);
	
	//先将所有单元的双亲域、孩子域赋值0，以初始化 
	for(i=1;i<=total;i++)      //为了实现方便，数组的0号单元不使用
	{
		  HT[i].parent = 0;
		  HT[i].lchild = 0; 
		  HT[i].rchild = 0;
	}  
	
	//向叶节点单元赋给其实际值与权值 
	for(i=1;i<=n;i++)
	{
		printf("输入实际值与它的权值:");
		scanf("%c,%d%*c",&data,&wei);       //%*c是跳过下一个要输入的内容，这里用于跳过回车键 
		HT[i].value = data;
		HT[i].weight = wei;
	}
	
	//选取两颗权值最小的树进行合并，得到新节点存储在数组的第n+1之后的单元中 
	for(i=n+1;i<=total;i++)                 
	{
		s1 = MinNode(HT,i-1);    
		s2 = MinNode(HT,i-1);     //在新结点所在单元之前的所有单元中，选取两颗权值最小且parent = 0的树
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;     
		HT[i].value = '@';        //'@'只代表该结点为合并节点，这里的实际值按需要可以赋其他值 
		HT[s1].parent = i;
		HT[s2].parent = i;
	}
	 
	return HT;
} 
/*--哈夫曼编码：--*/
/*--哈夫曼树左分支代表0，右分支代表1；--*/ 
/*--从根节点到叶节点的路径分支组成的0和1的序列即为对应叶节点实际值的编码--*/
HuffmanCode EnHuffmanCoding(HuffmanTree HT,int n)
{
	HuffmanCode HC;
	//哈夫曼编码是一个个不等长的0和1字符串，存储在HC指向的数组中 
	HC = (HuffmanCode)malloc((n+1)*sizeof(char*));       //0号单元不使用，数组大小为(n+1)
	if(!HC)
		exit(-1);
		
	//临时编码空间code，一个哈夫曼编码即为0和1组成的字符串
	//对于有n个叶子节点的赫夫曼树，各叶子节点的编码长度最长不超过n-1 
	char *code = (char*)malloc((n-1)*sizeof(char));
	if(!code)
		exit(-1);         
	
	int i;
	int final;          //final表示当前结点的双亲序号 
	int itemp;          //itemp暂时存储当前循环的i值(即当前叶节点序号)
	int start;          //start表示每个哈夫曼编码0和1字符串中起始的位置 
	
	code[n-1] = '\0';   //编码结束符   
	
	for(i=1;i<=n;i++)   //依次循环所有n个叶节点 
	{
		final = HT[i].parent;
		itemp = i;
		start = n-1;
		
		while(final != 0)
		{
			start -= 1;
			if(HT[final].lchild == itemp)
				code[start] = '0';
			else
				code[start] = '1';
			itemp = final;
			final = HT[final].parent;
		}
		
		HC[i] =  (char*)malloc((n-start)*sizeof(char));    //为第i个字符编码分配空间
		if(!HC[i])
			exit(-1);
		
		strcpy(HC[i],&code[start]);          
	}  
	
	free(code);         //释放临时编码空间code 
	return HC;
} 


/*--遍历哈夫曼树--*/
void PrintHTree(HuffmanTree HT)\
{
	int i=0;
	printf("哈夫曼树：\n");
	do
	{
		i++;
		printf("->|%d|%d|%d|%d|%d|%c|\n",i,HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild,HT[i].value);	
	}while(HT[i].parent!=0);
}

int main()
{       
	int i,j;
	HuffmanTree HT1;
	HuffmanCode HC1;
	HT1 = CreateHTree(8); 
	PrintHTree(HT1);
	HC1 = EnHuffmanCoding(HT1,8);     
	/*--这里HT1,HC1都为指针，所以CreateHTree()，EnHuffmanCoding()都返回了指针的值--*/
	/*--如果不返回，需用HT1,HC1的指针作形参，即指针的指针去申请内存空间--*/
	/*--我个人是这么理解的，不然就会指针错误，dev c++运行出错，停止运行！--*/ 
	printf("打印出哈夫曼编码：\n");
	for(i=1;i<=8;i++)
	{
		j = 0;
		printf("%c的哈夫曼编码为：",HT1[i].value); 
		while(HC1[i][j] != '\0')
		{
			printf("%c",HC1[i][j]);
			j++;
		}
		printf("\n");
	} 
	return 0;
} 
