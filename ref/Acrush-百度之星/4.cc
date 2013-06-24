////////////初赛#4 
#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 

const int bufsize=128*1024; 
int bufL; 
char buf[bufsize]; 

struct THashPoint 
{ 
  char *s; 
  int c; 
  THashPoint *next; 
}; 
int MemoryID=0; 
THashPoint **Hash,*Memory; 

char *text; 
int L,HashSize,minC; 

void ReadFile() 
{ 
  text=new char[bufsize+5]; 
  L=0; 
  int textL=bufsize+5; 
  while (1) 
  { 
	bufL=read(0,buf,bufsize); 
	if (bufL==0) 
	  break; 
	while (L+bufL>=textL) 
	{ 
	  char *t_text=text; 
	  textL*=2; 
	  text=new char[textL]; 
	  memcpy(text,t_text,L); 
	} 
	memcpy(text+L,buf,bufL); 
	L+=bufL; 
  } 
  text[L]=0; 
} 
bool Prime(int n) 
{ 
  for (int i=2;i*i<=n;i++) 
	if (n%i==0) 
	  return false; 
  return true; 
} 
void Prepare() 
{ 
  int N=0,i; 
  for (i=0;i<L;i++) 
	if (text[i]==' ' || text[i]=='\t' || text[i]=='\n') 
	  text[i]=0; 
  for (i=0;i<L;i++) 
	if ((i==0 || text[i-1]==0) && text[i]!=0) 
	  N++; 
  for (HashSize=N*2+10;!Prime(HashSize);HashSize++); 
  Hash=new THashPoint* [HashSize]; 
  for (i=0;i<HashSize;i++) 
	Hash[i]=NULL; 
  MemoryID=0; 
  Memory=new THashPoint[N+10]; 
} 
int HashTable_function(char *s) 
{ 
  int address=strlen(s)%HashSize; 
  for (int i=0;s[i];i++) 
	address=(address*137+s[i]+128)%HashSize; 
  return address; 
} 
void HashTable_Insert(char *s) 
{ 
  int address=HashTable_function(s); 
  THashPoint *p; 
  for (p=Hash[address];p!=NULL;p=p->next) 
	if (strcmp(p->s,s)==0) 
	{ 
	  p->c++; 
	  return; 
	} 
  p=&Memory[MemoryID++]; 
  p->s=s; 
  p->c=1; 
  p->next=Hash[address]; 
  Hash[address]=p; 
} 
bool Print(char *s) 
{ 
  int address=HashTable_function(s); 
  THashPoint *p; 
  for (p=Hash[address];p!=NULL;p=p->next) 
	if (strcmp(p->s,s)==0 && p->c==minC) 
	  return false; 
  return true; 
} 
void Solve() 
{ 
  int i; 
  for (i=0;i<L;i++) 
	if ((i==0 || text[i-1]==0) && text[i]!=0) 
	  HashTable_Insert(text+i); 
  minC=2000000000; 
  for (i=0;i<MemoryID;i++) 
	if (Memory[i].c<minC) 
	  minC=Memory[i].c; 
  bool first=true; 
  for (i=0;i<L;i++) 
	if ((i==0 || text[i-1]==0) && text[i]!=0 && Print(text+i)) 
	{ 
	  if (!first) 
		printf(" "); 
	  first=false; 
	  printf("%s",text+i); 
	} 
} 
int main() 
{ 
  freopen("corpus.txt","r",stdin); 
  ReadFile(); 
  Prepare(); 
  Solve(); 
  return 0; 
}     
