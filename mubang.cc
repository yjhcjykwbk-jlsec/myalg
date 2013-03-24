//乔治拿来一组等长的木棒，将它们随机地裁断，使得每一节木棍的长度都不超过50个长度单位。然后他又想把这些木棍恢复到为裁截前的状态，但忘记了初始时有多少木棒以及木棒的初始长度。请你设计一个程序，帮助乔治计算木棒的可能最小长度。每一节木棍的长度都用大于零的整数表示。
//
//输入
//第一行 n（<64）
//第二行 n个整数
//输出
//仅一个整数，输出原始木棒的可能最小长度
//样例输入
//9
//5 2 1 5 2 1 5 2 1
//样例输出
//6
#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
#define MAXLEN 50
#define MAXN  64

int Arr[MAXN+1];
int Len[MAXLEN+1];
int N;
int MLen,TLen;
void init(){
		cin>>N;
//	FILE* file=fopen("mubang.in1","r");
//	fscanf(file,"%d\n",&N);
	for(int i=1;i<=MAXLEN;i++) Len[i]=0;
	for(int i=0;i<N;i++){ 
//		fscanf(file,"%d",&Arr[i]);
				cin>>Arr[i];
		Len[Arr[i]]++;
	}
}
int max(int a,int b){return a>b?a:b;}
int min(int a,int b,int c){return a<b?(a<c?a:c):(b<c?b:c);}
//深搜
bool tryit(int k,int l,int remain,int len)
{
	if(k>=TLen/len-1) return true;
	if(remain==0) 
	{			
		int i; for(i=MLen;i>=1;i--) if(Len[i]>0) break;
		return (tryit(k+1,i,len-i,len)) ; //继续深度推进
	}
	for(int j=min(remain,MLen,l);j>=1;j--){
		if(Len[j]>0){
			if(remain>=j) {
				Len[j]--; if(tryit(k,j,remain-j,len)) return true; Len[j]++;
				if(remain==j) return false;//直接剪枝
			}
		}
	}
	return false;
}
bool test(int a){ Len[MLen]--;if(tryit(1,MLen,a-MLen,a)) return true;Len[MLen]++; return false;}
void calc(){
	TLen=0,MLen=0;
	for(int i=0;i<N;i++) TLen+=Arr[i],MLen=max(MLen,Arr[i]);
	for(int j=MLen;j<=TLen;j++){
		if(TLen%j!=0) continue;
		if(test(j)){ cout<<j<<endl;break;}
	}
}

int main(){
	init();
	calc();
	return 0;
}

