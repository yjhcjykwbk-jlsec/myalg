#include<iostream>
using namespace std;
int main(){
int x = 1;int y = 2;
int* const px = &x;
//px = &y;
typedef char * pStr;
char string[4] = "bbc";
const char *p1 = string; //1å¼
const pStr p2 = string; //2å¼
p1++;
//p2++;
return 0;
}
