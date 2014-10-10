#include  "opencv2/opencv.hpp"
#include  "opencv2/objdetect.hpp"
#include  "opencv2/highgui.hpp"
#include  "opencv2/imgproc.hpp"
#include "opencv2/test.h"
#include <stdio.h>
#include <unistd.h>
#include "sys/wait.h"
#include <fstream>
#include <iostream>
using namespace std;
#define rep(i,n) for(int i=0;i<n;i++)
typedef long long int ll;
/*
 *test class override
 */
class father{
	public :
		int test(){return 1;}
		virtual int vtest(){return 1;}
};
class son:public father{
	public:
		int test(){return 2;}
		int vtest(){return 2;}
};
int test(father &f){
	return f.test();
}
int test(father *f){
	return f->test();
}
int vtest(father f,bool s){
	return f.vtest();
}
int vtest(father &f){
	return f.vtest();
}
int vtest(father *f){
	return f->vtest();
}
void test1(){
	cout<<"test 1 ####"<<endl;
	son a;
	printf("test c ####lass overwrite:%d,%d,%d\n",a.test(),test(a),test(&a));
	printf("vtest class override:%d,%d,%d\n",a.vtest(),vtest(a),vtest(&a));
	printf("vtest class override:%d\n",vtest(a,true));
}
/*
 * test pointer
 */
void test2(){
	cout<<"test 2 ####"<<endl;
	int b[2]={1,2};
	int *a=b;
	cout<<a[1]<<":"<<*(a+1)<<endl;
}
/*
 * test int and unsigned int's operator >
 * 要防止用int负数跟unsigned数进行比较
 * 否则int负数就会被当成unsigned数
 */
void test3(){
	cout<<"test 3 ####"<<endl;
	int a=-1;
	size_t b=1;
	cout<<"a=-1,b=unsigned 1"<<endl;
	cout<<"a>(size_t)b ? :"<<(a>b)<<endl<<"a>(int)b ?:"<<(a>(int)b)<<endl;
	vector<int> s={};
	//@ERROR: 
	//unsigned 0 -1 = unsigned ....
	//i<-1 overflow
	for(int i=0;i<(int)(s.size()-1);i++){
		s[i]=0;
	}
	for(int i=0;i<(int)s.size()-1;i++){
		s[i]=0;
	}
	//test overflow with ll
	cout<<"test overflow with ll"<<endl;
	cout<<"(ll)1999999999*1999999999:"<<endl;
	int x=1999999999;
	//(type)a*b,then a first be cast to type(a), then return type(a)*b
	//(type)(a*b),then a first * b, then return type(a*b)
	//(type) operator has a higher priority than (*,/,+,-)
	cout<<(ll)x*x<<":"<<x*x<<":"<<(ll)(x*x)<<endl;//3999999996000000001:-1356539903
}
/*
 * test stl vector and xxx_bound
 */
void test4(){
	cout<<"test 4 ####"<<endl;
	vector<int> s={5,4,3,2,1};
	vector<int>::iterator it=lower_bound(s.begin(),s.end(),7,greater<int>());
	cout<<"lower bound bigger than 7:"<<*it<<endl;
	it=lower_bound(s.begin(),s.end(),4,greater<int>());
	cout<<"lower bound bigger than 4:"<<*it<<endl;
	it=upper_bound(s.begin(),s.end(),4,greater<int>());
	cout<<"upper bound bigger than 4:"<<*it<<endl;
	it=lower_bound(s.begin(),s.end(),4,less<int>());
	cout<<"lower bound smaller than 4:"<<*it<<endl;
}
/*
 *test bit algorithm
 */
void test5(){
	cout<<"test 5 ####"<<endl;
	unsigned int a=((unsigned int)(~0))/2;
	int b=(~0)>>1;
	printf("%x:%x\n",a,b);
	int c=1<<2+3;
	cout<<"*****1<<2+3:"<<c<<endl;
	c<<=2;
	cout<<"c<<=2:"<<c<<endl;
	cout<<"~0:"<<~0<<endl;
	cout<<"0x7fffffff:"<<0x7fffffff<<endl;
	cout<<"0x80000000:"<<0x80000000<<endl;
	cout<<"(int)0x80000000:"<<(int)0x80000000<<endl;
}
/*
 * test stl map and list
 */
