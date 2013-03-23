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
	for(int i=1;i<=MAXLEN;i++) Len[i]=0;
	for(int i=0;i<N;i++){ 
		cin>>Arr[i];
		Len[Arr[i]]++;
	}
}
int max(int a,int b){return a>b?a:b;}
int min(int a,int b,int c){return a<b?(a<c?a:c):(b<c?b:c);}
//深搜
bool tryit(int k,int l,int remain,int len)
{
	if(remain==0) 
			{
				int i; for(i=MLen;i>=1;i--) if(Len[i]>0) break;
				if(tryit(k+1,i,len-i,len)) return true; 
			}
	for(int j=min(remain,MLen,l);j>=1;j--){
		if(Len[j]>0){
			if(remain==j) {
				if(k>=TLen/len-1) return true;
				Len[j]--;
				if(tryit(k,j,remain-j,len)) return true;
				Len[j]++;return false;
			}if(remain>j) 
			{	Len[j]--;if(tryit(k,j,remain-j,len)) return true;Len[j]++;}
		}
	}
	return false;
}
bool test(int a){ return tryit(1,MLen,a,a); }
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
