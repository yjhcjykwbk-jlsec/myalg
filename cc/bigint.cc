#include <iostream>
#include <string>
#include <string.h>
using namespace std;
#define MAXN 1000
struct BigInt{
	char s[MAXN];
	int len;
	//拷贝构造函数，如果不自定义该函数，默认情况下编译器直接进行内存拷贝
	BigInt(const BigInt& t){
		cout<<"BigInt(const BigInt &):"<<this<<endl;
		len=t.len;
		for(int i=0;i<len;i++) s[i]=t.s[i];
//		*this=t;//拷贝构造函数调用赋值函数很危险，
				//因为赋值函数如果return*this，反过来调用拷贝函数
				//则会形成循环调用
	}	
	//构造
	BigInt(){
		cout<<"BigInt():"<<this<<endl;
		memset(s,0,sizeof(s));len=1;
	}
	BigInt(const char *str){
		cout<<"BigInt(const char*):"<<this<<endl;
		*this=str;
	}
	//析构
	~BigInt(){
		cout<<"~BigInt():"<<this<<endl;
	}
	//赋值
	//该赋值函数可以不用自定义，默认情况编译器会调用系统默认拷贝构造函数完成赋值
	void operator = (const BigInt &t){
		cout<<"=(BigInt)"<<endl;
		*this=t.str();
	}
	//试着将返回值换成void
	void operator = (const char *str){
		cout<<"=(const char*)"<<endl;
		len=strlen(str);
		for(int i=0;i<len;i++) s[i]=str[len-i-1]-'0';
		cout<<"~=(const char*)"<<endl;
//		return *this;//return *this将会调用拷贝构造函数
	}
	void operator = (const string& s){
		cout<<"=(const string&)"<<endl;
		*this=s.c_str();
		cout<<"~=(const string&)"<<endl;
//		return *this;
	}
	void operator +=(const BigInt &b){
		cout<<"+=(const BigInt&)"<<endl;
		*this=*this+b;
		cout<<"~+=(const BigInt&)"<<endl;
	}
	BigInt operator +(const BigInt &b){
		cout<<"+(const BigInt&)"<<endl;
		BigInt c;
		int x=0,i;
		for(i=0;i<max(len,b.len)||x;i++){
			if(i<len) x+=s[i];
			if(i<b.len) x+=b.s[i];
			c.s[i]=x%10;
			x=x/10;
		}
		c.len=i;
		cout<<"~+(const BigInt&)"<<endl;
		return c;
	}	
	//类型转换
	string str() const{
		string str="";
		for(int i=len-1;i>=0;i--)
			str=str+(char)('0'+s[i]);
		if(str=="") str="0";
		return str;
	}
	friend ostream & operator << ( ostream &os,const BigInt &t){
	  os<<t.str();
	  return os;
	}
};
int main(){
	cout<<"1:"<<endl;
	BigInt a="1234567724234325234524532251414132";
	cout<<"2:"<<endl;
	BigInt b=a;
	cout<<b<<endl;
	cout<<"3:1"<<endl;
	BigInt c;
	cout<<"3.2:"<<endl;
	c=a;
	cout<<c<<endl;
	cout<<"4:"<<endl;
	BigInt d;
	d+=a;
	cout<<d<<endl;
	cout<<"5:"<<endl;
	return 1;
}
