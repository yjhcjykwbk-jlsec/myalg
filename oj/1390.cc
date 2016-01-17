#include <iostream>
using namespace std;
struct fragment{
	int color;
	int num;
};
int getLargest(fragment frags[],int n){
	int color_num[3]={0,0,0};
	for(int i=0;i<n;i++)
		color_num[frags[i].color]+=frags[i].num;
	int t=0;
	for(int i=0;i<3;i++)
		t+=color_num[i]*color_num[i];
	return t;
}

