//treedp=dfs&dp,关键是对每个子树找到状态
#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
#define MAXN 105
#define MAX 999999
int tree[MAXN][3];
vector<int> Edges[MAXN];
int N;
void init(){
  cin>>N;
  bool E[MAXN][MAXN]; memset(E,0,sizeof(E));
  for(int i=1;i<N;i++){
	int a,b;cin>>a>>b;a--,b--;
	E[a][b]=E[b][a]=true;
  }
  queue<int> q;
  bool vis[MAXN];
  memset(vis,0,sizeof(vis));
  q.push(0);vis[0]=true;
  while(!q.empty()){
	int v=q.front();q.pop();
	for(int i=0;i<N;i++) 
	  if(E[v][i]&&vis[i]==false){Edges[v].push_back(i);vis[i]=true;q.push(i);}
  }
  for(int i=0;i<N;i++)
	tree[i][0]=tree[i][1]=tree[i][2]=MAX;
}
bool dfs(int v){
  if(Edges[v].size()==0) {tree[v][1]=0;return true;}
  for(int i=0;i<Edges[v].size();i++){
	int t=Edges[v][i];
	if(!dfs(Edges[v][i])) return false;
  }
  int num_0=0;
  for(int i=0;i<Edges[v].size();i++)
	num_0+=tree[Edges[v][i]][0];

  //tree[v][0]=1+ tree[son][1||2]*2||tree[son][2]*1:不在有环
  for(int i=0;i<Edges[v].size();i++){
	int s=Edges[v][i]; 
	int s0=tree[s][0];
	int s2=tree[s][2];
	if(s2<MAX){
	  int num=num_0-s0;
	  if(num<MAX&&tree[v][0]>s2+num+1)//
		tree[v][0]=s2+num+1;
	}
	for(int j=i+1;j<Edges[v].size();j++){
	  int t=Edges[v][j];
	  int t0=tree[t][0];
	  int s12=tree[s][1]<tree[s][2]?tree[s][1]:tree[s][2];
	  int t12=tree[t][1]<tree[t][2]?tree[t][1]:tree[t][2];
	  if(s12<MAX&&t12<MAX){
		int num=num_0-s0-t0;
		if(num<MAX&&tree[v][0]>s12+t12+num+1){
		  tree[v][0]=s12+t12+num+1;
		}
	  }
	}
  }
  //tree[v][1]=tree[son][0]*n
  if(num_0<MAX){	
	tree[v][1]=num_0;
  }
  //tree[v][2]=tree[son][1||2]*1
  for(int i=0;i<Edges[v].size();i++){
	int s=Edges[v][i]; 
	int s0=tree[s][0];
	int num=num_0-s0;
	if(num<MAX){
	  int s12=tree[s][1]<tree[s][2]?tree[s][1]:tree[s][2];
	  if(s12<MAX&&tree[v][2]>s12+num) tree[v][2]=s12+num;
	}
  }
  if(tree[v][0]>=MAX&&tree[v][1]>=MAX&&tree[v][2]>=MAX) return false;
  return true;
}
int main(){
  init();
  dfs(0);
  if(tree[0][0]<MAX) cout<<tree[0][0]<<endl;
  else cout<<"-1"<<endl;
  return 0;
}

