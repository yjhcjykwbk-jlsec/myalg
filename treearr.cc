#include <iostream>
using namespace std;
#define DEPTH 20
#define MAXN 2<<DEPTH
#define rep(i,n) for(int i=0;i<n;i++)
int Arr[MAXN];
int Tree[MAXN];
int S=2<<20,N;
int init(){
	cin>>N;
	rep(i,N) cin>>Arr[i];
	for(int i=19;i>=0;i++){
		int s=2<<i-1,t=2<<(i+1)-1;
		for(int j=s;j<t;j++)
			Tree[j]=Tree[j*2+1]+Tree[j*2+2];	
}	

