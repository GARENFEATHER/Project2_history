#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
typedef struct t
{
	char data;
	struct t *lchild,*rchild;
}Tree;
typedef struct d
{
	Tree *top,*bottom,*base;
	int size;
}stack;
void select(char *s,char a,int *p)
{
	int n,i;
	n=strlen(s);
	for(i=0;i<n;i++)
		if(s[i]==a)
		{
			*p=i;
			break;
		}
}
char* mget(int start,int end,char *s)
{
	int i,k=0;
	char *tmp,*t;
	tmp=(char* )malloc((end-start)*sizeof(char));
	t=tmp;
	for(i=start;i<end;i++,tmp++)
		*tmp=s[i];
	return t;
}
Tree* Cre(char *sp,char *sm,int n)
{
	Tree *T;
	int p,i;
	char *sPl,*sMl,*sPr,*sMr;
	T=(Tree* )malloc(sizeof(Tree));
	T->data=sp[0];
	T->lchild=T->rchild=NULL;
	select(sm,sp[0],&p);
	if(n>1)
	{
		sPl=mget(1,p+1,sp);
		sPr=mget(p+1,n,sp);
		sMl=mget(0,p,sm);
		sMr=mget(p+1,n,sm);
		if(p!=0) T->lchild=Cre(sPl,sMl,p);
		else T->lchild=NULL;
		if(p!=n-1) T->rchild=Cre(sPr,sMr,n-p-1);
		else T->rchild=NULL;
	}
	return T;
}
void pOut(Tree *T)
{
	if(T)
	{
		printf("%c ",T->data);
		pOut(T->lchild);
		pOut(T->rchild);
	}
}
void mOut(Tree *T)
{
	if(T)
	{
		mOut(T->lchild);
		printf("%c ",T->data);
		mOut(T->rchild);
	}
}
int depth(Tree *T)
{
	int d=0;
	int left=0,right=0;
	if(T==NULL) d=0;
	else
	{
		left=depth(T->lchild);
		right=depth(T->rchild);
		d=1+(left>right?left:right);
	}
	return d;
}
void push(stack *l,Tree q)
{
	int rel;
	rel=l->top-l->base;
	if(l->size==l->top-l->bottom+1)
	{
		l->size*=2;
		l->base=(Tree* )realloc(l->base,l->size*sizeof(Tree));
	}
	l->top=l->base+rel+1;//如果堆上空间不足，realloc将数据整体全部移到另一块区域上，仍旧留在原地的top和level，bottom等会失去base的踪迹，因此使用相对确定的rel来确保定位不变
	*l->top=q;
}
Tree* levelget(Tree *T,int *level,int d)
{
	stack L;
	int p,i;
	L.base=(Tree* )malloc(100*sizeof(Tree));
	*L.base=*T;
	L.bottom=L.top=L.base;
	level[0]=0;
	level[1]=1;
	for(i=2;i<=d+1;i++)//那么现在问题来了……Ltop的踪迹可以通过push里的rel确保……bottom呢？= =
	{
		if(i==2)
		{
			if(L.bottom->lchild!=NULL) push(&L,*L.bottom->lchild);
			if(L.bottom->rchild!=NULL) push(&L,*L.bottom->rchild);
			p=level[i]=L.top-L.base+1;
			L.bottom++;
		}
		else if(L.base!=L.bottom-p)
		{
			while(L.base!=L.bottom-p)
			{
				if(L.bottom->lchild!=NULL) push(&L,*L.bottom->lchild);
				if(L.bottom->rchild!=NULL) push(&L,*L.bottom->rchild);
				L.bottom++;
			}
			p=level[i]=L.top-L.base+1;
		}
	}
	return L.base;
}
void fullcheck(Tree *T,int *level,int d)
{
	int i,check=0,plus=1;
	for(i=0;i<d-1;i++)
	{
		if(level[i+1]-level[i]!=plus)
		{
			check=1;
			break;
		}
		plus*=2;
	}
	if(check==0) printf("\nYES");
	else printf("\nNO");
}
void levelprint(Tree *T,int x,int *level,int d)
{
	int i;
	Tree *t;
	t=levelget(T,level,d);
	if(x<=d)
		for(i=level[x-1];i<level[x];i++)
			printf("%c ",t[i]);
	else printf("depth error!");
}
int main()
{
	FILE *fp;
	Tree *T;
	int x=4,d,*level;
	char b[100],m[100];
	fp=fopen("6-3-1.txt","r");
	fscanf(fp,"%s",b);
	fscanf(fp,"%s",m);
	T=Cre(b,m,strlen(m));
	d=depth(T);
	level=(int* )malloc(d*sizeof(int));
	levelget(T,level,d);
	printf("中序：\n");
	mOut(T);
	printf("\n先序：\n");
	pOut(T);
	printf("\n按层：\n");
	levelprint(T,x,level,d);
	printf("\n是不是满二叉树：");
	fullcheck(T,level,d);
	system("pause");
}