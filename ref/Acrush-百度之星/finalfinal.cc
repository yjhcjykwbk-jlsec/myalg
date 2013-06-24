//////////////总决赛
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

const int hashsize=70001; 
const int maxnode=50000; 
const int maxp=40; 
const int ten[]={1,10,100,1000,10000,100000,1000000,10000000,100000000}; 
const int C[]={2,3,2,3,4,3,2,3,2}; 
const int EP[][4]={{1,3,0,0},{0,2,4,0},{1,5,0,0},{0,4,6,0},{1,3,5,7},{2,4,8,0},{3,7,0,0},{4,6,8,0},{5,7,0,0}}; 

struct Tlist 
{ 
  int data,d; 
  Tlist *next; 
}; 
struct Thashpoint 
{ 
  int data; 
  Thashpoint *next; 
}; 
//Memory 
int ID; 
Tlist listM[maxnode],*q; 
Thashpoint hashM[maxnode],*p; 
//data 
int src,dest; 
//heap 
Tlist *head[maxp],*expand[maxp],*lp1,*lp2; 
//Hash 
Thashpoint *hash[hashsize]; 
//expand 
int nowp,A[9],arcT[9],dist[9][9],b,depth,swap[9][9]; 
int data,G,newdata,newG; 
bool find_answer; 

void readdata(const char *filename,int &data) 
{ 
  int i,v; 
  FILE *f=fopen(filename,"r"); 
  data=0; 
  for (i=0;i<9;i++) 
  { 
	fscanf(f,"%d",&v); 
	data=data+v*ten[i]; 
  } 
  fclose(f); 
} 
bool check_noanswer() 
{ 
  int p[9],i,b1,b2; 
  bool vis[9]; 
  for (i=0;i<9;i++) 
	p[i]=arcT[src/ten[i]%10]; 
  for (b1=0; src/ten[b1]%10!=0;b1++); 
  for (b2=0;dest/ten[b2]%10!=0;b2++); 
  int countP=0; 
  memset(vis,false,sizeof(vis)); 
  for (i=0;i<9;i++) 
	if (!vis[i]) 
	{ 
	  countP++; 
	  for (int k=i;!vis[k];k=p[k]) 
		vis[k]=true; 
	} 
  return (countP-dist[b1][b2])%2==0; 
} 
void preprocess() 
{ 
  ID=0; 
  find_answer=false; 
  memset(hash,0,sizeof(hash)); 
  memset(head,0,sizeof(head)); 
  memset(expand,0,sizeof(expand)); 
  for (int k=0;k<9;k++) 
	arcT[dest/ten[k]%10]=k; 
  for (int u=0;u<9;u++) 
	for (int v=0;v<9;v++) 
	{ 
	  dist[u][v]=abs(u/3-v/3)+abs(u%3-v%3); 
	  swap[u][v]=ten[u]-ten[v]; 
	} 
} 
void addnode() 
{ 
  if (newdata==dest) 
  { 
	printf("%d\n",depth); 
	find_answer=true; 
	return; 
  } 
  int address=newdata%hashsize; 
  for (p=hash[address];p!=NULL;p=p->next) 
	if (p->data==newdata) 
	  return; 
  if (ID==maxnode) 
	return; 
  p=&hashM[ID]; 
  p->data=newdata; 
  p->next=hash[address]; 
  hash[address]=p; 
  q=&listM[ID]; 
  ID++; 
  q->data=newdata; 
  q->d=depth; 
  if (newG>=maxp) 
	return; 
  if (newG==nowp) 
  { 
	q->next=expand[depth]; 
	expand[depth]=q; 
  } 
  else 
  { 
	q->next=head[newG]; 
	head[newG]=q; 
  } 
} 
void solve() 
{ 
  nowp=-1; 
  newdata=src; 
  newG=0; 
  for (int k=0;k<9;k++) 
	if (src/ten[k]%10!=0) 
	  newG+=dist[arcT[src/ten[k]%10]][k]; 
  depth=0; 
  addnode(); 
  if (find_answer) 
	return; 
  for (int p=0;p<maxp;p++) if (head[p]!=NULL) 
  { 
	nowp=p; 
	for (lp1=head[p];lp1!=NULL;lp1=lp2) 
	{ 
	  lp2=lp1->next; 
	  lp1->next=expand[lp1->d]; 
	  expand[lp1->d]=lp1; 
	} 
	for (int d=0;d<=p;d++) 
	  for (;expand[d]!=NULL;) 
	  { 
		data=expand[d]->data; 
		G=p-expand[d]->d; 
		depth=expand[d]->d+1; 
		expand[d]->d=-2; 
		expand[d]=expand[d]->next; 
		for (b=0;data/ten[b]%10!=0;b++); 
		for (int v=0;v<C[b];v++) 
		{ 
		  int u=EP[b][v]; 
		  int c=data/ten[u]%10; 
		  newdata=data+swap[b][u]*c; 
		  c=arcT[c]; 
		  newG=depth+G-dist[c][u]+dist[c][b]; 
		  addnode(); 
		  if (find_answer) 
			return; 
		} 
	  } 
  } 
  printf("-1\n"); 
} 
int main() 
{ 
  readdata("start.txt",src); 
  readdata("goal.txt",dest); 
  preprocess(); 
  if (check_noanswer()) 
	printf("-1\n"); 
  else 
	solve(); 
  return 0; 
} 
