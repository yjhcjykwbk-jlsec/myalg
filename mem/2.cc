#include <stdlib.h>
#include <string.h>
#include <stdio.h>
void GetMemory(char **p, int num)
{
*p = (char*)malloc(num);
}
int main(void)
{
char *str = NULL;
GetMemory(&str, 100);
strcpy(str,"helloworld\n");
printf(str);
delete [] str;
return 0;
}
