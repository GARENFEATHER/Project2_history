#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int n,i=0,j=0,**a,num=0,*t1,*t2,*tmp,q=0,t=1;
	t1=&i;
	t2=&j;
	scanf("%d",&n);
	a=(int** )malloc(n*sizeof(int*));
	for(i=0;i<n;i++)
	{
		a[i]=(int* )malloc(n*sizeof(int));
		for(j=0;j<n;j++)
			a[i][j]=-1;
	}
	i=0;j=0;
	while(num!=n*n)
	{
		num++;
		a[i][j]=num;
		(*t2)+=t;
		if((j==n&&i==0)||(j==n-1&&i==n)||(j==-1&&i==n-1)||a[i][j]!=-1)
		{
			(*t2)-=t;
			tmp=t1;
			t1=t2;
			t2=tmp;
			q++;
			if(q==2)
			{
				t=-t;
				q=0;
			}
			(*t2)+=t;
		}
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			printf("%d\t",a[i][j]);
		printf("\n");
	}
	system("pause");
}
