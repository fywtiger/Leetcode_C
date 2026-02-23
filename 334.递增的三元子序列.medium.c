/*
 * @lc app=leetcode.cn id=334 lang=c
 *
 * [334] 递增的三元子序列
 *
 * https://leetcode-cn.com/problems/increasing-triplet-subsequence/description/
 *
 * algorithms
 * Medium (40.60%)
 * Likes:    239
 * Dislikes: 0
 * Total Accepted:    35.1K
 * Total Submissions: 86.4K
 * Testcase Example:  '[1,2,3,4,5]'
 *
 * 给你一个整数数组 nums ，判断这个数组中是否存在长度为 3 的递增子序列。
 *
 * 如果存在这样的三元组下标 (i, j, k) 且满足 i < j < k ，使得 nums[i] < nums[j] < nums[k] ，返回 true ；否则，返回 false 。
 *
 *
 *
 * 示例 1：
 *
 * 输入：nums = [1,2,3,4,5]
 * 输出：true
 * 解释：任何 i < j < k 的三元组都满足题意
 *
 *
 * 示例 2：
 *
 * 输入：nums = [5,4,3,2,1]
 * 输出：false
 * 解释：不存在满足题意的三元组
 *
 *
 * 示例 3：
 *
 * 输入：nums = [2,1,5,0,4,6]
 * 输出：true
 * 解释：其中一个满足题意的三元组是 (1, 4, 5)，因为 nums[1] == 1 < nums[4] == 4 < nums[5] == 6
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= nums.length <= 5 * 10^5
 * -231 <= nums[i] <= 231 - 1
 *
 *
 * 进阶：你能实现时间复杂度为 O(n) ，空间复杂度为 O(1) 的解决方案吗？
 *
 */
#include "Mylib.h"
// @lc code=start

/*
 * 算法思路：贪心算法
 * 维护两个变量 first（最小值）和 second（次小值）
 * 遍历数组时动态更新这两个值，若找到大于second的元素，则存在满足条件的三元组
 *
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */
bool increasingTriplet(int *nums, int numsSize) {
    if (numsSize < 3) {
        return false;
    }

    /* first 表示当前遍历到的最小值 */
    int first = INT_MAX;
    /* second 表示当前遍历到的次小值（必定比 first 大） */
    int second = INT_MAX;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] <= first) {
            /* 找到更小的值，更新 first */
            first = nums[i];
        } else if (nums[i] <= second) {
            /* 找到比 first 大但比 second 小的值，更新 second */
            second = nums[i];
        } else {
            /* 找到比 second 大的值，说明存在 first < second < nums[i] */
            return true;
        }
    }

    return false;
}

// @lc code=end
