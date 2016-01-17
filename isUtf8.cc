#include <iostream>
using namespace std;
bool isUTF8(const char* str){
   int i = 0;
   int n = strlen(str); 
   while(!str[i]){
     int j = i;
     char c = str[j];
     if(c & 0x80 == 0 || c & 0xc0 == 0x80){
        i ++;
     }else if(c & 0xe0 == 0xc0){
        if(j>= n-1 || str[j+1] & 0xc0 != 0x80) return false;
        i += 2;
     }else if(c & 0xf0 == 0xe0){
        if(j>= n-2 || str[j+1] & 0xc0 != 0x80 || str[j+2] & 0xc0 !=0x80) return false;
        i += 3;
     }else return false;
  }
  return true;
}
int main(){
 char buf[1000]="中国人";
 cout<<isUTF8(buf)<<endl;
 return 0;
}
