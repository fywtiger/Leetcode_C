/*
 * @lc app=leetcode.cn id=739 lang=c
 *
 * [739] 每日温度
 *
 * https://leetcode-cn.com/problems/daily-temperatures/description/
 *
 * algorithms
 * Medium (60.62%)
 * Likes:    319
 * Dislikes: 0
 * Total Accepted:    49.6K
 * Total Submissions: 81.3K
 * Testcase Example:  '[73,74,75,71,69,72,76,73]'
 *
 * 根据每日 气温
 * 列表，请重新生成一个列表，对应位置的输出是需要再等待多久温度才会升高超过该日的天数。如果之后都不会升高，请在该位置用 0
 * 来代替。
 *
 * 例如，给定一个列表 temperatures = [73, 74, 75, 71, 69, 72, 76, 73]，你的输出应该是 [1, 1, 4,
 * 2, 1, 1, 0, 0]。
 *
 * 提示：气温 列表长度的范围是 [1, 30000]。每个气温的值的均为华氏度，都是在 [30, 100] 范围内的整数。
 *
 */
#include "Mylib.h"
// @lc code=start

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct tStack {
    int val;
    int site;
};
typedef struct tStack TSTACK;
int UpdataRetArr(int start, TSTACK node, TSTACK *tStack, int sLen, int *retArr) {
    for (int i = start; i >= 0; i--) {
        if (node.val < tStack[i].val) {
            retArr[node.site] = tStack[i].site - node.site;
            break;
        } else {
            sLen--;
        }
    }
    return sLen;
}
int UpdataStack(TSTACK node, TSTACK *tStack, int sLen, int *retArr) {
    if (sLen == 0) {
        tStack[0].val = node.val;
        tStack[0].site = node.site;
        sLen++;
        return sLen;
    }
    for (int i = sLen - 1; i >= 0; i--) {
        if (node.val > tStack[i].val) {
            sLen--;
        } else {
            sLen = UpdataRetArr(i,node,tStack,sLen,retArr);
            break;
        }
    }
    tStack[sLen].val = node.val;
    tStack[sLen].site = node.site;
    sLen++;
    return sLen;
}
void CleanStack(TSTACK *tStack, int sLen, int *retArr) {
    for (int i = sLen - 1; i > 0; i--) {
        retArr[tStack[i].site] = tStack[i - 1].site - tStack[i].site;
    }
    retArr[tStack[0].site] = 0;
    return;
}
int *dailyTemperatures(int *T, int TSize, int *returnSize) {

    TSTACK *tStack = malloc(sizeof(TSTACK) * TSize);
    int *retArr = malloc(sizeof(int) * TSize);
    memset(retArr, 0, sizeof(int) * TSize);
    int sLen = 0;
    TSTACK node;
    for (int i = TSize - 1; i >= 0; i--) {
        node.val = T[i];
        node.site = i;
        sLen = UpdataStack(node, tStack, sLen, retArr);
    }
    CleanStack(tStack, sLen, retArr);
    free(tStack);
    *returnSize = TSize;
    return retArr;
}

// @lc code=end
