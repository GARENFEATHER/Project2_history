#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
void checkE(int *Htst,int *Hash,int n,int p)
{
	double sum=0;
	int i,key,count=1,di=0;
	for(i=0;i<n;i++)
	{
		key=Htst[i]%p;
		if(Hash[key]==Htst[i]) count=1;
		else for(di=0,count=1;;)
		{
			di++;
			if(Hash[(key+di*di)%p]=Htst[i])
			{
				count++;
				break;
			}
			else if(Hash[(key-di*di)%p]=Htst[i])
			{
				count+=2;
				break;
			}
			count+=2;;
		}
		sum+=count;
		di=0;
	}
	sum=sum/n;
	printf("everage:%lf",sum);
}
int main()
{
	FILE *fp;
	int n=0,num,m=51,p=51,*Hash,i,di=-1,die=0,*Htst;
	fp=fopen("9-1.txt","r");
	Hash=(int* )malloc(m*sizeof(int));
	Htst=(int* )malloc(sizeof(int));
	for(i=0;i<m;i++)
		Hash[i]=-1;
	for(;;)
	{
		fscanf(fp,"%d",&num);
		if(num==-1) break;
		n++;
		Htst=(int* )realloc(Htst,n*sizeof(int));
		Htst[n-1]=num;
		i=num%p;
		for(;;)
		{
			di++;
			if((i+di*di)%p<m && i>0)
			{
				if(Hash[(i+di*di)%p]==-1 || Hash[(i-di*di)%p]==-1)
				{
					if(Hash[(i+di*di)%p]==-1) i=(i+di*di)%p;
					else i=(i-di*di)%p;
					break;
				}
			}
			else
			{
				printf("ERROR!");
				die=1;
				break;
			}
		}
		if(die==1) break;
		Hash[i]=num;
		di=-1;
	}
	checkE(Htst,Hash,n,p);
	fclose(fp);
	system("pause");
}
