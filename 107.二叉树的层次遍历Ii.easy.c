/*
 * @lc app=leetcode.cn id=107 lang=c
 *
 * [107] 二叉树的层次遍历 II
 *
 * https://leetcode-cn.com/problems/binary-tree-level-order-traversal-ii/description/
 *
 * algorithms
 * Easy (65.12%)
 * Likes:    227
 * Dislikes: 0
 * Total Accepted:    55.2K
 * Total Submissions: 84.7K
 * Testcase Example:  '[3,9,20,null,null,15,7]'
 *
 * 给定一个二叉树，返回其节点值自底向上的层次遍历。
 * （即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）
 *
 * 例如：
 * 给定二叉树 [3,9,20,null,null,15,7],
 *
 * ⁠   3
 * ⁠  / \
 * ⁠ 9  20
 * ⁠   /  \
 * ⁠  15   7
 *
 *
 * 返回其自底向上的层次遍历为：
 *
 * [
 * ⁠ [15,7],
 * ⁠ [9,20],
 * ⁠ [3]
 * ]
 *
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

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
typedef struct TreeNode TREENODE;
struct sList {
    struct TreeNode *node;
    struct sList *next;
};
typedef struct sList SLIST;
struct outListNode {
    int size;
    SLIST *head;
    struct outListNode *next;
};
typedef struct outListNode OUTLIST;
SLIST *initStackList(struct TreeNode *root, int *sLen);
OUTLIST *initOutList();
OUTLIST *outInfoToList(SLIST *stackHead, int sLen, OUTLIST *outListTrail);
int updateStackList(SLIST *stackHead);
int **ChangOutListToArray(OUTLIST *outListHead, int oLen, int **returnColumnSizes);
void ListFree(OUTLIST *outListHead, SLIST *stackHead);
int **levelOrderBottom(struct TreeNode *root, int *returnSize, int **returnColumnSizes) {
    int sLen = 0, oLen = 0;
    SLIST *stackHead = initStackList(root, &sLen);
    OUTLIST *outListHead = initOutList();
    OUTLIST *outListTrail = outListHead;
    while (sLen != 0) {
        outListTrail = outInfoToList(stackHead, sLen, outListTrail);
        oLen++;
        sLen = updateStackList(stackHead);
    }
    *returnSize = oLen;
    int **returnArray = ChangOutListToArray(outListHead, oLen, returnColumnSizes);
    ListFree(outListHead, stackHead);
    return returnArray;
}
void ListFree(OUTLIST *outListHead, SLIST *stackHead) {
    free(stackHead);
    OUTLIST *outNodeHead = outListHead->next;
    OUTLIST *outNodePre = outNodeHead;
    SLIST *sListPre = NULL, *sListHead = NULL;
    while (outNodeHead != NULL) {
        outNodeHead = outNodeHead->next;
        sListPre = outNodePre->head;
        sListHead = outNodePre->head;
        while (sListHead != NULL) {
            sListHead = sListHead->next;
            free(sListPre);
            sListPre = sListHead;
        }
        free(outNodePre);
        outNodePre = outNodeHead;
    }
    free(outListHead);
    return;
}
SLIST *initStackList(struct TreeNode *root, int *sLen) {
    SLIST *stackList = malloc(sizeof(SLIST));
    stackList->next = NULL;
    if (root != NULL) {
        SLIST *node = malloc(sizeof(SLIST));
        node->node = root;
        node->next = NULL;
        stackList->next = node;
        *sLen = *sLen + 1;
    }
    return stackList;
}

OUTLIST *initOutList() {
    OUTLIST *outNode = malloc(sizeof(OUTLIST));
    outNode->next = NULL;
    return outNode;
}

OUTLIST *outInfoToList(SLIST *stackHead, int sLen, OUTLIST *outListTrail) {
    OUTLIST *outNode = malloc(sizeof(OUTLIST));
    outNode->size = sLen;
    outNode->head = stackHead->next;
    outNode->next = NULL;
    outListTrail->next = outNode;
    return outNode;
}

int updateStackList(SLIST *stackHead) {
    int len = 0;
    SLIST *head = stackHead->next;
    SLIST *nStackHead = malloc(sizeof(SLIST));
    nStackHead->next = NULL;
    SLIST *nStackTrail = nStackHead;
    SLIST *node = NULL;
    while (head != NULL) {
        if (head->node->left != NULL) {
            node = malloc(sizeof(SLIST));
            node->node = head->node->left;
            node->next = NULL;
            nStackTrail->next = node;
            nStackTrail = node;
            len++;
        }
        if (head->node->right != NULL) {
            node = malloc(sizeof(SLIST));
            node->node = head->node->right;
            node->next = NULL;
            nStackTrail->next = node;
            nStackTrail = node;
            len++;
        }
        head = head->next;
    }
    stackHead->next = nStackHead->next;
    free(nStackHead);
    return len;
}

int **ChangOutListToArray(OUTLIST *outListHead, int oLen, int **returnColumnSizes) {
    int **returnArray = malloc(sizeof(int *) * oLen);
    OUTLIST *head = outListHead->next;
    SLIST *node = NULL;
    int j;
    *returnColumnSizes = malloc(sizeof(int) * oLen);
    for (int i = oLen - 1; i >= 0; i--) {
        returnArray[i] = malloc(sizeof(int) * (head->size));
        node = head->head;
        j = 0;
        while (node != NULL) {
            returnArray[i][j] = node->node->val;
            j++;
            node = node->next;
        }
        (*returnColumnSizes)[i] = j;
        head = head->next;
    }
    return returnArray;
}

// @lc code=end
