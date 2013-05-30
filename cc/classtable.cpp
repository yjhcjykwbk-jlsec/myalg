#include <stdio.h>
typedef void (*Fun)(void);//Fun是函数指针类型
class B{
	private :
		int a;
		virtual void f1(){
			printf("hello f1\n");
		}
		virtual void f2(){
			printf("hello f2 and a is %d\n",this->a);
			printf("this pointer is %x\n",this);
		}
		virtual void f3(){
			printf("hello f3\n");
		}
	public :
		B(int s):a(s){}
		void func(){ f2();}
};
void main(){
	B b(11);
	printf("this pointer is %x\n",&b);
	for(int i=0;i<3;i++){
		int *p=(int*)*(int *)(&b);//即int* p=（int*)b, p=b
		Fun pFun=(Fun)*(p+i);//b指向一个int数组
		//数组里每个int元素（*(p+i))又是一个函数指针（Fun）。
		pFun(); //难以理解b的this指针放在哪里
	}
	b.func();
}
 
