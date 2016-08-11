#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
typedef struct c
{
	int value;
	int point;
	struct c *next;
}Arc;
typedef struct d
{
	int *top,*bottom,*base;
}stack;
typedef struct a
{
	int point,lowcost;
}primpoint;
typedef struct r
{
	int start,end,value;
	int size;
}Kruskal;
void* createGraph(FILE *fp,Arc *List,int n,Kruskal *Kru)
{
	int a=9999999,b,c,i,j,k=0;
	Arc *p,*tmp;
	for(i=0;i<n;i++)
	{
		List[i].value=-1;
		List[i].next=NULL;
		List[i].point=i;
	}
	for(;;)
	{
		fscanf(fp,"%d%d%d",&a,&b,&c);
		if(a==-1)
		{
			Kru[k].start=Kru[k].end=Kru[k].value=-1;
			break;
		}
		Kru[k].start=a-1;//方便后面kruskal算法遍历所以顺手先存着………………
		Kru[k].end=b-1;
		Kru[k].value=c;
		k++;
		for(i=0;i<2;i++)//用于双向构建邻接表，两次
		{
			tmp=(Arc* )malloc(sizeof(Arc));
			tmp->next=NULL;
			if(i == 0)
			{
				p=List+a-1;
				tmp->point=b-1;
			}
			else if(i == 1)
			{
				p=List+b-1;
				tmp->point=a-1;
			}
			tmp->value=c;
			while(p->next!=NULL)
					p=p->next;
				p->next=tmp;
		}
	}
	Kru->size=k;
}
int mininum(primpoint *c,int n,int *visit)
{
	int i,k=-1,pValue=65536;
	for(i=0;i<n;i++)
		if(c[i].lowcost<pValue && c[i].lowcost!=0 && visit[i]!=1)
		{
			k=i;
			pValue=c[i].lowcost;
		}
	return k;
}
void prim(Arc *L,int *visit,int n,Arc *t)
{
	int i,k,j=0,sum=0;//TE是已在树上的点的集合
	Arc *p;
	Kruskal *TE;
	primpoint *closedge;
	printf("\n\n最小生成树（prim）：");
	for(i=0;i<n;i++)
		visit[i]=0;
	closedge=(primpoint* )malloc(n*sizeof(primpoint));
	TE=(Kruskal* )malloc(n*sizeof(Kruskal));
	for(i=0;i<=n;i++)
	{
		TE[i].start=-1;
		TE[i].end=-1;
		TE[i].value=0;
	}
	for(i=0;i<n;i++)
		closedge[i].lowcost=65536;
	TE[0].start=TE[0].end=t->point;
	i=t->point;
	visit[i]=1;
	while(TE[n-2].end==-1)
	{
		for(p=(L+TE[i].end)->next;i>=0;i--)
		{
			while(p!=NULL)
			{
				if(p->value < closedge[p->point].lowcost && visit[p->point]!=1)
				{
					closedge[p->point].lowcost=p->value;
					closedge[p->point].point=TE[i].end;
				}
				p=p->next;
			}
		}
		k=mininum(closedge,n,visit);
		TE[j].start=closedge[k].point;
		TE[j].end=k;
		TE[j].value=closedge[k].lowcost;
		i=j;
		j++;
		visit[k]=1;
	}
	printf("\n分段路程:");
	for(i=0;i<n-1;i++)
	{
		printf("\n%d->%d:%d",TE[i].start,TE[i].end,TE[i].value);
		sum+=TE[i].value;
	}
	printf("\n总路程：%d",sum);
	
}
int circuit(Arc *C,int n)//回路算法按照压缩包内图示意
{
	int *arc,i,tmp,oh=0,max=INT_MIN,*delpoint,k;
	Arc *p,*Ctmp;
	arc=(int* )malloc(n*sizeof(int));
	delpoint=(int* )malloc(n*sizeof(int));
	for(i=0;i<n;i++)
	{
		arc[i]=0;
		p=&C[i];
		while(p->next!=NULL)
		{
			p=p->next;
			arc[i]+=1;
		}
	}
	for(;;)
	{
		for(i=0,k=0;i<n;i++)
		{
			if(arc[i]>max) max=arc[i];
			if(arc[i]==1)
			{
				delpoint[k]=i;
				k++;
			}
		}
		if(max==0) break;
		if(k==0)
		{
			oh=1;
			break;
		}
		for(i=k-1;i>=0;i--)
		{
			if(arc[delpoint[i]]==0) continue;
			p=C[delpoint[i]].next;
			while(arc[p->point]==0)
				p=p->next;
			tmp=p->point;
			arc[tmp]=arc[tmp]-1;
			arc[delpoint[i]]=0;
		}
		max=INT_MIN;
	}
	return oh;
}
void sort(Kruskal *Kru)
{
	int i,j;
	Kruskal tmp;
	for(i=0;i<Kru->size;i++)
		for(j=0;j<Kru->size-i-1;j++)
			if(Kru[j+1].value<Kru[j].value)
			{
				tmp=Kru[j];
				Kru[j]=Kru[j+1];
				Kru[j+1]=tmp;
			}
}
void kruskal(Arc *L,Kruskal *Kru,int n)//由于懒得从新遍历邻接表得到路径数据于是在创建邻接表的时候留了个后门Kru=_=
{
	Arc *C,*p1,*p2,*tmp1,*tmp2,*p;
	int i,k=0,check;
	C=(Arc* )malloc(n*sizeof(Arc));
	for(i=0;i<n;i++)
	{
		C[i].point=i;
		C[i].value=0;
		C[i].next=NULL;
	}
	sort(Kru);
	for(i=0;i<Kru->size;i++)
	{
		p1=C+Kru[i].start;
		p2=C+Kru[i].end;
		while(p1->next!=NULL) p1=p1->next;
		tmp1=(Arc* )malloc(sizeof(Arc));
		tmp1->next=NULL;
		tmp1->point=Kru[i].end;
		tmp1->value=Kru[i].value;
		p1->next=tmp1;
		//双向创建邻接表
		while(p2->next!=NULL) p2=p2->next;
		tmp2=(Arc* )malloc(sizeof(Arc));
		tmp2->next=NULL;
		tmp2->point=Kru[i].start;
		tmp2->value=Kru[i].value;
		p2->next=tmp2;
		check=circuit(C,n);
		if(check==1)//发现回路存在
		{
			p1->next=NULL;
			p2->next=NULL;
			free(tmp1);
			free(tmp2);
		}
	}
	printf("\n\n最小生成树(Kruskal):");
	for(i=0;i<n;i++)//遍历输出
	{
		p=C[i].next;
		while(p!=NULL)
		{
			if(p->point>i) printf("\n%d->%d:%d",i,p->point,p->value);
			p=p->next;
		}
	}
}
void Dijkstra(Arc *L,int n)
{
	Arc *p;
	int *D,*Pre,u;
	int min,i,j,*now,*final;
	printf("\n\nDijkstra算法结果:");
	D=(int* )malloc(n*sizeof(int));
	final=(int* )malloc(n*sizeof(int));
	Pre=(int* )malloc(n*sizeof(int));
	for(i=0;i<n;i++)
	{
		if(i==0)
		{
			D[i]=0;
			Pre[i]=0;
			final[i]=1;
		}
		else
		{
			D[i]=INT_MAX;
			final[i]=0;
		}
	}
	p=L[0].next;
	for(;p!=NULL;p=p->next) D[p->point]=p->value;
	for(i=1;i<n;i++)
	{
		for(j=1,min=INT_MAX;j<n;j++)
		{
			if(!final[j] && D[j]<min)
			{
				u=j;
				min=D[j];
			}
		}
		p=L[u].next;
		final[u]=1;
		while(p!=NULL)
		{
			if(!final[p->point] && p->value+min < D[p->point])
			{
				Pre[p->point]=u;
				D[p->point]=p->value+min;
			}
			p=p->next;
		}
	}
	for(i=1;i<n;i++)
		printf("\nto %d:%d",i,D[i]);
}
void DFS(Arc *p,int *visit,Arc *L,int start)
{
	int a;
	Arc *q;
	a=p->point;
	visit[a]=1;
	if(p-L==start) printf("%d",a);//第一个访问节点无前缀"->"
	else printf("->%d",a);
	q=&L[p->point];
	while(q!=NULL)
	{
		if(visit[q->point]!=1) DFS(q,visit,L,start);
		q=q->next;
	}
}
void width(Arc *p,int *visit,Arc *L,int n)
{
	int a,*w;
	Arc *q;
	stack S;
	for(a=0;a<n;a++)
		visit[a]=0;
	a=p->point;
	S.base=(int* )malloc(n*sizeof(int));
	*S.base=a;
	S.bottom=S.base;
	S.top=S.bottom-1;
	q=&L[a];
	do{
		while(q!=NULL)
		{
			if(visit[q->point]!=1)
			{
				S.top++;
				*S.top=q->point;
				visit[q->point]=1;
			}
			q=q->next;
		}
		S.bottom++;
		q=&L[*S.bottom];

	}while(S.top!=S.bottom-1);
	for(w=S.base;w<S.base+n;w++)
		if(w==S.base+n-1) printf("%d",*w);
		else printf("%d->",*w);
}
void Traverse(Arc *l,int n,Kruskal *Kru)
{
	int i,*visit,start;
	visit=(int* )malloc(n*sizeof(int));
	for(i=0;i<n;i++)
		visit[i]=0;
	start=1;//第start个节点起访问，可更改
/*	printf("\n第%d个起点起的深度优先搜索:\n",start);
	DFS(l+start,visit,l,start);
	printf("\n\n第%d个起点起的广度优先搜索:\n",start);
	width(l+start,visit,l,n);
	Dijkstra(l,n);*/
	//kruskal(l,Kru,n);
	prim(l,visit,n,l);//道理我都懂，结果都没错，但为什么这个算法还是死机了。
}
int main()
{
	FILE *fp;
	Kruskal *Kru;
	Arc *List;
	int n;
	fp=fopen("7-1.txt","r");
	fscanf(fp,"%d",&n);
	List=(Arc* )malloc(n*sizeof(Arc));
	Kru=(Kruskal* )malloc(n*(n-1)*sizeof(Kruskal));
	Kru->size=0;
	createGraph(fp,List,n,Kru);
	Traverse(List,n,Kru);
	system("pause");
}
