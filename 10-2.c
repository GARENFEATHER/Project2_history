#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
void simpleselect(int *L,int n)
{
	int i,j,tmp,k,change;
	for(i=0;i<n;i++)
	{
		tmp=L[i];
		k=i;
		for(j=i+1;j<n;j++)
			if(L[j] < tmp)
			{
				tmp=L[j];
				k=j;
			}
		if(i!=k)
		{
			change=L[i];
			L[i]=tmp;
			L[k]=change;
		}
	}
}
int check(int *L,int n)
{
	int i=0,j,c=0;
	for(i=0;i<n/2-1;i++)
	{
		j=2*(i+1)-1;
		if(L[i] < L[j] || L[i] < L[j+1])
		{
			c=1;
			break;
		}
	}
	return c;
}
void HeapAdjust(int *L,int s,int m)
{
	int rc,j;
	rc=L[s];
	for(j=2*(s+1)-1;j<m;j=(j+1)*2-1)
	{
		if(j<m && L[j]<L[j+1]) j++;
		if(rc>=L[j]) break;
		L[s]=L[j];
		s=j;
	}
	L[s]=rc;
}
void HeapSort(int *L,int n)
{
	int i,tmp;
	for(i=n/2;i>=0;i--)
		HeapAdjust(L,i,n-1);
	for(i=n-1;i>0;i--)
	{
		tmp=L[i];
		L[i]=L[0];
		L[0]=tmp;
		/*if(check(L,i+1) == 0) printf("YES ");
		else printf("NO ");*/
		HeapAdjust(L,0,i-1);
		/*if(check(L,i) == 0) printf("YES\n");
		else printf("NO\n");*/
	}
}

int quick(int *L,int low,int high)
{
	int tmp;
	tmp=L[low];
	while(low<high)
	{
		while(low<high && L[high]>=tmp) high--;
		L[low]=L[high];
		while(low<high && L[low]<=tmp) low++;
		L[high]=L[low];
	}
	L[low]=tmp;
	return low;
}
void StackQsort(int *L,int n,int low,int high)
{
	int *S,i=0,j=0,k=0,mid,size;
	size=n;
	S=(int* )malloc(size*sizeof(int));
	if(low<high)
	{
		mid=quick(L,low,high);
		if(low<mid-1)
		{
			if(k>=size)
			{
				size*=2;
				S=(int* )realloc(S,size*sizeof(int));
			}
			S[k++]=low;
			S[k++]=mid-1;
		}
		if(mid+1<high)
		{
			if(k>=size)
			{
				size*=2;
				S=(int* )realloc(S,size*sizeof(int));
			}	
			S[k++]=mid+1;
			S[k++]=high;
		}
		while(k!=0)//????
		{
			j=S[k-1]; k--;
			i=S[k-1]; k--;
			mid=quick(L,i,j);
			if(i<mid-1)
			{
				if(k>=size)
				{
					size*=2;
					S=(int* )realloc(S,size*sizeof(int));
				}
				S[k++]=i;
				S[k++]=mid-1;
			}
			if(mid+1<j)
			{
				if(k>=size)
				{
					size*=2;
					S=(int* )realloc(S,size*sizeof(int));
				}
				S[k++]=mid+1;
				S[k++]=j;
			}
		}
	}
}
int main()
{
	FILE *fp;
	int *L,i=0,tmp;
	fp=fopen("10-2.txt","r");
	L=(int* )malloc(sizeof(int));
	while(1)
	{
		fscanf(fp,"%d",&tmp);
		if(tmp == -1) break;
		L[i]=tmp;
		i++;
	}
	//simpleselect(L,i);
	//HeapSort(L,i);
	StackQsort(L,i,0,i-1);
	for(i=i-1;i>=0;i--)
		printf("%d µÚ%d¸ö\n",L[i],i);
	system("pause");
}