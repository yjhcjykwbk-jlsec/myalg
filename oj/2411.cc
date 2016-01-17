//å°æ¿è¦çé®é¢
#include<iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
#define MAXW 11
#define MAXS (1<<11)
////###long long防止int被爆
//状态：state[x][i],是第x行里砖排列的二进制译码为i的方案个数
long long int state[2][MAXS];
//状态转移矩阵
int num[MAXS][MAXS];
int H,W,states;
//这是用深度优先遍历DPS方法，计算状态之间转移矩阵num
void search(int *a,int *b,int x,int *c){
  if(x==W){
	int t=0;for(int i=W-1;i>=0;i--) {t*=2;if(b[i])t+=1;}
	c[t]++;
	return;
  }
  if(a[x]==0){
	b[x]=1;search(a,b,x+1,c);//æ©«ç 
	if(x<W-1&&a[x+1]==0) {b[x]=b[x+1]=0;search(a,b,x+2,c);}//ç«ç 
  }else{
	b[x]=0;search(a,b,x+1,c);
  }
}
//初始化状态转移矩阵，并调用DPS计算
//初始化状态矩阵
void init(){
  int  a[MAXW],b[MAXW];
  for(int i=0;i<states;i++){
	memset(num[i],0,sizeof(num[i]));
	for(int j=0;j<W;j++) {
	  a[j]=((1<<j)&i)>0?1:0;
	}
	search(a,b,0,num[i]);
  }
  for(int i=0;i<states;i++)
	state[0][i]=0;
  state[0][0]=1;
}
//进行状态推进，从第0行state[0]开始到第H行
void calc(){
  for(int i=1;i<=H;i++){
	  for(int j=0;j<states;j++)
		state[i%2][j]=0;
	  for(int j=0;j<states;j++){
		//##这里是关键点
		//这是一个疏松矩阵，所以适当的时候进行剪枝
		//将使得时间代价大幅度降低
		if(state[1-(i%2)][j]<=0) continue;
		for(int k=0;k<states;k++)
		  //##这里也是在剪枝
		  if(num[j][k]>0) state[i%2][k]+=state[1-(i%2)][j]*num[j][k];
	  }
  }
}
int main(){
  while(true){
	cin>>H>>W;	
	if(H==0||W==0) break;
	states=1<<W;
	init();calc();
	cout<<state[H%2][0]<<endl;
  }
  return 0;
}
