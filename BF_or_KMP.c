/*--@程豪琪--*/
/*--2017/10/20--*/
/*--模式匹配：BF算法 or KMP算法-*/

#include<stdio.h>
#include<string.h>


/*朴素的模式匹配算法：BF算法*/
/*返回主串S中从位置pos开始，首次出现模式串T的位置，否则返回-1*/
int Index_Bf(char *S,char *T,int pos)
{
	int i,j;
	i = pos;
	j = 0;
	while((i<strlen(S)) && (j<strlen(T)))
	{
		if(S[i] == T[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i-j+1;               //上一次匹配失败，下一次i从pos+1开始匹配 
			j = 0;                    
		}
	}
	if(j >= strlen(T))
		return i-strlen(T);          //匹配成功，返回主串中子串的起始index值 
	else
		return -1;                  //匹配失败，返回error值-1 
}

/*改进的模式匹配算法：KMP算法*/
 
/*首先是得到前缀函数next[j]=k的值*/
void Get_Next(char *T,int *next)  //这里传递的是地址，函数结束后数组next[]不会消失，故没有返回值 
{
	int k,j;	
	j = 0;
	k = -1;
	next[0] = -1;
	while(j < strlen(T)-1)
	{
		if((k==-1)||(T[j]==T[k]))       //T[j]表示后缀的单个字符，T[k]表示前缀的单个字符
		{
			++k;
			++j;
			next[j] = k;
		}
		else
			k = next[k];	
	}
}

/*然后将得到的next[]数组用于Kmp算法*/ 
int Index_Kmp(char *S,char *T,int pos)
{
	int i,j;
	int next[100];
	int Slen = strlen(S);             //我原直接使用while((i<strlen(S)) && (j<strlen(T)))
	int Tlen = strlen(T);             //但是j<strlen(T)似乎有问题？这样直接使用结果出错，不知道为啥？  
	i = pos;
	j = 0;
	Get_Next(T,next);
	while((i<Slen) && (j<Tlen))
	{
		if((j == -1)||(S[i] == T[j]))   //相对于BF算法，多了一个判断，j==-1 
		{
			i++;
			j++;                        //j==-1时，只能移动i,同时j归位位置0 
		}
		else
		{
			j = next[j];   //j退回合适的位置，i值不变 
		}
	}
	if(j>=Tlen)
		return i-Tlen;
	else
		return -1; 
}

/*改进后的KMP算法*/
/* 原KMP算法的缺陷：当T[j]!=S[i]时，因为T[j] = T[next[j]],移动j而出现的多余步骤!*/
void Get_Nextval(char *T,int *nextval) 
{
	int k,j;	
	j = 0;
	k = -1;
	nextval[0] = -1;
	while(j < strlen(T)-1)
	{
		if((k==-1)||(T[j]==T[k]))       //T[j]表示后缀的单个字符，T[k]表示前缀的单个字符
		{
			++k;
			++j;
			if(T[j] != T[k])           //当前前缀字符与后缀字符不等，即T[j] = T[next[j]] 
				nextval[j] = k;        //则当前的k为nextval在j位置的值
			else
				nextval[j] = nextval[k];    //若相同，则将前缀字符的nextval值赋给nextval在j位置的值 
		}                                   //这样就跳过了相同的值（T[j] = T[next[j]]），
		else                                //例如：T=‘aaax’,此时T[3]!=S[i],需移动j, 
			k = nextval[k];	                //即nextval[2] = nextval[1] = nextval[0]=-1，省略了一步！ 
	}
}

int Index_Kmpval(char *S,char *T,int pos)
{
	int i,j;
	int nextval[100];
	int Slen = strlen(S);             
	int Tlen = strlen(T);          
	i = pos;
	j = 0;
	Get_Nextval(T,nextval);
	while((i<Slen) && (j<Tlen))
	{
		if((j == -1)||(S[i] == T[j]))   
		{
			i++;
			j++;                        
		}
		else
		{
			j = nextval[j];    
		}
	}
	if(j>=Tlen)
		return i-Tlen;
	else
		return -1; 
}

int main()
{
	char str1[100] = "goddoooooooooogoogle";
	char str2[7] = "google";
	printf("Index of T:%d\n",Index_Bf(str1,str2,0));
	printf("Index of T:%d\n",Index_Kmp(str1,str2,0));
	printf("Index of T:%d\n",Index_Kmpval(str1,str2,0));
	return 0;
}
