//数组问题最难在于下标起点0/1的选择,以及初始化变量选择
////选择0，则意味着递推的时候边界0需要单独处理
////选择1，有很多好处，例如递推边界更好确定
//数组元素的初始化常见的有三种，都赋成0，-1或MAX
////选择0最容易出错，造成语义的混淆。
////选择-1和MAX可以表示极少、极多或者无效不可行不存在，并且语义一般不会混淆
#include <iostream>
#include <stdio.h>
#include <string.h> 
using namespace std;
#define loop(i,n) for(int i=0;i<n;i++)
#define MAXW  23
#define MAXN  9
int v[10]={2,4,6,1,3,7,9,11,5};
int w[10]={3,4,7,3,2,10,5,13,4};
void print_pack(){
  loop(i,MAXN) printf("%d:(%d#%d) ",i,w[i],v[i]); cout<<endl;
}
void print(int a[][MAXW+1],int b[][MAXW+1]){
  /////////////////输出背包变化
  loop(j,MAXW+1)  printf("%2d    ",j);cout<<endl;
  loop(i,MAXN){
	loop(j,MAXW+1)  printf("%2d:%2d|",b[i][j],a[i][j]);cout<<endl;
  }
}
int pack(){
  int a[MAXW+1][MAXN];
  loop(i,MAXW+1) a[i][0]=(i>=w[0]?v[0]:0);
  loop(i,MAXN) 	a[0][i]=0;
  for(int i=1;i<=MAXW;i++)//weight
	for(int j=1;j<MAXN;j++){//n
	  a[i][j]=max(a[i-1][j],a[i][j-1]);//比pack1增加了a[i][j-1]向a[i][j]传递
	  if(i>=w[j]) a[i][j]=max(a[i][j],a[i-w[j]][j-1]+v[j]);
	}
  loop(i,MAXN) cout<<a[MAXW][i]<<" ";cout<<endl;
  loop(i,MAXW+1) cout<<a[i][MAXN-1]<<" ";cout<<endl;
  return a[MAXW][MAXN-1];
}
//状态:a[n][w]前n样物品恰好装到重量为w时的最大价值
int pack1(){
  int a[MAXN][MAXW+1];
  int b[MAXN][MAXW+1];
  //边界条件
  loop(i,MAXN)loop(j,MAXW+1) a[i][j]=-1;//背包为空
  loop(i,MAXN)loop(j,MAXW+1) b[i][j]=-1;
  for(int i=0;i<MAXN;i++) a[i][0]=0;
  if(w[0]<=MAXW) a[0][w[0]]=v[0],b[0][w[0]]=0;//装入第一个物品，编号0
  //递推
  for(int i=1;i<MAXN;i++)
	for(int j=1;j<=MAXW;j++){
	  a[i][j]=a[i-1][j],b[i][j]=b[i-1][j];
	  if(j>=w[i]&&a[i-1][j-w[i]]>=0&&a[i-1][j-w[i]]+v[i]>a[i][j]) 
		a[i][j]=a[i-1][j-w[i]]+v[i],b[i][j]=i;
	}
  
  print(a,b);
  //输出背包
  int max=0; loop(i,MAXW+1) if(a[MAXN-1][i]>a[MAXN-1][max]) max=i;
  int t=b[MAXN-1][max],tw=max;
  while(t>=0){
	cout<<tw<<":"<<t<<"("<<w[t]<<"#"<<v[t]<<") ";
	tw-=w[t];
	if(t>0) t=b[t-1][tw];
	else break;
  }cout<<endl;
  return a[MAXN-1][max];
}

//状态:a[n][w]前n样物品装到重量w以内时的最大价值
int pack2(){
  int a[MAXN][MAXW+1];
  int b[MAXN][MAXW+1];
  //边界条件
  memset(a,0,sizeof(a));
  loop(i,MAXN)loop(j,MAXW+1) b[i][j]=-1;
  for(int j=0;j<=MAXW;j++)
	a[0][j]=(j>=w[0]?v[0]:0),b[0][j]=(j>=w[0]?0:-1);//装入物品0
  //递推
  for(int i=1;i<MAXN;i++)
	for(int j=1;j<=MAXW;j++){
	  a[i][j]=max(a[i-1][j],a[i][j-1]);//比pack1增加了a[i][j-1]向a[i][j]传递
	  if(j>=w[i]) a[i][j]=max(a[i][j],a[i-1][j-w[i]]+v[i]);
	  if(a[i][j]==a[i-1][j]) b[i][j]=b[i-1][j];
	  else if(a[i][j]==a[i][j-1]) b[i][j]=b[i][j-1];
	  else b[i][j]=i;
	}
  print(a,b);
  //输出背包
  int t=b[MAXN-1][MAXW],tw=MAXW;
  while(t>=0){
	cout<<tw<<":"<<t<<"("<<w[t]<<"#"<<v[t]<<") ";
	tw-=w[t];
	if(t>0) t=b[t-1][tw];
	else break;
  }cout<<endl;

  return a[MAXN-1][MAXW];
}
int main(){
  print_pack();
  cout<<"pack():"<<pack()<<endl;
  cout<<"======================="<<endl;
  cout<<"pack1():"<<pack1()<<endl;
  cout<<"======================="<<endl;
  cout<<"pack2():"<<pack2()<<endl;
  return 0;}
