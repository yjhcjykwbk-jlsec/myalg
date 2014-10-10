#include <iostream>
#include <vector>
#include <assert.h>
#include <math.h>
using namespace std;

typedef long long int ll;
typedef pair<ll,ll> Pair;//@pair<int,ll> can overflow!!! should be pair<ll,ll>
#define MOD 1000000007
int dump(ll x,int a[]){
	int i=0;while(x>0){ a[i++]=x%10;x/=10; }
	if(i==0) a[0]=0,i=1;
	return i;
}
ll dp(ll x, int K){
	// return the count of number in [0~x) that f(number)=K
	if(x==0) return 0;
	int a[18];int len=dump(x,a);

	int minN=0-(len/2)*9,maxN=(len+1)/2*9;//0909.. 9090..
	int delta=0-minN,n=maxN-minN+1;
	//p[i][j][k] : delta+ (+/-)xi .... -x1 + x0 = k, xi = j
	vector<vector<vector<Pair> > > p(len,vector<vector<Pair> >(10,
				vector<Pair>(n,Pair(0,0))));

	//init
	for(int j=0;j<10;j++) p[0][j][j+delta]=Pair(1,j); //i=0. j=x0, x0+delta=k
	for(int i=0;i<len-1;i++){
		vector<Pair> cnt(n,Pair(0,0));
		for(int j=0;j<10;j++){
			for(int k=0;k<n;k++){
				Pair &s=p[i][j][k];
				cnt[k].first=(s.first+cnt[k].first)%MOD;
				cnt[k].second=(s.second+cnt[k].second)%MOD;
			}
		}
		// [i][k] => [i+1][j][k+(+/-)j]
		for(int j=0;j<10;j++){
			int fh=pow(-1,i+1);
			ll d=(ll)(pow(10,i+1)*j)%MOD;
			cout<<d<<endl;
			for(int k=0;k<n;k++){
				if(k+fh*j<0||k+fh*j>=n) continue;
				Pair &s=p[i+1][j][k+fh*j];
				s.first=cnt[k].first;
				assert(d<MOD);
				assert(s.first<MOD);
				s.second=(d*s.first%MOD+cnt[k].second)%MOD;
			}
		}
	}

	// count of number in [0~xm..x3x2x1x0] , where m<len
	ll num=0;
	//int b[len];
	for(int i=len-2;i>=0;i--){
		//b[i+1]=0;
		int j;
		int fh=pow(-1,i); 
		if(i==0) j=0;
		else j=1;
		//if(fh==1)  (k-delta)=K; else  -(k-delta)=K
		int k=fh*K+delta;
		assert(k>=0&&k<n);
		for(;j<10;j++){
			//b[i]=j;
			num=(num+p[i][j][k].second)%MOD;
		}
	}

	//count of number in [10000...00,x)
	ll s=0;
	int lst=0;
	int fh=pow(-1,len-1);
	for(int i=len-1;i>=0;i--){
		int j; 
		if(i==len-1) j=1;
		else j=0;
		int k=(K-lst)*fh+delta;
		assert(k>=0&&k<n);
		for(;j<a[i];j++){
			// lst+fh*(k-delta)=K, k=(K-lst)/fh+delta
			Pair &q=p[i][j][k];
			ll d=(q.second+s*q.first%MOD)%MOD;
			num=(num+d)%MOD;
		}
		lst+=pow(-1,i)*fh*a[i];
		// s+=pow(10,i)*a[i];@error: here will overflow!!!!
		s=(s+(ll)pow(10,i)*a[i])%MOD;
	}
	return num;
}
int main(){
	ll l,r;int k;
	cin>>l>>r>>k;
	ll x1=dp(l,k);
	ll x2=dp(r,k);
	ll cnt=(x2-x1)%MOD;
	int b[18];int len=dump(r,b);
	int fh=pow(-1,len-1);int kk=0;
	for(int i=len-1;i>=0;i--) kk+=fh*pow(-1,i)*b[i];
	if(kk==k) cnt++;
	cout<<(MOD+cnt)%MOD<<endl;
	return 0;
}
