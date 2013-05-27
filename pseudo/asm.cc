#include <iostream>
using namespace std;
#define SIZE 10
int a[SIZE]={10,8,9,7,5,6,4,2,3,1};
int main(){
//	for(i=SIZE-1;i>0;i--){
	int i=SIZE;
	int *p=&a[i];
	__asm{
	mov eax,i; //i
	mov esi,p
LOOP:
	addi eax,-1; //i--
	jez i LOOPOUT;
	mov ebx,-1; //j=0
LOOP1:
		add ebx,1 //j++
		cmp ebx,eax;
		je LOOP;
		mov ecx,[esi+ebx*4]
		mov edx,[esi+ebx*4+4];
		cmp ecx,edx;
		jnb NOEXCHANGE;
		mov [esi+ebx*4],edx;
		mov [esi+ebx*4+4],ecx;
		jmp LOOP1
LOOPOUT:
//		for(j=0;j<i;j++){
//			if(a[j]>a[j+1]) swap(a,j,j+1);
//		}
	}
	for(i=0;i<10;i++) cout<<a[i]<<" ";cout<<endl;
	return 0;
}
