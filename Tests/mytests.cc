// #include  "opencv2/opencv.hpp"
// #include  "opencv2/objdetect.hpp"
// #include  "opencv2/highgui.hpp"
// #include  "opencv2/imgproc.hpp"
// #include "opencv2/test.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <algorithm>
#include <string.h>
#include <list>
#include <vector>
#include <stack>
#include <map>
#include <unistd.h>
#include <queue>
#include "sys/wait.h"
using namespace std;
#define rep(i,n) for(int i=0;i<n;i++)
#define MOD 1000000007
typedef long long int ll;

/**
 * base
 */
class TestBase{
  public:
    virtual void test(){
      cout<<"#### default test()"<<endl;
    }
};


/**
 *test class override
 */
class father{
  public :
    int t = 1;
    int test(){return 1;}
    virtual int vtest(){return 1;}
    virtual int vtest2(){return t;}
};
class son:public father{
  public:
    int t = 2;
    int test(){return 2;}
    int vtest(){return 2;}
};
class OverideTest: TestBase{
  public:
    int test(father f, bool s){
      return f.test();
    }
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
    int vtest2(father *f){
      return f->vtest2();
    }
    void test(){
      cout<<"test 1 ####"<<endl;
      son a;
      printf("test class overwrite:%d,%d,%d,%d\n",test(a, true), a.test(),test(a),test(&a));
      printf("vtest class override:%d,%d,%d,%d\n", vtest(a,true),a.vtest(),vtest(a),vtest(&a));
      printf("vtest2:%d\n",vtest2(&a));
    }
};


/**
 * test pointer and array
 * http://www.cnblogs.com/chengxin1982/archive/2009/01/13/1374575.html
 */
class ArrayPointerTest{
  public:
    // pointer 
    // sizeof
    void test(){
      {
        int b[2]={1,2};
        int *a=b;
        cout<<a[1]<<":"<<*(a+1)<<endl;
      }
      {
        double* (*a)[3][6]; 
        cout<<"double* (*a)[3][6]"<<endl; 
        cout<<"sizeof(a):"; // 4 a为指针
        cout<<sizeof(a)<<endl; // 4 a为指针
        cout<<"sizeof(*a):"; // 72 *a为一个有3*6个指针元素的数组
        cout<<sizeof(*a)<<endl; // 72 *a为一个有3*6个指针元素的数组
        cout<<"sizeof(**a):"; // 24 **a为数组一维的6个指针
        cout<<sizeof(**a)<<endl; // 24 **a为数组一维的6个指针
        cout<<"sizeof(***a):"; // 4 ***a为一维的第一个指针
        cout<<sizeof(***a)<<endl; // 4 ***a为一维的第一个指针
        cout<<"sizeof(****a):"; // 8 ****a为一个double变量
        cout<<sizeof(****a)<<endl; // 8 ****a为一个double变量
      }
      {
        double* *a[3][6]; 
        cout<<"double**a[3][6]"<<endl; 
        cout<<"sizeof(a):"; // 4 a为指针
        cout<<sizeof(a)<<endl; // 4 a为指针
        cout<<"sizeof(*a):"; // 72 *a为一个有3*6个指针元素的数组
        cout<<sizeof(*a)<<endl; // 72 *a为一个有3*6个指针元素的数组
        cout<<"sizeof(**a):"; // 24 **a为数组一维的6个指针
        cout<<sizeof(**a)<<endl; // 24 **a为数组一维的6个指针
        cout<<"sizeof(***a):"; // 4 ***a为一维的第一个指针
        cout<<sizeof(***a)<<endl; // 4 ***a为一维的第一个指针
        cout<<"sizeof(****a):"; // 8 ****a为一个double变量
        cout<<sizeof(****a)<<endl; // 8 ****a为一个double变量
      }
    }
};


/**
 * test int and unsigned int's operator >
 * 要防止用int负数跟unsigned数进行比较
 * 否则int负数就会被当成unsigned数
 */
class UnsignedIntTest{
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
    ll st=x*x;
    cout<<(ll)x*x<<":"<<x*x<<":"<<(ll)(x*x)<<":"<<st<<endl;//3999999996000000001:-1356539903
  }
};


