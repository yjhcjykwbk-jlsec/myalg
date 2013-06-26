//地板覆盖问题
#include<iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
#define MAXW 11
#define MAXS (1<<11)
int state[2][MAXS];
int num[MAXS][MAXS];
int W,states;
//一行当中11个格子从左到右，填充为1，非填充为0
void search(int *a,int *b,int x,int *c){
  if(x==W){
	int t=0;for(int i=W-1;i>=0;i--) {t*=2;if(b[i])t+=1;}
	c[t]++;
//		for(int i=0;i<W;i++) cout<<a[i]<<" ";cout<<endl;
//		for(int i=0;i<W;i++) cout<<b[i]<<" ";cout<<endl;
	return;
  }
  if(a[x]==0){
	b[x]=1;search(a,b,x+1,c);//橫砖
	if(x<W-1&&a[x+1]==0) {b[x]=b[x+1]=0;search(a,b,x+2,c);}//竖砖
  }else{
	b[x]=0;search(a,b,x+1,c);
  }
}
void init(){
  int  a[MAXW],b[MAXW];
  for(int i=0;i<states;i++){
	memset(num[i],0,sizeof(num[i]));
	for(int j=0;j<W;j++) {
	  a[j]=((1<<j)&i)>0?1:0;
	}
	search(a,b,0,num[i]);
  }
//  for(int i=0;i<states;i++)
//	state[0][i]=0;
//  state[0][0]=1;
}
int H;
int a[MAXS][MAXS];
int c[MAXS][MAXS];
int tmp[MAXS][MAXS];
//矩阵运算
void mul(int a[][MAXS],int b[][MAXS],int c[][MAXS],int w){
//	cout<<w<<endl;
	cout<<w<<" begin"<<endl;
  for(int i=0;i<w;i++){
	for(int j=0;j<w;j++){
	  tmp[i][j]=0;
	  for(int k=0;k<w;k++);
		//tmp[i][j]+=b[i][k]*c[k][j];	
	}
  }
  cout<<w<<" end"<<endl;
  for(int i=0;i<w;i++)
	for(int j=0;j<w;j++)
		a[i][j]=tmp[i][j];
}
void reset(int a[][MAXS],int w){
	memset(a,0,sizeof(num));
	for(int i=0;i<w;i++) a[i][i]=1;
}
void calc(){
  //(a0....an)(num[j][k])^H=(b0......bn)
	reset(a,states);
	memcpy(c,num,sizeof(num));
	int n=H;
	while(n>0){
	  cout<<n<<endl;
	  if(n%2) mul(a,a,c,states);//a=a*num
	  n/=2;	mul(c,c,c,states);//c=c*c
	}
//	cout<<a[0][0]<<endl;//从state[0]到state[0]
}
int main(){
  while(true){
	cin>>H>>W;	
	if(H==0||W==0) break;
	states=1<<W;
	cout<<"###########"<<endl;
	cout<<H<<":"<<W<<endl;
	init();
	calc();
  }
  return 0;
}
