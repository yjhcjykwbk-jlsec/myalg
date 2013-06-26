//5.1.3周期串
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int main(){
	char s[100];
	scanf("%s",s);
	cout<<s<<endl;
	int i,j;
	for(i=1;i<=strlen(s);i++){
	  if(strlen(s)%i==0){
		  for(j=i;j<strlen(s);j++)
			  if(s[j%i]!=s[j]) break;
		  if(j>=strlen(s)) {cout<<i<<endl;return 0;}
	  }
	}
	return 0;
}
