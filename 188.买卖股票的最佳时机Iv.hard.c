/*
 * @lc app=leetcode.cn id=188 lang=c
 *
 * [188] 买卖股票的最佳时机 IV
 *
 * https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iv/description/
 *
 * algorithms
 * Hard (29.55%)
 * Likes:    220
 * Dislikes: 0
 * Total Accepted:    19.7K
 * Total Submissions: 66.4K
 * Testcase Example:  '2\n[2,4,1]'
 *
 * 给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。
 *
 * 设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。
 *
 * 注意: 你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
 *
 * 示例 1:
 *
 * 输入: [2,4,1], k = 2
 * 输出: 2
 * 解释: 在第 1 天 (股票价格 = 2) 的时候买入，在第 2 天 (股票价格 = 4) 的时候卖出，这笔交易所能获得利润 = 4-2 = 2 。
 *
 *
 * 示例 2:
 *
 * 输入: [3,2,6,5,0,3], k = 2
 * 输出: 7
 * 解释: 在第 2 天 (股票价格 = 2) 的时候买入，在第 3 天 (股票价格 = 6) 的时候卖出, 这笔交易所能获得利润 = 6-2 = 4
 * 。
 * 随后，在第 5 天 (股票价格 = 0) 的时候买入，在第 6 天 (股票价格 = 3) 的时候卖出, 这笔交易所能获得利润 = 3-0 = 3 。
 *
 *
 */
#include "Mylib.h"
// @lc code=start

#define ERRORVAL -2147400000
int GetMaxProfit(int a, int b) {
    return a > b ? a : b;
}
int CalMaxProfit(int *prices, int day, int k, int status, int ***dp) {
    //交易没有开始的第0天，当前手里没有股票，收益为0,如果有股票则是异常状态。
    //首先base
    if (day == 0) {
        return (status == 0) ? 0 : ERRORVAL;
    }
    //没有进行任何的交易，没有持有股票，收益为零。如果有股票则为异常状态。
    if (k == 0) {
        return status == 0 ? 0 : ERRORVAL;
    }
    // dp不是初始值 直接返回
    if (dp[day][k][status] != ERRORVAL) {
        return dp[day][k][status];
    }
    //状态迁移方程
    int ret = ERRORVAL;
    for (int i = k; i <= k; i++) {
        if (status) {
            ret = GetMaxProfit(CalMaxProfit(prices, day - 1, k, 1, dp),
                               CalMaxProfit(prices, day - 1, k - 1, 0, dp) - prices[day - 1]);
        } else {
            ret = GetMaxProfit(CalMaxProfit(prices, day - 1, k, 0, dp),
                               CalMaxProfit(prices, day - 1, k, 1, dp) + prices[day - 1]);
        }
    }
    //给DP复制
    dp[day][k][status] = ret;
    return ret;
}

/*DP[d][k][s]:表示在d天完成了k笔交易后手里的获利值。
d表示第几天，k表示进行了多少笔交易，s表示当前手中股票的状态，0表示没有股票，1表示有股票，这里状态s不用区分出
是持有，买入还是卖出，通过k的交易笔数+当前状态就可以区分出来*/
int ***InitProfitDp(int k, int day) {
    int ***dp = malloc(sizeof(int **) * (day + 1));
    for (int i = 0; i <= day; i++) {
        dp[i] = malloc(sizeof(int *) * (k + 1));
        for (int j = 0; j <= k; j++) {
            dp[i][j] = malloc(sizeof(int) * 2);
            for (int s = 0; s < 2; s++) {
                dp[i][j][s] = ERRORVAL;
            }
        }
    }
    return dp;
}
int CalMaxProfitPlus(int *prices, int pricesSize) {
    int ret = 0;
    for (int i = 0; i < pricesSize - 1; i++) {
        if (prices[i + 1] > prices[i]) {
            ret = ret + prices[i + 1] - prices[i];
        }
    }
    return ret;
}
void FreeProfitMemory(int ***dp, int k, int day) {
    for (int i = 0; i <= day; i++) {
        for (int j = 0; j <= k; j++) {
            free(dp[i][j]);
        }
        free(dp[i]);
    }
    free(dp);
    return;
}
int maxProfit(int k, int *prices, int pricesSize) {
    if (pricesSize > 2 * k) {
        int ***dp = InitProfitDp(k, pricesSize);
        int ret = CalMaxProfit(prices, pricesSize, k, 0, dp);
        FreeProfitMemory(dp,k,pricesSize);
        return ret > 0 ? ret : 0;
    } else {
        return CalMaxProfitPlus(prices, pricesSize);
    }
}

// @lc code=end
