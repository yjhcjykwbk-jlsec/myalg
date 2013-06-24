//////////////////////////////////////
//http://tieba.baidu.com/p/53354730///
///  楼 教 主 百 度 之 星 2006 源 码  ///
//////////////////////////////////////
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#define _MAXL 2000000 

void GetN(char *s,long long &N) 
{ 
	N=0; 
	for (int i=0;s[i];i++) 
		N=N*10+(s[i]-48); 
} 
void print_bigint(long long n) 
{ 
	if (n>=10) 
		print_bigint(n/10); 
	printf("%d",int(n%10)); 
} 
void Solve(long long N) 
{ 
	bool find_answer=false; 
	long long L,T,A1,k; 
	for (L=2;L<=_MAXL && L*(L-1)/2<N;L++); 
	for (L--;L>=2;L--) 
	{ 
		T=L*(L-1)/2; 
		if (N>T && (N-T)%L==0) 
		{ 
			find_answer=true; 
			A1=(N-T)/L; 
			for (k=0;k<L;k++) 
			{ 
				if (k>0) 
					printf(" "); 
				print_bigint(A1+k); 
			} 
			printf("\n"); 
		} 
	} 
	if (!find_answer) 
		printf("NONE\n"); 
}	
int main(int argc,char *arg[]) 
{ 
	long long N; 
	GetN(arg[1],N); 
	Solve(N); 
	return 0; 
} 

