#include <iostream>
#include <stdio.h>
#define loop(n) for(int n=0;;n++)
using namespace std;
int main(){
	int x1,x2,x3;
	loop(x2){
		if(4*x2>12)break;
		loop(x1){
			if(4*x2+3*x1>12)break;
			loop(x3){
				if(4*x2+3*x1+2*x3>12)break;
				printf("(%d,%d,%d), ",x1,x2,x3);
			}
		}
	}
	return 0;
}
