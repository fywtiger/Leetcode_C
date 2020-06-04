/*
 * @lc app=leetcode.cn id=316 lang=c
 *
 * [316] 去除重复字母
 *
 * https://leetcode-cn.com/problems/remove-duplicate-letters/description/
 *
 * algorithms
 * Hard (38.18%)
 * Likes:    143
 * Dislikes: 0
 * Total Accepted:    11.1K
 * Total Submissions: 29K
 * Testcase Example:  '"bcabc"'
 *
 *
 * 给你一个仅包含小写字母的字符串，请你去除字符串中重复的字母，使得每个字母只出现一次。需保证返回结果的字典序最小（要求不能打乱其他字符的相对位置）。
 *
 *
 *
 * 示例 1:
 *
 * 输入: "bcabc"
 * 输出: "abc"
 *
 *
 * 示例 2:
 *
 * 输入: "cbacdcbc"
 * 输出: "acdb"
 *
 *
 *
 * 注意：该题与 1081
 * https://leetcode-cn.com/problems/smallest-subsequence-of-distinct-characters
 * 相同
 *
 */
#include "Mylib.h"
// @lc code=start

#define NMAX 26
int *InitSiteArr(char *s, int len) {
    int *site = malloc(sizeof(int) * NMAX);
    memset(site, 0, sizeof(int) * NMAX);
    for (int i = 0; i < len; i++) {
        site[s[i] - 'a'] = i;
    }
    return site;
}
char *MakeRetStr(char *s, int len, int *site) {
    char *stack = malloc(sizeof(char) * (len + 1));
    int stackVisit[NMAX] = {0};
    int sLen = 0;
    stack[0] = s[0];
    stackVisit[s[0] - 'a'] = 1;
    sLen = 1;
    for (int i = 1; i < len; i++) {
        if (stackVisit[s[i] - 'a'] == 0) {
            stackVisit[s[i] - 'a'] = 1;
            while (sLen > 0) {
                if (s[i] < stack[sLen - 1]) {
                    if (site[stack[sLen - 1] - 'a'] > i) {
                        stackVisit[stack[sLen - 1] - 'a'] = 0;
                        sLen--;
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            }
            stack[sLen] = s[i];
            sLen++;
        }
    }
    stack[sLen] = '\0';
    return stack;
}
char *removeDuplicateLetters(char *s) {
    int len = strlen(s);
    if (len == 0) {
        return "";
    }
    int *site = InitSiteArr(s, len);
    char *stack = MakeRetStr(s, len, site);
    free(site);
    return stack;
}

// @lc code=end
