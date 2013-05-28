#include <iostream>
using namespace std;
class A{
public: int a;
public: 
A(int x):a(x){cout<<"(A::construct1) "<<endl;}
A(){a=99;cout<<"(A::construct0) "<<endl;}
virtual void f() { cout<<"(A::f,my a is:"<<a<<endl; } 
virtual void f() const { cout<<"A::f const) my a is"<<a<<endl; } 
void t() const { cout<<"(A::t const) my a is:"<<a<<endl; }
void trouble(){ cout<<"(A::trouble) ";this->f();}//这个f也是可以多态的
};
class B:public A{
public: int a;
public: 
B(int x):a(x){cout<<"(B::construct) "<<endl;}
virtual void f() { cout<<"(B::f) my a is:"<<a<<" and my base's a is:"<<A::a<<endl; } 
virtual void f() const { cout<<"(B::f const) my a is:"<<a<<" and my base's a is:"<<A::a<<endl; }
void t() const { cout<<"(A::t const) my a is:"<<a<<" and my base's a is:"<<A::a<<endl;}
};
void g(const A* a){ a->f();}
int main(){ 
cout<<"首先强调:调用的是哪个子类(包括基类)的函数，就使用哪个子类的变量"<<endl;
A *b = new B(12); 
cout<<"//测试调用重载函数"<<endl;
b->f(); 
cout<<"//测试基类函数语句里调用子类重载函数"<<endl;
b->trouble();
cout<<"//测试调用const的重载函数"<<endl;
g(b); 
cout<<"//测试调用非重载函数"<<endl;
const A*c = new B(12); 
c->t();
return 0;
}
//B::f
//B::f const
