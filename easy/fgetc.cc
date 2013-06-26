#include <stdio.h>
int main(){
	FILE *f=fopen("3.3.in","rb");
	int n;
	while((n=fgetc(f))!=EOF)
		printf("%c ",n);
	return 0;
	}
	
