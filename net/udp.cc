#include <sys/types.h>
//socket通信头文件
#include <sys/socket.h>
//close函数所在文件
#include <unistd.h>

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
int main(){
	int s=socket(AF_INET,SOCK_STREAM,0);
//SOCK_DGRAM为面向无连接的，而listen时需要的socket是面向连接的，所以出错。
//[felix@toy]$ ./a.out
//listen: Operation not supported
//可以把SOCK_DGRAM改为SOCK_STREAM.
	if(s<0) {perror("socket");return 1;}
	struct sockaddr_in addr_serv;
	addr_serv.sin_family=AF_INET;
	addr_serv.sin_addr.s_addr=inet_addr("127.0.0.1");//htonl(0x7f000001);
	addr_serv.sin_port=htons(8888);
	int t=bind(s,(struct sockaddr*) &addr_serv,sizeof(addr_serv));
	if(t==-1) {perror("bind");return 1;}
	if((t=listen(s,5))<0){perror("listen");return 1;}
//	close(s);
//	return 0;
	while(true){}
	close(s);
	return 0;
}
