#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int get(char *s,char *t,char *a,int m,int n)
{
	char *tmp,*s1,*t1;
	int i=0,j=0,mar=0,k=0,max=0,control=0;
	s1=s; t1=t;
	tmp=(char* )malloc(m*sizeof(char));
	for(control=0;control<2;control++)
	{
	while(!(i==m&&j==n))
	{
		for(i=mar;i<m;)
		{
			if(s1[i]==t1[j])
			{
				tmp[k++]=s1[i]; i++; j++; mar=i; 
			}
			else i++;
		}
		if(t1[j]==s1[m-1]) break;
		j++;
	}
	if(k>max)
	{
		max=k;
		for(k=0;k<max;k++)
			a[k]=tmp[k];
	}
	i=m-1; j=n-1; k=0;
	while(!(i==0&&j==0))
	{
		for(i=mar;i>0;)
		{
			if(s1[i]==t1[j])
			{
				tmp[k++]=s1[i]; i--; j--; mar=i;
			}
			else i--;
		}
		if(t1[j]==s1[0]) break;
		j--;
	}
	if(k>max)
	{
		max=k;
		for(k=0;k<max;k++)
			a[k]=tmp[k];
	}
	s1=t; t1=s; k=0;
	}
	return max;
}
int main()
{
	int m=0,n=0,i,M;
	char *s,*t,*a,*s1,*t1,*s2,*t2,*s3,*t3;
	a=(char* )malloc(m*sizeof(char));
	s=(char* )malloc(m*sizeof(char));
	t=(char* )malloc(n*sizeof(char));
	gets(s);
	gets(t);
	m=strlen(s);
	n=strlen(t);
	M=get(s,t,a,m,n);
	for(i=0;i<M;i++)
		printf("%c",a[i]);
	printf("\n%d",M);
	system("pause");
}
