//寻找主元素
#include <iostream>
#include <stdlib.h>
using namespace std;
void swap(int *a,int l,int r){
	int tmp=a[l];a[l]=a[r],a[r]=tmp;
}

//功能：找到数组区间[l,r]中第n小的元素
//			返回该元素下标
//时间代价：O（n）
int find(int *a,int l,int r,int n){
	if(r<l) return -1;
	if(r==l) return l;
	int s=random()%(r-l+1)+l;//任取a[l,r]中的元素a[s]作为划分点,将区间划分为左右子区间
	int t=a[s];
	swap(a,s,l);
	int lp=l+1,rp=r;
	while(lp<=rp){
		while(lp<=r&&a[lp]<t) lp++;	
		while(rp>l&&a[rp]>=t) rp--;	
		if(lp<rp) swap(a,lp,rp);
	}	
	swap(a,l,rp);
	if(rp-l+1==n) return rp;//rp下标刚好对应第n小元素
	else if(rp-l+1>n) return find(a,l,rp-1,n);//在左区间中继续找
	else return find(a,rp+1,r,n-(rp-l+1));//在右区间中继续找
}

//功能：找到数组区间[l,r]中第n小的元素
//说明：消除递归
//时间代价：O（n）
int find_1(int *a,int l,int r,int n){
	while(true){
		if(r<l) return -1;//没找到
		if(r==l) 
				if(n==1)return l;//找到
				else return -1;
		int s=random()%(r-l+1)+l;//任取a[l,r]中的元素a[s]作为划分点,将区间划分为左右子区间
		int t=a[s];
		swap(a,s,l);
		int lp=l+1,rp=r;
		while(lp<=rp){
			while(lp<=r&&a[lp]<t) lp++;	
			while(rp>l&&a[rp]>=t) rp--;	
			if(lp<rp) swap(a,lp,rp);
		}	
		swap(a,l,rp);
		if(rp-l+1==n) return rp;//rp下标刚好对应第n小元素
		else if(rp-l+1>n) r=rp-1;//在左区间中继续找
		else n=n-(rp-l+1),l=rp+1;//在右区间中继续找
	}
}
int main(){
	int a[100];int n;
	cin>>n;for(int i=0;i<n;i++) cin>>a[i];
	int s=find_1(a,0,n-1,(n+1)/2);//找到中位数a[s]
	if(s!=-1){//判断是不是主元素
		int cnt=0;for(int i=0;i<n;i++) if(a[i]==a[s]) cnt++; 
		if(cnt>n/2) {cout<<"找到主元素"<<a[s]<<endl;return 0;}
		else cout<<"找到中位数"<<a[s]<<",不是主元素"<<endl;
	}
	cout<<"没有主元素"<<endl;
	return 0;
}
