#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(){
	char str1[] = "asrrtyknytdbtdiysfscd";
	char str2[] = "amvfnddjhastyknytrdhesrqaqmkurtykitfzutdspasrrnytdbtdiytyknyccbdassrsfscdrtsdicfgjyknystdbtdiysdccc";
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	int c[100][100];
	for(int i = 0; i < len1; i++)
		c[i][0] = 0;
	for(int i = 0; i < len2; i++)
		c[0][i] = 0;
	for(int i = 1; i <= len1; i++){
		for(int j = 1; j <= len2; j++){
			if(str1[i - 1] == str2[j - 1])
				c[i][j] = c[i - 1][j - 1] + 1;
			else if(c[i][j - 1] > c[i - 1][j]){
				c[i][j] = c[i][j - 1];
			}
			else{
				c[i][j] = c[i - 1][j];
			}
		}
	}
	printf("%d\n", c[len1][len2]);
	int k = len1; 
	int h = len2;
	char lcs[100];
	int count = 0;
	while(k > 0 && h  > 0){
		if(str1[k - 1] == str2[h - 1]){
			lcs[count++] = str1[k - 1];
			k--;
			h--;
		}
		else if(c[k][h - 1] > c[k - 1][h]){
			h--;
		}
		else{
			k--;
		}
	}
	for(int i = count - 1; i >= 0; i--){
		printf("%c", lcs[i]);
	}
	printf("\n");
	system("pause");
}
