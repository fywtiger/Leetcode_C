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

char *GetPalindrome(char *s, int len, int lSite, int rSite) {
    bool flag = false;
    while (lSite >= 0 && rSite <= len - 1 && s[lSite] == s[rSite]) {
        lSite--;
        rSite++;
        flag = true;
    }
    char *str = NULL;
    if (flag) {
        str = calloc(rSite - lSite, sizeof(char));
        memcpy(str, &s[lSite + 1], sizeof(char) * (rSite - lSite - 1));
    } else {
        str = calloc(1, sizeof(char));
    }
    return str;
}
char* GetPalindromeRetStr(char *str, char *pStr) {
    if (strlen(pStr) > strlen(str)) {
        free(str);
        return pStr;
    }
    free(pStr);
    return str;
}
char *longestPalindrome(char *s) {
    int len = strlen(s);
    char *pStr1 = NULL, *pStr2 = NULL, *str = calloc(1,sizeof(char));
    for (int i = 0; i < len; i++) {
        pStr1 = GetPalindrome(s, len, i, i);
        pStr2 = GetPalindrome(s, len, i, i + 1);
        str = GetPalindromeRetStr(str,pStr1);
        str = GetPalindromeRetStr(str,pStr2);
    }
    return str;
}

// @lc code=end
