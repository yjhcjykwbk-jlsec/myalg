#include <iostream>
#include <string.h> 
#include <list>
#include <queue>
using namespace std;
#define FAR 9999999
#define MAXN 1000
int D[MAXN];
int Pre[MAXN];
int s,t,n,num_l,num_r;
int num;
list<int> Edges[MAXN];
list<int> Flows[MAXN];
#define rep(i,n) for(int i=0;i<n;i++)
void init(){
	cin>>num_r>>num_l;//左右子图节点个数
	n=num_l+num_r+2;
	s=0,t=n-1;
	rep(i,n) Edges[i].clear();
	rep(i,num_l)Edges[s].push_back(i+1);
	rep(i,num_r) Edges[i+1+num_l].push_back(t);
	rep(i,num_r){
		int a;cin>>a;
		rep(j,a){
			int b;cin>>b;
			Edges[b].push_back(i+num_l+1);
		}
	}
	rep(i,n){
		Flows[i].clear();
		for( list<int>::iterator it=Edges[i].begin();it!=Edges[i].end();it++){
			int j=*it;
			Flows[i].push_back(j);
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
		for(list<int>::iterator _i=Flows[v].begin();_i!=Flows[v].end();_i++){
			int i=*_i;
			if(D[i]==FAR){
				D[i]=D[v]+1,Pre[i]=v,vqueue.push(i);
				if(i==t) return true;
			}
		}
	}
	return false;
}

int calc(){
	int num=0;
	bool vis[MAXN];
	memset(vis,false,sizeof(vis));
	for(int i=1;i<num_l+1;i++){
		for( list<int>::iterator it=Edges[i].begin();it!=Edges[i].end();it++){
			int j=*it;
			if(!vis[t]) {
				vis[t]=true;
				Flows[s].remove(i),Flows[i].push_back(s);
				Flows[j].remove(t),Flows[t].push_back(j);
				Flows[i].remove(j);Flows[j].push_back(i);
				num++;
				break;
			}
		}
	}
	if(num==num_r) return num;
	while(find()){
		int p,q=t;
		++num;
		while((p=Pre[q])!=-1)
	{
		Flows[p].remove(q);
		Flows[q].push_back(p);
		q=p;
	}	
	}
	return num;
}

int main(){
	int cases;cin>>cases;
	rep(i,cases){
	init();
	if(num_r>num_l) cout<<"NO"<<endl;
	else if(calc()==num_r) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	}
//	rep(i,num_l){
//		rep(j,num_r){
//			if(Flow[j+1+num_l][i+1]>0)
//				cout<<i+1<<"-"<<j+1+num_l<<endl;
//		}
//	}
return 0;
}

	
