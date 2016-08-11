#include<stdio.h>
#include<stdlib.h>
int main()
{
	char s='*';
	int n,i,j,t;
	scanf("%d",&n);
	for(i=0;i<2*n-1;i++)
	{
		if(i<n) t=i;
		else t=2*(n-1)-i;
		for(j=0;j<n*2-1;j++)
		{
			if(j==n-1-t || j==n-1+t) printf("*");
			else printf(" ");
		}
		printf("\n");
	}
	system("pause");
}