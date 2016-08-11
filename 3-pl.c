#include<stdio.h>
#include<stdlib.h>
typedef struct{
	int *top;
	int *base;
}stack;
int main()
{
	int i,n,t,tmp=0,*a,*s,count=0;
	stack L;
	scanf("%d",&n);
	a=(int* )malloc(n*sizeof(int));
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);
	s=(int* )malloc((n+1)*sizeof(int));
	L.top=L.base=s;
	for(i=0;i<n;i++)
	{
		if(a[i]>*(L.top-1))
		{
			for(t=tmp+1;t<=a[i];t++)
			{
				L.top++;
				*L.top=t;
				t++;
			}
			if(*(L.top-1)>tmp) tmp=*L.top;
			L.top--;
			count++;
		}
		else if(a[i]==*(L.top-1))
			{
				L.top--;
				count++;
		}
		else if(a[i]<*(L.top-1))
		{
			printf("NO");
			break;
		}
	}
	if(count==n) printf("yes");
	system("pause");
}