/**
 * test stl vector and xxx_bound
 */
struct Cmp1{
  bool operator() (int a, int b){ return a<b; }
}cmp1;
struct Cmp2{
  bool operator() (int a, int b){ return a<=b; }
}cmp2;
class VectorBoundTest{
  public:
    void test4(){
      cout<<"test 4 ####"<<endl;
      vector<int> s={5,4,3,2,1};
      vector<int>::iterator it=lower_bound(s.begin(),s.end(),7,greater<int>());
      cout<<"lower bound bigger than 7:"<<*it<<endl;
      it=lower_bound(s.begin(),s.end(),4,greater<int>());
      cout<<"lower bound bigger than 4:"<<*it<<endl;
      it=upper_bound(s.begin(),s.end(),4,greater<int>());//
      cout<<"upper bound bigger than 4:"<<*it<<endl;
      it=lower_bound(s.begin(),s.end(),4,less<int>());// ?
      cout<<"lower bound smaller_or_eq than 4:"<<*it<<endl;
      vector<int> t={1,2,4,5};
      it=lower_bound(t.begin(),t.end(),3,less<int>());// 4
      cout<<"lower bound smaller_or_eq than 3:"<<*it<<endl;
      it=lower_bound(t.begin(),t.end(),4,less<int>());// 4
      cout<<"lower bound smaller_or_eq than 4:"<<*it<<endl;
      it=lower_bound(t.begin(),t.end(),14,less<int>());// 0 (the end)
      cout<<"lower bound smaller_or_eq than 14:"<<*it<<":"<<(it==t.end())<<endl;
      it=upper_bound(t.begin(),t.end(),3,less<int>());// 4
      cout<<"upper bound bigger than 3:"<<*it<<endl;
      it=upper_bound(t.begin(),t.end(),4,less<int>());// 5
      cout<<"upper bound bigger than 4:"<<*it<<endl;
      it=upper_bound(t.begin(),t.end(),14,less<int>());// 0 (the end)
      cout<<"upper bound bigger than 14:"<<*it<<":"<<(it==t.end())<<endl;

      cout<<"lower_bound(..,x) return the first y that meet cmp(y,x)==false, which means y!<x "<<endl;
      cout<<"upper_bound(..,x) return the first y that meet cmp(x,y)==true, which means x<y, or y>x"<<endl;
      cout<<"test cmp1,cmp2:"<<endl;
      it=lower_bound(t.begin(),t.end(),4,cmp1);
      cout<<"lower bound smaller_or_eq than 4:"<<*it<<endl;// 4
      it=lower_bound(t.begin(),t.end(),4,cmp2);
      cout<<"lower bound smaller_or_eq than 4:"<<*it<<endl;// 5
      it=upper_bound(t.begin(),t.end(),4,cmp1);
      cout<<"upper bound bigger than 4:"<<*it<<endl;// 4
      it=upper_bound(t.begin(),t.end(),4,cmp2);
      cout<<"upper bound bigger than 4:"<<*it<<endl;// 5
    }
};


/**
 *test bit algorithm
 */
class BitTest{
  public:
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
};


/**
 * test stl map and list
 */
class MapIteratorTest{
  public:
    typedef list<int>::iterator It;
    static void display(list<int>& lst){
      for(It it=lst.begin();it!=lst.end();it++){
        cout<<*it<<" ";
      }cout<<endl;
    }
    void test(){
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
          // cout<<*(it--)<<endl;//**(it--) may return end,and double it-- may make it to begin()-1 (overflow)
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
};


/**
 * test cmp,sort,templates
 */
class CmparatorTest{
  public:
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
    };


    /**
     * test fstream fopen fread fwrite close
     */
    class FstreamTest{
      public:
        void test8(){
          std::fstream f("tmp");
          f<<"hello world"<<endl;

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
    };


