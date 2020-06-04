/*
 * @lc app=leetcode.cn id=546 lang=c
 *
 * [546] 移除盒子
 *
 * https://leetcode-cn.com/problems/remove-boxes/description/
 *
 * algorithms
 * Hard (49.54%)
 * Likes:    96
 * Dislikes: 0
 * Total Accepted:    2.3K
 * Total Submissions: 4.7K
 * Testcase Example:  '[1,3,2,2,2,3,4,3,1]\r'
 *
 * 给出一些不同颜色的盒子，盒子的颜色由数字表示，即不同的数字表示不同的颜色。
 * 你将经过若干轮操作去去掉盒子，直到所有的盒子都去掉为止。每一轮你可以移除具有相同颜色的连续 k
 * 个盒子（k >= 1），这样一轮之后你将得到 k*k 个积分。
 * 当你将所有盒子都去掉之后，求你能获得的最大积分和。
 *
 * 示例 1：
 * 输入:
 *
 *
 * [1, 3, 2, 2, 2, 3, 4, 3, 1]
 *
 *
 * 输出:
 *
 *
 * 23
 *
 *
 * 解释:
 *
 *
 * [1, 3, 2, 2, 2, 3, 4, 3, 1]
 * ----> [1, 3, 3, 4, 3, 1] (3*3=9 分)
 * ----> [1, 3, 3, 3, 1] (1*1=1 分)
 * ----> [1, 1] (3*3=9 分)
 * ----> [] (2*2=4 分)
 *
 *
 *
 *
 * 提示：盒子的总数 n 不会超过 100。
 *
 */
#include "Mylib.h"
// @lc code=start
#define MAVBOXv(a, b) ((a) > (b)) ? (a) : (b)
int GetMaxVal(int *boxes, int i, int j, int k, int ***dp) {
    if (i > j) {
        return 0;
    }
    if (dp[i][j][k] > 0) {
        return dp[i][j][k];
    }
    int ans = (k + 1) * (k + 1) + GetMaxVal(boxes, i + 1, j, 0, dp);
    for (int m = i + 1; m <= j; m++) {
        if (boxes[m] == boxes[i]) {
            ans =
                MAVBOXv(ans, GetMaxVal(boxes, i + 1, m - 1, 0, dp) + GetMaxVal(boxes, m, j, k + 1, dp));
        }
    }
    dp[i][j][k] = ans;
    return ans;
}
int ***InitDpArray(int *boxes, int boxesSize) {
    int ***dp = malloc(sizeof(int **) * boxesSize);
    for (int i = 0; i < boxesSize; i++) {
        dp[i] = malloc(sizeof(int *) * boxesSize);
        for (int j = 0; j < boxesSize; j++) {
            dp[i][j] = malloc(sizeof(int) * boxesSize);
            for (int k = 0; k < boxesSize; k++) {
                dp[i][j][k] = 0;
            }
        }
    }
    return dp;
}
void FreeDpArray(int ***dp, int boxesSize) {
    for (int i = 0; i < boxesSize; i++) {
        for (int j = 0; j < boxesSize; j++) {
            free(dp[i][j]);
        }
        free(dp[i]);
    }
    free(dp);
    return;
}
int removeBoxes(int *boxes, int boxesSize) {
    int ***dp = InitDpArray(boxes, boxesSize);
    int ret = GetMaxVal(boxes, 0, boxesSize - 1, 0, dp);
    FreeDpArray(dp,boxesSize);
    return ret;
}

// @lc code=end
