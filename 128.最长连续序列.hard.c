/*
 * @lc app=leetcode.cn id=128 lang=c
 *
 * [128] 最长连续序列
 *
 * https://leetcode-cn.com/problems/longest-consecutive-sequence/description/
 *
 * algorithms
 * Hard (48.62%)
 * Likes:    315
 * Dislikes: 0
 * Total Accepted:    37.2K
 * Total Submissions: 76.5K
 * Testcase Example:  '[100,4,200,1,3,2]'
 *
 * 给定一个未排序的整数数组，找出最长连续序列的长度。
 *
 * 要求算法的时间复杂度为 O(n)。
 *
 * 示例:
 *
 * 输入: [100, 4, 200, 1, 3, 2]
 * 输出: 4
 * 解释: 最长连续序列是 [1, 2, 3, 4]。它的长度为 4。
 *
 */
#include "Mylib.h"
// @lc code=start

int intCompare(const void *a, const void *b) {
    return *(int *)a < *(int *)b ? -1 : 1;
}
#define MAX(a, b) ((a) > (b) ? (a) : (b))
int longestConsecutive(int *nums, int numsSize) {
    if (numsSize == 0) {
        return 0;
    }
    qsort(nums, numsSize, sizeof(int), intCompare);

    int mLen = 1;
    int len = 1;
    for (int i = 0; i < numsSize - 1; i++) {
        if (nums[i + 1] - nums[i] == 1) {
            len++;
        } else if (nums[i + 1] == nums[i]) {
            continue;
        } else {
            mLen = MAX(mLen, len);
            len = 1;
        }
    }
    mLen = MAX(mLen, len);
    return mLen;
}

// @lc code=end
