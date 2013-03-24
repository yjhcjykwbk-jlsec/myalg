#include <iostream>
using namespace std;
int res[1000];

int calc(int s,int base);
void init(){
	int a,b;
	cin>>a>>b;
	int len=calc(a,b);
	cout<<a<<"=";
	for(int i=len-1;i>=0;i--) {
		if(res[i]>9) {char c='A'+res[i]-10;cout<<c;}
		else  cout<<res[i];
	}
	cout<<"(base"<<b<<")"<<endl;
}
int calc(int s,int base){
	for(int i=0;i<1000;i++){
		res[i]=s%base;
		s/=base;
		if(res[i]<0) res[i]-=base,s+=1;
		if(s==0) return i+1;
	}
	return -1;
}
int main(){
		init();
	return 0;
}
