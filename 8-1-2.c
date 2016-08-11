#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int main()//更改输入数据请更改txt，数据数量可更改，但保留末位结束标志-999，
{
	FILE *fp;
	int *c,i,j,t,csize=100,fin;
	fp=fopen("8-1-2.txt","r");
	c=(int* )malloc(csize*sizeof(int));
	for(i=0;;i++)
	{
		 fscanf(fp,"%d",&t);
		 if(t==-999) break;
		 if(i>=csize)
		 {
			 csize*=2;
			 c=(int* )malloc(csize*sizeof(int));
		 }
		 c[i]=t;
	}
	j=i-1;
	for(i=0;;)
	{
		if(c[i]>c[j])
		{
			i++;
			j--;
		}
		else 
		{
			if(c[j+1]<c[j]) fin=j+1;
			else if(c[i-1]>c[i]) fin=i;
			break;
		}
	}
	printf("the answer:%d",fin);
	system("pause");
}