/*
 * @lc app=leetcode.cn id=14 lang=c
 *
 * [14] 最长公共前缀
 *
 * https://leetcode-cn.com/problems/longest-common-prefix/description/
 *
 * algorithms
 * Easy (37.25%)
 * Likes:    1030
 * Dislikes: 0
 * Total Accepted:    259.5K
 * Total Submissions: 695K
 * Testcase Example:  '["flower","flow","flight"]'
 *
 * 编写一个函数来查找字符串数组中的最长公共前缀。
 *
 * 如果不存在公共前缀，返回空字符串 ""。
 *
 * 示例 1:
 *
 * 输入: ["flower","flow","flight"]
 * 输出: "fl"
 *
 *
 * 示例 2:
 *
 * 输入: ["dog","racecar","car"]
 * 输出: ""
 * 解释: 输入不存在公共前缀。
 *
 *
 * 说明:
 *
 * 所有输入只包含小写字母 a-z 。
 *
 */
#include "Mylib.h"
// @lc code=start

int GetMinValCommon(int a, int b) {
    return a < b ? a : b;
}
int GetRetStrLen(char **strs, int strsSize) {    
    int len = strlen(strs[0]);
    for (int i = 1; i < strsSize; i++) {
        len = GetMinValCommon(len, strlen(strs[i]));
    }
    return len;
}
bool IsCommonPre(char **strs, int strsSize, int site) {
    for (int j = 1; j < strsSize; j++) {
        if (strs[j][site] != strs[j - 1][site]) {
            return false;
        }
    }
    return true;
}
char *MakeCommonPreRetStr(char **strs, int strsSize, int rLen)
{
    char *rStr = calloc(rLen + 1, sizeof(char));
    int i;
    for (i = 0; i < rLen; i++) {
        if (!IsCommonPre(strs, strsSize, i)) {
            break;
        }
    }
    memcpy(rStr, strs[0], sizeof(char) * i);
    return rStr;
}
char *longestCommonPrefix(char **strs, int strsSize) {
    if (strsSize == 0) {
        return "";
    }
    int rLen = GetRetStrLen(strs, strsSize);
    return MakeCommonPreRetStr(strs,strsSize,rLen);
}

// @lc code=end
