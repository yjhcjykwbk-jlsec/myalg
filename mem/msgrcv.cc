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

	int torecv=0;
	while(running){
		if(msgrcv(msgid,(void*)&msg,MAXLEN,torecv,0)==-1)
		{
			printf("msgrecv failed\n");
			exit(1);
		}
		printf("you recv:%s\n",msg.text);
		if(strncmp(msg.text,"end",3)==0)
			running=0;
	}
	if(msgctl(msgid,IPC_RMID,0)==-1)
	{
		printf("msgct(IPC_RMID) failed\n");
		exit(1);
	}
	return 0;
}			

