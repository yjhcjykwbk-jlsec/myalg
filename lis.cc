//��lis��nlogn˼����lis��nlogn˼�롣f��ʾ����Ϊi���������������һ������С�Ƕ��١���Ȼ����f�ǵ����ġ� ����һ���µ���x���ҵ�ĳ��iʹ��x>f[i]��x<=f[i+1]��������xȥ����f[i+1]���ر�أ�������е�f[i]��С��x��������f�ĳ��ȡ� ���f�����ж೤�����ˡ� ����f���������Բ���iʱ�����ö��ֲ��ң����ʱ�临�Ӷ�ΪO(nlogn)�� �ٸ����ӣ���������Ϊ 3 2 8 6 7 4 5 7 3����f����ı仯�������£� 3 2 2 8 2 6 2 6 7 2 4 7 2 4 5 2 4 5 7 2 3 5 7 ���f�ĳ��ȴﵽ4����˴�Ϊ4�� ע�⣬����f���鲻һ��������������е�һ�������� 
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
				minOfLen[j]=arr[i];//��arr[i]ȡ��ԭ�е�j�����������һ��Ԫ��
				if(j==s+1) s=s+1;	
	}
	for(int i=1;i<=s;i++) cout<<minOfLen[i]<<" ";cout<<endl;
	return s;
}
//ǰ��������һ��
int findFirstLargerThan(int *a,int l,int r,int t){
	if(l>r) return -1;//���l>r,˵������������tС,�Ҳ�����һ����t���Ԫ��.������Ȼa[len-1]=Largeһ����t��.
	if(l==r) 
		return l;
	int mid=(l+r)/2;
	//�ϸ���֣�Ҫô��mid��߰���mid��Ҫô��mid�ұ߲�����mid��
	if(a[mid]<=t)  return findFirstLargerThan(a,mid+1,r,t);
	else return findFirstLargerThan(a,l,mid,t);
}
int main(){
	init();
	cout<<cal()<<endl;
	return 0;
}
