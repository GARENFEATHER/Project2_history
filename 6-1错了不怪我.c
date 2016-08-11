#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct t
{
	char data;
	struct t *lchild;
	struct t *rchild;
}Tree;
typedef struct z
{
	Tree *top,*bottom;
	int size;
}stack;
void push(stack *l,Tree *t,Tree q)
{
	if((l->top-l->bottom+1) > l->size)
	{
		l->size=l->size*2;
		t=(Tree* )realloc(t,l->size*sizeof(Tree));
	}
	l->top++;
	*l->top=q;
}
Tree* create()
{
	char a;
	Tree *T;
	scanf("%c",&a);
	if(a=='#') return NULL;
	else
	{
		T=(Tree* )malloc(sizeof(Tree));
		T->data=a;
		T->lchild=create();
		T->rchild=create();
	}
	return T;
}
void backvisit(Tree *T)//非递归后序
{
	int a[100],i;
	stack l;
	Tree *tmp,*p;
	for(i=0;i<100;i++)
		a[i]=0;
	l.size=100;
	tmp=(Tree* )malloc(100*sizeof(Tree));
	*tmp=*T;
	p=T;
	l.top=l.bottom=tmp;
	while((p->lchild!=NULL&&a[p->lchild->data-'A']!=1) || (p->rchild!=NULL&&a[p->rchild->data-'A']!=1) || l.top>l.bottom-1)
	{
		if(p->lchild!=NULL&&a[p->lchild->data-'A']!=1)
		{
			p=p->lchild;
			push(&l,tmp,*p);
		}
		else if(p->rchild!=NULL&&a[p->rchild->data-'A']!=1)
		{
			p=p->rchild;
			push(&l,tmp,*p);
		}
		else if(l.top>l.bottom-1)
		{
			printf("%c ",p->data);
			a[p->data-'A']=1;
			l.top--;
			p=l.top;
		}
		/*if(l.bottom>l.top)
		{
			free(tmp);
			break;//防止访问非法内存，回收空间
		}*/
	}
}
void rebackvist(Tree *T)//递归后序遍历
{
	if(T)
	{
		rebackvist(T->lchild);
		rebackvist(T->rchild);
		printf("%c ",T->data);
	}
}
int leaf(Tree *T)
{
	int count=0;
	if(T!=NULL)
	{
		if(T->lchild==NULL && T->rchild==NULL) count++;
		return count+leaf(T->lchild)+leaf(T->rchild);
	}
	else return 0;
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
void level(Tree *T)//深度
{
	stack L;
	Tree *tmp,*t;
	tmp=(Tree* )malloc(100*sizeof(Tree));
	*tmp=*T;
	L.top=L.bottom=tmp;
	L.size=100;
	t=T;
	while(L.top!=L.bottom-1)
	{
		if(t->lchild!=NULL)
		{
			L.size++;
			tmp=(Tree* )realloc(tmp,L.size*sizeof(Tree));
			L.top++;
			*(L.top)=*(t->lchild);
		}
		if(t->rchild!=NULL)
		{
			L.size++;
			tmp=(Tree* )realloc(tmp,L.size*sizeof(Tree));
			L.top++;
			*(L.top)=*(t->rchild);
		}
		printf("%c ",L.bottom->data);
		if(L.bottom<=L.top) L.bottom++;
		else break;//防止访问非法内存
		t=L.bottom;
	}
	printf("\n");
}
int main()
{
	int i=0,n,leaves,dep;
	Tree *T;
	T=(Tree* )malloc(sizeof(Tree));
	T=create();
	leaves=leaf(T);
	printf("\nleaves are %d",leaves);
	dep=depth(T);
	printf("\ndepth: %d\n",dep);
	level(T);
	rebackvist(T);
	printf("\n");
	backvisit(T);
	system("pause");
}