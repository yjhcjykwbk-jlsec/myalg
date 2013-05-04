#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
int main(){
	printf("I am process with pid %d \n", getpid());
	while(true){
		printf("hello\n");
		sleep(1);
	}
	return 1;
}
