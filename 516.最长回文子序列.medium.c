/*
 * @lc app=leetcode.cn id=516 lang=c
 *
 * [516] 最长回文子序列
 *
 * https://leetcode-cn.com/problems/longest-palindromic-subsequence/description/
 *
 * algorithms
 * Medium (53.52%)
 * Likes:    196
 * Dislikes: 0
 * Total Accepted:    18.5K
 * Total Submissions: 34.2K
 * Testcase Example:  '"bbbab"'
 *
 * 给定一个字符串s，找到其中最长的回文子序列。可以假设s的最大长度为1000。
 *
 * 示例 1:
 * 输入:
 *
 *
 * "bbbab"
 *
 *
 * 输出:
 *
 *
 * 4
 *
 *
 * 一个可能的最长回文子序列为 "bbbb"。
 *
 * 示例 2:
 * 输入:
 *
 *
 * "cbbd"
 *
 *
 * 输出:
 *
 *
 * 2
 *
 *
 * 一个可能的最长回文子序列为 "bb"。
 *
 */
#include "Mylib.h"
// @lc code=start
#define MAXSQVAL(a, b) ((a) > (b) ? (a) : (b))
int DfsDp(char *s, int **dp, int start, int end) {
    if (start > end) {
        return 0;
    }
    if (dp[start][end] != 0) {
        return dp[start][end];
    }
    if (start == end) {
        return 1;
    }
    int ret;
    if (s[start] == s[end]) {
        ret = DfsDp(s, dp, start + 1, end - 1) + 2;
    } else {
        ret = MAXSQVAL(DfsDp(s, dp, start, end - 1), DfsDp(s, dp, start + 1, end));
    }
    dp[start][end] = ret;
    return ret;
}
int **InitDp(int size) {
    int **dp = malloc(sizeof(int *) * size);
    for (int i = 0; i < size; i++) {
        dp[i] = malloc(sizeof(int) * size);
        memset(dp[i], 0, sizeof(int) * size);
    }
    return dp;
}
void FreeSQDp(int **dp, int size) {
    for (int i = 0; i < size; i++) {
        free(dp[i]);
    }
    free(dp);
    return;
}
int longestPalindromeSubseq(char *s) {
    int size = strlen(s);
    int **dp = InitDp(size);
    int ret = DfsDp(s, dp, 0, size - 1);
    FreeSQDp(dp,size);
    return ret;
}
// @lc code=end
