//最小费用流
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define FAR 9999999
#define MAXN 300
int dst[MAXN][MAXN];
int cap[MAXN][MAXN];//每条边的容量
vector<int> edges[MAXN];
int d[MAXN],pre[MAXN],inqueue[MAXN];
int N,M;
int S,T;
void init(){
	cin>>N;
	cin>>S>>T;
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			dst[i][j]=FAR,cap[i][j]=0;
	cin>>M;//M个边
	int a,b,c,d;
	for(int i=0;i<M;i++)
		cin>>a>>b>>c>>d,dst[a][b]=d,cap[a][b]=c,edges[a].push_back(b);//边容量和费用
}
bool spfa(){
	for(int j=0;j<N;j++) d[j]=FAR,inqueue[j]=0;
	queue<int> visit;
	visit.push(S);inqueue[S]=1;
	d[S]=0;pre[S]=-1;
	while(!visit.empty()){
		int v=visit.front();visit.pop();inqueue[v]=0;
		for(int _i=0;_i<edges[v].size();_i++){//访问节点v
			int i=edges[v][_i];
			if(dst[v][i]<FAR&&cap[v][i]>0) {//v->i可达 而且该边容量未满
				if(d[i]>dst[v][i]+d[v]){
					d[i]=dst[v][i]+d[v];
					pre[i]=v;
					if(inqueue[i]==0)//找到新的松弛点
						visit.push(i);inqueue[i]=1;
				}
			}
		}
	}
	if(d[T]!=FAR) return true;
	return false;
}
//调查剩余流的容量
int network(){
	int flow=0;//当前s->t的流量
	int cost=0;
	while(spfa()){
		int cf=FAR;
		int v1,v2=T;
		while((v1=pre[v2])!=-1) {
			if(cap[v1][v2]<cf) cf=cap[v1][v2];
			v2=v1;
		}
		flow+=cf;
		cost+=cf*d[T];
		v2=T;
		while((v1=pre[v2])!=-1) {
			cap[v1][v2]-=cf;
			cap[v2][v1]+=cf;
		}
	}
	return cost;//最小费用下的最大流？
}	
	
int main(){
	init();
	printf("network cost:%d\n",network());
	return 0;
}
