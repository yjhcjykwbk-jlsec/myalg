#include <iostream>
#include <vector>
#include <queue>
#include <stdio.h>
#include <string.h>
using namespace std;
#define MAXN 10
int N=4;
int ROOT=0;
struct Edge{
	int s,t,l;
	Edge(int a,int b,int c):s(a),t(b),l(c){}
	friend bool operator <(const Edge &s,const Edge&t) {
		return s.l>=t.l;
	}
};
vector<Edge> Edges[MAXN];
void prim(){
	bool visit[MAXN];
	priority_queue<Edge> queue;
	memset(visit,0,sizeof(visit));
	int v=ROOT;
	for(int i=0;i<N;i++){
		visit[v]=true;
		for(int j=0;j<Edges[v].size();j++){
			int e=Edges[v][j].t;
			if(!visit[e]) 
				queue.push(Edges[v][j]);
		}
		while(!queue.empty()){
			Edge e=queue.top();queue.pop();
			if(!visit[e.t]) {
				cout<<v<<","<<e.t
					<<":"<<e.l<<endl;
				v=e.t;
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
	prim();
	return 0;
}
