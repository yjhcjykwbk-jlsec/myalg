#include <iostream>
#include <stdio.h>
#include <set>
#include <algorithm>
using namespace std;
const int maxN=1000;
const int maxM=1000;
int M,N;
FILE *file;
//int a[maxN*maxN*maxN];
struct elimate{
	int a, b;//z方向的评估
	elimate(const elimate &t){a=t.a;b=t.b;}
	elimate(int _a,int _b){a=_a,b=_b;}
	elimate(){a=0,b=0;}
	friend bool operator< (const elimate &s,const elimate &t){
		if(s.a!=t.a) return s.a<t.a;
		return s.b<t.b;
	}
	friend bool operator ==(const elimate &s,const elimate &t){
		return s.a==t.a&&s.b==t.b;
	}
}ex[maxM],ey[maxM],ez[maxM];//限定x,y
static int ix=0,iy=0,iz=0;//记录数组元素个数
int calc();
int init(){
	fscanf(file,"%d %d\n",&N,&M);
	printf("N:%d,M:%d\n",N,M);
	char a,b;
	int ta,tb;
	ix=0,iy=0,iz=0;
	for(int i=0;i<M;i++){
		int x=0,y=0,z=0;
		fscanf(file,"%c=%d %c=%d\n",&a,&ta,&b,&tb);
		printf("%c=%d %c=%d\n",a,ta,b,tb);
		if(a=='X') x=ta;
		else y=ta;
		if(b=='Y') y=tb;
		else z=tb;
		if(x>0&&y>0) ez[iz++]=elimate(x,y);
		else if(x>0&&z>0) ey[iy++]=elimate(x,z);
		else			 ex[ix++]=elimate(y,z);
	}
	sort(ex,ex+ix);
	sort(ey,ey+iy);
	sort(ez,ez+iz);
	int t=calc();
	printf("result:%d\n",	t);
}
int find(elimate *arr,int l,int r,elimate &t){
	if(l>r) return -1;
	int mid=(l+r)/2;
	if(arr[mid]<t) return find(arr,mid+1,r,t);
	else if(arr[mid]==t) return mid;
	else return find(arr,l,mid-1,t);
}
bool find(int x,int y,int z){
	if(x==0){
		elimate t(y,z);
		if(find(ex,0,ix-1,t)>=0) return true;
	}
	else if(y==0){
		elimate t(x,z);
		if(find(ey,0,iy-1,t)>=0) return true;
	}
	else {
		elimate t(x,y);
		if(find(ez,0,iz-1,t)>=0) return true;
	}
	return false;
}
int calc(){
	int cnt=0;
	cnt+=N*ix;//yz
	set<int> hash;
	for(int i=0;i<iy;i++){//xz
		int x=ey[i].a,z=ey[i].b;
		cnt+=N;//
//		for(int y=1;y<=N;y++){
//			if(find(0,y,z)) cnt--;
//		}
		//or 
		for(int j=0;j<ix;j++)
		if(ex[j].b==z) cnt--; //xz collide with yz at z
	}
	for(int i=0;i<iz;i++){
		int x=ez[i].a,y=ez[i].b;
		cnt+=N;//
//		for(int z=1;z<=N;z++){
//			if(find(x,0,z)||find(0,y,z)) cnt--;
//		}
		//or
		for(int j=0;j<ix;j++)
		if(ex[j].a==y) cnt--,hash.insert(ex[j].b); //xy collide with yz at (x,y,z),
													//record z and next it will not be removed
		for(int j=0;j<iy;j++)
		if(ey[j].a==x&&hash.find(ey[j].b)==hash.end()) cnt--; //xy collide with xz at (x,y,z) ,while z not in hash
													//which means xy not collide with yz at (x,y,z)
	}
	//printf("cnt is %d\n",cnt);
	return cnt;
}
int main(){
	file=fopen("in.dat","r");
	int ss;
	fscanf(file,"%d\n",&ss);
	while(ss-->0)
		init();
	return 0;}
	//O(M(M条块)*N(N格子)*ln(M)(判断是否重复删除))
