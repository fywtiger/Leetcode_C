/*
 * @lc app=leetcode.cn id=652 lang=c
 *
 * [652] 寻找重复的子树
 *
 * https://leetcode-cn.com/problems/find-duplicate-subtrees/description/
 *
 * algorithms
 * Medium (53.09%)
 * Likes:    107
 * Dislikes: 0
 * Total Accepted:    7.2K
 * Total Submissions: 13.5K
 * Testcase Example:  '[1,2,3,4,null,2,4,null,null,4]'
 *
 * 给定一棵二叉树，返回所有重复的子树。对于同一类的重复子树，你只需要返回其中任意一棵的根结点即可。
 *
 * 两棵树重复是指它们具有相同的结构以及相同的结点值。
 *
 * 示例 1：
 *
 * ⁠       1
 * ⁠      / \
 * ⁠     2   3
 * ⁠    /   / \
 * ⁠   4   2   4
 * ⁠      /
 * ⁠     4
 *
 *
 * 下面是两个重复的子树：
 *
 * ⁠     2
 * ⁠    /
 * ⁠   4
 *
 *
 * 和
 *
 * ⁠   4
 *
 *
 * 因此，你需要以列表的形式返回上述重复子树的根结点。
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
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct ExtTreeNode {
    int count;
    int flag;
    struct TreeNode *node;
};

int calculateTreeNodeCount(struct TreeNode *root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + calculateTreeNodeCount(root->left) + calculateTreeNodeCount(root->right);
}

int inQueue(struct ExtTreeNode *tree, struct TreeNode *root, int *index) {
    int tmp;
    int left;
    int right;
    if (root == NULL) {
        return 0;
    }
    tmp = *index;
    tree[tmp].flag = 0;
    tree[tmp].node = root;
    (*index)++;
    left = inQueue(tree, root->left, index);
    right = inQueue(tree, root->right, index);
    tree[tmp].count = 1 + left + right;
    return tree[tmp].count;
}

bool isSameChildTree(struct TreeNode *firstTree, struct TreeNode *secondTree) {
    if ((firstTree == NULL) || (secondTree == NULL)) {
        return false;
    }

    if (firstTree->val == secondTree->val) {
        if ((firstTree->left == NULL) && (firstTree->right == NULL) && (secondTree->left == NULL) &&
            (secondTree->right == NULL)) {
            return true;
        }
        if ((firstTree->left == NULL) && (secondTree->left == NULL)) {
            return isSameChildTree(firstTree->right, secondTree->right);
        } else if ((firstTree->right == NULL) && (secondTree->right == NULL)) {
            return isSameChildTree(firstTree->left, secondTree->left);
        } else {
            return isSameChildTree(firstTree->left, secondTree->left) &&
                   isSameChildTree(firstTree->right, secondTree->right);
        }
    }
    return false;
}

int myCompare(const void *a, const void *b) {
    const struct ExtTreeNode *first = a;
    const struct ExtTreeNode *second = b;
    return first->count - second->count;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct TreeNode **findDuplicateSubtrees(struct TreeNode *root, int *returnSize) {    
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }
    int count = calculateTreeNodeCount(root);
    struct ExtTreeNode *queue = NULL;
    queue = malloc(sizeof(struct ExtTreeNode) * count);
    if (queue == NULL) {
        return NULL;
    }
    
    int index = 0;
    inQueue(queue, root, &index);
    qsort(queue, count, sizeof(struct ExtTreeNode), myCompare);

    int start = 0;
    for (int i = 0; i < count; i++) {
        if (queue[i].count != queue[start].count) {
            start = i;
        }
        for (int j = start; j < i; j++) {
            if (isSameChildTree(queue[i].node, queue[j].node)) {
                queue[j].flag = 1;
                break;
            }
        }
    }
    int number = 0;
    struct TreeNode **answer = NULL;
    answer = malloc(sizeof(struct TreeNode *) * count);
    for (int i = 0; i < count; i++) {
        if (queue[i].flag == 1) {
            answer[number] = queue[i].node;
            number++;
        }
    }
    free(queue);
    *returnSize = number;
    return answer;
}

// @lc code=end
