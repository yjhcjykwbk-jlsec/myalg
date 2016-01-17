//debug：
//注意n可以=1，此时超过dp边界（n>=2)，需要单独处理
//num[][][]和cnt要用long long int保存
//cnt要除以2(n>=2时），cnt=1(n==1时）
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
#define MAXN 13
#define MAX 99999999
int V[MAXN];
bool Edge[MAXN][MAXN];
int mon[1<<MAXN][MAXN][MAXN];
long long int num[1<<MAXN][MAXN][MAXN];
int N,M;
inline int get(int a,int b,int c){
  if(Edge[a][c]) return V[a]*V[b]*V[c];
  return 0;
} 
void dp(){
  for(int path=0;path<1<<N;path++){
	vector<int> vs;
	int t=path,i=0;
	while(t>0){
	  if(t%2) vs.push_back(i);t/=2;i++;
	}	
	if(vs.size()<2) continue;
	for(int i=0;i<vs.size();i++){
	  int t=vs[i];//最后经过t
	  int p=path-(1<<t);
	  for(int j=0;j<vs.size();j++){
		int s=vs[j];//倒数第二经过s
		if(i==j||!Edge[s][t]) continue;
		if(vs.size()==2) mon[path][s][t]=V[s]+V[t]+V[s]*V[t],num[path][s][t]=1;
		else{
		  int sec=V[s]*V[t]+V[t];
		  for(int k=0;k<vs.size();k++){
			int m=vs[k];
			if(m==t||mon[p][m][s]<=0) continue;
			int tmp=mon[p][m][s]+sec+get(m,s,t);//s>0
			if(mon[path][s][t]<tmp) mon[path][s][t]=tmp,num[path][s][t]=num[p][m][s];
			else if(mon[path][s][t]==tmp) num[path][s][t]+=num[p][m][s];
		  }
		}
//		cout<<"path:"<<path<<" s:"<<s<<" t:"<<t<<" mon:"<<mon[path][s][t]<<endl;
	  }
	}
  }
}
int main(){
  int cases;
  cin>>cases;
  for(int i=0;i<cases;i++){
	cin>>N>>M;
	memset(Edge,0,sizeof(Edge));
	memset(mon,0,(1<<N)*sizeof(int)*MAXN*MAXN);
	for(int j=0;j<N;j++) cin>>V[j];
	for(int j=0;j<M;j++){
	  int a,b;cin>>a>>b;a--,b--;
	  Edge[a][b]=Edge[b][a]=true;
	}
	dp();
	int S=0,p=(1<<N)-1;long long int cnt;
	for(int i=0;i<N;i++)
	  for(int j=0;j<N;j++){
		if(mon[p][i][j]>S) S=mon[p][i][j],cnt=num[p][i][j];
		else if(mon[p][i][j]==S) cnt+=num[p][i][j];
	  }
	if(N==1) S=V[0],cnt=2;
	if(S==0) cout<<"0 0"<<endl;
	else cout<<S<<" "<<cnt/2<<endl;
  }
  return 0;
}
