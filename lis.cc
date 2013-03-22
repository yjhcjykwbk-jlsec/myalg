//求lis的nlogn思想求lis的nlogn思想。f表示长度为i的上升子序列最后一个数最小是多少。显然数组f是单增的。 读到一个新的数x后，找到某个i使得x>f[i]且x<=f[i+1]，于是用x去更新f[i+1]；特别地，如果所有的f[i]都小于x，则增加f的长度。 最后看f数组有多长就行了。 由于f单增，所以查找i时可以用二分查找，因此时间复杂度为O(nlogn)。 举个例子，假如序列为 3 2 8 6 7 4 5 7 3，则f数组的变化过程如下： 3 2 2 8 2 6 2 6 7 2 4 7 2 4 5 2 4 5 7 2 3 5 7 最后，f的长度达到4，因此答案为4。 注意，最后的f数组不一定是最长上升子序列的一个方案。 
#include <iostream>
#include <stdio.h>
using namespace std;
#define MAXN 10000
#define LARGE 999999
#define SMALL -999999
int minOfLen[MAXN];//
int arr[MAXN];
int len;
void init(){
	FILE *file=fopen("lis.in","r");
	fscanf(file,"%d\n",&len);
	for(int i=0;i<len;i++)
		fscanf(file,"%d",&arr[i]);
	fclose(file);
}
int findFirstLargerThan(int *a,int l,int r,int t);
int cal(){
	for(int i=0;i<len;i++)
		minOfLen[i]=LARGE;
	minOfLen[0]=SMALL;
	int s=0;//record the maxlength of lis
	for(int i=0;i<len;i++){
				int j=findFirstLargerThan(minOfLen,0,s+1,arr[i]);
				minOfLen[j]=arr[i];//用arr[i]取代原有的j长子序列最后一个元素
				if(j==s+1) s=s+1;	
	}
	for(int i=1;i<=s;i++) cout<<minOfLen[i]<<" ";cout<<endl;
	return s;
}
//前提条件：一定
int findFirstLargerThan(int *a,int l,int r,int t){
	if(l>r) return -1;//如果l>r,说明所有数都比t小,找不到第一个比t大的元素.但是显然a[len-1]=Large一定比t大.
	if(l==r) 
		return l;
	int mid=(l+r)/2;
	//严格二分：要么在mid左边包含mid，要么在mid右边不包含mid。
	if(a[mid]<=t)  return findFirstLargerThan(a,mid+1,r,t);
	else return findFirstLargerThan(a,l,mid,t);
}
int main(){
	init();
	cout<<cal()<<endl;
	return 0;
}
