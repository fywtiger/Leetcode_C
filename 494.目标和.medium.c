/*
 * @lc app=leetcode.cn id=494 lang=c
 *
 * [494] 目标和
 *
 * https://leetcode-cn.com/problems/target-sum/description/
 *
 * algorithms
 * Medium (44.31%)
 * Likes:    279
 * Dislikes: 0
 * Total Accepted:    29.4K
 * Total Submissions: 66.4K
 * Testcase Example:  '[1,1,1,1,1]\n3'
 *
 * 给定一个非负整数数组，a1, a2, ..., an,
 * 和一个目标数，S。现在你有两个符号 + 和 -。对于数组中的任意一个整数，你都可以从 + 或 -中选择一个符号添加在前面。
 *
 * 返回可以使最终数组和为目标数 S 的所有添加符号的方法数。
 *
 * 示例 1:
 *
 * 输入: nums: [1, 1, 1, 1, 1], S: 3
 * 输出: 5
 * 解释:
 *
 * -1+1+1+1+1 = 3
 * +1-1+1+1+1 = 3
 * +1+1-1+1+1 = 3
 * +1+1+1-1+1 = 3
 * +1+1+1+1-1 = 3
 *
 * 一共有5种方法让最终目标和为3。
 *
 *
 * 注意:
 *
 *
 * 数组非空，且长度不会超过20。
 * 初始的数组的和不会超过1000。
 * 保证返回的最终结果能被32位整数存下。
 *
 *
 */
#include "Mylib.h"
// @lc code=start

int CalAllWay(int *nums, int site, int A1, int A2, int **dp) {
    if (site < -1 || A1 < 0 || A2 < 0) {
        return 0;
    }
    if (A1 == 0 && A2 == 0 && site == -1) {
        return 1;
    }
    if (dp[A1][A2] != -1) {
        return dp[A1][A2];
    }

    dp[A1][A2] = CalAllWay(nums, site - 1, A1 - nums[site], A2, dp) + CalAllWay(nums, site - 1, A1, A2 - nums[site], dp);
    return dp[A1][A2];
}

int CalNumsSum(int *nums, int numsSize) {
    int sum = 0;
    for (int i = 0; i < numsSize; i++) {
        sum = sum + nums[i];
    }
    return sum;
}

int **InitAllSumDp(int A1, int A2) {
    int **dp = malloc(sizeof(int *) * (A1 + 1));
    for (int i = 0; i <= A1; i++) {
        dp[i] = malloc(sizeof(int) * (A2 + 1));
        memset(dp[i], -1, sizeof(int) * (A2 + 1));
    }
    return dp;
}

void FreeAllSumDp(int **dp, int line) {
    for (int i = 0; i <= line; i++) {
        free(dp[i]);
    }
    free(dp);
    return;
}

int findTargetSumWays(int *nums, int numsSize, int S) {
    int sum = CalNumsSum(nums, numsSize);
    if (sum < S || ((S + sum) % 2 != 0)) {
        return 0;
    }
    int A1 = (S + sum) / 2;
    int A2 = sum - A1;
    int **dp = InitAllSumDp(A1, A2);
    int ret = CalAllWay(nums, numsSize - 1, A1, A2, dp);
    FreeAllSumDp(dp, A1);
    return ret;
}

// @lc code=end
