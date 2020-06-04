/*
 * @lc app=leetcode.cn id=41 lang=c
 *
 * [41] 缺失的第一个正数
 *
 * https://leetcode-cn.com/problems/first-missing-positive/description/
 *
 * algorithms
 * Hard (38.15%)
 * Likes:    489
 * Dislikes: 0
 * Total Accepted:    48.7K
 * Total Submissions: 127.5K
 * Testcase Example:  '[1,2,0]'
 *
 * 给你一个未排序的整数数组，请你找出其中没有出现的最小的正整数。
 *
 *
 *
 * 示例 1:
 *
 * 输入: [1,2,0]
 * 输出: 3
 *
 *
 * 示例 2:
 *
 * 输入: [3,4,-1,1]
 * 输出: 2
 *
 *
 * 示例 3:
 *
 * 输入: [7,8,9,11,12]
 * 输出: 1
 *
 *
 *
 *
 * 提示：
 *
 * 你的算法的时间复杂度应为O(n)，并且只能使用常数级别的额外空间。
 *
 */
#include "Mylib.h"
// @lc code=start

int ComPareInt(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}
int firstMissingPositive(int *nums, int numsSize) {
    int mixNumSite = -1;
    int i = 0;
    if (0 == numsSize || NULL == nums) {
        return 1;
    }
    qsort(nums, numsSize, sizeof(int), ComPareInt);
    if (nums[0] < 1) {
        return 1;
    } else if (nums[numsSize - 1] > 1) {
        return 1;
    } else {
        for (i = numsSize - 1; i > 0; i--) {
            if (nums[i - 1] - nums[i] > 1 && nums[i - 1] > 1) {
                mixNumSite = i;
                break;
            }
        }
    }
    if (-1 == mixNumSite) {
        return (nums[0] + 1);
    } else if (nums[mixNumSite] <= 0) {
        return 1;
    } else {
        return (nums[mixNumSite] + 1);
    }
}

// @lc code=end
