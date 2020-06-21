/*
 * @lc app=leetcode.cn id=16 lang=c
 *
 * [16] 最接近的三数之和
 *
 * https://leetcode-cn.com/problems/3sum-closest/description/
 *
 * algorithms
 * Medium (44.02%)
 * Likes:    450
 * Dislikes: 0
 * Total Accepted:    109.6K
 * Total Submissions: 247.3K
 * Testcase Example:  '[-1,2,1,-4]\n1'
 *
 * 给定一个包括 n 个整数的数组 nums 和 一个目标值 target。找出 nums 中的三个整数，使得它们的和与 target
 * 最接近。返回这三个数的和。假定每组输入只存在唯一答案。
 *
 *
 *
 * 示例：
 *
 * 输入：nums = [-1,2,1,-4], target = 1
 * 输出：2
 * 解释：与 target 最接近的和是 2 (-1 + 2 + 1 = 2) 。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 3 <= nums.length <= 10^3
 * -10^3 <= nums[i] <= 10^3
 * -10^4 <= target <= 10^4
 *
 *
 */
#include "Mylib.h"
// @lc code=start
#define MAXRETVAL 3000
int CompaerIntThreeSumClosest(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}
int FindNextMaxSiteClosest(int start, int end, int *nums) {
    for (int i = end - 1; i > start; i--) {
        if (nums[i] != nums[end]) {
            return i;
        }
    }
    return -1;
}
int FindNextMinSiteClosest(int start, int end, int *nums) {
    for (int i = start + 1; i < end; i++) {
        if (nums[i] != nums[start]) {
            return i;
        }
    }
    return end + 1;
}
int GetMinValClosest(int a, int b) {
    return abs(a) < abs(b) ? a : b;
}
void CalthreeSumRetNumsClosest(int *nums, int start, int end, int sum, int *ret) {
    if (start >= end || *ret == 0) {
        return;
    }
    int target = nums[start] + nums[end] + sum;
    if (target == 0) {
        *ret = 0;
        return;
    }
    if (target > 0) {
        end = FindNextMaxSiteClosest(start, end, nums);
        *ret = GetMinValClosest(*ret, target);
        CalthreeSumRetNumsClosest(nums, start, end, sum, ret);
        return;
    }
    if (target < 0) {
        start = FindNextMinSiteClosest(start, end, nums);
        *ret = GetMinValClosest(*ret, target);
        CalthreeSumRetNumsClosest(nums, start, end, sum, ret);
        return;
    }
    return;
}
int threeSumClosest(int *nums, int numsSize, int target) {
    qsort(nums, numsSize, sizeof(int), CompaerIntThreeSumClosest);
    int val = nums[0] - 1;
    int ret = MAXRETVAL;
    for (int i = 0; i < numsSize; i++) {
        if (val < nums[i]) {
            val = nums[i];
            CalthreeSumRetNumsClosest(nums, i + 1, numsSize - 1, val - target, &ret);
        }
    }
    return target + ret;
}
// @lc code=end
