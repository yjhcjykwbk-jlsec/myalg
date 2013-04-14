#include <iostream>
#include <string.h>
#include <queue>
//erfentu pipei
//hopcroft-karp
using namespace std;
#define MAXN 1000
#define rep(i,m,n) for(int i=m;i<=n;i++)
#define FAR 0xfffffff
int LNum,RNum;//num of vertexes of left and right graph
int du[MAXN][MAXN];
int D[MAXN];
//vector<int> Graph[MAXN];//edges from left to right
//int RMatch[MAXN];//vertexes that match left
//int LMatch[MAXN];
int S=0,T;
void init(){
	cin>>LNum>>RNum;T=LNum+RNum+1;
	memset(du,0,sizeof(du));
	rep(i,1,LNum) du[S][i]=1;
	rep(i,LNum+1,LNum+RNum) du[i][T]=1;
	int n;cin>>n;
	rep(i,1,n){
		int a,b;cin>>a>>b;du[a][LNum+b]=1;
		cout<<a<<":"<<b<<endl;
	}
}
bool wfs(){
	queue<int> vqueue;
	vqueue.push(S);
	rep(i,0,T) D[i]=FAR;
	while(!vqueue.empty()){
		int v=vqueue.front();vqueue.pop();
		rep(i,1,T-1) {
			if(du[v][i]>0&&D[i]==FAR) {
				D[i]=D[v]+1,vqueue.push(i);
			}
		}
		if(du[v][T]>0){D[T]=D[v]+1;return true;}
	}
	return false;
}
int dfs(int v,int f){
	if(f<=0) return 0;
	if(v==T) return 1;//////////////
	int num=0;
	rep(i,0,T){
		if(du[v][i]>0&&D[i]==D[v]+1) {
			int d=dfs(i,1);
			if(d>0){
				f-=1;num++;du[v][i]=0;du[i][v]=1;
			}
			if(f==0) break;
		}
	}
	return num;
}
int main(){
	init();
	int num=0;
	while(wfs()){
		num+=dfs(S,MAXN);
	}
	cout<<"pipei:"<<num<<endl;
	rep(i,1,LNum){
		rep(j,LNum+1,LNum+RNum){
			if(du[j][i]>0) cout<<i<<"->"<<j-LNum<<endl;
		}
	}
	return 0;
}

