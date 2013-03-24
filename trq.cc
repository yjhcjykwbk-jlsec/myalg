#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <map>
using namespace std;
#define MAXM 100000
#define MAXN 10000
#define MAXQ 10000
#define FAR 999999;
vector<int> roads[MAXM+1];//link list to neighbor
struct Cross{
	int next;
	int rnum;
	Cross(int a,int b){next=a,rnum=b;}
	Cross(const Cross &t){next=t.next,rnum=t.rnum;}
	Cross(){next=-1,rnum=-1;}
};
vector<Cross> crosses[MAXN];
int M,N,Q;

bool visit[MAXM];
int dst[MAXM];

vector<pair<int,int> > quests[MAXM];
int answers[MAXQ];
void getDst(int l){
	for(int i=0;i<M;i++){ dst[i]=FAR;visit[i]=false;}
	queue<int> vqueue;
	dst[l]=0;vqueue.push(l);visit[l]=true;
	while(!vqueue.empty()){
		int v=vqueue.front();vqueue.pop();
		int d=dst[v];
		for(int i=0;i<roads[v].size();i++){
			int t=roads[v][i];
			if(!visit[t]){ dst[t]=d+1;visit[t]=true;vqueue.push(t);}
		}
	}
}
void init(){
	FILE *file=fopen("trq.in","r");
	fscanf(file,"%d %d\n",&N,&M);
//	cin>>N>>M;
	for(int i=0;i<M;i++){
		int a,b;
	fscanf(file,"%d %d\n",&a,&b);
//	cin>>a>>b;
		crosses[a].push_back(Cross(b,i+1));
		crosses[b].push_back(Cross(a,i+1));
	}
	for(int i=0;i<N;i++){
		for(int j=0;j<crosses[i].size();j++){
			for(int k=j+1;k<crosses[i].size();k++){
				int l=crosses[i][j].rnum,r=crosses[i][k].rnum;
				roads[l].push_back(r);
				roads[r].push_back(l);//相互邻接的路面
			}
		}
	}
//	cin>>Q;
	fscanf(file,"%d\n",&Q);
	for(int i=0;i<Q;i++){
		int a,b;
	//	cin>>a>>b;
	fscanf(file,"%d %d\n",&a,&b);
		if(a<b)
			quests[a].push_back(pair<int,int>(b,i));
		else 
			quests[b].push_back(pair<int,int>(a,i));
	}
}
void answer(){
	for(int i=0;i<MAXM;i++){
		if(quests[i].size()>0){
			getDst(i);
			for(int j=0;j<quests[i].size();j++)
				answers[quests[i][j].second]=dst[quests[i][j].first];
		}
	}
	for(int i=0;i<Q;i++) cout<<answers[i]<<endl;
}
int main(){
	init();
	answer();
	return 0;
}
