#include<stdio.h>
#include <string.h>
#include <stdlib.h>
char* my_find(char  input[],   char rule[])
{
	//write your code here
#define MAXM 1000
#define MAXN 1000
	bool match[MAXM][MAXN];
	int size=strlen(input); char *_input=input;
	for(int start=0;start<size;start++){
		input=_input+start;
		int M=strlen(rule),N=strlen(input);

		//init 
		if(rule[0]==input[0]||rule[0]=='?'||rule[0]=='*')
			match[0][0]=true;
		else continue;
		for(int j=1;j<N;j++)	match[0][j]=(rule[0]=='*')?true:false;
		for(int i=1;i<M;i++) 
		{
			if(rule[i]=='*') match[i][0]=true;
			else {
				if(rule[i]==input[0]||rule[i]=='?') match[i][0]=true;
				else match[i][0]=false;
				for(i=i+1;i<M;i++) match[i][0]=false;
			}
		}
		//find...
		int hasmatch=-1;
		for(int i=1;i<M;i++){//rule
			hasmatch=-1;	
			for(int j=1;j<N;j++){//input
				if(match[i-1][j-1]&&(rule[i]==input[j]||rule[i]=='?'||rule[i]=='*')
						||match[i][j-1]&&rule[i]=='*'
						||match[i-1][j]&&rule[i]=='*')
					match[i][j]=true,hasmatch=j;
				else match[i][j]=false;
			}
			if(hasmatch<0){ break;}
		}
		if(hasmatch>0){ 
			char*res=(char*)malloc(hasmatch+2);
			strncpy(res,input,hasmatch+1);
			return res; }
	}
	return NULL;
}



//start 提示：自动阅卷起始唯一标识，请勿删除或增加。
int main()
{    
	//write your code here
	char input[100]="abaaaaaaababa";char rule[100]="a*ab*b";
	char *s=my_find(input,rule);
	if(s) printf("%s\n",s);
	return 0;
}
//end //提示：自动阅卷结束唯一标识，请勿删除或增加。
