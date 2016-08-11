#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
typedef struct s
{
	int *data;
	int size;
	int *next;
}List;
void simpleSort(List L)
{
	int i,tmp,j;
	for(i=0;i<L.size;i++)
		if(L.data[i]<L.data[i-1])
		{
			tmp=L.data[i];
			for(j=i-1;tmp<L.data[j];j--)
				L.data[j+1]=L.data[j];
			L.data[j+1]=tmp;
		}
}
void half(List L)
{
	int i,mid,low,high,tmp,j;
	for(i=1;i<L.size;i++)
	{
		tmp=L.data[i];
		low=0;
		high=i-1;
		while(low<=high)
		{
			mid=(low+high)/2;
			if(tmp>L.data[mid]) low=mid+1;
			else high=mid-1;
		}
		for(j=i-1;j>=high+1;j--) L.data[j+1]=L.data[j];
		L.data[j+1]=tmp;
	}
}
void bubble(List L)
{
	int i,tmp,j,last,mark;
	last=L.size-1;
	for(i=0;i<L.size;i++)
	{
		for(j=0;j<last;j++)
			if(L.data[j+1]<L.data[j])
			{
				tmp=L.data[j+1];
				L.data[j+1]=L.data[j];
				L.data[j]=tmp;
				mark=j;
			}
		last=mark;
	}
}
void listinsert(List L)
{
	int i,j,k,start;
	start=L.data[0]>L.data[1]?1:0;
	L.next[0]=1;
	L.next[1]=0;
	for(i=2;i<L.size;i++)
	{
		j=start;
		k=L.next[start];
		while(1)
		{
			if(L.data[i]>=L.data[j] && L.data[i]<=L.data[k])
			{
				L.next[j]=i;
				L.next[i]=k;
				break;
			}
			if(L.data[j]>L.data[k])
			{
				L.next[j]=i;
				L.next[i]=k;
				if(L.data[i]<L.data[k]) start=i;
				break;
			}
			j=k;
			k=L.next[k];
		}
	}
}
void shellinsert(List L,int dlta)
{
	int i=0,j,tmp;
	for(i=dlta;i<L.size;i++)
		if(L.data[i] < L.data[i-dlta])
		{
			tmp=L.data[i];
			for(j=i-dlta;j>=0,tmp<L.data[j];j-=dlta)
				L.data[j+dlta]=L.data[j];
			L.data[j+dlta]=tmp;
		}
}
void shellsort(List L,int *dlta,int n)//BUG
{
	int i;
	for(i=n-1;i>=0;i--)
		shellinsert(L,dlta[i]);
	for(i=0;i<L.size;i++)
		printf("%d ",L.data[i]);
}
int quick(List L,int low,int high)
{
	int tmp;
	tmp=L.data[low];
	while(low<high)
	{
		while(low<high && L.data[high]>=tmp) high--;
		L.data[low]=L.data[high];
		while(low<high && L.data[low]<=tmp) low++;
		L.data[high]=L.data[low];
	}
	L.data[low]=tmp;
	return low;
}
void quicksort(List L,int low,int high)
{
	int point;
	if(low<high)
	{
		point=quick(L,low,high);
		quicksort(L,low,point-1);
		quicksort(L,point+1,high);
	}
}
void Qsort(List L)
{
	int low,high,i;
	low=0;
	high=L.size-1;
	quicksort(L,low,high);//答案都对但就是停止工作
}

int main()
{
	FILE *fp;
	List L;
	int i,tmp;
	int dlda[3]={1,3,5};
	fp=fopen("10-1.txt","r");
	L.data=(int* )malloc(sizeof(int));//不需要多开n*sizeof？？？？
	L.size=0;
	L.next=(int* )malloc(sizeof(int));
	for(i=0;;i++)
	{
		fscanf(fp,"%d",&tmp);
		if(tmp==-1) break;
		L.data[i]=tmp;
		L.size++;
		L.next[i]=-1;
	}
	//listinsert(L);
	//half(L);
	//shellsort(L,dlda,3);
	//Qsort(L);
	system("pause");
}
