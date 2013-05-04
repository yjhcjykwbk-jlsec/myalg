#include <iostream>
#include <stdio.h>
using namespace std;
#define MAXN 1000
#define rep(i,n) for(int i=0;i<n;i++)
void swap(int *a,int l,int r){
	int tmp=a[l];a[l]=a[r];a[r]=tmp;
}
struct Treap{
	int a[MAXN];
	int n;//size
Treap(int s[],int m){
	n=m;
	rep(i,m) a[i]=s[i];
	init();
}
int left(int i){return i*2+1;}
int right(int i){return i*2+2;}
void down(int i){
	if(i>=n) return;
	int l=left(i),r=right(i);
	int m=i;
	if(l<n&&a[l]>a[m]) m=l;
	if(r<n&&a[r]>a[m]) m=r;
	if(i!=m) {
		swap(a,i,m);
		down(m);
	}	
}
void up(int i){
	int p=(i-1)/2;
	while(i>0&&a[i]>a[p]){
		swap(a,i,p);
		i=p,p=(p-1)/2;
	}
}
void init(){
	rep(i,n){
		up(i);
	}
}
int pop(){
	if(n<=0) return -1;
	int t=a[0];
	a[0]=a[--n]; down(0);
	return t;
	}
};
int main(){
	int a[10]={1,3,2,4,5,7,6,9,8};
	Treap s(a,9);	
	rep(i,9) printf("%d ",s.pop());
	return 0;
}