typedef list<int>::iterator It;
void display(list<int>& lst){
	for(It it=lst.begin();it!=lst.end();it++){
		cout<<*it<<" ";
	}cout<<endl;
}
void test6(){
	cout<<"test 6 ####"<<endl;
	map<int,int> s;
	s.erase(2);
	{
		list<int> l={1,2,3,4};
		It it=l.begin(),tmp;it++;it=++l.begin();
		cout<<*it<<endl;//2
		//@ERROR: l.begin()+n 
		//for list iterator don't support +/- n operation
		cout<<*(--it)<<endl;//1	
		cout<<*(++it)<<endl;//2
		l.erase(++l.begin());
		cout<<*it<<endl;//2
		l.clear();
		cout<<*it<<endl;//2

		it=l.begin();
		l.insert(it,1);
		cout<<"after insert 1:";
		cout<<*it<<endl;//当前ｉｔ还指向ｉｎｓｅｒｔ之前的l.begin,一个未初始化的ｎｏｄｅ，即xxxx未知数
		//ｉｔ亲手在自己背后插入一个值，又亲手删掉它,并ｉｔ始终指向原来的值
		tmp=it;
		cout<<*(++it)<<endl;
		cout<<*(++tmp)<<endl;


		it=l.begin();
		cout<<*it<<endl;
		l.insert(++(tmp=it),2);
		cout<<"after insert 2:";
		display(l);
		cout<<*(l.end())<<":"<<*(--l.end())<<endl;
		cout<<"after erase 1:";
		l.erase((tmp=it)++);//in fact, this equals l.erase(it), ++ not work
		display(l);
		// it=l.erase((tmp=it)++);//ｅｒａｓｅ后返回下一个节点，此处是l.end()
		// cout<<*it<<endl;//段错误

		cout<<"test insert begin/end"<<endl;
		l.clear();
		l.insert(l.begin(),1);
		display(l);	
		l.clear();
		l.insert(l.end(),1);
		display(l);	
		// l.erase(it);


		list<int> r={1,2,3,4};
		it=r.begin();
		//mem fault
		// cout<<"after erase it:"<<endl;
		// cout<<*it<<*(it++)<<endl;
		cout<<"reverse for loop and erase for list:"<<endl;
		for(it=--r.end();;it--){
			cout<<*(it)<<" ";
			r.erase(it++);
			if(it==r.begin()) break;
			//pagefault: 
			// cout<<*(it--)<<endl;//*(it--) may return end,and double it-- may make it to begin()-1 (overflow)
		}
		assert(r.empty());
	}

	{
		cout<<"vector:...."<<endl;
		vector<int> vec={5,4,4,3,4,2,5,2,1};
		vector<int>::iterator it=std::unique(vec.begin(),vec.end());
		vec.erase(it,vec.end());
		rep(i,vec.size()) cout<<vec[i]<<" ";cout<<endl;
		std::sort(vec.begin(),vec.end());
		it=std::unique(vec.begin(),vec.end());
		vec.erase(it,vec.end());
		rep(i,vec.size()) cout<<vec[i]<<" ";cout<<endl;
	}
}
/*
 * test cmp,sort,templates
 */
void test7(){
	cout<<"test 7 ####"<<endl;
	struct Cmp{
		bool operator ()(const int &a,const int &b){//const pair<cv::Rect,int> &l,const pair<cv::Rect,int> &r){
			return a<b;
		}
	}cmp;
	vector<int> a={3,4,2,1,5,0};
	std::sort(a.begin(),a.end(),cmp);
	rep(i,a.size()) cout<<a[i]<<" ";cout<<endl;
}
/*
 * test fstream fopen fread fwrite close
 */
void test8(){
	std::fstream f("tmp");
	// f<<"hello world"<<endl;
	
	string s;
	f>>s;
	cout<<s<<endl;//'hello'

	//@ERROR: here may invoke a memory corruption 
	//(string s)'s memory can be overflowed by f.getline
	char *tt=(char *)s.c_str();//const char * to char*
	f.getline(tt,100,'\n');

	cout<<tt<<endl;//' world'
	cout<<s<<endl;//' worl', string's size keep 5

	fstream g("tmp");
	char buf[10];
	g.getline(buf,10,'\n');
	cout<<buf<<endl;//'hello wor'
	g.getline(buf,10,'\n');
	cout<<buf<<endl;//''
}
/*
 *test procession
 */
void test9(){
	FILE *fp=fopen("test9","wr");
	if(fp==NULL) return;
	char *s1="hello world",*s2="hello londan";
	fprintf(fp,"%s\n",s1);

	int c=-9;
	c=fork();
	if(c==-1) return;
	else if(c==0) cout<<"i am child"<<endl;
	else cout<<"i am father and just forked a son:"<<c<<endl;
	// cout<<c<<":"<<" add s2 to outstream"<<endl;
	// fprintf(fp,"%s\n",s2);

	//father code
	if(c!=0) {
		int status=0;
		rep(i,1000000);
		cout<<"wait for son to exit"<<endl;
		int sid=wait(&status);
		cout<<"my son "<<sid<<" exited some time ago"<<endl;
	}
	//son code
	else{
		cout<<"son exit.."<<endl;
		exit(0);
		cout<<"son still alive?"<<endl;
	}
	fclose(fp);
	return;
}

/**
 * test string
 */
void test10(){
	string s="helloworld";
	char buf[100];
	strcpy(buf,s.c_str());
	cout<<buf<<endl;
}

/*
 * test math
 */
void test11(){
	ll x=pow(10,18);
	cout<<"pow 10,18:";
	cout<<x<<endl;
}
int main(){
	// printf("hello world:%d\n",hello());
	// test2();
	test3();
	// test4();
	// test5();
	// test6();
	// test7();
	// test8();
	// test9();//s1 s2 s1 s2
	// test10();
	// test11();
	return 0;
}
