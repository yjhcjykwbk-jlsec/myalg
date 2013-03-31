#include <iostream>
using namespace std;
#define MAXM 1000
#define MAXN 1000
int M,N;
#define rep(i,m,n) for(int i=m;i<n;i++)
char *S,*T;
int Num[MAXM][MAXN];
int calc(){
	rep(i,0,M+1) Num[i][0]=0;
	rep(i,0,N+1) Num[0][i]=0;
	rep(i,1,M+1)
		rep(j,1,N+1){
			if(S[i-1]==T[j-1]) Num[i][j]=Num[i-1][j-1]+1;
			else{
					Num[i][j]=Num[i][j-1]>Num[i-1][j]?Num[i][j-1]:Num[i-1][j];
			}
		}
	return Num[M][N];
}
int main(){
 S="123456789";T="123467";
 M=9,N=6;
cout<<calc()<<endl;
return 0;
}
