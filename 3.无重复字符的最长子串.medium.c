/*
 * @lc app=leetcode.cn id=3 lang=c
 *
 * [3] 无重复字符的最长子串
 *
 * https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/description/
 *
 * algorithms
 * Medium (34.53%)
 * Likes:    3743
 * Dislikes: 0
 * Total Accepted:    510.1K
 * Total Submissions: 1.5M
 * Testcase Example:  '"abcabcbb"'
 *
 * 给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。
 *
 * 示例 1:
 *
 * 输入: "abcabcbb"
 * 输出: 3
 * 解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
 *
 *
 * 示例 2:
 *
 * 输入: "bbbbb"
 * 输出: 1
 * 解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
 *
 *
 * 示例 3:
 *
 * 输入: "pwwkew"
 * 输出: 3
 * 解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
 * 请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
 *
 *
 */
#include "Mylib.h"
// @lc code=start
#define MASKSIZE 128
void ChangeMask(int *mask, char *s, int start, int end) {
    for (int i = start; i <= end; i++) {
        mask[(int)s[i]] = -1;
    }
}
int *InitStrMask() {
    int *mask = malloc(sizeof(int) * MASKSIZE);
    memset(mask, -1, sizeof(int) * MASKSIZE);
    return mask;
}
int CalMaxLenSubString(int *mask, char *s) {
    int len = strlen(s);
    int maxLen = 0, subLen = 0, start = 0;
    int i, j, tmp;
    for (i = 0; i < len; i = j + 1) {
        for (j = i; j < len; j++) {
            if (mask[(int)s[j]] == -1) {
                mask[(int)s[j]] = j;
                subLen++;
            } else {
                maxLen = maxLen > subLen ? maxLen : subLen;
                subLen += start - mask[(int)s[j]];
                tmp = mask[(int)s[j]];
                ChangeMask(mask, s, start, mask[(int)s[j]]);
                start = tmp + 1;
                mask[(int)s[j]] = j;
                break;
            }
        }
    }
    return maxLen > subLen ? maxLen : subLen;
}
int lengthOfLongestSubstring(char *s) {
    int *mask = InitStrMask();
    int maxLen = CalMaxLenSubString(mask, s);
    free(mask);
    return maxLen;
}
// @lc code=end
