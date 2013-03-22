#include <vector>
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
#define MAXM 201
#define MAXN 57
int N,M;
vector<int> poses[MAXN];
void init(){
	FILE *file=fopen("nationalday.in","r");	
	fscanf(file,"%d %d\n",&N,&M);
	int a,b;
	for(int i=1;i<=N*N;i++)
	{
		fscanf(file,"%d %d\n",&a,&b);
		if(a==0&&b==0) break;
		poses[a].push_back(b);
	}
	for(int i=1;i<=N;i++) sort(poses[i].begin(),poses[i].end());
	int min=99999999;
	for(int i=1;i<=M-N+1;i++) {
		int cn=0;
		for(int j=1;j<=N;j++){
			for(int k=0;k<N;k++)
				cn+=abs(poses[j][k]-(i+k));
		}
		if(cn<min) min=cn;
	}
	cout<<min<<endl;
}
int main(){
	init();
	return 0;
}

