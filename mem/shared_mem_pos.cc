#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
char arr[1000];
void test(){
	int a;
	printf("test(): stack top:%x\n",&a);
}
int main(){
	int shmid;
	char *p,*sp;
	printf("static arr from %x to %x\n",&arr[0],&arr[1000]);//arr在static段中
	printf("stack top  %x\n",&shmid); //shmid在栈顶
	if((p=(char*)malloc(1000))==NULL){
		return 1;}
	printf("heap %x\n",p);//malloc在堆上
	if((shmid=shmget(IPC_PRIVATE,1000,SHM_R|SHM_W))<0){
		return 1;}
	if((sp=(char*)shmat(shmid,0,0))==NULL){
		return 1;}
	printf("shared memory %x to %x\n",sp,sp-1000);//共享内存段附加在了进程栈下面
	test();
	if(shmctl(shmid,IPC_RMID,0)<0){
		return 4;}
	return 0;}
