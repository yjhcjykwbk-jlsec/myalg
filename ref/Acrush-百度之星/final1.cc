/////网上决赛#1 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 

const int maxn2=100000+5; 
const int maxn=5000+5; 
const int max_outputL=10000000; 
const int oo=1000000000; 
//buf 
const int bufsize=256*1024; 
int bufL,bufP; 
char buf[bufsize]; 
char *bufp; 
//输入图 
int n2,indexID[maxn2],indexP[maxn2]; 
int deg2[maxn2],*G2[maxn2],*W2[maxn2]; 
//并查集 
int father[maxn2],sortlist[maxn2]; 
//新建图 
int n,listM[maxn],G[maxn][maxn],tG[maxn][maxn]; 
//输出 
int outputL=0; 
char outputs[max_outputL]; 
//最小树形图 
int prev[maxn],tmpG[maxn]; 
bool saved[maxn],incycle[maxn]; 
//深度优先搜索 
int DFS_count; 
bool DFS_vis[maxn]; 

//输入数据函数 
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
bool Valid(char c) 
{ 
  return (c!=' ') && (c!='\t') && (c!='\n') && (c!=0); 
} 
bool ReadString(char *s) 
{ 
  while (1) 
  { 
	if (*bufp==0) 
	  return false; 
	if (Valid(*bufp)) 
	  break; 
	bufp++; 
  } 
  int L=0; 
  for (;Valid(*bufp);bufp++) 
	s[L++]=*bufp; 
  s[L]=0; 
  return true; 
} 
void ReadLine() 
{ 
  char c; 
  while (1) 
  { 
	int L=0; 
	while (1) 
	{ 
	  c=readchar(); 
	  if (c=='\n' || c==0) 
		break; 
	  outputs[L++]=c; 
	} 
	outputs[L]=0; 
	if (L>=2) 
	  break; 
  } 
} 
//输出数据函数 
void push_char(char c) 
{ 
  outputs[outputL++]=c; 
} 
void write(int v) 
{ 
  if (v>=10) 
	write(v/10); 
  push_char('0'+v%10); 
} 
//并查集函数 
int getfather(int v)  
{ 
  return (father[v]==0)?v:(father[v]=getfather(father[v])); 
} 
void merge(int i,int j) 
{ 
  i=getfather(i); 
  j=getfather(j); 
  if (i<j) 
	father[j]=i; 
  if (j<i) 
	father[i]=j; 
} 

