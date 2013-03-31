#include <iostream>
#include <queue>
using namespace std;
#define FAR 9999999
#define MAXN 1000
int D[MAXN];
int Pre[MAXN];
int s,t,n,num_l,num_r;
int Flow[MAXN][MAXN];
int Edge[MAXN][MAXN];
#define rep(i,n) for(int i=0;i<n;i++)
void init(){
	cin>>num_l>>num_r;//左右子图节点个数
	n=num_l+num_r+2;
	s=0,t=n-1;
	rep(i,n) rep(j,n) Edge[i][j]=FAR;
	int m;cin>>m;
	rep(i,m){
		int a,b;
		cin>>a>>b;
		Edge[a][b]=1;
	}
	rep(i,num_l) Edge[s][i+1]=1;
	rep(i,num_r) Edge[i+1+num_l][t]=1;
	rep(i,n){
		rep(j,n){
			if(Edge[i][j]<FAR) Flow[i][j]=1;
			else Flow[i][j]=0;
		}
	}
}
bool find(){
	queue<int> vqueue;
	rep(i,n) D[i]=FAR;
	vqueue.push(s);
	D[s]=0;Pre[s]=-1;
	while(!vqueue.empty()){
		int v=vqueue.front();vqueue.pop();
		rep(i,n){
			if(Flow[v][i]>0&&D[i]==FAR){
				D[i]=D[v]+1,Pre[i]=v,vqueue.push(i);
				if(i==t) return true;
			}
		}
	}
	return false;
}

void calc(){
	int num=0;
	while(find()){
		int p,q=t;
		++num;
		while((p=Pre[q])!=-1)
	{
		Flow[p][q]--;Flow[q][p]++;
		q=p;
	}	
	}
}

int main(){
	init();
	calc();
	rep(i,num_l){
		rep(j,num_r){
			if(Flow[j+1+num_l][i+1]>0)
				cout<<i+1<<"-"<<j+1+num_l<<endl;
		}
	}
return 0;
}

	
