#include<stdio.h>
#include<stdlib.h>
int main()
{
	int i,code=0,ans=0,a[4];
	printf("����������:\n");
	scanf("%d",&code);
	printf("����%d��Ӧ������:\n",code);
	ans=code;
	for(i=0;i<4;i++)
	{
		a[i]=ans%10;
		a[i]=a[i]+5;
		a[i]=a[i]%10;
		ans=ans/10;
		printf("%d",a[i]);
	}
	system("pause");
}