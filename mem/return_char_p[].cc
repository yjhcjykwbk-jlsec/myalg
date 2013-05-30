#include <stdlib.h>
#include <string.h>
#include <stdio.h>
char *GetMemory(void)
{
char p[]="helloworld";
return p;
}
int main()
{
char *str = NULL;
str = GetMemory();
printf(str);
return 0;
}
