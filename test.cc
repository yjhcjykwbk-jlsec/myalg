#include <iostream>
#include <string.h>

using namespace std;
int main(){
	int a[10];
	memset(a,-1,sizeof(a));
	cout<<a[5]<<endl;
	return 0;
}
