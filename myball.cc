#include <iostream>
#include<stdlib.h>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include <assert.h>
using namespace std;
#define Pi 3.1415926
#define H 500
#define W 1000
#define rep(i,n) for(int i=0;i<n;i++)
#define tep(i,m,n) for(int i=m;i<n;i++)
float K=0.0002,OLen=3;
struct Pos;
typedef struct Pos Speed;//速度
typedef struct Pos Aspeed;//加速度
struct Pos{
	float x,y;
	Pos(float a,float b){x=a,y=b;}
	Pos(){x=0,y=0;}
	void change(const Speed& s){ x+=s.x;y+=s.y; }
	void change(float dx,float dy){ x+=dx;y+=dy; }
	void set(float a,float b){
		x=a,y=b;
	}
	void init(){
		x=0,y=0;
	}
	void speed_zuni(){
		x*=0.94;y*=0.94;
	}
};
struct Ball{
	int size;//半径
	Pos  pos;//位置
	Speed speed;//速度
	Aspeed aspeed;//加速度
	Ball(){
		pos.init();
		speed.init();
		aspeed.init();
	}
	Ball(float x,float y){
		pos.set(x,y);
		speed.init();
		aspeed.init();
	}
	void set(float x,float y){
		pos.set(x,y);
		speed.init();
		aspeed.init();
	}
	void change(){
		speed.change(aspeed);
		speed.speed_zuni();
		pos.change(speed);
	}
	void print(){
		cout<<pos.x<<"("<<(int)pos.x<<")"<<","<<pos.y<<"("<<(int)pos.y<<")";
	}
};
//弹簧的力,OLen为弹簧原长
float getPower(float dd){
	float f;
	if(abs(dd-OLen)<0.3) f=K*pow(0.3,2.0)/2;
	else f=K*pow((dd-OLen),2.0)/2;
	return (dd>OLen?0-f:f);
}
//小球之间的排斥力
float getPower1(float dd){
	if(dd<0.3) return 5*pow(0.3,-1.6);
	else return 5*pow(dd,-1.6);
}
//计算小球受到的屏幕边缘的排斥力产生的加速度
void influence(Ball *lp){
	float dx1=lp->pos.x,dx2=W-dx1;
//	float dx1=abs(lp->pos.x),dx2=abs(W-dx1);
	if(dx1<0) dx1=0.5; else if(dx2<0) dx2=0.5;
	float fx=pow(dx1,-1.5)-pow(dx2,-1.5);

	float dy1=lp->pos.y,dy2=H-dy1;
	if(dy1<0) dy1=0.5; else if(dy2<0) dy2=0.5;
	float fy=pow(dy1,-1.5)-pow(dy2,-1.5);

	lp->aspeed.change(fx,fy);
}
//计算小球之间因为互相作用力func而产生的加速度
void influence(Ball *lp,Ball *rp,float (*func)(float dd)){
	float dx=rp->pos.x-lp->pos.x;
	float dy=rp->pos.y-lp->pos.y;
	float cos,sin;//-1 - 1
	float dd=pow(dx,2.0)+pow(dy,2.0);
	if(dd<=0.1) dd=0.1,cos=dx>0?1:-1,sin=0;
	else{ dd=pow(dd,0.5);cos=dx/dd; sin=dy/dd; }
//	cout<<"dd:"<<dd<<",cos:"<<cos<<",sin:"<<sin<<endl;
	float f=func(dd);
	float fx=f*cos,fy=f*sin;	
	rp->aspeed.change(fx,fy);
	lp->aspeed.change(0-fx,0-fy);
}
struct Edge{//弹簧
	Ball * lp;//小的球编号
	Ball * rp;//大的球编号
	Edge(Ball *l,Ball *r){lp=l;rp=r;}
	Edge(){lp=NULL;rp=NULL;}
	void set(Ball *l,Ball *r){lp=l;rp=r;}
	void change(){
		influence(lp,rp,getPower);
	}
};

//////////////////////////////////////////////////////////
Ball balls[1000];Edge edges[1000];
int n_edge; int n_ball;
//随时间刷新数据
void refresh(){
	rep(i,n_ball)
		balls[i].aspeed.init();//初始化加速度
	rep(i,n_edge)
		edges[i].change();//因为弹簧作用力产生的加速度
	rep(i,n_ball){
		int dt=0;//步
		if(n_ball>i+1+10) dt=(n_ball-(i+1))/10;
		else dt=1;
		for(int j=i+1;j<n_ball;j+=random()%dt+1)//随机找10个点
		influence(&balls[i],&balls[j],getPower1);//计算小球i与他们之间排斥力产生的加速度
	}
	rep(i,n_ball)
		influence(&balls[i]);//因为屏幕边缘对小球排斥力产生的加速度
	rep(i,n_ball)
		balls[i].change();//由加速度，计算新的速度和位置
}
//初始化数据
void init(int n){
	rep(i,n)
	{
		int x=W/2+random()%200;
		int y=H/2+random()%200;
		balls[i].set(x,y);
	}
	rep(i,n-1){
		int j=random()%(n-i-1)+i+1;
		edges[i].set(balls+i,balls+j);
	}
	//	edges[i-1].set(&balls[i-1],&balls[0]);
	n_ball=n;n_edge=n-1;	
	cout<<"after init"<<endl;
}
///////////////////////////////////////////////////
//画图
void drawLine(Ball *lp,Ball *rp)  {
	float x1=lp->pos.x,y1=lp->pos.y;
	float x2=rp->pos.x,y2=rp->pos.y;
	glColor3f (0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(x1,y1);
	glVertex2f(x2,y2);
	glEnd();
}
void drawBall(float x,float y,float R){
	int n=1000;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for(int count=0; count<=n; count++)
	{
		glVertex2f(x+R*cos(count*2*Pi/n), y+R*sin(count*2*Pi/n));
	}
	glEnd();
}
void drawBallsAndEdges(){
	int R=5,n=300;
	rep(i,n_ball)
	{
		float x=balls[i].pos.x,y=balls[i].pos.y;
		drawBall(x,y,4);
	}
	rep(i,n_edge)
	{
		drawLine(edges[i].lp,edges[i].rp);
	}
}
void _display();
void timerFunc(int value){
	_display();
}
void _display(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (0.0, 0.0, 0.0);
	drawBallsAndEdges();
	glEnd();
	glFlush ();
	refresh();//刷新数据
	glutTimerFunc(20,timerFunc,0);
}
void _init (void) 
{
	glClearColor (1.0, 1.0, 1.0, 0.0);
	glColor3f(1.0, 0.0, 0.0) ;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1000.0, 0.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 0);
	glutCreateWindow ("hello");
	cout<<"ball num:"<<endl;int n;cin>>n;
	init(n);
	_init ();
	glutDisplayFunc(_display);
	glutTimerFunc(50,timerFunc,0);
	glutMainLoop();
	return 0;
}
