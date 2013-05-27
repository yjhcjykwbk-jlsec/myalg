#include <iostream>
#include <queue>
using namespace std;
#define MAXN 10
int N=4;
struct Edge{
	int s,t,l;
	Edge(int a,int b,int c):s(a),t(b),l(c){}
	friend bool operator <(const Edge &s,const Edge&t) {
		return s.l>=t.l;
	}
};
vector<Edge> Edges[MAXN];
struct BC{
	int Arr[MAXN];
	void init(int n){for(int i=0;i<n;i++) Arr[i]=i;}
	BC(int n){init(n);}
	int getF(int s){
		if(Arr[s]==s) return s;
		return Arr[s]=getF(Arr[s]);
	}
	bool is_conn(int s,int t){
		return getF(s)==getF(t);
	}
	void conn(int s,int t){
		Arr[s]=t;
	}
};
void krustal(){
	priority_queue<Edge> queue;
	BC bc(N);
	for(int i=0;i<N;i++)
		for(int j=0;j<Edges[i].size();j++)
			queue.push(Edges[i][j]);
	for(int i=1;i<N;i++){
		while(!queue.empty()){
			Edge e=queue.top();queue.pop();
			int s=e.s,t=e.t,l=e.l;
			if(!bc.is_conn(s,t)){
				bc.conn(s,t);
				cout<<s<<","<<t<<":"<<l<<endl;
				break;
			}
		}
	}
}
void init(){
	// (0,1,10),(0,2,30),(1,2,12),(0,3,15),(2,3,3),(1,3,2)
	for(int i=0;i<6;i++){
		int s,t,l;
		cin>>s>>t>>l;
		Edges[s].push_back(Edge(s,t,l));	
		Edges[t].push_back(Edge(t,s,l));	
	}
}
int main(){
	init();
	krustal();
	return 0;
}
