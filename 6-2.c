#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct t
{
	char data;
	struct t *lchild,*rchild;
}Tree;
typedef struct s
{
	Tree **top,**buttom;
	int size;
}stack;
Tree* inputcheck(FILE *fp)
{
	int i=0;
	char a[3];
	Tree *p,*tmp,**tq,*t;
	stack L;
	tq=(Tree** )malloc(100*sizeof(Tree));
	L.top=L.buttom=tq;
	L.size=100;
	while(1)
	{
		for(i=0;i<3;i++)
			fscanf(fp,"%c",&a[i]);
		if(a[0]=='^'&&a[1]=='^') break;
		tmp=(Tree* )malloc(sizeof(Tree));
		tmp->data=a[1];
		tmp->lchild=NULL;
		tmp->rchild=NULL;
		if(a[0]=='^')
		{
			*L.top=*L.buttom=tmp;
			t=tmp;
		}
		else 
		{
			if(L.top-L.buttom>L.size)
			{
				L.size++;
				tq=(Tree** )realloc(tq,L.size*sizeof(Tree));
			}
			L.top++;
			*L.top=tmp;
			p=*L.buttom;
			if(a[0]!=p->data)
				while(a[0]!=p->data)
				{
					L.buttom++;
					p=*L.buttom;
				}
			if(a[2]=='L') p->lchild=tmp;
			else if(a[2]=='R') p->rchild=tmp;
		}
	}
	return t;
}
void mOut(Tree *t)
{
	if(t)
	{
		mOut(t->lchild);
		printf("%c",t->data);
		mOut(t->rchild);
	}
}
int depth(Tree *T)
{
	int d=0;
	int left=0,right=0;
	if(!T) d=0;
	else
	{
		left=depth(T->lchild);
		right=depth(T->rchild);
		d=1+(left>right?left:right);
	}
	return d;
}
int main()
{
	FILE *fp;
	Tree *t;
	fp=fopen("6-2.txt","r");
	t=(Tree* )malloc(sizeof(Tree));
	t=inputcheck(fp);
	mOut(t);
	printf("\n%d\n",depth(t));
	fclose(fp);
	system("pause");
}