//min road
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define MAXN 1000
#define FAR 0x7fffffff
#define rep(i,n) for (int i=0 ; i<n; i++ )

int D[MAXN],N;
bool Visit[MAXN];
vector<pair<int,int> > dis[MAXN];//nextp,weight

struct Dist{
	int v,w;
	Dist(int a,int b){v=a,w=b;}
	bool operator < (const Dist&s) const{	return w>s.w;}
};
void init(){
	cin>>N;
	int n;cin>>n;
	rep(i,n){
		int a,b,d;
		cin>>a>>b>>d;
		dis[a].push_back(pair<int,int>(b,d));
		dis[b].push_back(pair<int,int>(a,d));
	}
}

void diliklie(int s){
	priority_queue<Dist> vqueue;
	vqueue.push(Dist(s,0));
	rep(i,N) D[i]=FAR;D[s]=0;
	rep(i,N) Visit[i]=false;
	while(!vqueue.empty()){
		int c=vqueue.top().v;vqueue.pop();
		if(Visit[c]==true) continue;
		Visit[c]=true;
		for(int i=0;i<dis[c].size();i++)
		{
			int v=dis[c][i].first;int w=dis[c][i].second;
			if(D[v]>D[c]+w) {
				D[v]=D[c]+w;
//				if(v==t) goto findT;
				vqueue.push(Dist(v,D[v]));
			}
		}
	}
//	findT:
	rep(i,N) cout<<D[i]<<" ";cout<<endl;
}
int main(){
	init();
	diliklie(0);
	return 0;
}
