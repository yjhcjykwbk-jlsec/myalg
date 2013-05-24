#include <iostream>
using namespace std;
int MinW=99999;
int value[4][3]={ {10,8,12},{20,21,30},{40,42,30},{30,60,45}};
int weight[4][3]={ {5,6,4},{8,10,5},{5,4,10},{20,10,15}};
int ans[5];
int the_min[5];
void func(int i,int v,int w){//处理第i个配件时重量为w,价值v
	if (w>MinW||v>120)
		return;
	if (i>=4){
		if (w<MinW){
			MinW=w;
			for(int k=0;k<4;k++) the_min[k]=ans[k];
		}
		return;
	}
	for(int j=0;j<3;j++)
	{
		ans[i]=j;
		func(i+1,v+value[i][j],w+weight[i][j]); 
	}
	//value[i][j]:第i种配件在供应商j的价值
}
int main(){
	func(0,0,0);
			cout<<MinW<<endl;
			for(int k=0;k<4;k++) cout<<the_min[k]<<" ";
			return 0;
			}

