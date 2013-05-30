#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
void print_msg(char*pt);
int main(){
	pthread_t p1,p2;
	char *msg1="hello\n",*msg2="world\n";
	pthread_create(&p1,NULL,(void*)(&print_msg),(void*)msg1);
	pthread_create(&p2,NULL,(void*)(&print_msg),(void*)msg2);
	sleep(1);
	return 0;
}	
void print_msg(char *pt){
	printf("ThreadID:%lx",pthread_slef());
	printf("%s",pt);
	int t;
	pthread_exit(&t);
}
