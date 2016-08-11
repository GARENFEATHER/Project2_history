#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct u
{
	char name;
	int fre;
	char *Hfc;
}data;
typedef struct t
{
	int weight,parent,lchild,rchild;
}Hfnode;
void Select(Hfnode *h,int m,int *s1,int *s2)
{
	int i;
	*s1=0;
	*s2=0;
	for(i=0;i<m+1;i++)
		if(h[i].weight!=0 && (h[i].parent==-1 || h[i].parent==0))
		{
			if(h[i].weight<h[*s2].weight)
				if(h[i].weight<h[*s1].weight) *s1=i;
				else *s2=i;
		}
}
void Code(data *w,Hfnode *h,int n,int m)
{
	int i=0,s1,s2;
	s1=s2=0;
	for(i=0;i<n;i++)
	{
		h[i].weight=w[i].fre;
		h[i].lchild=h[i].rchild=h[i].parent=0;
	}
	for(;i<m+1;i++)
	{
		h[i].lchild=h[i].rchild=h[i].weight=0;
		h[i].parent=-1;
	}
	for(i=n;i<m+1;i++)
	{
		Select(h,m,&s1,&s2);
		h[i].lchild=s1;
		h[i].rchild=s2;
		h[i].weight=h[s2].weight+h[s1].weight;
		h[s1].parent=i; h[s2].parent=i;
	}
}
void getCode(data *w,Hfnode *h,int n)
{
	int i=0,j,t,k=0;
	char *tmp;
	Hfnode *p;
	tmp=(char* )malloc(100*sizeof(char));
	for(i=0;i<n;i++)
	{
		for(p=&h[i],j=0;p->parent!=-1;)
		{
			t=p->parent;
			if(h[t].lchild==p-h) tmp[j++]='0';
			else tmp[j++]='1';
			p=&h[t];
		}
		w[i].Hfc=(char* )malloc((j+1)*sizeof(char));
		w[i].Hfc[j]='\0';
		for(k=0;k<j;k++)
			w[i].Hfc[k]=tmp[k];
	}
	for(i=0;i<n;i++)
	{
		printf("%c:",w[i].name);
		puts(w[i].Hfc);
	}
}
int main()
{
	FILE *fp;
	int i=0,n,m;
	data *w;
	Hfnode *Hfcoding;
	fp=fopen("6-2-2.txt","r");
	fscanf(fp,"%d",&n);
	m=2*n-1;
	Hfcoding=(Hfnode* )malloc((m+1)*sizeof(Hfnode));
	w=(data* )malloc(n*sizeof(data));
	for(i=0;i<n;i++)
		fscanf(fp,"%c",&w[i].name);
	for(i=0;i<n;i++)
		fscanf(fp,"%d",&w[i].fre);
	Code(w,Hfcoding,n,m);
	getCode(w,Hfcoding,n);
	fclose(fp);
	system("pause");
}