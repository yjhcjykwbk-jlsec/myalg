#include<iostream>
using namespace std;
class A{
public:A(){
	cout<<"A"<<endl;
	foo();
}virtual void foo(){
	cout<<"A.foo"<<endl;
}};class B:public A{
public:B(){
	cout<<"B"<<endl;
	foo();
} void foo(){
	cout<<"B.foo"<<endl;
}};class C:public B{
public:C(){
	cout<<"C"<<endl;
	foo();
} void foo(){
	cout<<"C.foo"<<endl;
}};
int main(){
C*cp=new C;
cout<<"then......"<<endl;
cp->foo();
return 0;
}
//A
//A.foo
//B
//B.foo
//C
//C.foo
//then......
//C.foo
//
