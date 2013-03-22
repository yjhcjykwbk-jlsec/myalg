#include <iostream>
#include <list>
#include <stdio.h>
#include <map>
using namespace std;
#define MAXN 100
#define MAXM 10000
list<pair<int,int> > Row[MAXN];
list<pair<int,int> > Col[MAXM];
int N,M;
bool init(FILE* file){
	fscanf(file,"%d %d\n",&N,&M);
	if(N==0&&M==0) return false;
	for(int i=0;i<N;i++) Row[i].clear();
	for(int i=0;i<M;i++) Col[i].clear();
	for(int i=0;i<N;i++)
		for(int j=0;j<M;j++)
		{
			int a;
			fscanf(file,"%d",&a);
			if(a>0) Row[i].push_back(pair<int,int>(j,a)),Col[j].push_back(pair<int,int>(i,a));
		}
	return true;
}
int max(int a,int b){ if(a>b) return a;return b;}
int getmin(){
	int t=1;//慢慢增大
	int min=t;
	while(true){
		for(int i=0;i<N;i++){
			int begin=0;
			bool divtwo=false;
			list<pair<int,int> >::iterator lastindex=Row[i].end();
			list<pair<int,int> >::iterator pt;
			for(list<pair<int,int> >::iterator it=Row[i].begin();;it++){
				while(it!=Row[i].end()&&it->second<t) {pt=it++;Row[i].erase(pt);}
				if(it==Row[i].end()) break;
				if(divtwo) min=max(min,(it->first-begin+2)/2);
				else min=max(min,it->first-begin+1);
				divtwo=true; begin=it->first;lastindex=it;//有一个灯在亮着
			}
			if(lastindex==Row[i].end()) return -1;
			min=max(min,M-lastindex->first);
		}
		for(int i=0;i<M;i++){
			int begin=0;
			bool divtwo=false;
			list<pair<int,int> >::iterator lastindex=Col[i].end();
			list<pair<int,int> >::iterator pt;
			for(list<pair<int,int> >::iterator it=Col[i].begin();;it++){
				while(it!=Col[i].end()&&it->second<t){pt=it++; Col[i].erase(pt);}
				if(it==Col[i].end()) break;
				if(divtwo) min=max(min,(it->first-begin+2)/2);
				else min=max(min,it->first-begin+1);
				divtwo=true; begin=it->first;lastindex=it;
			}
			if(lastindex==Col[i].end()) return -1;
			min=max(min,N-lastindex->first);
		}
		if(t==min) return t;
		else t=min;
		if(min>N&&min>M) return -1;//too big
	}
}
int main(){
	FILE*file=fopen("searchlight.in","r");
	while(	init(file)){
		int t=getmin();
		if(t>0)
			cout<<t<<endl;
		else cout<<"NO ANSWER!"<<endl;
	}
}
