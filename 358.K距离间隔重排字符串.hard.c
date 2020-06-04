#include "Mylib.h"
#define CHARLEN 26
struct sNode {
    char a;
    int num;
};
typedef struct sNode STRARR;
void PrintStrArr(STRARR *arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("arr[%d]:%c num:%d\n", i, arr[i].a, arr[i].num);
    }
    return;
}
STRARR *InitStrArr(char *input, int *rLen, int *iLen) {
    int strArr[CHARLEN] = {0};
    int sLen = strlen(input);
    int len = 0;
    for (int i = 0; i < sLen; i++) {
        if (strArr[input[i] - 'a'] == 0) {
            len++;
        }
        strArr[input[i] - 'a']++;
    }
    STRARR *retArr = malloc(sizeof(STRARR) * len);
    len = 0;
    for (int i = 0; i < CHARLEN; i++) {
        if (strArr[i] != 0) {
            retArr[len].a = 'a' + i;
            retArr[len].num = strArr[i];
            len++;
        }
    }
    *rLen = len;
    *iLen = sLen;
    return retArr;
}
int CompareStrArr(const void *a, const void *b) {
    STRARR *arrA = (STRARR *)a;
    STRARR *arrB = (STRARR *)b;
    return arrB->num - arrA->num;
}
bool MakeRetStr358(char *rStr, int start, int rLen, STRARR *strArr, int sLen, int interval) {
    int step = 0;
    for (int i = 0; i < sLen; i++) {
        if (strArr[i].num > 0 && step < interval) {
            rStr[start + step] = strArr[i].a;
            strArr[i].num--;
            step++;
        } else {
            break;
        }
    }
    return ((step == interval) || (start + step == rLen)) ? true : false;
}
char *rearrangeString(char *s, int k) {
    int sLen = 0;
    int iLen = 0;
    STRARR *strArr = InitStrArr(s, &sLen, &iLen);
    char *retStr = malloc(sizeof(char) * (iLen + 1));
    int startSite = 0;
    int step = iLen;
    if (k == 0) {
        return s;
    }
    while (step > 0) {
        qsort(strArr, sLen, sizeof(STRARR), CompareStrArr);
        if (MakeRetStr358(retStr, startSite, iLen, strArr, sLen, k)) {
            step = step - k;
            startSite = startSite + k;
        } else {
            free(retStr);
            return "";
        }
    }
    retStr[iLen] = '\0';
    return retStr;
}