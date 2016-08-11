#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
typedef struct s
{
	int data;
	struct s *lchild,*rchild;
}Tree;
typedef struct a
{
	int size;
	Tree *top,*bottom;
}Stack;
Tree* search(Tree *T,int data,int *c)
{
	Tree *p,*f;
	p=(Tree* )malloc(sizeof(Tree));
	p->data=-1;
	f=T;
	if(T->data!=-1)
	{
		while(f!=NULL)
		{
			if(data == f->data)
			{
				if(p->data==-1) p->lchild=f;
				break;
			}
			else
			{
				p=f;
				if(data < f->data) f=f->lchild;
				else f=f->rchild;
			}
		}
		if(f == NULL) *c=0;
		else *c=1;
	}
	else *c=-1;
	return p;
}
void insert(Tree *T,int data)
{
	int c;
	Tree *tmp,*f;
	f=search(T,data,&c);//传进去的指针只是个形参？
	if(!c)//c==0
	{
		tmp=(Tree* )malloc(sizeof(Tree));
		tmp->data=data;
		tmp->lchild=NULL;
		tmp->rchild=NULL;
		if(data>f->data) f->rchild=tmp;
		else if(data<f->data) f->lchild=tmp;
	}
	else if(c==-1)
	{
		T->data=data;
		T->lchild=NULL;
		T->rchild=NULL;
	}
}
void createSTree(FILE *fp,Tree *T)
{
	int data;
	for(;;)
	{
		fscanf(fp,"%d",&data);
		if(data==-1) break;
		else insert(T,data);
	}
}
void del(Tree *T,int data)
{
	int c;
	Tree *f,*p,*t;
	char mark1,mark2;
	printf("\n");
	f=search(T,data,&c);
	if(c==1)
	{
		if(f->lchild->data == data)
		{
			p=f->lchild;
			if(p->lchild == NULL) f->lchild=p->rchild;
			else if(p->rchild == NULL) f->lchild=p->lchild;
			else
			{
				f->lchild=p->lchild;
				t=p->lchild;
				while(t->rchild!=NULL)
					t=t->rchild;
				t->rchild=p->rchild;
			}
		}
		else if(f->rchild->data == data)
		{
			p=f->rchild;
			if(p->lchild == NULL) f->rchild=p->rchild;
			else if(p->rchild == NULL) f->rchild=p->lchild;
			else
			{
				f->rchild=p->rchild;
				t=p->rchild;
				while(t->lchild!=NULL)
					t=t->lchild;
				t->lchild=p->lchild;
			}
		}
		free(p);
	}
	else printf("NOT DATA EXISIT!\n");
}
void destroy(Tree *T)
{
	if(T->lchild == NULL && T->rchild ==NULL) free(T);
	else if(T->lchild!=NULL &&T->rchild == NULL)
	{
		destroy(T->lchild);
		free(T);
	}
	else if(T->rchild!=NULL &&T->lchild == NULL)
	{
		destroy(T->rchild);
		free(T);
	}
	else if(T->lchild!=NULL && T->rchild!=NULL)
	{
		destroy(T->lchild);
		destroy(T->rchild);
		free(T);
	}
}
void show(Tree *T)
{
	if(T)
	{
		show(T->lchild);
		printf("%d ",T->data);
		show(T->rchild);
	}
}
int main()
{
	FILE *fp;
	Tree *T,*tst;
	fp=fopen("8-1-1.txt","r");
	T=(Tree* )malloc(sizeof(Tree));
	T->data=-1;
	createSTree(fp,T);
	tst=T->lchild;
	show(T);
	del(T,93);
	show(T);
	destroy(T);
	fclose(fp);
	system("pause");
}

