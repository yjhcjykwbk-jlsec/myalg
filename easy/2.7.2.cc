#include <iostream>
#include <assert.h>
using namespace std;
#define MAXN 1000
#define rep(i,n) for(int i=0;i<n;i++)
typedef int Node;
struct Bcha{//并查集
	Node Arr[MAXN];//n个节点值
	int Tree[MAXN];//子树
	int	Size[MAXN];//记录每个子树的size
	int N;//子树个数
	Bcha(int n){
		N=n;
		rep(i,N) 
			Tree[i]=i,Size[i]=1;//初始化，有N棵子树,每个子树只有节点i
	}
	//合并子树m.n
	void merge(int n,int m){
		assert (!(n==m||n<0||n>=N||m<0||m>=N)) ;
		if(getF(n)==getF(m)) return;
		Size[getF(m)]+=Size[getF(n)];
		Size[getF(n)]=0;
		Tree[getF(n)]=m;
	}
	int getF(int n){
		assert(!(n<0||n>=N));
		if(Tree[n]==n) return n;
		else return Tree[n]=getF(Tree[n]);//先计算
	}
};

int main(){
	int n;cin>>n;
	Bcha a(n);
	for(int i=0;i<n;i++) cin>>a.Arr[i];
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
			if(a.Arr[i]==a.Arr[j]) {a.merge(i,j);break;}
	for(int i=0;i<n;i++) {
		if(a.Size[i]>n/2) {cout<<"找到主元素"<<a.Arr[i]<<endl;return 0;}
	}
	cout<<"找不到"<<endl;return 0;
}