    /**
     *test procession
     */
    class ThreadTest: public TestBase{
      public:
        void test(){
          FILE *fp=fopen("test9","wr");
          if(fp==NULL) return;
          const char *s1="hello world",*s2="hello londan";
          fprintf(fp,"%s\n",s1);

          int c[4];
          for(int i = 0; i<4; i++){
            sleep(2);
            c[i]=fork();
            if(c[i]==-1) return;
            else if(c[i]==0) cout<<"i am child "<<i<<":"<<getpid()<<endl;
            else cout<<"i am father "<<getpid()<<" and just forked a son:"<<c[i]<<endl;
            // cout<<c<<":"<<" add s2 to outstream"<<endl;
            // fprintf(fp,"%s\n",s2);

            //son code
            if(c[i]==0) {
              sleep(5);
              cout<<"son "<<i<<":"<<getpid()<<" exit.."<<endl;
              exit(0);
              cout<<"son still alive?"<<endl;
            }
          }

          if(c[0]!=0) {
            int status=0;
            cout<<"i am father "<<getpid()<<" and wait for son to exit"<<endl;
            for(int i = 0 ; i< 4; i++)
            {
              // int sid=wait(&status);
              int sid=waitpid(c[i], &status, 0);
              cout<<"my son "<<sid<<" exited some time ago"<<endl;
            }
          }
          fclose(fp);
          return;
        }
    };


    /**
     * test string
     */
    class StringTest: public TestBase{
      public:
        void test(){
          string s="helloworld";
          char buf[100];
          strcpy(buf,s.c_str());
          cout<<buf<<endl;
          char *s1="hello world",*s2="hello londan";
          ////segmentation fault
          //s1[0] = 'f';
          cout<<s1<<endl;
        }
    };


    /**
     * test queue
     */
    class QueueTest{
      public:
        void test11(){
          vector <int> a= { 4,5,2,3,1};
          sort(a.begin(), a.end(), less<int>());
          priority_queue<int, vector<int>, less<int> > que;
          que.push(3); que.push(2); que.push(9); que.push(5); que.push(0);
          for(int i = 0; i<(int) a.size(); i++){
            cout<<a[i]<<" ";
          }cout<<endl;
          while(!que.empty()){
            int s = que.top(); que.pop();
            cout<<s<<" ";
          }cout<<endl;
        }
    };


    /**
     * test stack
     */
    class StackTest: public TestBase{
      public:
        void test(){
          cout<<"test stack without exception?"<<endl;
          stack<int> a;
          a.pop();
          a.pop();
          cout<<a.top()<<endl;//this would invoke a segmentation fault
        }
    };


    /**
     * test memory
     */
    #include <sys/types.h>
    #include <sys/ipc.h>
    #include <sys/shm.h>
    char arr[1000];
    class MemTest: public TestBase{
      public:
        void test(){
          int shmid;
          char *p,*sp;
          printf("static arr from %x to %x\n",&arr[0],&arr[1000]);//arr在static段中
          printf("stack top  %x\n",&shmid); //shmid在栈顶
          if((p=(char*)malloc(1000))==NULL){
            cout<<1<<endl;}
          printf("heap %x\n",p);//malloc在堆上
          if((shmid=shmget(IPC_PRIVATE,1000,SHM_R|SHM_W))<0){
            cout<<1<<endl;}
          if((sp=(char*)shmat(shmid,0,0))==NULL){
            cout<<1<<endl;}
          printf("shared memory %x to %x\n",sp,sp-1000);//共享内存段附加在了进程栈下面
          if(shmctl(shmid,IPC_RMID,0)<0){
            cout<<4<<endl;}
          cout<<0<<endl;
        }
    };


    /**
     * 更多c++模板用法，见
     * http://www.cnblogs.com/stephen-liu74/category/335657.html
     */
    template <typename T>
      class Decorator{
        public:
          static void test(){
            cout<<"######################"<<endl
              <<typeid(T).name()<<":"<<endl;
            T t;
            t.test();
          }
      };


    int main(){
      // printf("hello world:%d\n",hello());
      Decorator<ArrayPointerTest>::test();
      Decorator<OverideTest>::test();
      Decorator<StringTest>::test();
      Decorator<MemTest>::test();
      Decorator<ThreadTest>::test();
      //VectorBoundTest::test4();
      // test5();
      // test6();
      // test7();
      // test8();
      // test9();//s1 s2 s1 s2
      // test10();
      // test11();
      Decorator<StackTest>::test();
      return 0;
    }
