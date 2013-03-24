#include <iostream>
#include <queue>
#include <map>
using namespace std;
#define MAXN 1000
#define FAR 99999999
int dst[MAXN][MAXN];
char Map[MAXN][MAXN];
bool visit[MAXN][MAXN];
int N,M;
int SX,SY;
int EX,EY;
void init(){
	cin>>N>>M;
	for(int i=1;i<=N;i++)
		for(int j=1;j<=M;j++)
		{
			cin>>Map[i][j];
			if(Map[i][j]=='S') SX=i,SY=j;
			if(Map[i][j]=='E') EX=i,EY=j;
			visit[i][j]=false;
			dst[i][j]=FAR;
		}
	for(int i=1;i<=N;i++) Map[i][0]=Map[i][M+1]='X';
	for(int i=1;i<=M;i++) Map[0][i]=Map[N+1][i]='X';
}
int direction[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
int calc(){
	queue<pair<int,int> > vqueue;//访问队列
	vqueue.push(pair<int,int>(SX,SY));
	visit[SX][SY]=true;dst[SX][SY]=0;
	while(!vqueue.empty()){
		pair<int,int> pairs=vqueue.front();
		vqueue.pop();int x,y;
		for(int i=0;i<4;i++){
			x=pairs.first+direction[i][0];
			y=pairs.second+direction[i][1];
			if(!visit[x][y]&&Map[x][y]!='X') 
			{visit[x][y]=true;vqueue.push(pair<int,int>(x,y));dst[x][y]=dst[pairs.first][pairs.second]+1;}
			if(x==EX&&y==EY) return dst[x][y];
		}
	}
	return -1;//不可达
}
int main(){
	init();
	cout<<calc()<<endl;
	return 0;
}





