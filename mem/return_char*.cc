#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void GetMemory(char *p)
{
printf ("p:%x\n",p);
p=(char*)malloc(100);
printf("after\n");
}

int main(void)
{
char *str = NULL;
GetMemory(str);
strcpy(str,"hello world");
printf(str);
return 0;
}
