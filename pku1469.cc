#include <iostream>
#include <string.h> 
#include <vector>
#include <queue>
using namespace std;
#define FAR 9999999
#define MAXN 1000
int N,num_l,num_r;
int num;
vector<int> Edges[MAXN];
#define rep(i,n) for(int i=0;i<n;i++)
void init(){
	cin>>num_l>>num_r;//左右子图节点个数
	N=num_l+num_r+1;
	rep(i,num_l+1) Edges[i].clear();
	rep(i,num_l){
		int a;cin>>a;
		rep(j,a){
			int b;cin>>b;
			Edges[b].push_back(i+num_l);
		}
	}
}
bool Use[MAXN];int From[MAXN];
bool match(int x){
		for(vector<int>::iterator it=Edges[x].begin();it!=Edges[x].end();it++){
			int j=*it;
			if(!Use[j]){//占用该点，别的x不能用这个点
			Use[j]=true;
			if(From[j]==-1||match(From[j])){
				From[j]=x;return true;//matched
			}
		}	
	}
	return false;
}
bool calc(){
	rep(i,N) From[i]=-1;
	int num=0;
	for(int i=1;i<=num_l;i++){
		rep(j,N) Use[j]=false;
		if(match(i)) num++;
		else return false;
	}
	return true;
}
int main(){
	int cases;cin>>cases;
	rep(i,cases){
		init();
		if(num_r>num_l) cout<<"NO"<<endl;
		else if(calc()) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}