void ReadData() 
{ 
  int i,j,v,k; 
  char s[100]; 
  ReadLine(); 
  bufp=outputs; 
  ReadString(s); 
  for (n2=0;ReadString(s);) 
  { 
	sscanf(s,"%d",&v); 
	indexID[++n2]=v; 
  } 
  int maxd=0; 
  for (i=1;i<=n2;i++) 
  { 
	ReadLine(); 
	bufp=outputs; 
	ReadString(s); 
	sscanf(s,"%d",&v); 
	for (k=1;indexID[k]!=v;k++); 
	//calc deg[k] 
	deg2[k]=0; 
	for (;ReadString(s);) 
	{ 
	  if (s[0]=='/') 
		continue; 
	  sscanf(s,"%d",&v); 
	  if (v>0) 
		deg2[k]++; 
	} 
	if (deg2[k]>maxd) 
	  maxd=deg2[k]; 
	G2[k]=new int[deg2[k]+5]; 
	W2[k]=new int[deg2[k]+5]; 
	//read again 
	bufp=outputs; 
	ReadString(s); 
	deg2[k]=0; 
	for (j=1;j<=n2;j++) 
	{ 
	  ReadString(s); 
	  if (s[0]=='/') 
		continue; 
	  sscanf(s,"%d",&v); 
	  if (v>0) 
	  { 
		G2[k][++deg2[k]]=j; 
		W2[k][deg2[k]]=v; 
	  } 
	} 
  } 
} 
void DFS(int v) 
{ 
  if (DFS_vis[v]) 
	return; 
  DFS_vis[v]=true; 
  DFS_count++; 
  for (int i=1;i<=n;i++) 
	if (G[v][i]<oo) 
	  DFS(i); 
} 
bool process() 
{ 
  if (n==1) 
  { 
	write(listM[1]); 
	push_char(' '); 
	write(0); 
	push_char('\n'); 
	return true; 
  } 
  int i,j,u,v; 
  int answer=oo,total; 
  for (int srcp=1;srcp<=n;srcp++) 
  { 
	for (u=1;u<=n;u++) 
	  for (v=1;v<=n;v++) 
		G[u][v]=tG[u][v]; 
	DFS_count=0; 
	for (i=1;i<=n;i++) 
	  DFS_vis[i]=false; 
	DFS(srcp); 
	if (DFS_count<n) 
	  continue; 
	total=oo; 
	for (i=1;i<=n;i++) 
	  if (G[i][srcp]<total) 
		total=G[i][srcp]; 
	if (total==oo) 
	  continue; 
	for (i=1;i<=n;i++) 
	{ 
	  prev[i]=0; 
	  saved[i]=true; 
	} 
	while (1) 
	{ 
	  int minCost=oo; 
	  for (i=1;i<=n;i++) if(i!=srcp && prev[i]==0 && saved[i]) 
		for (j=1;j<=n;j++) if (saved[j]) 
		  if (G[j][i]<minCost) 
		  { 
			minCost=G[j][i]; 
			u=j; 
			v=i; 
		  } 
	  if (minCost==oo) 
		break; 
	  total+=minCost; 
	  //insert edge (u,v) 
	  prev[v]=u; 
	  for (i=u;prev[i]!=0 && i!=v;i=prev[i]); 
	  if (prev[i]==0) 
		continue; 
	  //cycle 
	  for (i=1;i<=n;i++) 
		incycle[i]=false; 
	  incycle[v]=true; 
	  for (i=u;i!=v;i=prev[i]) 
		incycle[i]=true; 
	  for (i=1;i<=n;i++) 
		tmpG[i]=oo; 
	  for (i=1;i<=n;i++) if (saved[i] && !incycle[i]) 
		for (j=1;j<=n;j++) if (saved[j] && incycle[j]) 
		{ 
		  if (G[j][i]<G[v][i]) 
			G[v][i]=G[j][i]; 
		  if (G[i][j]<oo) 
		  { 
			int t=G[i][j]-G[prev[j]][j]; 
			if (t<tmpG[i]) 
			  tmpG[i]=t; 
		  } 
		} 
	  for (i=1;i<=n;i++) if (saved[i] && !incycle[i]) 
		if (prev[i]>0 && incycle[prev[i]]) 
		  prev[i]=v; 
	  prev[v]=0; 
	  for (i=u;i!=v;i=prev[i]) 

		saved[i]=false; 
	  for (i=1;i<=n;i++) 
		G[i][v]=tmpG[i]; 
	} 
	if (total<answer) 
	  answer=total; 
  } 
  if (answer==oo) 
	return false; 
  for (i=1;i<=n;i++) 
  { 
	write(listM[i]); 
	push_char(' '); 
  } 
  write(answer); 
  push_char('\n'); 
  return true; 
} 
int qsort_comp(const void *p1,const void *p2) 
{ 
  int t1=*(int *)p1,t2=*(int *)p2; 
  if (getfather(t1)!=getfather(t2)) 
	return getfather(t1)-getfather(t2); 
  return t1-t2; 
} 
void solve() 
{ 
  int i,j,u,v; 
  memset(father,0,sizeof(father)); 
  for (i=1;i<=n2;i++) 
	for (j=1;j<=deg2[i];j++) 
	  merge(i,G2[i][j]); 
  for (i=1;i<=n2;i++) 
	sortlist[i]=i; 
  qsort(sortlist+1,n2,sizeof(int),qsort_comp); 
  for (i=1;i<=n2;i=j) 
	if (father[sortlist[i]]==0) 
	{ 
	  for (j=i;j<=n2 && getfather(sortlist[i])==getfather(sortlist[j]);j++); 
	  n=j-i; 
	  if (n>maxn-5) 
	  { 
		printf("NONE\n"); 
		return; 
	  } 
	  for (v=i;v<j;v++) 
	  { 
		listM[v-i+1]=indexID[sortlist[v]]; 
		indexP[sortlist[v]]=v-i+1; 
	  } 
	  for (u=1;u<=n;u++) 
		for (v=1;v<=n;v++) 
		  tG[u][v]=oo; 
	  for (u=i;u<j;u++) 
		for (v=1;v<=deg2[sortlist[u]];v++) 
		  tG[indexP[sortlist[u]]][indexP[G2[sortlist[u]][v]]]=W2[sortlist[u]][v]; 
	  if (!process()) 
	  { 
		printf("NONE\n"); 
		return; 
	  } 
	} 
  outputs[outputL]=0; 
  printf("%s",outputs); 
} 
int main() 
{ 
  freopen("sites.txt","r",stdin); 
  bufP=bufL=0; 
  ReadData(); 
  solve(); 
  return 0; 
} 

