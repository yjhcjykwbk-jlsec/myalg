#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAXLEN 1000
struct my_msg{
	int len;
	char text[MAXLEN];
}msg;
int main(){
	int msgid=msgget((key_t)11111,0666|IPC_CREAT);
	if(msgid<0) {
		printf("failed\n");return 0;
	}else printf("create msg:%d\n",msgid);
	int running=1;
	char buf[12]="helloworld";
	while(running){
		strcpy((char*)msg.text,buf);
		msg.len=strlen(buf);
		if(msgsnd(msgid,(void*)&msg,MAXLEN,0)==-1)
		{
			printf("msgsnd failed\n");
			exit(1);
		}if(strncmp(msg.text,"end",3)==0)
			running=0;
	}
	return 0;
}			
