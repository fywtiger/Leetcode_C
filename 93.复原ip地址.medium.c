/*
 * @lc app=leetcode.cn id=93 lang=c
 *
 * [93] 复原IP地址
 */
#include "Mylib.h"
// @lc code=start

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define MAXADDLEN 15
struct listNode {
    char address[MAXADDLEN + 1];
    struct listNode *next;
};
typedef struct listNode LISTNODE;
struct addressList {
    int num;
    LISTNODE *head;
    LISTNODE *trail;
};
typedef struct addressList ADLIST;
ADLIST *InitAddressList() {
    ADLIST *rList = malloc(sizeof(ADLIST));
    rList->num = 0;
    rList->head = NULL;
    rList->trail = NULL;
    return rList;
}
int ChangeStrToInt(char *str, int len) {
    if (len > 3 || len == 0 || (*str == '0' && len != 1)) {
        return -1;
    }
    int val = 0;
    int i;
    for (i = 0; i < len; i++) {
        val = val * 10 + str[i] - '0';
    }
    return val;
}
bool CheckStrValid(char *str, int len) {
    int val = ChangeStrToInt(str, len);
    if (val == -1 || val > 255) {
        return false;
    }
    return true;
}
LISTNODE *InitListNode(char *str, int *site) {
    LISTNODE *node = malloc(sizeof(LISTNODE));
    node->next = NULL;
    int sLen = 0;
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = site[i]; j < site[i + 1]; j++, sLen++) {
            node->address[sLen] = str[j];
        }
        node->address[sLen++] = '.';
    }
    node->address[sLen - 1] = '\0';
    return node;
}
void InsertStrToList(ADLIST *rList, LISTNODE *node) {
    rList->num++;
    if (rList->head == NULL) {
        rList->head = node;
        rList->trail = node;
    } else {
        rList->trail->next = node;
        rList->trail = node;
    }
    return;
}
void MakeRlistByStr(char *s, int site, int *sArr, int len, int deep,
                    ADLIST *rList) {
    if (deep > 4) {
        return;
    }
    if (site >= len) {
        return;
    }
    if (deep == 4) {
        if (CheckStrValid(&s[site], len - site)) {
            LISTNODE *node = InitListNode(s, sArr);
            InsertStrToList(rList, node);
            return;
        }
        return;
    }
    int i;
    for (i = 1; i <= 3; i++) {
        if (site + i < len && CheckStrValid(&s[site], i)) {
            sArr[deep] = site + i;
            MakeRlistByStr(s, site + i, sArr, len, deep + 1, rList);
        }
    }
}
int *InitSiteArray(int len) {
    int *site = malloc(sizeof(int) * 5);
    memset(site, -1, sizeof(int) * 5);
    site[0] = 0;
    site[4] = len;
    return site;
}
char **restoreIpAddresses(char *s, int *returnSize) {
    int sLen = strlen(s);
    ADLIST *rList = InitAddressList();
    int *site = InitSiteArray(sLen);
    MakeRlistByStr(s, 0, site, sLen, 1, rList);
    *returnSize = rList->num;
    char **retArr = malloc(sizeof(char *) * rList->num);
    int i;
    for (i = 0; i < rList->num; i++) {
        retArr[i] = malloc(sizeof(char) * (MAXADDLEN + 1));
    }
    i = 0;
    LISTNODE *head = rList->head;
    while (head != NULL) {
        strcpy(retArr[i++], head->address);
        head = head->next;
    }

    return retArr;
}

// @lc code=end
