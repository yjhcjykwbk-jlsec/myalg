//fib 示例函数
#include <iostream>
#include <string.h>
using namespace std;
struct BigInt{
	int len;int a[1000];
	public :
	BigInt operator +(const BigInt &s);
	void operator +=(const BigInt &s);
	BigInt operator +(int s);
	BigInt operator *(const BigInt &s);
	BigInt operator *(int s);
	BigInt();//默认构造函数0
	BigInt(int s);//默认构造函数1
	//赋值和拷贝构造函数
	BigInt(const BigInt& s);
	//BigInt operator =(const BigInt &s);
	friend ostream & operator <<(ostream &os,const BigInt &s);
	//调整函数
	void adjust(){ int c=0,i;for(i=0;i<len||c>0;i++) {if(i<len) c+=a[i];a[i]=c%10,c/=10;} len=i; }
};
BigInt::BigInt(){
	len=1;memset(a,0,sizeof(a));
}

BigInt::BigInt(int s){
	memset(a,0,sizeof(a));
	a[0]=s;len=1;
	adjust();
}

BigInt::BigInt(const BigInt& s){
	len=s.len;memset(a,0,sizeof(a));
	for(int i=0;i<len;i++) a[i]=s.a[i];
}

BigInt BigInt::operator +(const BigInt &s){
	BigInt tmp;
	int min=len<s.len?len:s.len;int c=0;
	int max=len>s.len?len:s.len;int i;
	for(i=0;i<min;i++)
		c=c+a[i]+s.a[i],tmp.a[i]=c%10,c/=10;
	for(i=min;i<max||c>0;i++){
		if(i<max){
			if(len>s.len) c+=a[i];
			else c+=s.a[i];
		}
		tmp.a[i]=c%10,c/=10;
	}
	tmp.len=i;
	return tmp;
}

BigInt BigInt::operator +(int s){
	BigInt tmp(*this);
	tmp.a[0]+=s;
	tmp.adjust();
	return tmp;
}

void BigInt::operator +=(const BigInt &s){
	int min=len<s.len?len:s.len;int c=0;
	int max=len>s.len?len:s.len;int i;
	for(i=0;i<min;i++)
		c=c+a[i]+s.a[i],a[i]=c%10,c/=10;
	for(i=min;i<max||c>0;i++){
		if(i<s.len)  c+=s.a[i];
		else if(i<len) c+=a[i];
		a[i]=c%10,c/=10;
	}
	len=i;
}

BigInt BigInt::operator *(const BigInt &s){
	BigInt tmp;
	for(int i=0;i<len;i++)
		for(int j=0;j<s.len;j++)
			tmp.a[i+j]+=a[i]*s.a[j];
	tmp.len=len+s.len-1;
	tmp.adjust();
	return tmp;
}
		

BigInt BigInt::operator *(int s){
	BigInt tmp(*this);
	for(int i=0;i<len;i++)
		tmp.a[i]*=s;
	tmp.adjust();
	return tmp;
}


ostream & operator <<(ostream &os,const BigInt &s){
	for(int i=s.len-1;i>=0;i--)
		os<<s.a[i];
	return os;
}
BigInt a[2][2]={{0,1},{1,2}};
BigInt b[2][2]={{1,1},{1,2}};
BigInt c[2][2];
BigInt d[2][2]={{1,0},{0,1}};

void set(BigInt a[][2],BigInt b[][2]){
	for(int i=0;i<2;i++)
		for(int j=0;j<2;j++)
			a[i][j]=b[i][j];
}
void play(BigInt a[][2]){
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			cout<<a[i][j]<<'\t';
		}cout<<endl;
	}
}
void multi(BigInt a[][2],BigInt b[][2],BigInt c[][2]){
	BigInt tmp[2][2];
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			for(int k=0;k<2;k++) tmp[i][j]+=b[i][k]*c[k][j];
		}
	}
//	play(b);cout<<"*"<<endl;play(c);cout<<"="<<endl;play(tmp);
	set(a,tmp);
}
BigInt getFib(int n){
	//从0，1，2，3->n,n+1,n+2,n+3 需要 (n-0)/2 
	int ss[100],i;
	bool qi=n%2!=0;
	n/=2;
	for(i=0;i<100&&n>0;i++)
	{
		if(n%2>0) ss[i]=1;
		else ss[i]=0;
		n/=2;
	}
	set(c,d);
//	for(int j=i-1;j>=0;j--) cout<<ss[j]<<" ";cout<<endl;
//	cout<<"j="<<i-1<<"->"<<0<<" c="<<endl;
	for(int j=i-1;j>=0;j--){
		if(ss[j]>0) multi(c,b,c);
		if(j!=0) multi(c,c,c);
//		play(c);
//		cout<<"- - - - - -"<<endl;
	}	
	multi(c,a,c);
	if(qi) return c[0][1];
	return c[0][0];
}
int main(){
	int n;while(cin>>n&&n>=0){
		cout<<getFib(n)<<endl;
//		cout<<"==================="<<endl;
	}
	return 0;
}
