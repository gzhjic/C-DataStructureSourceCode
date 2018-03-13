/*--@�̺���--*/
/*--2017/11/07--*/
/*--�����������洢�ṹ��˳��洢�����飩--*/

/*����������㣺   ____________________________________________  */
/*                |_weight_|_parent_|_lchild_|_rchild_|_value_|  */

/*--����������������m��Ȩֵ{w1,w2,...,wm},���Թ���һ�ú�n��Ҷ�ӽ��Ķ�����--*/
/*--ÿ��Ҷ�ӽ���ȨΪwi,�����д�Ȩ·������WPL=w1*l1+w2*l2+...wm*lm��С�Ķ�������Ϊ����������--*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
typedef char ElemType;
typedef char* *HuffmanCode;    //���������洢ÿ��Ҷ�ӽ��Ĺ��������룻
/*----------------------------------typedef char **HuffmanCode;----------------------------------------*/
                                                  
/*--char*  �����ַ�ָ�����ͣ���ָ��һ���ַ����ĵ�һ��Ԫ�أ���������ַ���,��char* str = "shcool"��   --*/
/*--char** �������Ϊ�ַ������飬��char* *a = new char* [10];                                        --*/
/*--                                   for(i=0;i<10;i++)                                             --*/
/*--								   { a[i]=new char[6]; }                                         --*/
/*--								   =>a[0] = "school"��a[0][2] = 'h' ;                            --*/

/*----------------------------------typedef char **HuffmanCode;----------------------------------------*/

typedef struct HTNode
{
	int weight;                //����Ȩֵ��һ��Ϊint,float��double��
	int parent,lchild,rchild;
	ElemType value;                 //ʵ��ֵ 
}HTNode,*HuffmanTree;           //�������������洢����HuffmanTree����Ķ�̬�����������


/*һ������ѡȡȨֵ��С����*/
int MinNode(HuffmanTree HT,int n)
{
	int i,min;
	int min_weight;
	i = 1;
	while(HT[i].parent != 0)           //Ѱ�ҵ���һ��û��˫�ף�δ��ѡȡ�����Ľ�� 
		i++;                       
	min_weight = HT[i].weight;
	min = i;                          
	for(;i<n;i++)                     //ѡȡȨֵ��С��parent = 0���� 
	{
		if((HT[i+1].weight<min_weight)&&(HT[i+1].parent==0))
		{
			min_weight = HT[i+1].weight;
			min = i+1;                        
		}
	}
	HT[min].parent = 1;                       //�����ÿ�����˫�׽�㸳�����1�Ľ�㣬�����´�ѡȡ 
	return min;                               //����Ȩֵ��С��parent = 0��������� 
}

/*--�����������--*/
HTNode *CreateHTree(int n)
{
	HuffmanTree HT;
	int i;
	ElemType data;
	int wei;
	int s1,s2;
	if(n<=1)
		return;
	int total = 2*n-1;         //һ����n��Ҷ�ӽ��Ĺ��������ܹ���(2*n-1)����� 
	HT = (HuffmanTree)malloc(total*sizeof(HTNode));
	if(!HT)
		exit(-1);
	
	//�Ƚ����е�Ԫ��˫���򡢺�����ֵ0���Գ�ʼ�� 
	for(i=1;i<=total;i++)      //Ϊ��ʵ�ַ��㣬�����0�ŵ�Ԫ��ʹ��
	{
		  HT[i].parent = 0;
		  HT[i].lchild = 0; 
		  HT[i].rchild = 0;
	}  
	
	//��Ҷ�ڵ㵥Ԫ������ʵ��ֵ��Ȩֵ 
	for(i=1;i<=n;i++)
	{
		printf("����ʵ��ֵ������Ȩֵ:");
		scanf("%c,%d%*c",&data,&wei);       //%*c��������һ��Ҫ��������ݣ��������������س��� 
		HT[i].value = data;
		HT[i].weight = wei;
	}
	
	//ѡȡ����Ȩֵ��С�������кϲ����õ��½ڵ�洢������ĵ�n+1֮��ĵ�Ԫ�� 
	for(i=n+1;i<=total;i++)                 
	{
		s1 = MinNode(HT,i-1);    
		s2 = MinNode(HT,i-1);     //���½�����ڵ�Ԫ֮ǰ�����е�Ԫ�У�ѡȡ����Ȩֵ��С��parent = 0����
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;     
		HT[i].value = '@';        //'@'ֻ����ý��Ϊ�ϲ��ڵ㣬�����ʵ��ֵ����Ҫ���Ը�����ֵ 
		HT[s1].parent = i;
		HT[s2].parent = i;
	}
	 
	return HT;
} 
/*--���������룺--*/
/*--�����������֧����0���ҷ�֧����1��--*/ 
/*--�Ӹ��ڵ㵽Ҷ�ڵ��·����֧��ɵ�0��1�����м�Ϊ��ӦҶ�ڵ�ʵ��ֵ�ı���--*/
HuffmanCode EnHuffmanCoding(HuffmanTree HT,int n)
{
	HuffmanCode HC;
	//������������һ�������ȳ���0��1�ַ������洢��HCָ��������� 
	HC = (HuffmanCode)malloc((n+1)*sizeof(char*));       //0�ŵ�Ԫ��ʹ�ã������СΪ(n+1)
	if(!HC)
		exit(-1);
		
	//��ʱ����ռ�code��һ�����������뼴Ϊ0��1��ɵ��ַ���
	//������n��Ҷ�ӽڵ�ĺշ���������Ҷ�ӽڵ�ı��볤���������n-1 
	char *code = (char*)malloc((n-1)*sizeof(char));
	if(!code)
		exit(-1);         
	
	int i;
	int final;          //final��ʾ��ǰ����˫����� 
	int itemp;          //itemp��ʱ�洢��ǰѭ����iֵ(����ǰҶ�ڵ����)
	int start;          //start��ʾÿ������������0��1�ַ�������ʼ��λ�� 
	
	code[n-1] = '\0';   //���������   
	
	for(i=1;i<=n;i++)   //����ѭ������n��Ҷ�ڵ� 
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
		
		HC[i] =  (char*)malloc((n-start)*sizeof(char));    //Ϊ��i���ַ��������ռ�
		if(!HC[i])
			exit(-1);
		
		strcpy(HC[i],&code[start]);          
	}  
	
	free(code);         //�ͷ���ʱ����ռ�code 
	return HC;
} 


/*--������������--*/
void PrintHTree(HuffmanTree HT)\
{
	int i=0;
	printf("����������\n");
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
	/*--����HT1,HC1��Ϊָ�룬����CreateHTree()��EnHuffmanCoding()��������ָ���ֵ--*/
	/*--��������أ�����HT1,HC1��ָ�����βΣ���ָ���ָ��ȥ�����ڴ�ռ�--*/
	/*--�Ҹ�������ô���ģ���Ȼ�ͻ�ָ�����dev c++���г���ֹͣ���У�--*/ 
	printf("��ӡ�����������룺\n");
	for(i=1;i<=8;i++)
	{
		j = 0;
		printf("%c�Ĺ���������Ϊ��",HT1[i].value); 
		while(HC1[i][j] != '\0')
		{
			printf("%c",HC1[i][j]);
			j++;
		}
		printf("\n");
	} 
	return 0;
} 
