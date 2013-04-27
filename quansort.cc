#include <iostream>
#include <algorithm>
using namespace std;
void swap(int *arr,int a,int b){ int t=arr[a];arr[a]=arr[b];arr[b]=t;}
inline void reverse(int *arr,int a,int b){  
			int mid=(a+b+1)/2;
			for(int i=a;i<mid;i++) swap(arr,i,a+b-i);
}
bool next(int *arr,int n){
	int i;
	for(i=n-1;i>=1;i--)
		if(arr[i]>arr[i-1])
			break;
	if(i==0) return false;
	else{
		int j; 
		for(j=i;j<n-1;j++) 
			if(arr[j+1]<arr[i-1]) break;
		swap(arr,i-1,j);
		reverse(arr,i,n-1);
		}
	return true;
}
int main(){
	int a[10]={1,2,3,4};
	int num=1;
	int N=4;
	while(true){
		for(int i=0;i<N;i++) cout<<a[i];cout<<endl;
		if(!next(a,N)) break;
		num++;
	}
cout<<"total:"<<num<<endl;
	return 0;
}
