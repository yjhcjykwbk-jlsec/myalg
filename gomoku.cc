#include <vector>
#include <assert.h>
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
#define SIZE(X) ((int)(X.size()))//NOTES:SIZE(
#define LENGTH(X) ((int)(X.length()))//NOTES:LENGTH(
#define MP(X,Y) make_pair(X,Y)//NOTES:MP(
typedef long long int64;//NOTES:int64
typedef unsigned long long uint64;//NOTES:uint64
#define two(X) (1<<(X))//NOTES:two(
#define twoL(X) (((int64)(1))<<(X))//NOTES:twoL(
#define contain(S,X) (((S)&two(X))!=0)//NOTES:contain(
#define containL(S,X) (((S)&twoL(X))!=0)//NOTES:containL(
const double pi=acos(-1.0);//NOTES:pi
const double eps=1e-11;//NOTES:eps
//ENDTEMPLATE_BY_ACRUSH_TOPCODER
enum ChessType{Invalid=-1,Empty=0,White=1,Black=2};
struct Pos{
	int x,y;
	Pos(int a,int b):x(a),y(b){}
	Pos():x(-1),y(-1){};
	bool operator <(const Pos &t){
		if(x!=t.x) return x<t.x;
		return y<t.y;
	}
	bool operator ==(const Pos &t){
		if(x==t.x&&y==t.y) return true;
		return false;
	}
	void null(){x=y=-1;}
	bool isnull(){return x==-1&&y==-1;}
	void set(int a,int b){x=a,y=b;}
	void change(Pos &p){x+=p.x,y+=p.y;}
	void change(int a,int b){x+=a,y+=b;}
};
const char *chessColor(ChessType t){
	if(t==White) return "white";
	else if(t==Black) return "black";
	return "empty";
}
//棋盘类型
struct Chess{
	static const int xnum=15;
	static const int ynum=15;//如10*10 
	ChessType board[20][20];
	void init(){
		rep0(i,xnum)
			rep0(j,ynum)
				board[i][j]=Empty;
	}
	ChessType getType(Pos &p){
		if(p.x<0||p.x>=xnum) return Invalid;
		if(p.y<0||p.y>=ynum) return Invalid;
		return (ChessType)board[p.x][p.y];
	}
	void set(int x,int y,ChessType type){
		assert(x>=0&&x<xnum);
		assert(y>=0&&y<ynum);
//		//printf("set %d %d as %s\n",x,y,type==White?"White":"Black");
		board[x][y]=type;
	}
}chess;
int numOf(ChessType type){
	int num=0;
	rep0(i,chess.xnum)
	rep0(j,chess.ynum)
		if(chess.board[i][j]==type) 	
			num++;
	return num;
}
ChessType whoIsNext(){
	if(numOf(Black)-numOf(White)>1 || numOf(White)>numOf(Black)) return Empty;//不可能出现的情况
	if(numOf(White)<numOf(Black)) return White;
	else return Black;
}
ChessType First;//先手的一方
struct Link{//两个位置，一个填上以后下一个成为W点
	Pos a,b;
	Link(Pos s,Pos t){
		if(s<t) a=s,b=t;//小的位置放到a（将要赢的位置） 大的位置放到b（第一步去的位置）
		else a=t,b=s;
	}
	bool operator <(const Link &t){
		return a<t.a;
	}
	bool operator ==(const Link &t){
		return a==t.a&&b==t.b;
	}
};
list<Link> w3_first,w3_second;
list<Pos> q_first,q_second;
void repchess(int x0,int y0,int dx,int dy,ChessType type,list<Pos> &plist,list<Link> &w3){
		Pos p;int t;
		Pos e1,e2;int l1,l2,l3;
		p.set(x0,y0);
		l1=0;e1.null();//init
		while((t=chess.getType(p))>=0){//防止越过边界
			if(t==3-type)
				l1=0,e1.null();//init
			else if(t==Empty){//空格
				if(e1.isnull()) {
					e1=p;e2.null();
					if(l1>=4) {
						//printf("found l1>=4");
						//printf(" at %d,%d whose color is %s while direction is %d,%d\n",p.x,p.y,chessColor(chess.getType(p)),dx,dy);
						//printf("e1:%d,%d\n",e1.x,e1.y);
						plist.push_front(e1);
						e1.null();l1=0;
					}
					else l2=0;
				}
				else if(e2.isnull()){
					e2=p;
					if(l1+l2>=3) {
						//printf("found l1+l2>=3");
						//printf(" at %d,%d whose color is %s while direction is %d,%d\n",p.x,p.y,chessColor(chess.getType(p)),dx,dy);
						//printf("e1:%d,%d e2:%d,%d\n",e1.x,e1.y,e2.x,e2.y);
						w3.push_front(Link(e1,e2));
						e1=e2;e2.null();l1=l2;l2=0;
					}
					else l3=0;
				}else{
					e1=e2,e2=p;l1=l2;l2=l3;l3=0;
				}
			}else{
				if(e1.isnull()) {
					l1++;
					assert(l1<5);
				}
				else if(e2.isnull()) {
					l2++;
					assert(l2<5);
					if(l1+l2>=4){
						//printf("found l1+l2>=4");
						//printf(" at %d,%d whose color is %s while direction is %d,%d\n",p.x,p.y,chessColor(chess.getType(p)),dx,dy);
						//printf("e1:%d,%d\n",e1.x,e1.y);
						plist.push_front(e1);
						e1.null();l1=l2;
					}
				}
				else{
					l3++;
					assert(l3<5);
					if(l1+l2+l3>=3){ 
						//printf("found l1+l2+l3>=3");
						//printf(" at %d,%d whose color is %s while direction is %d,%d\n",p.x,p.y,chessColor(chess.getType(p)),dx,dy);
						//printf("e1:%d,%d e2:%d,%d\n",e1.x,e1.y,e2.x,e2.y);
						w3.push_front(Link(e1,e2));
						e1=e2;e2.null();l1=l2;l2=l3;
					}
				}
			}
			p.change(dx,dy);
		}
}
//判断type下一个能否胜利(type=1\2) 寻找W点
void findW(ChessType type,list<Pos> &plist,list<Link> &w3){
	assert(type==White||type==Black);
	plist.clear();w3.clear();

	//枚举横向(0度角)
	rep0(j,chess.ynum){
	//	p.set(0,j);
		repchess(0,j,1,0,type,plist,w3);
	//	p.change(1,0);
	}
	//枚举纵向
	rep0(i,chess.xnum){
//		p.set(i,0);
//		p.change(0,1);
		repchess(i,0,0,1,type,plist,w3);
		}

	//枚举45度角
	for(int i=chess.xnum-5;i>=0;i--){
//		p.set(i,0);
//		p.change(1,1);
		repchess(i,0,1,1,type,plist,w3);
	}
	for(int j=1;j<=chess.ynum-5;j++){
//		p.set(0,i);
//		p.change(1,1);
		repchess(0,j,1,1,type,plist,w3);
	}
	//枚举135度角
	for(int j=4;j<chess.ynum;j++){
//		p.set(0,j);
//		p.change(1,-1);
		repchess(0,j,1,-1,type,plist,w3);
	}
	for(int i=1;i<=chess.xnum-5;i++){
//		p.set(i,chess.ynum-1);
//		p.change(1,-1);
		repchess(i,chess.ynum-1,1,-2,type,plist,w3);
	}
	plist.sort();
	w3.sort();
	plist.unique();
	w3.unique();
//	w3.unique();
}
int main(){
	int n,x,y,type;
	while(scanf("%d",&n)){
		if(n==0) break;
		chess.init();
		rep0(i,n){
			scanf("%d %d %d\n",&x,&y,&type);
			chess.set(x,y,(ChessType)(type+1));
		}
		ChessType type=whoIsNext(),alter=White;
		if(type==Empty) {printf("Invalid.\n");continue;}
		if(type==White) alter=Black;
		findW(type,q_first,w3_first);
		if(q_first.size()>=1) {
			Pos p=q_first.front();
			printf("Place %s at (%d,%d) to win in 1 move.\n",chessColor(type),p.x,p.y);
		}else {
			findW(alter,q_second,w3_second);
			if(q_second.size()>=2){
			printf("Lose in 2 moves\n");	
			}else{
				if(w3_first.size()>=1){
				Pos related[Chess::xnum][Chess::ynum]; bool hastwo[Chess::xnum][Chess::ynum];
				rep0(i,Chess::xnum)rep0(j,Chess::ynum) 
					hastwo[i][j]=false;
				for(list<Link>::iterator it=w3_first.begin();it!=w3_first.end();it++){
					Link l=*it;
					Pos p1=l.a,p2=l.b;
//					printf("%d,%d with %d,%d\n",p1.x,p1.y,p2.x,p2.y);
					if(related[p1.x][p1.y].isnull()) related[p1.x][p1.y]=p2;else hastwo[p1.x][p1.y]=true;
					if(related[p2.x][p2.y].isnull()) related[p2.x][p2.y]=p1;else hastwo[p2.x][p2.y]=true;
				}Pos min(Chess::xnum,Chess::ynum);int minx=Chess::xnum,miny=Chess::ynum;
				rep0(i,Chess::xnum)rep0(j,Chess::ynum) 
						if(hastwo[i][j]&&related[i][j]<min) min=related[i][j],minx=i,miny=j; 
				if(minx!=Chess::xnum) 
					printf("Place %s at(%d,%d) to win in 3 moves.\n",chessColor(type),minx,miny);
				else printf("Cannot win in 3 moves.\n");
				}
				else printf("Cannot win in 3 moves.\n");
			}
		}
	}
	return 0;
}
