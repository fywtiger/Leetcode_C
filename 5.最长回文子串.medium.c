/*
 * @lc app=leetcode.cn id=5 lang=c
 *
 * [5] 最长回文子串
 *
 * https://leetcode-cn.com/problems/longest-palindromic-substring/description/
 *
 * algorithms
 * Medium (30.48%)
 * Likes:    2306
 * Dislikes: 0
 * Total Accepted:    291.6K
 * Total Submissions: 949.7K
 * Testcase Example:  '"babad"'
 *
 * 给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。
 *
 * 示例 1：
 *
 * 输入: "babad"
 * 输出: "bab"
 * 注意: "aba" 也是一个有效答案。
 *
 *
 * 示例 2：
 *
 * 输入: "cbbd"
 * 输出: "bb"
 *
 *
 */
#include "Mylib.h"
// @lc code=start
typedef struct {
    int len;
    int startSite;
} PALINDROMESITE;
void GetPalindrome(char *s, int len, int lSite, int rSite, PALINDROMESITE *ret) {
    bool flag = false;
    while (lSite >= 0 && rSite <= len - 1 && s[lSite] == s[rSite]) {
        lSite--;
        rSite++;
        flag = true;
    }
    if (flag) {
        ret->startSite = ret->len < (rSite - lSite - 1) ? lSite + 1 : ret->startSite;
        ret->len = ret->len < (rSite - lSite - 1) ? rSite - lSite - 1 : ret->len;
    }
    return;
}
char *longestPalindrome(char *s) {
    int len = strlen(s);
    PALINDROMESITE ret;
    ret.len = 0;
    ret.startSite = 0;
    for (int i = 0; i < len; i++) {
        GetPalindrome(s, len, i, i, &ret);
        GetPalindrome(s, len, i, i + 1, &ret);
    }
    s[ret.startSite + ret.len] = '\0';
    return &s[ret.startSite];
}

// @lc code=end
