#include <stdio.h>
#include <malloc.h>

void strcopy(char *to,char *from);
void main()
{
    char str_arr[20] = "how are you";
    char *str_poit = (char *)malloc(5);
    strcopy(str_poit,str_arr);
    printf("%s\n",str_poit);
}

void strcopy(char *to,char *from)
{
    while(*to++ = *from++)
    ;
}
