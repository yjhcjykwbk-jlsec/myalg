//time limit excceed
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
#define MAXN 100
int V[MAXN];
bool Edge[MAXN][MAXN];
vector<int> E[MAXN];
int path[MAXN];
bool vis[MAXN];
int N,M;
int S,cnt;
void search(int n,int f,int s){
//	cout<<n<<":"<<f<<":"<<s<<endl;
	if(f==N) {//已经装入f个顶点
		if(s>S) {S=s;cnt=1;}
		else if(s==S){ cnt++;}
		return;
	}
	for(int i=0;i<E[n].size();i++){
		int t=E[n][i];
		if(!vis[t]){
			path[f]=t;
			vis[t]=true;
			int sec=0,thr=0;
			if(f>=1) sec=V[path[f]]*V[path[f-1]];
			if(f>=2&&Edge[path[f-2]][path[f]]) thr=V[path[f-2]]*V[path[f-1]]*V[path[f]];
			search(i,f+1,s+V[t]+sec+thr);
			vis[t]=false;
		}
	}
}
int main(){
	int cases;
	cin>>cases;
	for(int i=0;i<cases;i++){
		cin>>N>>M;
		memset(Edge,0,sizeof(Edge));
		memset(vis,0,sizeof(vis));
		for(int j=0;j<N;j++) E[j].clear();

		for(int j=0;j<N;j++) cin>>V[j];
		for(int j=0;j<M;j++){
			int a,b;cin>>a>>b;a--,b--;
			Edge[a][b]=Edge[b][a]=true;
			E[a].push_back(b);E[b].push_back(a);
		}
		S=0;
		for(int i=0;i<N;i++) {
			path[0]=i;vis[i]=true;
			search(i,1,V[i]);vis[i]=false;
		}
		if(S==0) cout<<"0 0"<<endl;
		else cout<<S<<" "<<cnt<<endl;
	}
	return 0;
}
