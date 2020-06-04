/*
 * @lc app=leetcode.cn id=449 lang=c
 *
 * [449] 序列化和反序列化二叉搜索树
 *
 * https://leetcode-cn.com/problems/serialize-and-deserialize-bst/description/
 *
 * algorithms
 * Medium (51.35%)
 * Likes:    64
 * Dislikes: 0
 * Total Accepted:    4.8K
 * Total Submissions: 9.3K
 * Testcase Example:  '[2,1,3]'
 *
 * 序列化是将数据结构或对象转换为一系列位的过程，以便它可以存储在文件或内存缓冲区中，或通过网络连接链路传输，以便稍后在同一个或另一个计算机环境中重建。
 *
 * 设计一个算法来序列化和反序列化二叉搜索树。
 * 对序列化/反序列化算法的工作方式没有限制。
 * 您只需确保二叉搜索树可以序列化为字符串，并且可以将该字符串反序列化为最初的二叉搜索树。
 *
 * 编码的字符串应尽可能紧凑。
 *
 * 注意：不要使用类成员/全局/静态变量来存储状态。
 * 你的序列化和反序列化算法应该是无状态的。
 *
 */
#include "Mylib.h"
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#define INVALIDVAL (-1)
#define MAXTREELEN 15
struct serialNode {
    int len;
    char s[MAXTREELEN];
    struct serialNode *next;
};
typedef struct serialNode sNode;
struct serialStack {
    int sLen;
    sNode *sHead;
    sNode *sTrail;
};
typedef struct serialStack sStack;
/** Encodes a tree to a single string. */

int ChangeIntToStr(int val, char *str) {
    int len = 0;
    int tmp = abs(val);
    if (val < 0) {
        str[len++] = '-';
    } else {
        do {
            str[len++] = tmp % 10 + '0';
            tmp = tmp / 10;
        } while (tmp);
    }
    str[len++] = '+';
    return len;
}
int GetStrLen(char *str) {
    int len = 0;
    while (str[len] != '+') {
        len++;
    }
    return len;
}
int ChangeTreeStrToInt(char *str, int *site) {
    int len = GetStrLen(str);
    if (len == 0) {
        *site = 1;
        return INVALIDVAL;
    }
    int end = (str[0] == '-') ? 1 : 0;
    int ret = 0;
    for (int i = len - 1; i >= end; i--) {
        ret = ret * 10 + str[i] - '0';
    }
    *site = len + 1;
    return end ? (-1 * ret) : ret;
}
void InsertNodeToStack(sStack *retStack, sNode *node) {
    retStack->sLen = retStack->sLen + node->len;
    if (retStack->sHead == NULL) {
        retStack->sHead = node;
        retStack->sTrail = node;
    } else {
        retStack->sTrail->next = node;
        retStack->sTrail = node;
    }
    return;
}
void ChangeTreeNodeToStr(struct TreeNode *root, sStack *retStack) {
    sNode *node = malloc(sizeof(sNode));
    node->next = NULL;
    if (root == NULL) {
        node->len = 1;
        node->s[0] = '+';
        InsertNodeToStack(retStack, node);
        return;
    }
    node->len = ChangeIntToStr(root->val, node->s);
    InsertNodeToStack(retStack, node);
    ChangeTreeNodeToStr(root->left, retStack);
    ChangeTreeNodeToStr(root->right, retStack);
    return;
}
void PrintTree(struct TreeNode *root) {
    if (root == NULL) {
        printf("NULL->");
        return;
    }
    printf("%d->", root->val);
    PrintTree(root->left);
    PrintTree(root->right);
    return;
}
char *serialize(struct TreeNode *root) {
    if (root == NULL) {
        return NULL;
    }
    sStack retStack;
    retStack.sLen = 0;
    retStack.sHead = NULL;
    retStack.sTrail = NULL;
    ChangeTreeNodeToStr(root, &retStack);
    char *retStr = malloc(sizeof(char) * (retStack.sLen + 1));
    sNode *head = retStack.sHead;
    sNode *pre = head;
    int rLen = 0;
    while (head != NULL) {
        memcpy(&retStr[rLen], head->s, sizeof(char) * head->len);
        rLen = rLen + head->len;
        pre = head;
        head = head->next;
        free(pre);
    }
    retStr[rLen] = '\0';
    return retStr;
}
struct TreeNode *ChangeStrToTreeNode(char *str, int sLen, int *start) {
    if (sLen == *start) {
        return NULL;
    }
    int site = 0;
    int val = ChangeTreeStrToInt(&str[*start], &site);
    *start = *start + site;
    if (val == INVALIDVAL) {
        return NULL;
    }
    struct TreeNode *root = malloc(sizeof(struct TreeNode));
    root->val = val;
    root->left = ChangeStrToTreeNode(str, sLen, start);
    root->right = ChangeStrToTreeNode(str, sLen, start);
    return root;
}

/** Decodes your encoded data to tree. */
struct TreeNode *deserialize(char *data) {
    if (data == NULL) {
        return NULL;
    }
    int sLen = strlen(data);
    int start = 0;
    // printf("data:%s\n",data);
    struct TreeNode *root = ChangeStrToTreeNode(data, sLen, &start);
    // PrintTree(root);
    return root;
}

// Your functions will be called as such:
// char* data = serialize(root);
// deserialize(data);
// @lc code=end
