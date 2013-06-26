#include <iostream>
#include <stdio.h>
#include <string.h>
#include <set>
#include <cmath>
#include <algorithm>
using namespace std;
#define loop(i,n) for(int i=0;i<n;i++)
#define soop(i,n,m) for(int i=n-1;i>=m;i--)
int next0(int n){
	char a[5];
	sprintf(a,"%d",n);
	int len=strlen(a),max,min;
	//sort
	loop(i,len) soop(j,len,i+1) if(a[j]<a[j-1]) {int tmp=a[j];a[j]=a[j-1];a[j-1]=tmp;}
	sscanf(a,"%d",&min);
	//revert
	loop(i,len/2){int tmp=a[i];a[i]=a[len-i-1];a[len-i-1]=tmp;}
	sscanf(a,"%d",&max);
	//result
	cout<<":"<<max<<":"<<min<<endl;
	return max-min;
}

int next(int n){
	int a[4];
	loop(i,4){
		a[i]=n%10;n/=10;
	}
	sort(a,a+4);
	int max=0,min=0;
	loop(i,4){
		max+=pow(10,i)*a[i];
		min*=10;min+=a[i];
	}
//	cout<<":"<<max<<":"<<min<<endl;
	return max-min;
}
void cnt(int n){
	set<int> set;
	set.insert(n);
	cout<<n;
	while(true){
		n=next0(n);
			cout<<"->"<<n;	
		if(set.find(n)!=set.end()) break;
		set.insert(n);
	}
	cout<<endl;
}
int main(){
	cnt(1234);
	return 1;
}
