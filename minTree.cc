#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;
#define rep(i,n) for(int i=0;i<n;i++)
#define MAXN 1000  //最多点数
//krustal 最小生成树，用到并查集
struct Bcha{
	int bc[MAXN];
	int size;//geshu
	Bcha(int n){
		size=n;
		rep(i,size) bc[i]=i;
	}
	void setF(int n,int m){
		if(n<0||n>=size) return;
		bc[getF(n)]=m;
	}
	int getF(int n){
		if(n<0||n>=size) return -1;
		if(bc[n]==n) return n;
		else return bc[n]=getF(bc[n]);//先计算
	}
};
struct Edge{
	int l; int r; int len;
	Edge(int a,int b,int _len){l=a;r=b;len=_len;}
	Edge(const Edge &s){l=s.l;r=s.r;len=s.len;}
	friend ostream & operator << (ostream &o,const Edge& s){
		o<<s.l<<"#"<<s.r<<"("<<s.len<<")";
		return o;
	}
	friend bool operator <(const Edge& s,const Edge&t){return s.len>t.len;}
};

vector<Edge >edges[MAXN]; int n_vertex;
void init(){
	cin>>n_vertex;
	rep(i,n_vertex)
	{
		edges[i].clear();
		int m;cin>>m;
		rep(j,m){
			int t,len;
			cin>>t>>len;
			Edge edge(i,t,len);
			if(t>i) edges[i].push_back(edge);
		}
	}
	rep(i,n_vertex)
		rep(j,edges[i].size()) 
		cout<<edges[i][j]<<endl;
	cout<<"after init"<<endl;
}
void krustal(){
	//将edges[n]->mintree
	priority_queue<Edge> vqueue;
	rep(i,n_vertex){
		rep(j,edges[i].size())
			vqueue.push(edges[i][j]);
		edges[i].clear();
	}
	Bcha bcha(n_vertex);
	while(!vqueue.empty()){
		Edge s=vqueue.top();vqueue.pop();
		int a=s.l,b=s.r;
		if(bcha.getF(a)!=bcha.getF(b)){
		//	cout<<a<<"("<<bcha.getF(a)<<")"<<b<<"("<<bcha.getF(b)<<")#"<<s.len<<endl;
			edges[a].push_back(s);		
			bcha.setF(a,b);	
		}
	}
}
int main(){
	init();
	krustal();
	rep(i,n_vertex)
		rep(j,edges[i].size())
		cout<<edges[i][j]<<endl;
	return 0;
}



