#include <iostream.h>
class A{
 public :
  virtual void func(){
  	  cout<<"A"<<endl;
	  }};
class B: public A{
  public :
   virtual void func(){
   	 cout<<"B"<<endl;
	 }};
void test(A& a){
	a.A::func();
	a.func();
	}
void main(){
 B b;
 test(b);
 } 
