#include<stdio.h>
#include<stdlib.h>
int m,n;
typedef struct
{
	int x,y,di;
}posi;
typedef struct
{
	posi *top,*base;
	int size;
}Sqstack;
void push(Sqstack *l,posi t)
{
	if(l->top-l->base>=l->size)
	{
		l->size+=1;
		l->base=(posi* )realloc(l->base,(l->size+1)*sizeof(posi));
		}
	*l->top=t;
	l->top++;
}
void changedi(int *x,int *y,int di)
{
	if(di==1) (*y)++;
	else if(di==2) (*x)++;
	else if(di==3) (*y)--;
	else if(di==4) (*x)--;
}
int pass(int p,Sqstack *q,int i,int j)
{
	int a=0;
	posi *qt=q->top-2;
	if(i>m-1||i<0||j<0||j>n-1) return 0;
	else
	{
		while(qt>=q->base)
		{
			if(qt->x==i&&qt->y==j)
			{
				a=1;
				break;
			}
			qt--;
		}
		if(p==1&&a==0) return 1;
		else return 0;
	}
}
void pop(Sqstack *l,posi *e,int *i,int*j)
{
	l->top--;
	l->size--;
	switch(e->di)
	{
		case 1:changedi(i,j,3);break;
		case 2:changedi(i,j,4);break;
		case 3:changedi(i,j,1);break;
		case 4:changedi(i,j,1);
	}
}
void mark(Sqstack *l,int *a)
{
	*a=0;
	l->top--;
}
void out(Sqstack l)
{
	posi *p;
	p=l.base;
	while(p!=l.top)
	{
		printf("%d,%d,%d\n",p->x,p->y,p->di);
		p++;
	}
}
int main()
{
	int i,x,y,fx,fy,j,**p;
	posi e,*tmp;
	Sqstack L;
	scanf("%d %d",&m,&n);
	p=(int** )malloc(sizeof(int* )*m);
	for(i=0;i<m;i++)
	{
		p[i]=(int* )malloc(n*sizeof(int));
		for(j=0;j<n;j++)
			scanf("%d",&p[i][j]);
	}
	scanf("%d %d",&x,&y);
	scanf("%d %d",&fx,&fy);
	tmp=(posi* )malloc(2*sizeof(posi));
	tmp->x=i=e.x=x;
	tmp->y=j=e.y=y;
	tmp->di=e.di=1;
	L.size=1;
	L.base=tmp;
	L.top=L.base+1;
	changedi(&i,&j,e.di);
	do{
		if(pass(p[i][j],&L,i,j)==1)
		{
			e.x=i; e.y=j; e.di=1;
			push(&L,e);
			if(e.x==fx&&e.y==fy) break;
			changedi(&i,&j,1);
		}
		else{
			if(L.top-L.base>=0){
				pop(&L,&e,&i,&j);
				while(e.di==4&&L.top!=L.base){
					mark(&L,&p[i][j]); 
					pop(&L,&e,&i,&j);
					e.di=(L.top-1)->di;
				}
				if(e.di<4){
					e.di++;
					if(pass(p[e.x][e.y],&L,e.x,e.y)) push(&L,e);
					changedi(&i,&j,e.di);
				}
			}
		}
	}while(L.top-L.base>=0);
	out(L);
	system("pause");
}




