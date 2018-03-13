/*--@�̺���--*/
/*--2017/10/20--*/
/*--ģʽƥ�䣺BF�㷨 or KMP�㷨-*/

#include<stdio.h>
#include<string.h>


/*���ص�ģʽƥ���㷨��BF�㷨*/
/*��������S�д�λ��pos��ʼ���״γ���ģʽ��T��λ�ã����򷵻�-1*/
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
			i = i-j+1;               //��һ��ƥ��ʧ�ܣ���һ��i��pos+1��ʼƥ�� 
			j = 0;                    
		}
	}
	if(j >= strlen(T))
		return i-strlen(T);          //ƥ��ɹ��������������Ӵ�����ʼindexֵ 
	else
		return -1;                  //ƥ��ʧ�ܣ�����errorֵ-1 
}

/*�Ľ���ģʽƥ���㷨��KMP�㷨*/
 
/*�����ǵõ�ǰ׺����next[j]=k��ֵ*/
void Get_Next(char *T,int *next)  //���ﴫ�ݵ��ǵ�ַ����������������next[]������ʧ����û�з���ֵ 
{
	int k,j;	
	j = 0;
	k = -1;
	next[0] = -1;
	while(j < strlen(T)-1)
	{
		if((k==-1)||(T[j]==T[k]))       //T[j]��ʾ��׺�ĵ����ַ���T[k]��ʾǰ׺�ĵ����ַ�
		{
			++k;
			++j;
			next[j] = k;
		}
		else
			k = next[k];	
	}
}

/*Ȼ�󽫵õ���next[]��������Kmp�㷨*/ 
int Index_Kmp(char *S,char *T,int pos)
{
	int i,j;
	int next[100];
	int Slen = strlen(S);             //��ԭֱ��ʹ��while((i<strlen(S)) && (j<strlen(T)))
	int Tlen = strlen(T);             //����j<strlen(T)�ƺ������⣿����ֱ��ʹ�ý��������֪��Ϊɶ��  
	i = pos;
	j = 0;
	Get_Next(T,next);
	while((i<Slen) && (j<Tlen))
	{
		if((j == -1)||(S[i] == T[j]))   //�����BF�㷨������һ���жϣ�j==-1 
		{
			i++;
			j++;                        //j==-1ʱ��ֻ���ƶ�i,ͬʱj��λλ��0 
		}
		else
		{
			j = next[j];   //j�˻غ��ʵ�λ�ã�iֵ���� 
		}
	}
	if(j>=Tlen)
		return i-Tlen;
	else
		return -1; 
}

/*�Ľ����KMP�㷨*/
/* ԭKMP�㷨��ȱ�ݣ���T[j]!=S[i]ʱ����ΪT[j] = T[next[j]],�ƶ�j�����ֵĶ��ಽ��!*/
void Get_Nextval(char *T,int *nextval) 
{
	int k,j;	
	j = 0;
	k = -1;
	nextval[0] = -1;
	while(j < strlen(T)-1)
	{
		if((k==-1)||(T[j]==T[k]))       //T[j]��ʾ��׺�ĵ����ַ���T[k]��ʾǰ׺�ĵ����ַ�
		{
			++k;
			++j;
			if(T[j] != T[k])           //��ǰǰ׺�ַ����׺�ַ����ȣ���T[j] = T[next[j]] 
				nextval[j] = k;        //��ǰ��kΪnextval��jλ�õ�ֵ
			else
				nextval[j] = nextval[k];    //����ͬ����ǰ׺�ַ���nextvalֵ����nextval��jλ�õ�ֵ 
		}                                   //��������������ͬ��ֵ��T[j] = T[next[j]]����
		else                                //���磺T=��aaax��,��ʱT[3]!=S[i],���ƶ�j, 
			k = nextval[k];	                //��nextval[2] = nextval[1] = nextval[0]=-1��ʡ����һ���� 
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
