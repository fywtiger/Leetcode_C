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

struct subStrMap {
    int base;
    int compare;
};
#define INVALIDLEN (-1)
typedef struct subStrMap SUBSTRMAP;
int getSubStrLen(char *s, int startSite, int endSite, SUBSTRMAP *subStrArray, int subStrLen,
                 int *flag);
SUBSTRMAP *initSubStrMap(char *t, int *subStrLen);
#define MAXSLEN 128
char *minWindow(char *s, char *t) {

    int subStrLen;
    SUBSTRMAP *subStrArray = initSubStrMap(t, &subStrLen);
    int tLen = strlen(t);
    int sLen = strlen(s);
    int minSubStrLen = sLen;
    int retLen;
    int startSite = 0;
    char *retNull = "";
    if (sLen < tLen) {
        return retNull;
    }
    bool subStrNullFlag = true;
    int compareFlag = 0;
    int i = 0;
    while (i < sLen - tLen + 1) {
        if (subStrArray[(int)s[i]].base != 0) {
            retLen = getSubStrLen(s, i, sLen, subStrArray, subStrLen, &compareFlag);
            if (retLen == INVALIDLEN) {
                break;
            } else {
                subStrNullFlag = false;
            }
            if (retLen < minSubStrLen) {
                minSubStrLen = retLen;
                startSite = i;
                i++;
            } else {
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
int getSubStrLen(char *s, int startSite, int endSite, SUBSTRMAP *subStrArray, int subStrLen,
                 int *flag) {
    int tSubStrLen = subStrLen;
    int i, site;
    for (i = startSite; i < endSite; i++) {
        site = (int)s[i];
        if (subStrArray[site].base != 0) {
            if (*flag % 2) {
                if (subStrArray[site].compare < subStrArray[site].base) {
                    subStrArray[site].compare++;
                    tSubStrLen = (subStrArray[site].compare == subStrArray[site].base)
                                     ? (tSubStrLen - 1)
                                     : tSubStrLen;
                }
            } else {
                if (subStrArray[site].compare > 0) {
                    subStrArray[site].compare--;
                    tSubStrLen = (subStrArray[site].compare == 0) ? (tSubStrLen - 1) : tSubStrLen;
                }
            }

            if (tSubStrLen == 0) {
                *flag = 1 - *flag;
                return i + 1 - startSite;
            }
        }
    }
    return -1;
}
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
