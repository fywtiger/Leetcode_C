/*
 * @lc app=leetcode.cn id=115 lang=c
 *
 * [115] 不同的子序列
 *
 * https://leetcode-cn.com/problems/distinct-subsequences/description/
 *
 * algorithms
 * Hard (47.80%)
 * Likes:    187
 * Dislikes: 0
 * Total Accepted:    13.3K
 * Total Submissions: 27.8K
 * Testcase Example:  '"rabbbit"\n"rabbit"'
 *
 * 给定一个字符串 S 和一个字符串 T，计算在 S 的子序列中 T 出现的个数。
 *
 * 一个字符串的一个子序列是指，通过删除一些（也可以不删除）字符且不干扰剩余字符相对位置所组成的新字符串。（例如，"ACE" 是 "ABCDE"
 * 的一个子序列，而 "AEC" 不是）
 *
 * 题目数据保证答案符合 32 位带符号整数范围。
 *
 *
 *
 * 示例 1：
 *
 * 输入：S = "rabbbit", T = "rabbit"
 * 输出：3
 * 解释：
 *
 * 如下图所示, 有 3 种可以从 S 中得到 "rabbit" 的方案。
 * (上箭头符号 ^ 表示选取的字母)
 *
 * rabbbit
 * ^^^^ ^^
 * rabbbit
 * ^^ ^^^^
 * rabbbit
 * ^^^ ^^^
 *
 *
 * 示例 2：
 *
 * 输入：S = "babgbag", T = "bag"
 * 输出：5
 * 解释：
 *
 * 如下图所示, 有 5 种可以从 S 中得到 "bag" 的方案。
 * (上箭头符号 ^ 表示选取的字母)
 *
 * babgbag
 * ^^ ^
 * babgbag
 * ^^    ^
 * babgbag
 * ^    ^^
 * babgbag
 * ⁠ ^  ^^
 * babgbag
 * ⁠   ^^^
 *
 */
#include "Mylib.h"
// @lc code=start

char *GetNewStr(char *s, char *t) {
    int sLen = strlen(s);
    char *str = calloc(sLen + 1, sizeof(char));
    int mask[255] = {0};
    for (int i = 0; i < strlen(t); i++) {
        mask[(int)t[i]] = 1;
    }
    int len = 0;
    for (int i = 0; i < sLen; i++) {
        if (mask[(int)s[i]]) {
            str[len++] = s[i];
        }
    }
    return str;
}
int GetTimesSubStr(char *str, int sSite, char *t, int tSite, int **dp) {
    if (tSite == -1) {
        return sSite >= -1 ? 1 : 0;
    }
    if (sSite == -1) {
        return 0;
    }
    if (dp[sSite][tSite] != -1) {
        return dp[sSite][tSite];
    }
    int ret = 0;
    if (str[sSite] == t[tSite]) {
        ret = GetTimesSubStr(str, sSite - 1, t, tSite - 1, dp) + GetTimesSubStr(str, sSite - 1, t, tSite, dp);
    } else {
        ret = GetTimesSubStr(str, sSite - 1, t, tSite, dp);
    }
    dp[sSite][tSite] = ret;
    return ret;
}
int **InitMaskSubStr(int line, int col) {
    int **dp = malloc(sizeof(int *) * line);
    for (int i = 0; i < line; i++) {
        dp[i] = malloc(sizeof(int) * col);
        memset(dp[i], -1, sizeof(int) * col);
    }
    return dp;
}
void FreeSubStrTimesMemory(int **dp, int line, char *str) {
    for (int i = 0; i < line; i++) {
        free(dp[i]);
    }
    free(dp);
    free(str);
    return;
}
int numDistinct(char *s, char *t) {
    char *nStr = GetNewStr(s, t);
    int nSlen = strlen(nStr);
    int tLen = strlen(t);
    int **dp = InitMaskSubStr(nSlen, tLen);
    int ret = GetTimesSubStr(nStr, nSlen - 1, t, tLen - 1, dp);
    FreeSubStrTimesMemory(dp, nSlen, nStr);
    return ret;
}

// @lc code=end
