#include <iostream>
#include <stdio.h>
using namespace std;
#define DEPTH 20
#define MAXN 2<<DEPTH
#define rep(i,n) for(int i=0;i<n;i++)
int Arr[MAXN];
int Tree[MAXN];
inline int lowBit(int n){
	if(n<=0) return 0;
	int t=1;
	while(1!=(n&1)){
		n>>=1;
		t<<=1;
	}
	return t;
}
int getN(int n){
	int t=n;int res=0;
	while(t>0){
		res+=Tree[t];
		t-=lowBit(t);
	}
return res;
}
void setN(int n){
	int t=n;
	int m=lowBit(n)/2;
	int res=0;
	if(m==0){
		if(t>0) res=Arr[t-1];
	}	
	else{
	 t-=lowBit(n);
	 while(m!=0){
		t+=m;
		res+=Tree[t];
		m/=2;
		}
		res+=Arr[t];
	}	
	Tree[n]=res;
}
void refresh(int n,int s){
	int t=n,l=1,r=lowBit(n)==0?1:lowBit(n)*2;
	while(l<lowBit(n)){
		Tree[n+l]+=(s-Arr[n]);//在n右边找到0位，换成1
		l*=2;
	}
	while(r<MAXN){
		if(!(n&r)){
			t=n&(~(r-1))|r;//在n左边找到0位，换成1，右边全都置为0
			Tree[t]+=(s-Arr[n]);
		}
		r*=2;
	}
	Arr[n]=s;
}
int main(){
	for(int i=0;i<9;i++)
		Arr[i]=i;
	for(int i=0;i<9;i++)
		setN(i);//初始化树状数组
	for(int i=1;i<9;i++)
		printf("smaller than %d:%d\n",i,getN(i));
	refresh(2,0);
	for(int i=1;i<9;i++)
		printf("smaller than %d:%d\n",i,getN(i));
	return 1;
}

