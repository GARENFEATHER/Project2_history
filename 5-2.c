#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef int datatype;
typedef struct a{
	int i,j;
	datatype d;
}tri;
void show(tri *p,int n)
{
	int i,j,d=0,k=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			if(!(i==p[k].i&&j==p[k].j)) printf("%d\t",d);
			else { printf("%d\t",p[k].d); k++; }
		printf("\n");
	}
}
void T(tri *a,int k)
{
	int i,j,t;
	tri tmp;
	for(i=0;i<k;i++)
		for(j=i+1;j<k-i-1;j++)
			if(a[j].j<a[i].j) { tmp=a[j]; a[j]=a[i]; a[i]=tmp; }
			else if(a[j].j==a[i].j)
				if(a[j].i<a[i].i) { tmp=a[j]; a[j]=a[i]; a[i]=tmp; }
	for(i=0;i<k;i++)
	{
		t=a[i].i;
		a[i].i=a[i].j;
		a[i].j=t;
	}
}
void aplusb(tri *a,tri *b,tri *c,int n)
{
	int i=0,j=0,ka=0,kb=0,k=0;
	while(i<n)
	{
		j=0;
		while(j<n)
		{
			if((i==a[ka].i&&j==a[ka].j) || (i==b[kb].i&&j==b[kb].j))
			{
				k++;
				c=(tri* )realloc(c,k*sizeof(tri));
				c[k-1].i=i; c[k-1].j=j;
				if((i==a[ka].i&&j==a[ka].j) && !(i==b[kb].i&&j==b[kb].j))
				{
					c[k-1].d=a[ka].d; ka++;
				}
				else if(!(i==a[ka].i&&j==a[ka].j) && (i==b[kb].i&&j==b[kb].j))
				{
					c[k-1].d=b[kb].d; kb++;
				}
				else
				{
					c[k-1].d=a[ka].d+b[kb].d; 
					ka++; kb++;
				}
			}
			j++;
		}
		i++;
	}
	printf("a+b:\n");
	show(c,n);
}
void multi(tri *a,tri *b,int ka,int kb,int n)
{
	int i,j,k=0,t=0,tp=0;
	datatype **tmp;
	for(i=0;i<n;i++)
		tmp=(int** )malloc(n*sizeof(int*));
	for(i=0;i<n;i++)
	{
		tmp[i]=(int* )malloc(n*sizeof(int));
		for(j=0;j<n;j++)
			tmp[i][j]=0;
	}
	while(k<ka)
	{
		i=a[k].j;
		while(b[t].i!=i) t++;
		while (b[t].i==i)
		{
			tp=a[k].d*b[t].d;
			tmp[a[k].i][b[t].j]+=tp;
			t++;
		}
		t=0;
		k++;
	}
	printf("a*b:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			printf("%d\t",tmp[i][j]);
		printf("\n");
	}
}
int main()
{
	int i,n,t,j,k,ka,kb;
	tri *a,*b,*c;
	FILE *fp;
	fp=fopen("2.txt","r");
	a=(tri* )malloc(sizeof(tri));
	b=(tri* )malloc(sizeof(tri));
	c=(tri* )malloc(sizeof(tri));
	fscanf(fp,"%d",&n);
	for(i=0,k=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			fscanf(fp,"%d",&t);
			if(t!=0)
			{
				k++;
				a=(tri* )realloc(a,k*sizeof(tri));
				a[k-1].i=i; a[k-1].j=j; a[k-1].d=t;
			}
		}
	ka=k;
	for(i=0,k=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			fscanf(fp,"%d",&t);
			if(t!=0)
			{
				k++;
				b=(tri* )realloc(b,k*sizeof(tri));
				b[k-1].i=i; b[k-1].j=j; b[k-1].d=t;
			}
		}
	kb=k;
	T(a,ka);
	show(a,n);
	T(a,ka);
	aplusb(a,b,c,n);
	multi(a,b,ka,kb,n);
	system("pause");
}