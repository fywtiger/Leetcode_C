/*
 * @lc app=leetcode.cn id=113 lang=c
 *
 * [113] 路径总和 II
 *
 * https://leetcode-cn.com/problems/path-sum-ii/description/
 *
 * algorithms
 * Medium (59.65%)
 * Likes:    247
 * Dislikes: 0
 * Total Accepted:    53.8K
 * Total Submissions: 89.8K
 * Testcase Example:  '[5,4,8,11,null,13,4,7,2,null,null,5,1]\n22'
 *
 * 给定一个二叉树和一个目标和，找到所有从根节点到叶子节点路径总和等于给定目标和的路径。
 *
 * 说明: 叶子节点是指没有子节点的节点。
 *
 * 示例:
 * 给定如下二叉树，以及目标和 sum = 22，
 *
 * ⁠             5
 * ⁠            / \
 * ⁠           4   8
 * ⁠          /   / \
 * ⁠         11  13  4
 * ⁠        /  \    / \
 * ⁠       7    2  5   1
 *
 *
 * 返回:
 *
 * [
 * ⁠  [5,4,11,2],
 * ⁠  [5,8,4,5]
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
typedef struct TreeNode TNODE;
typedef struct {
    int **retSum;
    int retSize;
    int **returnColumnSizes;
} RETSUM;

int TreeSumPath(TNODE *node, int sum, int *tSum, int deep, RETSUM *retNode) {
    if (node == NULL && sum == 0) {
        (*retNode->returnColumnSizes)[retNode->retSize] = deep;
        memcpy(retNode->retSum[retNode->retSize], tSum, sizeof(int) * deep);
        retNode->retSize += 1;
        return 1;
    }
    if (node == NULL) {
        return 0;
    }
    tSum[deep] = node->val;
    sum -= node->val;
    deep++;
    if (node->right == NULL) {
        return TreeSumPath(node->left, sum, tSum, deep, retNode);
    }
    if (node->left == NULL) {
        return TreeSumPath(node->right, sum, tSum, deep, retNode);
    }
    return TreeSumPath(node->right, sum, tSum, deep, retNode) + TreeSumPath(node->left, sum, tSum, deep, retNode);
}
int GetDeepMaxVal(int a, int b) {
    return a > b ? a : b;
}
int GetTreePoint(struct TreeNode *node, int deep, int *maxDeep) {
    if (node->left == NULL && node->right == NULL) {
        *maxDeep = GetDeepMaxVal(*maxDeep, deep);
        return 1;
    }
    if (node->left == NULL) {
        return GetTreePoint(node->right, deep + 1, maxDeep);
    }
    if (node->right == NULL) {
        return GetTreePoint(node->left, deep + 1, maxDeep);
    }
    return GetTreePoint(node->right, deep + 1, maxDeep) + GetTreePoint(node->left, deep + 1, maxDeep);
}
int **InitRetSum(struct TreeNode *root, int **returnColumnSizes, RETSUM *retNode) {
    int deep = 0;
    int point = GetTreePoint(root, 1, &deep);
    retNode->retSum = malloc(sizeof(int *) * point);
    for (int i = 0; i < point; i++) {
        retNode->retSum[i] = malloc(sizeof(int) * deep);
        *returnColumnSizes = malloc(sizeof(int) * point);
    }
    retNode->retSize = 0;
    retNode->returnColumnSizes = returnColumnSizes;
    return deep;
}
int **pathSum(struct TreeNode *root, int sum, int *returnSize, int **returnColumnSizes) {
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }
    RETSUM retNode;
    int tSize = InitRetSum(root, returnColumnSizes, &retNode);
    int tSum[tSize];
    *returnSize = TreeSumPath(root, sum, tSum, 0, &retNode);
    return retNode.retSum;
}

// @lc code=end
