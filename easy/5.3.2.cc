//文件说明：白皮书5.3.2字典排序查找字符串操作基础
//本程序和范例程序相似度极高
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <set>
#include <cmath>
#include <algorithm>
using namespace std;
#define loop(i,n) for(int i=0;i<n;i++)
#define soop(i,n,m) for(int i=n-1;i>=m;i--)
char dict[100][7];
char sdict[100][7];
int N;
int my_strcmp(const void *a,const void *b){
	return strcmp((char*)a,(char*)b);
}
//void quicksort(char s[][7],int left,int right)
//{
//    int i=left,j=right,p=left;
//    char temp[7];
//    strcpy(temp,s[left]);
//    while(i<j)
//    {
//        while(strcmp(s[j],temp)>=0&&j>=p)j--;
//        if(j>=p)strcpy(s[p],s[j]),p=j;
//        while(strcmp(s[i],temp)<=0&&i<=p)i++;
//        if(i<=p)strcpy(s[p],s[i]),p=i;
//    }
//    strcpy(s[p],temp);
//    if(p-left>1)quicksort(s,left,p-1);
//    if(right-p>1)quicksort(s,p+1,right);
//}
void init(){
	int i;
	for(i=0;i<100;i++)
		if(scanf("%s",dict[i])<=0||dict[i][0]=='*') break;
	N=i;	
//	quicksort(dict,0,N-1);//字典先排序
	qsort(dict,N,sizeof(dict[0]),my_strcmp);//注意快排标准用法（在stdlib.h中）
	char a[7];
	loop(i,N){
		strcpy(sdict[i],dict[i]);
		sort(sdict[i],sdict[i]+strlen(sdict[i]));//另一个字典字符串内部排序
	}
}
void find(char *s){
	sort(s,strlen(s)+s);
	bool found=false;
	loop(i,N){
		if(strcmp(s,sdict[i])==0){//另一个字典中查找
			found=true;
			printf("%s ",dict[i]);
		}
	}
	if(!found) printf(":(");
	printf("\n");
}
int main(){
	init();
	char a[7];
	loop(i,100){
		if(scanf("%s",a)<=0) break;
		find(a);
	}
	return 1;
}
	
		
