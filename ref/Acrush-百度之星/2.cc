////////////////////#2 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 

//buf 
const int bufsize=128*1024; 
int bufL,bufP; 
char buf; 
//segments 
const int maxn=1000005; 
int n; 
unsigned int A[maxn],B[maxn]; 
//sort 
const int countsize=65536; 
int arcA[maxn],arcB[maxn],turnB[maxn]; 
int count[countsize],tmp[maxn]; 
//solve 
unsigned int maxB[maxn],maxL[maxn]; 

void swap(unsigned int &a,unsigned int &b) 
{ 
  unsigned int t=a; 
  a=b; 
  b=t; 
} 
char readchar() 
{ 
  if (bufL==bufP) 
  { 
	bufL=read(0,buf,bufsize); 
	if (bufL==0) 
	  return 0; 
	bufP=0; 
  } 
  return buf; 
}     
bool readnumber(unsigned int &v) 
{ 
  char c; 
  do{ 
	c=readchar(); 
	if (c==0) 
	  return false; 
  }while (c<'0' || c>'9'); 
  for (v=0;c>='0' && c<='9';c=readchar()) 
	v=v*10+(c-48); 
  return true; 
} 
void init() 
{ 
  bufL=bufP=0; 
  for (n=0;readnumber(A[n+1]) && readnumber(B[n+1]);) 
  { 
	n++; 
	if (A[n]>B[n]) 
	  swap(A[n],B[n]); 
  } 
} 
void count_sort(unsigned int A[],int arc[]) 
{ 
  int i; 
  //lower bit 
  memset(count,0,sizeof(count)); 
  for (i=1;i<=n;i++) 
	count[A[i]&65535]++; 
  for (i=1;i<countsize;i++) 
	count[i]+=count[i-1]; 
  for (i=n;i>=1;i--) 
	tmp[count[A[i]&65535]--]=i; 
  //higher bit 
  memset(count,0,sizeof(count)); 
  for (i=1;i<=n;i++) 
	count[A[i]>>16]++; 
  for (i=1;i<countsize;i++) 
	count[i]+=count[i-1]; 
  for (i=n;i>=1;i--) 
	arc[tmp[i]]=(count[A[tmp[i]]>>16]--); 
} 
void preprocess() 
{ 
  count_sort(A,arcA); 
  count_sort(B,arcB); 
  for (int i=1;i<=n;i++) 
	turnB[arcB[i]]=i; 
} 
void checkmax(double &answer,unsigned int S,unsigned int T) 
{ 
  if (S>T) 
	return; 
  double t=double(T)-double(S)+1; 
  if (t>answer) 
	answer=t; 
} 
#define lowbit(n) (((n)^((n)-1))&(n)) 
void add_maxB(int i,unsigned int v) 
{ 
  for (;i<=n;i+=lowbit(i)) 
	if (v>maxB[i]) 
	  maxB[i]=v; 
} 
void add_maxL(int i,unsigned int v) 
{ 
  i=n+1-i; 
  for (;i<=n;i+=lowbit(i)) 
	if (v>maxL[i]) 
	  maxL[i]=v; 
} 
unsigned int get_maxB(int i) 
{ 
  unsigned int t=0; 
  for (;i>0;i-=lowbit(i)) 
	if (maxB[i]>t) 
	  t=maxB[i]; 
  return t; 
} 
unsigned int get_maxL(int i) 
{ 
  i=n+1-i; 
  unsigned int t=0; 
  for (;i>0;i-=lowbit(i)) 
	if (maxL[i]>t) 
	  t=maxL[i]; 
  return t; 
} 
void solve() 
{ 
  double answer=0; 
  memset(maxB,0,sizeof(maxB)); 
  memset(maxL,0,sizeof(maxL)); 
  for (int T=1;T<=n;T++) 
  { 
	int i=turnB[T],LA=arcA[i]; 
	checkmax(answer,A[i],get_maxB(LA)); 
	checkmax(answer,1   ,get_maxL(LA)); 
	add_maxB(LA,B[i]); 
	add_maxL(LA,B[i]-A[i]+1); 
  } 
  printf("%0.0lf\n",answer); 
} 
int main() 
{ 
  freopen("input.txt","r",stdin); 
  init(); 
  preprocess(); 
  solve(); 
  return 0; 
} 
