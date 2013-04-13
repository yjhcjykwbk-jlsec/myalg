//计算逆序对的算法
#include <iostream>
using namespace std;
#define MAXN 1000
int b[MAXN],a[MAXN];
int N;//a元素个数
#define rep(i,m,n) for(int i=m;i<=n;i++)

//功能：归并两个区间（l1~r1 l2~r2)
//			并且计算逆序数
int merge(int *a,int l1,int r1,int r2){
	int l2=l1+1;	
	int p1=l1,p2=l2,p3=l1;
	int num=0;
	while(p1<=r1&&p2<=r2){
		if(a[p1]<a[p2]) //放左边,逆序增加
			b[p3++]=a[p1++],num+=(p2-l2);
		else 
			b[p3++]=a[p2++];//放右边
	}
	if(p1<=r1) //p2=r2+1
		while(p1<=r1){ b[p3++]=a[p1++],num+=(p2-l2); }
	else while(p2<=r2)  b[p3++]=a[p2++];

	rep(i,l1,r2) a[i]=b[i];

	return num;
}

//功能：先对左右区间排序,再调用merge归并左右区间
int div(int *a,int l,int r){
	if(l>=r) return 0;
	int mid=(l+r)/2;
	int n1=div(a,l,mid);
	int n2=div(a,mid+1,r);
	int n3=merge(a,l,mid,r);
	return n1+n2+n3;
}

int main(){
	cin>>N;
	rep(i,0,N-1) cin>>a[i];
	cout<<"逆序数:"<<div(a,0,N-1)<<endl;
	return 0;
}
