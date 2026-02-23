/*
 * @lc app=leetcode.cn id=76 lang=c
 *
 * [76] 最小覆盖子串
 *
 * https://leetcode-cn.com/problems/minimum-window-substring/description/
 *
 * algorithms
 * Hard (35.76%)
 * Likes:    462
 * Dislikes: 0
 * Total Accepted:    38.1K
 * Total Submissions: 106.3K
 * Testcase Example:  '"ADOBECODEBANC"\n"ABC"'
 *
 * 给你一个字符串 S、一个字符串 T，请在字符串 S 里面找出：包含 T 所有字符的最小子串。
 *
 * 示例：
 *
 * 输入: S = "ADOBECODEBANC", T = "ABC"
 * 输出: "BANC"
 *
 * 说明：
 *
 *
 * 如果 S 中不存这样的子串，则返回空字符串 ""。
 * 如果 S 中存在这样的子串，我们保证它是唯一的答案。
 *
 *
 */
#include "Mylib.h"
// @lc code=start

/*
 * 算法思路：滑动窗口法
 * 1. 用哈希表统计目标字符串 T 中每个字符的出现次数
 * 2. 使用双指针维护一个滑动窗口
 * 3. 移动窗口，找到包含所有目标字符的最小子串
 */

struct subStrMap {
    int base;     /* 目标字符串 T 中该字符需要出现的次数 */
    int compare;  /* 当前窗口中该字符已经匹配的次数 */
};
#define INVALIDLEN (-1)
typedef struct subStrMap SUBSTRMAP;
int getSubStrLen(char *s, int startSite, int endSite, SUBSTRMAP *subStrArray, int subStrLen,
                 int *flag);
SUBSTRMAP *initSubStrMap(char *t, int *subStrLen);
#define MAXSLEN 128
/*
 * 寻找包含 T 所有字符的最小子串
 */
char *minWindow(char *s, char *t) {

    int subStrLen;
    SUBSTRMAP *subStrArray = initSubStrMap(t, &subStrLen);
    int tLen = strlen(t);
    int sLen = strlen(s);
    int minSubStrLen = sLen;  /* 当前找到的最小窗口长度 */
    int retLen;
    int startSite = 0;  /* 最小子串的起始位置 */
    char *retNull = "";
    if (sLen < tLen) {
        return retNull;
    }
    bool subStrNullFlag = true;  /* 标记是否找到有效子串 */
    int compareFlag = 0;  /* 用于区分不同匹配阶段 */
    int i = 0;
    while (i < sLen - tLen + 1) {
        if (subStrArray[(int)s[i]].base != 0) {
            /* 找到目标字符，尝试扩展窗口 */
            retLen = getSubStrLen(s, i, sLen, subStrArray, subStrLen, &compareFlag);
            if (retLen == INVALIDLEN) {
                break;
            } else {
                subStrNullFlag = false;
            }
            if (retLen < minSubStrLen) {
                /* 找到更小的窗口，更新最小值 */
                minSubStrLen = retLen;
                startSite = i;
                i++;
            } else {
                /* 跳过一些不可能更优的位置 */
                i = i + 1 + retLen - minSubStrLen;
            }

        } else {
            i++;
        }
    }
    if (subStrNullFlag) {
        return retNull;
    }
    char *retStr = malloc(sizeof(char) * (minSubStrLen + 1));
    strncpy(retStr, &s[startSite], minSubStrLen);
    retStr[minSubStrLen] = '\0';
    return retStr;
}
/*
 * 滑动窗口扩展函数
 * 寻找从 startSite 开始，包含所有目标字符的最小窗口
 * flag: 用于区分匹配和收缩两个阶段
 */
int getSubStrLen(char *s, int startSite, int endSite, SUBSTRMAP *subStrArray, int subStrLen,
                 int *flag) {
    int tSubStrLen = subStrLen;  /* 还需要匹配的不同字符数 */
    int i, site;
    for (i = startSite; i < endSite; i++) {
        site = (int)s[i];
        if (subStrArray[site].base != 0) {
            if (*flag % 2) {
                /* 收缩阶段：减少窗口 */
                if (subStrArray[site].compare < subStrArray[site].base) {
                    subStrArray[site].compare++;
                    tSubStrLen = (subStrArray[site].compare == subStrArray[site].base)
                                     ? (tSubStrLen - 1)
                                     : tSubStrLen;
                }
            } else {
                /* 扩展阶段：增加窗口 */
                if (subStrArray[site].compare > 0) {
                    subStrArray[site].compare--;
                    tSubStrLen = (subStrArray[site].compare == 0) ? (tSubStrLen - 1) : tSubStrLen;
                }
            }

            if (tSubStrLen == 0) {
                /* 所有字符都已匹配 */
                *flag = 1 - *flag;
                return i + 1 - startSite;
            }
        }
    }
    return -1;
}
/*
 * 初始化字符映射表
 * 统计目标字符串 T 中每个字符的出现次数
 */
SUBSTRMAP *initSubStrMap(char *t, int *subStrLen) {
    SUBSTRMAP *subStrArray = malloc(sizeof(SUBSTRMAP) * MAXSLEN);
    memset(subStrArray, 0, sizeof(SUBSTRMAP) * MAXSLEN);
    int mapSize = 0;
    int site;
    for (int i = 0; i < strlen(t); i++) {
        site = (int)t[i];
        if (subStrArray[site].base == 0) {
            subStrArray[site].base = 1;
            subStrArray[site].compare = 1;
            mapSize++;
        } else {
            subStrArray[site].base++;
            subStrArray[site].compare++;
        }
    }
    *subStrLen = mapSize;
    return subStrArray;
}

// @lc code=end
