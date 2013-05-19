#include <iostream>
using namespace std;
class A{public: 
virtual void f() { cout<<"A::f"<<endl; } 
virtual void f() const { cout<<"A::f const"<<endl; }};

class B:public A{public: 
virtual void f() { cout<<"B::f"<<endl; } 
virtual void f() const { cout<<"B::f const"<<endl; }};

void g(const A* a){ a->f();}
int main(){ 
A *b = new B(); 
b->f(); 
g(b); 
return 0;
}
