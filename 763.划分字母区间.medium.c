/*
 * @lc app=leetcode.cn id=763 lang=c
 *
 * [763] 划分字母区间
 *
 * https://leetcode-cn.com/problems/partition-labels/description/
 *
 * algorithms
 * Medium (71.74%)
 * Likes:    145
 * Dislikes: 0
 * Total Accepted:    13.4K
 * Total Submissions: 18.9K
 * Testcase Example:  '"ababcbacadefegdehijhklij"'
 *
 * 字符串 S
 * 由小写字母组成。我们要把这个字符串划分为尽可能多的片段，同一个字母只会出现在其中的一个片段。返回一个表示每个字符串片段的长度的列表。
 *
 *
 *
 * 示例 1：
 *
 * 输入：S = "ababcbacadefegdehijhklij"
 * 输出：[9,7,8]
 * 解释：
 * 划分结果为 "ababcbaca", "defegde", "hijhklij"。
 * 每个字母最多出现在一个片段中。
 * 像 "ababcbacadefegde", "hijhklij" 的划分是错误的，因为划分的片段数较少。
 *
 *
 *
 *
 * 提示：
 *
 *
 * S的长度在[1, 500]之间。
 * S只包含小写字母 'a' 到 'z' 。
 *
 *
 */
#include "Mylib.h"
// @lc code=start

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define LABLEMAPLEN 128
int *InitLabelMap(char *s) {
    int len = strlen(s);
    int *map = malloc(sizeof(int) * LABLEMAPLEN);
    for (int i = 0; i < len; i++) {
        map[(int)s[i]] = i;
    }
    return map;
}
int GetMaxSite(int a, int b) {
    return a > b ? a : b;
}
int *MakeRetArray(int *map, char *s, int *returnSize) {
    int len = strlen(s);
    int *retArray = malloc(sizeof(int) * len);
    int site = 0;
    int rLen = 0;
    int nSite = 0;
    while (site < len) {
        nSite = map[(int)s[site]];
        for (int i = site; i <= nSite; i++) {
            nSite = GetMaxSite(nSite, map[(int)s[i]]);
        }
        retArray[rLen] = nSite - site + 1;
        site = nSite + 1;
        rLen++;
    }
    *returnSize = rLen;
    return retArray;
}
int *partitionLabels(char *S, int *returnSize) {
    int *map = InitLabelMap(S);
    int *retArray = MakeRetArray(map, S, returnSize);
    return retArray;
}
// @lc code=end
