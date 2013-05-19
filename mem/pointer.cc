#include <iostream>
using namespace std;
int main(){
int a=999;
int * p=&a;
cout<<p<<":"<<*p<<endl;
//int * p1;*p1=a;
//cout<<p1<<":"<<*p1<<endl;
int * p2;p2=&a;
cout<<p2<<":"<<*p2<<endl;
return 0;
}
