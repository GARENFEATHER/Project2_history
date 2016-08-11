#include<stdio.h>
#include<stdlib.h>
void getnext(char *t,int *next,int tn)
{
	int i=0,j=-1;
	next[0]=-1;
	while(i<tn)
	{
		if(j==-1||t[i]==t[j])
		{
			i++;
			j++;
			next[i]=j;
		}
		else j=next[j];
	}
}
int KMP(char *m,char *t,int mn,int tn,int posi)
{
	int *nxt,i,j=0;
	i=posi;
	nxt=(int* )malloc(tn*sizeof(int));
	getnext(t,nxt,tn);
	while(i<mn&&j<tn)
		if(j==-1||m[i]==t[j]) { i++; j++; }
		else j=nxt[j];
	if(j>=tn) return i-tn+1;
	else return -1;
}
int main()
{
	char *m,*t,tmp;
	int mn,tn,i,result,po=3;
	FILE *fp;
	fp=fopen("tst.txt","r");
	scanf("%d %d\n",&mn,&tn);
	m=(char* )malloc(mn*sizeof(char));
	t=(char* )malloc(tn*sizeof(char));
	fgets(m,100,fp);
	fgets(t,100,fp);
	result=KMP(m,t,mn,tn,po);
	printf("%d",result);
	system("pause");
}