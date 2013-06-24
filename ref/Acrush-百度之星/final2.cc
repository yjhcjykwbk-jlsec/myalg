//////////////////网上决赛#2 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 

const char *rules_filename="rules.txt"; 
const char *facts_filename="facts.txt"; 
const int hashsize=1000007; 
const int maxm=100000+5; 
const int maxn=1000000+5; 
const int bufsize=256*1024; 

//读入 
int bufL,bufP; 
char buf[bufsize]; 
char str[1000000]; 
//读入函数 
char readchar() 
{ 
  if (bufL==bufP) 
  { 
	bufL=read(0,buf,bufsize); 
	bufP=0; 
	if (bufL==0) 
	  return 0; 
  } 
  return buf[bufP++]; 
} 
bool valid(char c) 
{ 
  return (c!=0 && c!='\t' && c!='\n' && c!=' ' && c!='&' && c!='-' && c!='>'); 
} 
bool readstring(char *s) 
{ 
  int L=0; 
  char c; 
  do{ 
	c=readchar(); 
	if (c==0) 
	  return false; 
	if (L==0 && c=='>') 
	  s[L++]=c; 
  }while (!valid©); 
  for (;valid©;c=readchar()) 
	s[L++]=c; 
  s[L]=0; 
  return true; 
} 
//目标变量 
int goal; 
//规则集合 
struct TRule 
{ 
  char *rule_name; 
  int n,*C,A; 
}; 
int m; 
TRule Rules[maxm]; 
int _n,_C[1000000]; 
int left[maxm],nlist,list[maxm]; 
//命题集合 
struct Tpoint 
{ 
  int v; 
  Tpoint *next; 
}; 
int n; 
bool fact[maxn],need_prove[maxn],org_fact[maxn]; 
Tpoint *Appear[maxn]; 
//HashTable,用于保存(命题名)->(int)的映射 
struct THashTable 
{ 
  char *var; 
  int id; 
  THashTable *next; 
}; 
THashTable *Hash[hashsize]; 

int find(char *s) 
{ 
  int L=strlen(s); 
  int address=L; 
  for (int i=0;s[i];i++) 
	address=(address*101+s[i])%hashsize; 
  THashTable *p; 
  for (p=Hash[address];p!=NULL;p=p->next) 
	if (strcmp(p->var,s)==0) 
	  return p->id; 
  p=new THashTable; 
  p->next=Hash[address]; 
  Hash[address]=p; 
  p->var=new char[L+2]; 
  strcpy(p->var,s); 
  p->id=(++n); 
  return n; 
} 
void insert_Point(int v,int pp) 
{ 
  Tpoint *p=new Tpoint; 
  p->v=pp; 
  p->next=Appear[v]; 
  Appear[v]=p; 
} 
void read_rules() 
{ 
  m=0; 
  while (1) 
  { 
	if (!readstring(str)) 
	  return; 
	m++; 
	Rules[m].rule_name=new char[strlen(str)+2]; 
	strcpy(Rules[m].rule_name,str); 
	_n=0; 
	while (1) 
	{ 
	  readstring(str); 
	  if (str[0]=='>') 
	  { 
		Rules[m].A=find(str+1); 
		break; 
	  } 
	  else 
		_C[++_n]=find(str); 
	} 
	Rules[m].C=new int[_n+2]; 
	Rules[m].n=_n; 
	for (int k=1;k<=_n;k++) 
	{ 
	  Rules[m].C[k]=_C[k]; 
	  insert_Point(_C[k],m); 
	} 
  } 
} 
void read_facts() 
{ 
  memset(fact,false,sizeof(fact)); 
  FILE *f=fopen(facts_filename,"r"); 
  while (fscanf(f,"%s",&str)!=-1) 
	fact[find(str)]=true; 
  fclose(f); 
} 
void TPsort() 
{ 
  int i,j,k; 
  Tpoint *p; 
  nlist=0; 
  for (i=1;i<=m;i++) 
  { 
	left[i]=0; 
	for (j=1;j<=Rules[i].n;j++) 
	  if (!fact[Rules[i].C[j]]) 
		left[i]++; 
	if (left[i]==0) 
	  list[++nlist]=i; 
  } 
  for (i=1;i<=nlist;i++) 
  { 
	k=Rules[list[i]].A; 
	if (fact[k]) 
	  continue; 
	fact[k]=true; 
	for (p=Appear[k];p!=NULL;p=p->next) 
	{ 
	  left[p->v]--; 
	  if (left[p->v]==0) 
		list[++nlist]=p->v; 
	} 
  } 
} 
void solve_data() 
{ 
  for (int i=1;i<=nlist;i++) 
  { 
	printf(" %s",Rules[list[i]].rule_name); 
	if (Rules[list[i]].A==goal) 
	  break; 
  } 
  printf("\n"); 
} 
void solve_goal() 
{ 
  int i,k; 
  memset(need_prove,false,sizeof(need_prove)); 
  need_prove[goal]=true; 
  for (i=1;i<=nlist;i++) 
	if (Rules[list[i]].A==goal) 
	  break; 
  for (;i>0;i--) 
	if (need_prove[Rules[list[i]].A] && !org_fact[Rules[list[i]].A]) 
	{ 
	  printf(" %s",Rules[list[i]].rule_name); 
	  for (k=1;k<=Rules[list[i]].n;k++) 
		need_prove[Rules[list[i]].C[k]]=true; 
	} 
  printf("\n"); 
} 
int main(int argc,char *arg[]) 
{ 
  if (argc!=3) 
  { 
	printf("Argument Error!\n"); 
	return 0; 
  } 
  freopen(rules_filename,"r",stdin); 
  bufP=bufL=n=0; 
  memset(Hash,0,sizeof(Hash)); 
  memset(Appear,0,sizeof(Appear)); 
  goal=find(arg[2]); 
  read_rules(); 
  read_facts(); 
  memcpy(org_fact,fact,sizeof(fact)); 
  if (fact[goal]) 
  { 
	printf("TRUE %s\n",arg[1]); 
	return 0; 
  } 
  TPsort(); 
  if (!fact[goal]) 
	printf("UNCERTAIN\n"); 
  else 
  { 
	printf("TRUE %s",arg[1]); 
	if (strcmp(arg[1],"data")==0) 
	  solve_data(); 
	else 
	  solve_goal(); 
  } 
  return 0; 
} 
