/*
 * @lc app=leetcode.cn id=10 lang=c
 *
 * [10] 正则表达式匹配
 *
 * https://leetcode-cn.com/problems/regular-expression-matching/description/
 *
 * algorithms
 * Hard (27.53%)
 * Likes:    1145
 * Dislikes: 0
 * Total Accepted:    71.6K
 * Total Submissions: 260.1K
 * Testcase Example:  '"aa"\n"a"'
 *
 * 给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。
 *
 * '.' 匹配任意单个字符
 * '*' 匹配零个或多个前面的那一个元素
 *
 *
 * 所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。
 *
 * 说明:
 *
 *
 * s 可能为空，且只包含从 a-z 的小写字母。
 * p 可能为空，且只包含从 a-z 的小写字母，以及字符 . 和 *。
 *
 *
 * 示例 1:
 *
 * 输入:
 * s = "aa"
 * p = "a"
 * 输出: false
 * 解释: "a" 无法匹配 "aa" 整个字符串。
 *
 *
 * 示例 2:
 *
 * 输入:
 * s = "aa"
 * p = "a*"
 * 输出: true
 * 解释: 因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串
 * "aa" 可被视为 'a' 重复了一次。
 *
 *
 * 示例 3:
 *
 * 输入:
 * s = "ab"
 * p = ".*"
 * 输出: true
 * 解释: ".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。
 *
 *
 * 示例 4:
 *
 * 输入:
 * s = "aab"
 * p = "c*a*b"
 * 输出: true
 * 解释: 因为 '*' 表示零个或多个，这里 'c' 为 0 个, 'a' 被重复一次。因此可以匹配字符串 "aab"。
 *
 *
 * 示例 5:
 *
 * 输入:
 * s = "mississippi"
 * p = "mis*is*p*."
 * 输出: false
 *
 */
#include "Mylib.h"
// @lc code=start

bool DpMatchStr(char *s, int sLen, int sSite, char *p, int pLen, int pSite, int **memo);
int **InitMemo(int size, int colSize);
bool isMatch(char *s, char *p) {
    int sLen = strlen(s);
    int pLen = strlen(p);
    int **memo = InitMemo(sLen + 1, pLen + 1);
    bool ret = DpMatchStr(s, sLen, 0, p, pLen, 0, memo);
    return ret;
}
int **InitMemo(int size, int colSize) {
    int **memo = malloc(sizeof(int *) * size);
    for (int i = 0; i < size; i++) {
        memo[i] = malloc(sizeof(int) * colSize);
        memset(memo[i], -1, sizeof(int) * colSize);
    }
    return memo;
}
bool DpMatchStr(char *s, int sLen, int sSite, char *p, int pLen, int pSite, int **memo) {
    if (pSite == pLen) {
        return sLen == sSite;
    }
    if (sSite > sLen || pSite > pLen) {
        return false;
    }
    if (memo[sSite][pSite] != -1)
        return memo[sSite][pSite];
    bool ret = true;
    if (p[pSite + 1] == '*') {
        if (s[sSite] == p[pSite]) {
            if (s[sSite] != s[sSite + 1]) {
                ret = ret && (DpMatchStr(s, sLen, sSite, p, pLen, pSite + 2, memo) ||
                              DpMatchStr(s, sLen, sSite + 1, p, pLen, pSite + 2, memo));
            } else {
                ret = ret && (DpMatchStr(s, sLen, sSite + 2, p, pLen, pSite + 2, memo) ||
                              DpMatchStr(s, sLen, sSite, p, pLen, pSite + 2, memo) ||
                              DpMatchStr(s, sLen, sSite + 1, p, pLen, pSite + 2, memo));
            }
        } else if (p[pSite] == '.') {
            ret = ret && (DpMatchStr(s, sLen, sSite + 2, p, pLen, pSite, memo) ||
                          DpMatchStr(s, sLen, sSite, p, pLen, pSite + 2, memo) ||
                          DpMatchStr(s, sLen, sSite + 1, p, pLen, pSite + 2, memo));
        } else {
            ret = ret && DpMatchStr(s, sLen, sSite, p, pLen, pSite + 2, memo);
        }

    } else if (s[sSite] == p[pSite] || p[pSite] == '.') {
        ret = ret && DpMatchStr(s, sLen, sSite + 1, p, pLen, pSite + 1, memo);
    } else {
        ret = false;
    }

    memo[sSite][pSite] = ret;
    return ret;
}

// @lc code=end
