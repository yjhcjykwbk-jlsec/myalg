#include <iostream>
#include <string.h>
#include <queue>
using namespace std;
int a[7][7];
struct ele{
	bool init(){
		cin>>a[0][2];
		if(a[0][2]==0) return false;
		cin>>a[0][4];
		cin>>a[1][2]>>a[1][4];
		for(int i=0;i<7;i++) cin>>a[2][i];
		cin>>a[3][2]>>a[3][4];
		for(int i=0;i<7;i++) cin>>a[4][i];
		cin>>a[5][2]>>a[5][4];
		cin>>a[6][2]>>a[6][4];
		return true;
	}
	void print(int a[][7]){
		cout<<"##"<<a[0][2]<<"#"<<a[0][4]<<"##"<<endl;
		cout<<"##"<<a[1][2]<<"#"<<a[1][4]<<"##"<<endl;
		for(int i=0;i<7;i++) cout<<a[2][i];cout<<endl;
		cout<<"##"<<a[3][2]<<"#"<<a[3][4]<<"##"<<endl;
		for(int i=0;i<7;i++) cout<<a[4][i];cout<<endl;
		cout<<"##"<<a[5][2]<<"#"<<a[5][4]<<"##"<<endl;
		cout<<"##"<<a[6][2]<<"#"<<a[6][4]<<"##"<<endl;
	}
	void turn(int a[][7],int x){
		int t;
		switch(x){
			case(0):
				t=a[0][2];
				for(int i=1;i<7;i++) a[i-1][2]=a[i][2];
				a[6][2]=t;
				break;
			case(1):
				t=a[0][4];
				for(int i=1;i<7;i++) a[i-1][4]=a[i][4];
				a[6][4]=t;
				break;
			case(5)://F
				t=a[6][2];
				for(int i=6;i>=1;i--) a[i][2]=a[i-1][2];
				a[0][2]=t;
				break;
			case(4)://E
				t=a[6][4];
				for(int i=6;i>=1;i--) a[i][4]=a[i-1][4];
				a[0][4]=t;
				break;
			case(2)://c
				t=a[2][6];
				for(int i=6;i>=1;i--) a[2][i]=a[2][i-1];
				a[2][0]=t;
				break;
			case(3)://D
				t=a[4][6];
				for(int i=6;i>=1;i--) a[4][i]=a[4][i-1];
				a[4][0]=t;
				break;
			case(7)://7
				t=a[2][0];
				for(int i=1;i<7;i++) a[2][i-1]=a[2][i];
				a[2][6]=t;
				break;
			case(6)://7
				t=a[4][0];
				for(int i=1;i<7;i++) a[4][i-1]=a[4][i];
				a[4][6]=t;
				break;
			default:cout<<"error:"<<x<<endl;
		}
	}
	int is(int s[],int time){
		int tmp[7][7];
		memcpy(tmp,a,sizeof(a));
		for(int i=0;i<time;i++)
			turn(tmp,s[i]);	
		int t=tmp[2][2];
		if(tmp[4][2]!=t||tmp[4][3]!=t||tmp[4][4]!=t) return 0;
		if(tmp[2][3]!=t||tmp[2][4]!=t||tmp[3][2]!=t||tmp[3][4]!=t) return 0;
		return t;
	}
	bool next(int s[],int time){
		for(int i=time-1;i>=0;i--)
			if(s[i]<7){
				s[i]+=1;
				for(int j=i+1;j<time;j++) 
					s[j]=0;
				return true;
			}
		return false;
	}
};
bool solve(){
	ele e;
	if(!e.init()) return false;
	int s[100];
	for(int i=0;i<100;i++){
		memset(s,0,i*sizeof(int));
		while(true){
			int t;if((t=e.is(s,i)))
			{
				if(i==0) cout<<"No moves needed"<<endl;
				else{for(int j=0;j<i;j++) cout<<(char)('A'+s[j]);cout<<endl;}
				cout<<t<<endl;
				return true;
			}
			if(!e.next(s,i)) break;
		}
	}
	return false;
}
int main(){
	while(solve());
	return 0;
}


