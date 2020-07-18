/*
 * @lc app=leetcode.cn id=22 lang=c
 *
 * [22] 括号生成
 *
 * https://leetcode-cn.com/problems/generate-parentheses/description/
 *
 * algorithms
 * Medium (75.42%)
 * Likes:    1171
 * Dislikes: 0
 * Total Accepted:    150K
 * Total Submissions: 198K
 * Testcase Example:  '3'
 *
 * 数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
 *
 *
 *
 * 示例：
 *
 * 输入：n = 3
 * 输出：[
 * ⁠      "((()))",
 * ⁠      "(()())",
 * ⁠      "(())()",
 * ⁠      "()(())",
 * ⁠      "()()()"
 * ⁠    ]
 *
 *
 */
#include "Mylib.h"
// @lc code=start

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
void generate(int n, int left, int right, char **ret, char *s, int *returnSize) {
    if (left == n && right == n) {
        ret[*returnSize] = calloc(2 * n + 1, sizeof(char));
        strcpy(ret[*returnSize], s);
        *returnSize = *returnSize + 1;
        return;
    }
    if (left < n) {
        s[left + right] = '(';
        generate(n, left + 1, right, ret, s, returnSize);
    }
    if (right < left) {
        s[left + right] = ')';
        generate(n, left, right + 1, ret, s, returnSize);
    }
    return;
}
char **InitRetGenerateParenthesis(int n) {
    int initSize = 1;
    for (int i = 1; i <= n; i++) {
        initSize *= i;
    }
    char **ret = malloc(sizeof(char *) * initSize);
    return ret;
}

char **generateParenthesis(int n, int *returnSize) {
    char *s = calloc(2 * n + 1, sizeof(char));
    char **ret = InitRetGenerateParenthesis(n);
    *returnSize = 0; //默认是0
    generate(n, 0, 0, ret, s, returnSize);
    free(s);
    return ret;
}

// @lc code=end
