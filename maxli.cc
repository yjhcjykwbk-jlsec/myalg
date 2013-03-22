#include <iostream>
#include <stdio.h>
using namespace std;
#define MAXN 10000
#define SMALL -999999
int M[MAXN];
int a[MAXN];
bool b[MAXN];
int N;
int main(){
	FILE *file=fopen("maxli.in","r");
	int i;
	for(i=1;i<MAXN;i++)
		if(fscanf(file,"%d",&a[i])<=0) break;
	N=i; M[0]=0;b[i]=false;
	for(i=1;i<=N;i++){
		if(M[i-1]>0){b[i]=true; M[i]=a[i]+M[i-1];}
		else M[i]=a[i],b[i]=false;
	}
	int s=SMALL,k;
	for(i=1;i<=N;i++)
		if(M[i]>s) s=M[i],k=i;
	for(i=k;i>=1;i--) if(!b[i]) break;
	cout<<i-1<<"-"<<k-1<<":"<<s<<endl;
	return 0;
}
