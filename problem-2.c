#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int main()
{
	int n,*s,tmp,i,j;
	scanf("%d",&n);
	s=(int* )malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
		scanf("%d",&s[i]);
	for(i=0;i<n;i++)
		for(j=0;j<n-i-1;j++)
			if(s[j]>s[j+1])
			{
				tmp=s[j];
				s[j]=s[j+1];
				s[j+1]=tmp;
			}
	printf("%d",s[n-1]+s[n-2]);
}