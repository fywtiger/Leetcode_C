/*
 * @lc app=leetcode.cn id=112 lang=c
 *
 * [112] 路径总和
 *
 * https://leetcode-cn.com/problems/path-sum/description/
 *
 * algorithms
 * Easy (49.66%)
 * Likes:    323
 * Dislikes: 0
 * Total Accepted:    84.9K
 * Total Submissions: 170.2K
 * Testcase Example:  '[5,4,8,11,null,13,4,7,2,null,null,null,1]\n22'
 *
 * 给定一个二叉树和一个目标和，判断该树中是否存在根节点到叶子节点的路径，这条路径上所有节点值相加等于目标和。
 *
 * 说明: 叶子节点是指没有子节点的节点。
 *
 * 示例: 
 * 给定如下二叉树，以及目标和 sum = 22，
 *
 * ⁠             5
 * ⁠            / \
 * ⁠           4   8
 * ⁠          /   / \
 * ⁠         11  13  4
 * ⁠        /  \      \
 * ⁠       7    2      1
 *
 *
 * 返回 true, 因为存在目标和为 22 的根节点到叶子节点的路径 5->4->11->2。
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
typedef struct TreeNode TNODE;
bool TreeSumIsEq(TNODE *node, int sum) {
    if (node == NULL) {
        return sum == 0;
    }
    if (node->right == NULL) {
        return TreeSumIsEq(node->left, sum - node->val);
    }
    if (node->left == NULL) {
        return TreeSumIsEq(node->right, sum - node->val);
    }
    return TreeSumIsEq(node->right, sum - node->val) || TreeSumIsEq(node->left, sum - node->val);
}
bool hasPathSum(struct TreeNode *root, int sum) {
    return root == NULL ? false : TreeSumIsEq(root, sum);
}

// @lc code=end
