#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int mystrlen(char* s)
{
	int length,i;
	for(i=0;s[i]!='\0';i++);
	length=i;
	return length;
}
void mystrcpy(char* s1,char* s2)
{
	int i=0;
	if(s1 != NULL)
	{
		for(i=0;s2[i]!='\0';i++)
			s1[i]=s2[i];
	}
}
int main()
{
	int n=0;
	char *s="ssssssss",c[20];
	n=mystrlen(s);
	//printf("%d",n);
	//strcpy(c,s);
	mystrcpy(c,s);
	printf("%s",c);
	system("pause");
}