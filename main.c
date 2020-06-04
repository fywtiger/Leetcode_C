#include "Mylib.h"
char **restoreIpAddresses(char *s, int *returnSize);
int main(int argc, char const *argv[])
{
    int rLen=0;
    char str[20];
    scanf("%s",str);
    char **retStr = restoreIpAddresses(str,&rLen);
    int i;
    printf("len:%d\n",rLen);
    for(i=0;i<rLen;i++)
    {
        printf("%s",retStr[i]);
    }
    return 0;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

