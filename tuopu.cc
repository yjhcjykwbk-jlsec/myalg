//tuopu sort
#include <iostream>
#include <map>
#include <vector>
#include <queue>
using namespace std;
#define MAXN 10000
#define rep(i,n) for(int i=0;i<n;i++)

typedef pair<int,int> Edge;
vector<pair<int,int> > edges[MAXN];
int rudu[MAXN];int N;
void init(){
	cin>>N;
	rep(i,N) edges[i].clear(),rudu[i]=0;
	int n;cin>>n;
	rep(i,n){
		int a,b,d;
		cin>>a>>b>>d;edges[a].push_back(Edge(b,d));rudu[b]++;
	}
}
void sort(){
	queue<int> vqueue;
	rep(i,N) if(rudu[i]==0) vqueue.push(i);
	while(!vqueue.empty()){
		int v=vqueue.front();vqueue.pop();
		cout<<v<<" ";
		for(int i=0;i<edges[v].size();i++){
			int t=edges[v][i].first;rudu[t]--;
			if(rudu[t]==0) vqueue.push(t);
		}	
	}
	cout<<endl;
}
int main(){
		init();sort();return 0;
}
	
