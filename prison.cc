
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;
#define rep0(i,n) for(int i=0;i<n;i++)  //[0,n)
#define rep(i,m,n) for(int i=m;i<n;i++) //[m,n)
#define tep0(i,m) for(int i=m;i>0;i--)  //[m.0)
#define tep(i,m,n) for(int i=m;i>n;i--) //[m.n)
//BEGINTEMPLATE_BY_ACRUSH_TOPCODER
//ENDTEMPLATE_BY_ACRUSH_TOPCODER

#define FAR 999999

struct Pos{
	int x;
	int y;
	Pos(int a,int b){x=a,y=b;}
	Pos(){x=-1,y=-1;}
};
int n,m;
char a[20][20];
int E;//最大电量
int dst[16][16];//
int number[16][16];
bool isEPool[16];
int fnum;//起始编号
int tnum;//所有的个数
Pos poses[16];//编号为i的位置
int endstate;
int direction[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
void initnum(){
	rep0(i,n)rep0(j,m) number[i][j]=-1;//初始尚未编号
	int num=0;
	endstate=0;
	rep0(i,16) isEPool[i]=false;
	rep0(i,n)rep0(j,m) 
		if(a[i][j]=='G'||a[i][j]=='Y'||a[i][j]=='F'){
			number[i][j]=num,poses[num]=Pos(i,j);
			if(a[i][j]=='Y') endstate+=(1<<(num));//必须关掉的灯
			if(a[i][j]=='F') fnum=num;
			if(a[i][j]=='G') isEPool[num]=true;//可以充电的地方
			num++;
		}
	tnum=num;
}
int d[16][16];
void getDst(int s){
	rep0(i,n)rep0(j,m) d[i][j]=FAR;
	queue<Pos> vqueue;
	Pos p=poses[s];
	vqueue.push(p);
	d[p.x][p.y]=0;
	while(!vqueue.empty()){
		p=vqueue.front();vqueue.pop();
		int x=p.x,y=p.y;
		for(int i=0;i<4;i++){
			int x1=x+direction[i][0],y1=y+direction[i][1];
			if(a[x1][y1]!='D'&&d[x1][y1]==FAR) {
				d[x1][y1]=d[x][y]+1;vqueue.push(Pos(x1,y1));
			}
		}
	}
	rep0(i,tnum){
		p=poses[i];dst[s][i]=d[p.x][p.y];dst[i][s]=d[p.x][p.y];
	}
}
void initdst(){
	rep0(i,tnum) getDst(i);
}
bool init(){
	scanf("%d%d",&n,&m);
	if(n==0||m==0) return false;
	rep0(i,n+2) rep0(j,m+2) a[i][j]='D';
	char t[20];
	rep(i,1,n+2)
	{scanf("%s",t);
		rep(j,0,m+2)
			a[i][j+1]=t[j];
	}
//	rep0(i,n+1){rep0(j,m+1) cout<<a[i][j];cout<<endl;}
	initnum();
	initdst();
	return true;
}
int energy[1<<16][16];
void initenergy(){
	//cout<<" tnum:"<<tnum<<endl;
	rep0(i,1<<tnum)rep0(j,tnum) energy[i][j]=-1;
}
bool f(int state,int pos,int e){
	if(state&endstate==endstate) return true;
	//cout<<"i am at "<<pos<<" with energy "<<e<<" state "<<state<<endl;
	rep0(i,tnum){
		int d=dst[pos][i];
		//cout<<"if go to "<<i<<" i need energy "<<d<<endl;
		//cout<<"then state will change to "<<(state&(1<<i))<<endl;
		//cout<<state<<":"<<(1<<i)<<endl;
		if((state&(1<<i))==0&&d<=e)
		{
			//cout<<"i try go to "<<i<<" i need energy "<<d<<endl;
			d=isEPool[i]?E:e-d;
			if(energy[state|(1<<i)][i]<d){
				if(f(state|(1<<i),i,d)) return true;
			}
		}
	}
	return false;
}

int search(){
	int l=1,r=800;
	while(true){
		if(l>r) return -1;
		int mid=(l+r)/2;
		E=mid;
		int state=1<<fnum;
		initenergy();
		energy[state][fnum]=E;//初始电量
		if(f(state,fnum,E)) r=mid;
		else l=mid+1;
		if(l==r) return l;
	}
}

int main(){
		while(true){
	if(!init()) return 0;
	//cout<<"from F="<<fnum<<" to every place needs:"<<endl;
	//	rep0(i,tnum)
		//cout<<dst[fnum][i]<<" ";
	cout<<search()<<endl;
		}
	return 0;
}
