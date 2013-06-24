////////////初赛#3 
#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 

//buf 
const int bufsize=128*1024; 
int bufL,bufP; 
char buf[bufsize]; 

char readchar() 
{ 
  if (bufL==bufP) 
  { 
	bufL=read(0,buf,bufsize); 
	if (bufL==0) 
	  return 0; 
	bufP=0; 
  } 
  return buf[bufP++]; 
} 

//data 
const int max_strlen=512*1024; 
const int hashsize=30011; 

struct THashPoint 
{ 
  char *s1,*s2; 
  THashPoint *next; 
}; 
char lines[max_strlen],*s1,*s2; 
FILE *f; 
THashPoint *Hash[hashsize]; 

bool read_str() 
{ 
  lines[0]=0; 
  fgets(lines,max_strlen,f); 
  if (strlen(lines)>0 && lines[strlen(lines)-1]=='\n') 
	lines[strlen(lines)-1]=0; 
  if (strlen(lines)<3) 
	return false; 
  for (int i=0;lines[i];i++) 
	if (lines[i]==' ' || lines[i]=='\t') 
	{ 
	  s1=lines; 
	  s2=lines+i+1; 
	  lines[i]=0; 
	  return true; 
	} 
  return false; 
} 
int HashTable_function(char *s) 
{ 
  int address=strlen(s)%hashsize; 
  for (int i=0;s[i];i++) 
	address=(address*107+s[i]+128)%hashsize; 
  return address; 
} 
void HashTable_Insert() 
{ 
  int address=HashTable_function(s1); 
  THashPoint *p; 
  for (p=Hash[address];p!=NULL;p=p->next) 
	if (strcmp(p->s1,s1)==0) 
	{ 
	  p->s2=new char[strlen(s2)+1]; 
	  strcpy(p->s2,s2); 
	  return; 
	} 
  p=new THashPoint; 
  p->s1=new char[strlen(s1)+1]; 
  p->s2=new char[strlen(s2)+1]; 
  strcpy(p->s1,s1); 
  strcpy(p->s2,s2); 
  p->next=Hash[address]; 
  Hash[address]=p; 
} 
void Print(char *s) 
{ 
  int address=HashTable_function(s); 
  THashPoint *p; 
  for (p=Hash[address];p!=NULL;p=p->next) 
	if (strcmp(p->s1,s1)==0) 
	{ 
	  printf("%s",p->s2); 
	  return; 
	} 
  printf("%s",s); 
} 
void Init_HashTable() 
{ 
  f=fopen("dict.txt","r"); 
  while (read_str()) 
	HashTable_Insert();	
  fclose(f); 
} 
int main() 
{ 
  Init_HashTable(); 
  //Main 
  freopen("text.txt","r",stdin); 
  bufL=bufP=0; 
  int L=0; 
  for (char c;(c=readchar())!=0;) 
	if (c==' ' || c=='\t' || c=='\n') 
	{ 
	  lines[L]=0; 
	  Print(lines); 
	  printf("%c",c); 
	  L=0; 
	} 
	else 
	  lines[L++]=c; 
  lines[L]=0; 
  Print(lines); 
  return 0; 
}     

