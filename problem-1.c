#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int main()
{
	int n,sum=0,i,tmp;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&tmp);
		sum+=tmp;
	}
	printf("%d",sum);
	system("pause");
}