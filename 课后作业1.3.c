#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
	int i=0,j=0,k=0;
	char s1[100],s2[100],temp[100];
	printf("请输入两个英文单词:\n");
	scanf("%s",s1);
	scanf("%s",s2);
	printf("最长的公共后缀:\n");
	for(i=0;s1[i]!='\0';i++);
	for(j=0;s2[j]!='\0';j++);
	if(i!=0 || j!=0)
		while(s1[i] == s2[j])
		{
			temp[k++]=s1[i];
			i--;
			j--;
		}
	if(k == 1) printf("空串");
	else
	while(k!=1)
	{
		k--;
		printf("%c",temp[k]);
	}
	printf("\n");
	system("pause");
}