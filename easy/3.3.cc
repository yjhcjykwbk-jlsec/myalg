#include <stdio.h>
#include <iostream>
#include <string.h>
#include <ctype.h>
using namespace std;
char buf[1000];
char sbuf[1000];
int  s[1000];
void init()
{
  fgets(buf,1000,stdin);
  int i,j;
  for(i=0,j=0;buf[i]!='\0';i++){
	if(isalpha(buf[i])) {
	  if(buf[i]<='Z'&&buf[i]>='A') 
		sbuf[j]=buf[i]+32;
	  else sbuf[j]=buf[i];
	  s[j++]=i;
	}
  }
  sbuf[j]=0;
}
int main(){
  init();
  int len=strlen(sbuf);
  int max=0;
  int p=-1,q=-1;
  for(int i=0;i<len;i++){//i~Len-1,找到回文 
	int l=(i+len-1)/2;
	int r=(i+len-1)-l;
	while(l>=i){
	  if(sbuf[l]==sbuf[r]){
		if(r-l+1>max) {max=r-l+1;p=s[l];q=s[r];}
	  } 
	  else break;
	  l--;r++;
	}
  }
  for(int i=0;i<len-1;i++){//0~i,找到回文 
	int l=(i+0)/2; //左中点下标
	int r=(i+0)-l;//右中点下标
	while(r<=i){
	  if(sbuf[l]==sbuf[r]){
		if(r-l+1>max) {max=r-l+1;p=s[l];q=s[r];}
	  } 
	  else break;
	  l--;r++;
	}
  }
  if(max>0){
	cout<<max<<endl;
	for(int i=p;i<q+1;i++) cout<<buf[i];
  }
  cout<<endl;
  return 0;
}
